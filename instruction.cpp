#include "instruction.h"
#include "ast.h"
#include "block.h"
#include "global.h"

#include <array>
#include <typeinfo>

inline std::array<std::string, 8> binary_ops = {
	"BINARY_ADD",
	"BINARY_SUBTRACT",
	"BINARY_MULTIPLY",
	"BINARY_TRUE_DIVIDE",
	"BINARY_FLOOR_DIVIDE",
	"BINARY_MODULO",
	"BINARY_AND",
	"BINARY_OR"
};

inline std::array<std::string, 3> unary_ops = {
	"UNARY_POSITIVE",
	"UNARY_NEGATIVE",
	"UNARY_INVERT"
};

std::shared_ptr<Block::Type> load_store_variable(Block::Block* block, std::string name, std::string operation, std::vector<Instruction>& buffer, bool is_closure = false)
{
	std::string suffix;

	if (is_closure)
		suffix = "_CLOSURE";
	else
		suffix = "_DEREF";

	if (operation != "LOAD" && (is_closure || operation != "STORE"))
		throw std::logic_error("Unknown operation");
	if (auto it = block->var_map.find(name); it != block->var_map.end())
	{
		auto [type, pos] = it->second;

		if (type == Block::VARIABLE_CELL)
		{
			buffer.emplace_back(operation + suffix, pos);
			return block->cellvars[pos]->type;
		}
		else if (type == Block::VARIABLE_FREE)
		{
			buffer.emplace_back(operation + suffix, pos + block->cellvars.size());
			return block->freevars[pos]->type;
		}
		else
		{
			throw std::logic_error("Unknown variable type");
		}
	}
	else // global
	{
		if (is_closure)
			throw std::logic_error("Global cannot load to closure");

		auto type = resolveGlobalSymbol(name);

		if (typeid(*type) == typeid(Block::NullType))
			throw std::logic_error("Unknown global variable " + name);

		buffer.emplace_back(operation + "_GLOBAL", Block::getName(block, name));
		return type;
	}
}

void generateConvert(Block::Block* block, Block::Type* sourceType, Block::Type* targetType, std::vector<Instruction>& buffer)
{
	if (sourceType->name != targetType->name && !dynamic_cast<Block::ObjectType*>(targetType))
	{
		if (dynamic_cast<Block::RealType*>(targetType))
		{
			if (dynamic_cast<Block::IntType*>(sourceType))
			{
				buffer.emplace_back("LOAD_GLOBAL", Block::getName(block, "float"));
				buffer.emplace_back("CALL_FUNCTION", 1);
			}
			else
				throw std::logic_error("Cannot convert type " + sourceType->name + " to " + targetType->name);
		}
		else if (dynamic_cast<Block::IntType*>(targetType))
		{
			if (dynamic_cast<Block::RealType*>(sourceType))
			{
				throw std::logic_error("Disabled implicit convertion from " + sourceType->name + " to " + targetType->name);
			}
			else
				throw std::logic_error("Cannot convert type " + sourceType->name + " to " + targetType->name);
		}
	}
}

void generateProlog(Block::Block* block, std::vector<Instruction>& buffer)
{
	for (auto func : block->funcdecls)
	{
		for (auto freevar : func->block->freevars)
		{
			load_store_variable(block, freevar->name->name, "LOAD", buffer, true);
		}
		buffer.emplace_back("BUILD_TUPLE", func->block->freevars.size());
		buffer.emplace_back("LOAD_CONST", Block::getConst(block, func->block));
		buffer.emplace_back("LOAD_CONST", Block::getConst(block, func->var->name->name));

		buffer.emplace_back("MAKE_FUNCTION", 8);
		load_store_variable(block, func->var->name->name, "STORE", buffer);

		compile(func->block.get());
	}

	for (auto var : block->cellvars)
	{
		if (auto const_variable = std::dynamic_pointer_cast<Block::ConstVariable>(var); const_variable)
		{
			buffer.emplace_back("LOAD_CONST", Block::getConst(block, const_variable->value));
			load_store_variable(block, var->name->name, "STORE", buffer);
		}

		if (auto array_type = std::dynamic_pointer_cast<Block::ArrayType>(var->type); array_type)
		{
			auto now = var->type;
			std::vector<std::pair<int, int>> dims;
			buffer.emplace_back("LOAD_GLOBAL", Block::getName(block, "Array"));

			while (array_type = std::dynamic_pointer_cast<Block::ArrayType>(now), array_type)
			{
				dims.push_back({ array_type->floor, array_type->ceil });
				now = array_type->elementType;
			}

			std::reverse(dims.begin(), dims.end());

			for (auto [start, end] : dims)
			{
				buffer.emplace_back("LOAD_CONST", Block::getConst(block, start));
				buffer.emplace_back("LOAD_CONST", Block::getConst(block, end));
				buffer.emplace_back("BUILD_TUPLE", 2);
			}

			buffer.emplace_back("BUILD_LIST", dims.size());
			buffer.emplace_back("CALL_FUNCTION", 1);
			load_store_variable(block, var->name->name, "STORE", buffer);
		}
	}
}

