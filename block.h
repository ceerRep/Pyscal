#ifndef _BLOCK_H

#define _BLOCK_H

#include <any>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <typeinfo>
#include <vector>

#include "ast.h"

#include "instruction.h"

namespace Block {

struct Block;
struct Variable;
struct MutableVariable;
struct ConstVariable;
struct Type;
struct FuncDecl;

enum VarPos {
	VARIABLE_ERROR,
	VARIABLE_FREE,
	VARIABLE_CELL
};

struct Block {
	int argument_count;
	std::string block_name;
	std::vector<std::string> arg_name;

	std::shared_ptr<Type> ret_type;

	Block* parent;

	std::map<std::string, int> name_map;
	std::map<std::string, std::pair<VarPos, int>> var_map;
	std::map<std::variant<std::variant<std::monostate, int, double, std::string>, std::shared_ptr<Block>>, int> const_map;

	std::vector<std::string> names;
	std::vector<std::shared_ptr<Variable>> freevars, cellvars;
	std::vector<std::variant<std::variant<std::monostate, int, double, std::string>, std::shared_ptr<Block>>> consts;

	std::vector<std::shared_ptr<FuncDecl>> funcdecls;

	ASTStmt code;

	void resolve();

	std::vector<Instruction> instructions;
};

struct Variable {
	std::shared_ptr<ASTIdentifier> name;
	std::shared_ptr<Type> type;

	virtual ~Variable() = default;
};

struct ConstVariable : public Variable {
	std::variant<std::monostate, int, double, std::string> value;
};

struct MutableVariable : public Variable { };

struct Type {
	bool mut = true;
	std::string name;

	Type(std::string name)
		: name(name)
	{
	}
	virtual ~Type() = default;
};

struct IntType : public Type {
	IntType()
		: Type("i")
	{
	}
};

struct RealType : public Type {
	RealType()
		: Type("r")
	{
	}
};

struct StringType : public Type {
	StringType()
		: Type("s")
	{
	}
};

struct ArrayType : public Type {
	int floor, ceil;
	std::shared_ptr<Type> elementType;
	ArrayType(int f, int c, std::shared_ptr<Type> etype)
		: Type(etype->name + "[" + std::to_string(f) + "." + std::to_string(c))
		, floor(f)
		, ceil(c)
		, elementType(etype)
	{
	}
};

struct FunctionType : public Type {
	std::vector<std::shared_ptr<Type>> paramType;
	std::shared_ptr<Type> retType;
	FunctionType(std::vector<std::shared_ptr<Type>> param, std::shared_ptr<Type> ret)
		: Type("")
		, paramType(param)
		, retType(ret)
	{
		std::stringstream ss;
		for (auto p : param)
			ss << p->name;
		ss << ret->name;
		ss << "(" << param.size();
		name = ss.str();
	}
};

struct NullType : public Type {
	NullType()
		: Type("n")
	{
	}
};

struct ObjectType : public Type {
	ObjectType()
		: Type("*")
	{
	}
};

struct FuncDecl {
	std::shared_ptr<Variable> var;
	std::shared_ptr<Block> block;
};

std::shared_ptr<Type> buildTypeFromString(std::string s);
std::shared_ptr<Type> buildTypeFromAST(ASTNodeBase* pnode);
std::shared_ptr<Block> buildBlockFromAST(std::shared_ptr<ASTNodeBase> pnode, Block* parent);

void addVar(Block* block, std::shared_ptr<Variable> var, VarPos pos);
int getConst(Block* block, decltype(Block::consts)::value_type v);
int getName(Block* block, std::string name);

}

class SyntaxError : public std::exception {
public:
	SyntaxError(std::string s, ASTNodeBase* node)
		: std::exception((s + " (" + std::to_string(node->lino) + ", " + std::to_string(node->column) + ")").c_str())
	{
	}
};
#endif
