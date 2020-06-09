#include "ast.h"
#include "block.h"

#include "global.h"

#include <typeinfo>

namespace Block {

void resolveSymbol(Block* block, ASTIdentifier* symbol)
{
	Block *begin = block, *now = block;

	auto&& str = symbol->name;

	std::shared_ptr<Variable> var;

	while (now)
	{
		if (now->var_map.count(str) != 0)
		{
			auto [pos, ind] = now->var_map[str];

			if (pos == VARIABLE_CELL)
				var = now->cellvars[ind];
			else if (pos == VARIABLE_FREE)
				var = now->freevars[ind];
			break;
		}

		now = now->parent;
	}

	if (now == nullptr)
	{
		// std::cout << str << ' ' << typeid(*(resolveGlobalSymbol(str).get())).name() << std::endl;
		if (typeid(*(resolveGlobalSymbol(str).get())) == typeid(NullType))
		{
			throw std::logic_error("Unable to resolve symbol: " + str);
		}
	}
	else
	{
		while (begin != now)
		{
			addVar(begin, var, VARIABLE_FREE);
			begin = begin->parent;
		}
	}
}

void resolveDFSAST(Block* block, ASTNodeBase* node)
{
	if (auto pASTIdentifier = dynamic_cast<ASTIdentifier*>(node); pASTIdentifier)
	{
		resolveSymbol(block, pASTIdentifier);
	}
	else if (auto pASTAssignStmt = dynamic_cast<ASTAssignStmt*>(node); pASTAssignStmt)
	{
		resolveDFSAST(block, convertToBase(pASTAssignStmt->left));
		resolveDFSAST(block, convertToBase(pASTAssignStmt->right));
	}
	else if (auto pASTForStmt = dynamic_cast<ASTForStmt*>(node); pASTForStmt)
	{
		resolveDFSAST(block, convertToBase(pASTForStmt->begin));
		resolveDFSAST(block, convertToBase(pASTForStmt->end));
		resolveDFSAST(block, pASTForStmt->varname.get());
		resolveDFSAST(block, convertToBase(pASTForStmt->stmt));
	}
	else if (auto pASTWhileStmt = dynamic_cast<ASTWhileStmt*>(node); pASTWhileStmt)
	{
		resolveDFSAST(block, convertToBase(pASTWhileStmt->expr));
		resolveDFSAST(block, convertToBase(pASTWhileStmt->stmt));
	}
	else if (auto pASTRepeatStmt = dynamic_cast<ASTRepeatStmt*>(node); pASTRepeatStmt)
	{
		for (auto stmt : pASTRepeatStmt->stmts)
			resolveDFSAST(block, convertToBase(stmt));
		resolveDFSAST(block, convertToBase(pASTRepeatStmt->expr));
	}
	else if (auto pASTCallStmt = dynamic_cast<ASTCallStmt*>(node); pASTCallStmt)
	{
		resolveDFSAST(block, pASTCallStmt->identifier.get());
	}
	else if (auto pASTComplStmt = dynamic_cast<ASTComplStmt*>(node); pASTComplStmt)
	{
		for (auto stmt : pASTComplStmt->stmts)
			resolveDFSAST(block, convertToBase(stmt));
	}
	else if (auto pASTExprStmt = dynamic_cast<ASTExprStmt*>(node); pASTExprStmt)
	{
		resolveDFSAST(block, convertToBase(pASTExprStmt->expr));
	}
	else if (auto pASTIfStmt = dynamic_cast<ASTIfStmt*>(node); pASTIfStmt)
	{
		resolveDFSAST(block, convertToBase(pASTIfStmt->expr));
		resolveDFSAST(block, convertToBase(pASTIfStmt->bodyStmt));
		resolveDFSAST(block, convertToBase(pASTIfStmt->elseStmt));
	}
	else if (auto pASTBinaryOp = dynamic_cast<ASTBinaryOp*>(node); pASTBinaryOp)
	{
		resolveDFSAST(block, convertToBase(pASTBinaryOp->left));
		resolveDFSAST(block, convertToBase(pASTBinaryOp->right));
	}
	else if (auto pASTUnaryOp = dynamic_cast<ASTUnaryOp*>(node); pASTUnaryOp)
	{
		resolveDFSAST(block, convertToBase(pASTUnaryOp->expr));
	}
	else if (auto pASTFuncCall = dynamic_cast<ASTFuncCall*>(node); pASTFuncCall)
	{
		resolveDFSAST(block, convertToBase(pASTFuncCall->func));

		for (auto param : pASTFuncCall->params)
			resolveDFSAST(block, convertToBase(param));
	}
	else if (auto pASTArrayAccess = dynamic_cast<ASTArrayAccess*>(node); pASTArrayAccess)
	{
		resolveDFSAST(block, convertToBase(pASTArrayAccess->array));
		resolveDFSAST(block, convertToBase(pASTArrayAccess->index));
	}
}

void Block::resolve()
{
	resolveDFSAST(this, convertToBase(code));

	for (auto&& var : this->consts)
	{
		if (auto p = std::get_if<std::shared_ptr<Block>>(&var); p)
		{
			(*p)->resolve();
		}
	}
}
}
