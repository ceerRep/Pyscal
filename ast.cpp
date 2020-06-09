#include "ast.h"
#include "block.h"

#include <iostream>

std::string ASTProgram::toJSON()
{
    std::cout << "ASTProgram" << std::endl;

    JSONBuilder builder(this);
    builder.add(subprogram.get());
    return builder.get();
}

std::string ASTSubprogram::toJSON()
{
    std::cout << "ASTSubprogram" << std::endl;

    JSONBuilder builder(this);

    for (auto decl : decls)
        builder.add(decl.get());
    builder.add(convertToBase(stmt));
    return builder.get();
}

std::string ASTNull::toJSON()
{
    std::cout << "ASTNull" << std::endl;

    JSONBuilder builder(this);
    return builder.get();
}

std::string ASTConstDecl::toJSON()
{
    std::cout << "ASTConstDecl" << std::endl;

    JSONBuilder builder(this);
    builder.add(name.get());
    builder.add(value.get());
    return builder.get();
}

std::string ASTVarDecl::toJSON()
{
    std::cout << "ASTVarDecl" << std::endl;

    JSONBuilder builder(this, Block::buildTypeFromAST(convertToBase(this->type))->name);
    builder.add(name.get());
    builder.add(convertToBase(type));
    return builder.get();
}

std::string ASTFuncDecl::toJSON()
{
    std::cout << "ASTFuncDecl" << std::endl;

    JSONBuilder builder(this);

    builder.add(name.get());
    for (auto&& [a, b] : params) {
        builder.add(a.get()).add(convertToBase(b));
    }

    builder.add(body.get());
    builder.add(convertToBase(retType));

    return builder.get();
}

std::string ASTConstLiteral::toJSON()
{
    std::cout << "ASTConstLiteral" << std::endl;

    JSONBuilder builder(this);

    return builder.get();
}

std::string ASTIdentifier::toJSON()
{
    std::cout << "ASTIdentifier" << std::endl;

    JSONBuilder builder(this);

    return builder.get();
}

std::string ASTPointerType::toJSON()
{
    std::cout << "ASTPointerType" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(targetType));

    return builder.get();
}

std::string ASTFunctionType::toJSON()
{
    std::cout << "ASTFunctionType" << std::endl;

    JSONBuilder builder(this);

    for (auto&& [a, b] : params) {
        builder.add(a.get()).add(convertToBase(b));
    }

    builder.add(convertToBase(retType));

    return builder.get();
}

std::string ASTArrayType::toJSON()
{
    std::cout << "ASTArrayType" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(elementType));

    return builder.get();
}

std::string ASTAssignStmt::toJSON()
{
    std::cout << "ASTAssignStmt" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(left));
    builder.add(convertToBase(right));

    return builder.get();
}

std::string ASTForStmt::toJSON()
{
    std::cout << "ASTForStmt" << std::endl;

    JSONBuilder builder(this);

    builder.add(varname.get());
    builder.add(convertToBase(stmt));

    return builder.get();
}

std::string ASTWhileStmt::toJSON()
{
    std::cout << "ASTWhileStmt" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(expr));
    builder.add(convertToBase(stmt));

    return builder.get();
}

std::string ASTRepeatStmt::toJSON()
{
    std::cout << "ASTRepeatStmt" << std::endl;

    JSONBuilder builder(this);

    for (auto& stmt : stmts)
        builder.add(convertToBase(stmt));
    builder.add(convertToBase(expr));

    return builder.get();
}

std::string ASTCallStmt::toJSON()
{
    std::cout << "ASTCallStmt" << std::endl;

    JSONBuilder builder(this);

    builder.add(identifier.get());

    return builder.get();
}

std::string ASTComplStmt::toJSON()
{
    std::cout << "ASTComplStmt" << std::endl;

    JSONBuilder builder(this);

    for (auto& stmt : stmts)
        builder.add(convertToBase(stmt));

    return builder.get();
}

std::string ASTExprStmt::toJSON()
{
    std::cout << "ASTExprStmt" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(expr));

    return builder.get();
}

std::string ASTIfStmt::toJSON()
{
    std::cout << "ASTIfStmt" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(expr));
    builder.add(convertToBase(bodyStmt));
    builder.add(convertToBase(elseStmt));

    return builder.get();
}

std::string ASTEmptyStmt::toJSON()
{
    std::cout << "ASTEmptyStmt" << std::endl;

    JSONBuilder builder(this);
    return builder.get();
}

std::string ASTBreakStmt::toJSON()
{
	std::cout << "ASTBreakStmt" << std::endl;

	JSONBuilder builder(this);
	return builder.get();
}

std::string ASTBinaryOp::toJSON()
{
    std::cout << "ASTBinaryOp" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(left));
    builder.add(convertToBase(right));

    return builder.get();
}

std::string ASTUnaryOp::toJSON()
{
    std::cout << "ASTUnaryOp" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(expr));

    return builder.get();
}

std::string ASTFuncCall::toJSON()
{
    std::cout << "ASTFuncCall" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(func));

    for (auto& expr : params)
        builder.add(convertToBase(expr));

    return builder.get();
}

std::string ASTArrayAccess::toJSON()
{
    std::cout << "ASTArrayAccess" << std::endl;

    JSONBuilder builder(this);

    builder.add(convertToBase(array));
    builder.add(convertToBase(index));

    return builder.get();
}
