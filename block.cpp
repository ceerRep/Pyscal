#include "block.h"

#include <sstream>

#include "global.h"

namespace Block {

std::shared_ptr<Type> buildTypeFromString(std::string s)
{
	int x, y;
	char op;
	std::stringstream ss(s);
	std::vector<std::shared_ptr<Type>> stack;

	while (ss >> op)
	{
		switch (op)
		{
		case 'i':
			stack.push_back(std::make_shared<IntType>());
			break;

		case 'r':
			stack.push_back(std::make_shared<RealType>());
			break;

		case 's':
			stack.push_back(std::make_shared<StringType>());
			break;

		case '*':
			stack.push_back(std::make_shared<ObjectType>());
			break;

		case 'n':
			stack.push_back(std::make_shared<NullType>());
			break;

		case '[': {

			if (!(stack.size() >= 1 && (ss >> x) && (ss >> op) && (ss >> y) && (op != '.')))
				throw std::invalid_argument("ill-formed type string " + s);

			auto now = std::make_shared<ArrayType>(x, y, stack.back());
			stack.back() = now;
			break;
		}
		case '(': {

			if (!((ss >> x) && stack.size() >= x + 1))
				throw std::invalid_argument("ill-formed type string " + s);

			auto param = std::vector<std::shared_ptr<Type>>(stack.end() - x - 1, stack.end() - 1);
			auto ret = stack.back();

			auto now = std::make_shared<FunctionType>(param, ret);

			for (int i = 0; i < x + 1; i++)
				stack.pop_back();

			stack.push_back(now);

			break;
		}
		default:
			throw std::invalid_argument("ill-formed type string " + s);
		}
	}

	if (stack.size() != 1)
		throw std::invalid_argument("ill-formed type string " + s);

	return stack.front();
}

std::shared_ptr<Type> buildTypeFromAST(ASTNodeBase* pnode)
{
	std::shared_ptr<Type> ret;

	if (auto pnull = dynamic_cast<ASTNull*>(pnode); pnull)
	{
		ret = std::make_shared<NullType>();
	}
	else if (auto pid = dynamic_cast<ASTIdentifier*>(pnode); pid)
	{
		if ((pid)->name == "int")
		{
			ret = std::make_shared<IntType>();
		}
		else if ((pid)->name == "real")
		{
			ret = std::make_shared<RealType>();
		}
		else if ((pid)->name == "string")
		{
			ret = std::make_shared<StringType>();
		}
		else
		{
			throw SyntaxError("Unknown type: " + (pid)->name, pid);
		}
	}
	else if (auto pfunc = dynamic_cast<ASTFunctionType*>(pnode); pfunc)
	{
		std::vector<std::shared_ptr<Type>> params;

		for (auto [id, param] : (pfunc)->params)
			params.push_back(buildTypeFromAST(convertToBase(param)));
		ret = std::make_shared<FunctionType>(params, buildTypeFromAST(convertToBase((pfunc)->retType)));
	}
	else if (auto pfunc = dynamic_cast<ASTFuncDecl*>(pnode); pfunc)
	{
		std::vector<std::shared_ptr<Type>> params;

		for (auto [id, param] : (pfunc)->params)
			params.push_back(buildTypeFromAST(convertToBase(param)));
		ret = std::make_shared<FunctionType>(params, buildTypeFromAST(convertToBase((pfunc)->retType)));
	}
	else if (auto parray = dynamic_cast<ASTArrayType*>(pnode); parray)
	{
		ret = std::make_shared<ArrayType>((parray)->begin, (parray)->end, buildTypeFromAST(convertToBase((parray)->elementType)));
	}
	else if (auto pconst = dynamic_cast<ASTConstLiteral*>(pnode); pconst)
	{
		if (std::get_if<int>(&pconst->value))
		{
			ret = std::make_shared<IntType>();
		}
		else if (std::get_if<double>(&pconst->value))
		{
			ret = std::make_shared<RealType>();
		}
		else if (std::get_if<std::string>(&pconst->value))
		{
			ret = std::make_shared<StringType>();
		}
		else
		{
			throw SyntaxError(std::string("Unknown type ") + std::to_string(pconst->value.index()), pconst);
		}
	}
	else
	{
		throw SyntaxError(std::string("Unknown ASTType ") + typeid(*pnode).name(), pnode);
	}

	return ret;
}

std::shared_ptr<Block> buildBlockFromAST(std::shared_ptr<ASTNodeBase> pnode, Block* parent)
{
	std::shared_ptr<Block> block = std::make_shared<Block>();

	block->argument_count = 0;
	block->parent = parent;

	if (auto pp = std::dynamic_pointer_cast<ASTProgram>(pnode); pp)
	{
		pnode = pp->subprogram;
	}

	if (auto pp = std::dynamic_pointer_cast<ASTFuncDecl>(pnode); pp)
	{
		for (auto [identifier, type] : pp->params)
		{
			auto pmutvar = std::make_shared<MutableVariable>();
			pmutvar->name = identifier;
			pmutvar->type = buildTypeFromAST(convertToBase(type));

			addVar(block.get(), pmutvar, VARIABLE_CELL);
			block->argument_count++;
			block->arg_name.push_back(identifier->name);
		}

		block->ret_type = buildTypeFromAST(convertToBase(pp->retType));

		block->block_name = pp->name->name;

		pnode = pp->body;
	}

	auto psub = std::dynamic_pointer_cast<ASTSubprogram>(pnode);
	if (!psub)
		throw SyntaxError(std::string("Node should be ASTProgram or ASTSubProgram, but ") + typeid(*pnode).name() + " found", pnode.get());

	for (auto pdecl : psub->decls)
	{
		if (auto pconstdecl = std::dynamic_pointer_cast<ASTConstDecl>(pdecl); pconstdecl)
		{
			auto pconstvar = std::make_shared<ConstVariable>();
			pconstvar->name = pconstdecl->name;
			pconstvar->value = pconstdecl->value->value;
			pconstvar->type = buildTypeFromAST(pconstdecl->value.get());
			pconstvar->type->mut = false;

			addVar(block.get(), pconstvar, VARIABLE_CELL);
		}
		else if (auto pvardecl = std::dynamic_pointer_cast<ASTVarDecl>(pdecl); pvardecl)
		{
			auto pmutvar = std::make_shared<MutableVariable>();
			pmutvar->name = pvardecl->name;
			pmutvar->type = buildTypeFromAST(convertToBase(pvardecl->type));

			addVar(block.get(), pmutvar, VARIABLE_CELL);
		}
		else if (auto pastfuncdecl = std::dynamic_pointer_cast<ASTFuncDecl>(pdecl); pastfuncdecl)
		{
			auto subblock = buildBlockFromAST(pastfuncdecl, block.get());

			auto pmutvar = std::make_shared<MutableVariable>();
			pmutvar->name = pastfuncdecl->name;
			pmutvar->type = buildTypeFromAST(pastfuncdecl.get());

			auto funcdecl = std::make_shared<FuncDecl>();
			funcdecl->block = subblock;
			funcdecl->var = pmutvar;

			addVar(block.get(), pmutvar, VARIABLE_CELL);
			getConst(block.get(), subblock);
			block->funcdecls.push_back(funcdecl);
		}
		else
		{
			throw SyntaxError("Unknown decl", pdecl.get());
		}
	}

	block->code = psub->stmt;

	return block;
}

int getConst(Block* block, decltype(Block::consts)::value_type v)
{
	if (block->const_map.count(v) == 0)
	{
		block->consts.push_back(v);
		return (block->const_map[v] = block->consts.size() - 1);
	}
	else
		return block->const_map[v];
}

void addVar(Block* block, std::shared_ptr<Variable> var, VarPos pos)
{
	if (block->var_map.count(var->name->name) != 0)
	{
		throw SyntaxError(std::string("Redefinition of ") + var->name->name, var->name.get());
	}

	auto& vec = pos == VARIABLE_CELL ? block->cellvars : block->freevars;

	vec.push_back(var);
	block->var_map[var->name->name] = {
		pos,
		vec.size() - 1
	};
}

int getName(Block* block, std::string name)
{
	if (auto it = block->name_map.find(name); it != block->name_map.end())
		return it->second;

	block->names.push_back(name);
	return (block->name_map[name] = block->names.size() - 1);
}

}