void generateEpilog(Block::Block* block, std::vector<Instruction>& buffer)
{
	buffer.emplace_back("LOAD_CONST", Block::getConst(block, std::monostate()));
	buffer.emplace_back("RETURN_VALUE");
}

std::shared_ptr<Block::Type> generateInstruction(Block::Block* block, ASTNodeBase* node, std::vector<Instruction>& buffer)
{
	std::shared_ptr<Block::Type> ret = std::make_shared<Block::NullType>();
	if (auto pASTIdentifier = dynamic_cast<ASTIdentifier*>(node); pASTIdentifier)
	{
		ret = load_store_variable(block, pASTIdentifier->name, "LOAD", buffer);
	}
	if (auto pASTConstLiteral = dynamic_cast<ASTConstLiteral*>(node); pASTConstLiteral)
	{
		buffer.emplace_back("LOAD_CONST", Block::getConst(block, pASTConstLiteral->value));
		ret = Block::buildTypeFromAST(pASTConstLiteral);
	}
	if (auto pASTAssignStmt = dynamic_cast<ASTAssignStmt*>(node); pASTAssignStmt) // TODO: type check
	{
		auto rtype = generateInstruction(block, convertToBase(pASTAssignStmt->right), buffer);

		if (auto ppid = std::get_if<std::shared_ptr<ASTIdentifier>>(&pASTAssignStmt->left); ppid)
		{
			auto pASTIdentifier = *ppid;

			if (pASTIdentifier->name == block->block_name) // return
				buffer.emplace_back("RETURN_VALUE");
			else
			{
				auto ltype = load_store_variable(block, pASTIdentifier->name, "STORE", buffer);

				if (!ltype->mut)
					throw std::logic_error("Cannot assign to a const variable");

				if (ltype->name != rtype->name)
				{
					buffer.pop_back();
					generateConvert(block, rtype.get(), ltype.get(), buffer);
					load_store_variable(block, pASTIdentifier->name, "STORE", buffer);
				}
			}
		}
		else if (auto pparrayaccess = std::get_if<std::shared_ptr<ASTArrayAccess>>(&pASTAssignStmt->left); pparrayaccess)
		{
			auto parrayaccess = *pparrayaccess;
			auto arrayType = generateInstruction(block, convertToBase(parrayaccess->array), buffer);
			auto indexType = generateInstruction(block, convertToBase(parrayaccess->index), buffer);
			buffer.emplace_back("STORE_SUBSCR");
		}
		else
		{
			throw std::logic_error("Not implemented yet");
		}
	}
	if (auto pASTForStmt = dynamic_cast<ASTForStmt*>(node); pASTForStmt)
	{
		int stepPos = Block::getConst(block, pASTForStmt->step);

		int startBlock = buffer.size();
		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("SETUP_LOOP", 0);

		buffer.emplace_back("LOAD_GLOBAL", Block::getName(block, "range"));
		auto beginType = generateInstruction(block, convertToBase(pASTForStmt->begin), buffer);
		auto endType = generateInstruction(block, convertToBase(pASTForStmt->end), buffer);
		buffer.emplace_back("LOAD_CONST", stepPos);
		buffer.emplace_back("BINARY_ADD");
		buffer.emplace_back("LOAD_CONST", stepPos);
		buffer.emplace_back("CALL_FUNCTION", 3); // range()

		buffer.emplace_back("GET_ITER");

		int forIterPos = buffer.size();
		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("FOR_ITER", 0);

		// Type check
		if (!dynamic_cast<Block::IntType*>(beginType.get()) || !dynamic_cast<Block::IntType*>(endType.get()))
		{
			throw std::logic_error("For range should be int, but " + beginType->name + " + " + endType->name + " get");
		}

		auto itype = load_store_variable(block, pASTForStmt->varname->name, "STORE", buffer);

		if (!itype->mut)
			throw std::logic_error("Cannot assign to a const variable");

		if (!dynamic_cast<Block::IntType*>(itype.get()))
		{
			buffer.pop_back();
			generateConvert(block, beginType.get() /* int type */, itype.get(), buffer);
			load_store_variable(block, pASTForStmt->varname->name, "STORE", buffer);
		}

		generateInstruction(block, convertToBase(pASTForStmt->stmt), buffer);

		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("JUMP_ABSOLUTE", 0);
		buffer[buffer.size() - 2].param = (2 * forIterPos) >> 8;
		buffer[buffer.size() - 1].param = (2 * forIterPos) & 0xFF;

		buffer[forIterPos].param = (2 * (buffer.size() - forIterPos - 2)) >> 8;
		buffer[forIterPos + 1].param = (2 * (buffer.size() - forIterPos - 2)) & 0xFF;
		buffer.emplace_back("POP_BLOCK");

		buffer[startBlock].param = (2 * (buffer.size() - startBlock - 2)) >> 8;
		buffer[startBlock + 1].param = (2 * (buffer.size() - startBlock - 2)) & 0xFF;
	}
	if (auto pASTWhileStmt = dynamic_cast<ASTWhileStmt*>(node); pASTWhileStmt)
	{
		int startBlock = buffer.size();
		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("SETUP_LOOP", 0);
		int jumpToPos = buffer.size();
		generateInstruction(block, convertToBase(pASTWhileStmt->expr), buffer);
		int popJumpPos = buffer.size();
		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("POP_JUMP_IF_FALSE", 0); // ABSOLUTE

		generateInstruction(block, convertToBase(pASTWhileStmt->stmt), buffer);

		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("JUMP_ABSOLUTE", 0);
		buffer[buffer.size() - 2].param = (2 * jumpToPos) >> 8;
		buffer[buffer.size() - 1].param = (2 * jumpToPos) & 0xFF;

		buffer[popJumpPos].param = (2 * buffer.size()) >> 8;
		buffer[popJumpPos + 1].param = (2 * buffer.size()) & 0xFF;
		buffer.emplace_back("POP_BLOCK");

		buffer[startBlock].param = (2 * (buffer.size() - startBlock - 2)) >> 8;
		buffer[startBlock + 1].param = (2 * (buffer.size() - startBlock - 2)) & 0xFF;
	}
	if (auto pASTRepeatStmt = dynamic_cast<ASTRepeatStmt*>(node); pASTRepeatStmt)
	{
		int startBlock = buffer.size();
		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("SETUP_LOOP", 0);
		int jumpToPos = buffer.size();

		for (auto stmt : pASTRepeatStmt->stmts)
			generateInstruction(block, convertToBase(stmt), buffer);

		generateInstruction(block, convertToBase(pASTRepeatStmt->expr), buffer);

		buffer.emplace_back("EXTENDED_ARG", (2 * jumpToPos) >> 8);
		buffer.emplace_back("POP_JUMP_IF_TRUE", (2 * jumpToPos) & 0xFF); // ABSOLUTE

		buffer.emplace_back("POP_BLOCK");
		buffer[startBlock].param = (2 * (buffer.size() - startBlock - 2)) >> 8;
		buffer[startBlock + 1].param = (2 * (buffer.size() - startBlock - 2)) & 0xFF;
	}
	if (auto pASTCallStmt = dynamic_cast<ASTCallStmt*>(node); pASTCallStmt)
	{
		generateInstruction(block, pASTCallStmt->identifier.get(), buffer);
		buffer.emplace_back("CALL_FUNCTION", 0);
		buffer.emplace_back("POP_TOP");
	}
	if (auto pASTComplStmt = dynamic_cast<ASTComplStmt*>(node); pASTComplStmt)
	{
		for (auto stmt : pASTComplStmt->stmts)
			generateInstruction(block, convertToBase(stmt), buffer);
	}
	if (auto pASTExprStmt = dynamic_cast<ASTExprStmt*>(node); pASTExprStmt)
	{
		bool doDefult = true;
		if (auto ppi = std::get_if<std::shared_ptr<ASTIdentifier>>(&pASTExprStmt->expr); ppi && (*ppi)->name == block->block_name)
		{
			buffer.emplace_back("LOAD_CONST", Block::getConst(block, std::monostate()));
			buffer.emplace_back("RETURN_VALUE");
			doDefult = false;
		}
		if (auto ppfunc = std::get_if<std::shared_ptr<ASTFuncCall>>(&pASTExprStmt->expr); ppfunc)
		{
			if (auto ppi = std::get_if<std::shared_ptr<ASTIdentifier>>(&(*ppfunc)->func); ppi)
			{
				if ((*ppi)->name == "bytecode") // inline bytecode
				{
					if ((*ppfunc)->params.size() == 0 || (*ppfunc)->params.size() >= 3)
						throw std::logic_error("Inline bytecode should 1 or 2 paramters");

					auto ppinst = std::get_if<std::shared_ptr<ASTConstLiteral>>(&(*ppfunc)->params[0]);
					if (!ppinst)
						throw std::logic_error("The first parampter of inline bytecode should be string literal");

					auto ppstrinst = std::get_if<std::string>(&(*ppinst)->value);
					if (!ppstrinst)
						throw std::logic_error("The first parampter of inline bytecode should be string literal");

					if ((*ppfunc)->params.size() == 1)
					{
						buffer.emplace_back(*ppstrinst);
					}
					else
					{
						if (auto ppconst = std::get_if<std::shared_ptr<ASTConstLiteral>>(&(*ppfunc)->params[1]))
						{
							buffer.emplace_back(*ppstrinst, Block::getConst(block, (*ppconst)->value));
						}
						else if (auto ppid = std::get_if<std::shared_ptr<ASTIdentifier>>(&(*ppfunc)->params[1]))
						{
							if ((*ppid)->name == "None")
							{
								buffer.emplace_back(*ppstrinst, Block::getConst(block, std::monostate()));
							}
							else
							{
								load_store_variable(block, (*ppid)->name, "LOAD", buffer);
								buffer.back().instruction = *ppstrinst;
							}
						}
						else
							throw std::logic_error("The second parampter of inline bytecode should be const literal or identifier");
					}

					doDefult = false;
				}
			}
		}

		if (doDefult)
		{
			generateInstruction(block, convertToBase(pASTExprStmt->expr), buffer);
			buffer.emplace_back("POP_TOP");
		}
	}
	if (auto pASTEmptyStmt = dynamic_cast<ASTEmptyStmt*>(node); pASTEmptyStmt)
	{
		buffer.emplace_back("NOP");
	}
	if (auto pASTBreakStmt = dynamic_cast<ASTBreakStmt*>(node); pASTBreakStmt)
	{
		for (int i = 1; i < pASTBreakStmt->num; i++)
			buffer.emplace_back("POP_BLOCK");
		buffer.emplace_back("BREAK_LOOP");
	}
	if (auto pASTIfStmt = dynamic_cast<ASTIfStmt*>(node); pASTIfStmt)
	{
		generateInstruction(block, convertToBase(pASTIfStmt->expr), buffer);

		int start_if = buffer.size();
		buffer.emplace_back("EXTENDED_ARG", 0);
		buffer.emplace_back("POP_JUMP_IF_FALSE", 0);

		generateInstruction(block, convertToBase(pASTIfStmt->bodyStmt), buffer);

		if (!std::get_if<std::shared_ptr<ASTNull>>(&pASTIfStmt->elseStmt))
		{
			int start_else = buffer.size();
			buffer.emplace_back("EXTENDED_ARG", 0);
			buffer.emplace_back("JUMP_ABSOLUTE", 0);

			buffer[start_if].param = (2 * buffer.size()) >> 8;
			buffer[start_if + 1].param = (2 * buffer.size()) & 0xFF;

			generateInstruction(block, convertToBase(pASTIfStmt->elseStmt), buffer);

			buffer[start_else].param = (2 * buffer.size()) >> 8;
			buffer[start_else + 1].param = (2 * buffer.size()) & 0xFF;
		}
		else
		{
			buffer[start_if].param = (2 * buffer.size()) >> 8;
			buffer[start_if + 1].param = (2 * buffer.size()) & 0xFF;
		}
	}
	if (auto pASTBinaryOp = dynamic_cast<ASTBinaryOp*>(node); pASTBinaryOp)
	{
		auto ltype = generateInstruction(block, convertToBase(pASTBinaryOp->left), buffer);
		auto rtype = generateInstruction(block, convertToBase(pASTBinaryOp->right), buffer);

		if (dynamic_cast<Block::RealType*>(ltype.get()))
		{
			ret = ltype;
			if (dynamic_cast<Block::RealType*>(rtype.get())) { }
			else if (dynamic_cast<Block::IntType*>(rtype.get())) { 
				buffer.emplace_back("LOAD_GLOBAL", Block::getName(block, "float"));
				buffer.emplace_back("CALL_FUNCTION", 1);
			}
			else
			{
				throw std::logic_error("Bad binary operation between " + ltype->name + " and " + rtype->name);
			}
		}
		else if (dynamic_cast<Block::IntType*>(ltype.get()))
		{
			if (dynamic_cast<Block::IntType*>(rtype.get()))
			{
				ret = ltype;
			}
			else if (dynamic_cast<Block::RealType*>(rtype.get()))
			{
				ret = rtype;
				buffer.emplace_back("ROT_TWO");
				buffer.emplace_back("LOAD_GLOBAL", Block::getName(block, "float"));
				buffer.emplace_back("CALL_FUNCTION", 1);
				buffer.emplace_back("ROT_TWO");
			}
			else
			{
				throw std::logic_error("Bad binary operation between " + ltype->name + " and " + rtype->name);
			}
		}
		else
		{
			throw std::logic_error("Bad binary operation between " + ltype->name + " and " + rtype->name);
		}

		if (pASTBinaryOp->op < pASTBinaryOp->START_CONDITION) // NORMAL
		{
			if (pASTBinaryOp->op >= pASTBinaryOp->BIT_OPERATION)
				if (dynamic_cast<Block::RealType*>(ret.get()))
					throw std::logic_error("Bad bit operation between " + ltype->name + " and " + rtype->name);
			buffer.emplace_back(binary_ops[pASTBinaryOp->op]);
		}
		else
		{
			ret = std::make_shared<Block::IntType>();
			buffer.emplace_back("COMPARE_OP", pASTBinaryOp->op - pASTBinaryOp->START_CONDITION);
		}
	}
	if (auto pASTUnaryOp = dynamic_cast<ASTUnaryOp*>(node); pASTUnaryOp)
	{
		ret = generateInstruction(block, convertToBase(pASTUnaryOp->expr), buffer);

		if (pASTUnaryOp->op < pASTUnaryOp->BIT_OPERATION)
		{
			if (!dynamic_cast<Block::RealType*>(ret.get()) && !dynamic_cast<Block::IntType*>(ret.get()))
				throw std::logic_error("Bad unary operation with type " + ret->name);
		}
		else if (pASTUnaryOp->op >= pASTUnaryOp->BIT_OPERATION)
		{
			if (dynamic_cast<Block::RealType*>(ret.get()))
				throw std::logic_error("Bad bit operation with type " + ret->name);
		}

		buffer.emplace_back(unary_ops[pASTUnaryOp->op]);
	}
	if (auto pASTFuncCall = dynamic_cast<ASTFuncCall*>(node); pASTFuncCall)
	{
		auto rawfunctype = generateInstruction(block, convertToBase(pASTFuncCall->func), buffer);
		auto functype = dynamic_cast<Block::FunctionType*>(rawfunctype.get());

		if (!functype)
		{
			throw std::logic_error(rawfunctype->name + " is not callable");
		}

		ret = functype->retType;

		if (pASTFuncCall->params.size() != functype->paramType.size())
			throw std::logic_error(functype->name + " needs " + std::to_string(functype->paramType.size()) + " argument(s), but " + std::to_string(pASTFuncCall->params.size()) + " given");
		
		for (int i = 0, end = pASTFuncCall->params.size(); i < end; i++)
		{
			auto param = pASTFuncCall->params[i];
			auto targetType = functype->paramType[i];

			auto sourceType = generateInstruction(block, convertToBase(param), buffer);

			generateConvert(block, sourceType.get(), targetType.get(), buffer);
		}
			

		buffer.emplace_back("CALL_FUNCTION", pASTFuncCall->params.size());
	}
	if (auto pASTArrayAccess = dynamic_cast<ASTArrayAccess*>(node); pASTArrayAccess)
	{
		auto arrayType = generateInstruction(block, convertToBase(pASTArrayAccess->array), buffer);
		auto indexType = generateInstruction(block, convertToBase(pASTArrayAccess->index), buffer);

		auto parray = dynamic_cast<Block::ArrayType*>(arrayType.get());

		if (!parray)
			throw std::logic_error(arrayType->name + " is not subscriptable");

		if (!dynamic_cast<Block::IntType*>(indexType.get()))
			throw std::logic_error("Index should be int, but " + arrayType->name + " get");
		
		ret = parray->elementType;

		buffer.emplace_back("BINARY_SUBSCR");

	}

	return ret;
}

void compile(Block::Block* block)
{
	generateProlog(block, block->instructions);
	generateInstruction(block, convertToBase(block->code), block->instructions);
	generateEpilog(block, block->instructions);
}
