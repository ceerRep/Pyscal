#ifndef _AST_H

#define _AST_H

#include <list>
#include <memory>
#include <sstream>
#include <type_traits>
#include <typeinfo>
#include <variant>
#include <vector>

#include "util.h"

#include <iostream>

struct ASTNodeBase;
struct ASTProgram;
struct ASTSubprogram;
struct ASTDecl;
struct ASTConstDecl;
struct ASTVarDecl;
struct ASTFuncDecl;
struct ASTConstLiteral;
struct ASTIdentifier;
struct ASTPointerType;
struct ASTFunctionType;
struct ASTArrayType;
struct ASTAssignStmt;
struct ASTForStmt;
struct ASTWhileStmt;
struct ASTRepeatStmt;
struct ASTCallStmt;
struct ASTComplStmt;
struct ASTExprStmt;
struct ASTEmptyStmt;
struct ASTBreakStmt;
struct ASTIfStmt;
struct ASTBinaryOp;
struct ASTUnaryOp;
struct ASTFuncCall;
struct ASTArrayAccess;
struct ASTNull;

using ASTType = std::variant<
    std::shared_ptr<ASTNull>,
    std::shared_ptr<ASTIdentifier>,
    std::shared_ptr<ASTPointerType>,
    std::shared_ptr<ASTFunctionType>,
    std::shared_ptr<ASTArrayType>>;

using ASTStmt = std::variant<
    std::shared_ptr<ASTNull>,
    std::shared_ptr<ASTAssignStmt>,
    std::shared_ptr<ASTForStmt>,
    std::shared_ptr<ASTWhileStmt>,
    std::shared_ptr<ASTRepeatStmt>,
    std::shared_ptr<ASTCallStmt>,
    std::shared_ptr<ASTComplStmt>,
    std::shared_ptr<ASTExprStmt>,
    std::shared_ptr<ASTEmptyStmt>,
	std::shared_ptr<ASTBreakStmt>,
    std::shared_ptr<ASTIfStmt>>;

using ASTExpr = std::variant<
    std::shared_ptr<ASTNull>,
    std::shared_ptr<ASTIdentifier>,
    std::shared_ptr<ASTConstLiteral>,
    std::shared_ptr<ASTBinaryOp>,
    std::shared_ptr<ASTUnaryOp>,
    std::shared_ptr<ASTFuncCall>,
    std::shared_ptr<ASTArrayAccess>>;

template <typename T>
struct convertToTypeHelper {
    bool operator()(ASTType& ret, std::shared_ptr<ASTNodeBase> node) const
    {
        if constexpr (!std::is_same_v<T, std::monostate>)
            if (auto p = std::dynamic_pointer_cast<typename T::element_type>(node); p) {
                ret = p;
                return true;
            }
        return false;
    }
};

inline ASTType convertToType(std::shared_ptr<ASTNodeBase> node)
{
    ASTType ret;
    ExtractTemplateArgument<ASTType, convertToTypeHelper>::process(ret, node);
    return ret;
}

template <typename T>
struct convertToExprHelper {
    bool operator()(ASTExpr& ret, std::shared_ptr<ASTNodeBase> node) const
    {
        if constexpr (!std::is_same_v<T, std::monostate>)
            if (auto p = std::dynamic_pointer_cast<typename T::element_type>(node); p) {
                ret = p;
                return true;
            }
        return false;
    }
};

inline ASTExpr convertToExpr(std::shared_ptr<ASTNodeBase> node)
{
    ASTExpr ret;
    ExtractTemplateArgument<ASTExpr, convertToExprHelper>::process(ret, node);
    return ret;
}

template <typename T>
struct convertToStmtHelper {
    bool operator()(ASTStmt& ret, std::shared_ptr<ASTNodeBase> node) const
    {
        if constexpr (!std::is_same_v<T, std::monostate>)
            if (auto p = std::dynamic_pointer_cast<typename T::element_type>(node); p) {
                ret = p;
                return true;
            }
        return false;
    }
};

inline ASTStmt convertToStmt(std::shared_ptr<ASTNodeBase> node)
{
    ASTStmt ret;
    ExtractTemplateArgument<ASTStmt, convertToStmtHelper>::process(ret, node);
    return ret;
}

template <typename T>
struct convertToBaseTypeHelper {
    bool operator()(ASTNodeBase*& ret, ASTType& node) const
    {
        if constexpr (!std::is_same_v<T, std::monostate>)
            if (auto p = std::get_if<T>(&node); p) {
                ret = p->get();
                return true;
            }
        return false;
    }
};

template <typename T>
struct convertToBaseExprHelper {
    bool operator()(ASTNodeBase*& ret, ASTExpr& node) const
    {
        if constexpr (!std::is_same_v<T, std::monostate>)
            if (auto p = std::get_if<T>(&node); p) {
                ret = p->get();
                return true;
            }
        return false;
    }
};

template <typename T>
struct convertToBaseStmtHelper {
    bool operator()(ASTNodeBase*& ret, ASTStmt& node) const
    {
        if constexpr (!std::is_same_v<T, std::monostate>)
            if (auto p = std::get_if<T>(&node); p) {
                ret = p->get();
                return true;
            }
        return false;
    }
};

template <typename T>
inline ASTNodeBase* convertToBase(T var)
{
    ASTNodeBase* base = nullptr;

    if constexpr (std::is_same_v<T, ASTType>)
        ExtractTemplateArgument<T, convertToBaseTypeHelper>::process(base, var);
    if constexpr (std::is_same_v<T, ASTExpr>)
        ExtractTemplateArgument<T, convertToBaseExprHelper>::process(base, var);
    if constexpr (std::is_same_v<T, ASTStmt>)
        ExtractTemplateArgument<T, convertToBaseStmtHelper>::process(base, var);

    if (base == nullptr)
        throw std::invalid_argument("Not a node");
    return base;
}

struct ASTNodeBase {
    int lino, column;

    virtual ~ASTNodeBase() = default;

    virtual std::string toJSON() { throw std::logic_error("Not implemented yet"); }
};

struct JSONBuilder {
    std::stringstream ss;
    JSONBuilder(ASTNodeBase* p, std::string name = "")
    {
        ss << "{ text: { name: \"";

        if (name == "")
            ss << typeid(*p).name();
        else
            ss << name;

        ss << "\" }, \n";

        ss << "children: [\n";
    }

    auto& add(ASTNodeBase* ch)
    {
        ss << ch->toJSON() << ",";
        return *this;
    }

    auto get()
    {
        return ss.str() + "]\n}\n";
    }
};

struct ASTProgram : public ASTNodeBase {
    std::shared_ptr<ASTSubprogram> subprogram;

    virtual std::string toJSON() override;
};

struct ASTSubprogram : public ASTNodeBase {
    std::vector<std::shared_ptr<ASTDecl>> decls;
    ASTStmt stmt;

    virtual std::string toJSON() override;
};

struct ASTNull : public ASTNodeBase {
    virtual std::string toJSON() override;
};

struct ASTDecls : public ASTNodeBase {
    std::list<std::shared_ptr<ASTDecl>> decls;
};

struct ASTIdentifiers : public ASTNodeBase {
    std::list<std::shared_ptr<ASTIdentifier>> identifiers;
};

struct ASTParams : public ASTNodeBase {
    std::list<std::pair<std::shared_ptr<ASTIdentifier>, ASTType>> params;
};

struct ASTStmts : public ASTNodeBase {
    std::list<ASTStmt> stmts;
};

struct ASTExprs : public ASTNodeBase {
    std::list<ASTExpr> exprs;
};

struct ASTDecl : public ASTNodeBase {
    std::shared_ptr<ASTIdentifier> name;
};

struct ASTConstDecl : public ASTDecl {
    std::shared_ptr<ASTConstLiteral> value;
    virtual std::string toJSON() override;
};

struct ASTVarDecl : public ASTDecl {
    ASTType type;
    virtual std::string toJSON() override;
};

struct ASTFuncDecl : public ASTDecl {
    std::vector<std::pair<std::shared_ptr<ASTIdentifier>, ASTType>> params;
    ASTType retType;
    std::shared_ptr<ASTSubprogram> body;
    virtual std::string toJSON() override;
};

struct ASTConstLiteral : public ASTNodeBase {
    std::variant<std::monostate, int, double, std::string> value;
    virtual std::string toJSON() override;
};

struct ASTIdentifier : public ASTNodeBase {
    std::string name;
    virtual std::string toJSON() override;
};

struct ASTPointerType : public ASTNodeBase {
    ASTType targetType;
    ASTPointerType()
        : ASTNodeBase()
    {
        throw std::logic_error("Not implemented yet");
    }
    virtual std::string toJSON() override;
};

struct ASTFunctionType : public ASTNodeBase {
    std::vector<std::pair<std::shared_ptr<ASTIdentifier>, ASTType>> params;
    ASTType retType;
    virtual std::string toJSON() override;
};

struct ASTArrayType : public ASTNodeBase {
    int begin, end;
    ASTType elementType;
    virtual std::string toJSON() override;
};

struct ASTAssignStmt : public ASTNodeBase {
    ASTExpr left, right;
    virtual std::string toJSON() override;
};

struct ASTForStmt : public ASTNodeBase {
    std::shared_ptr<ASTIdentifier> varname;
    int step;
	ASTExpr begin, end;
    ASTStmt stmt;
    virtual std::string toJSON() override;
};

struct ASTWhileStmt : public ASTNodeBase {
    ASTExpr expr;
    ASTStmt stmt;
    virtual std::string toJSON() override;
};

struct ASTRepeatStmt : public ASTNodeBase {
    std::vector<ASTStmt> stmts;
    ASTExpr expr;
    virtual std::string toJSON() override;
};

struct ASTCallStmt : public ASTNodeBase {
    std::shared_ptr<ASTIdentifier> identifier;
    virtual std::string toJSON() override;
};

struct ASTComplStmt : public ASTNodeBase {
    std::vector<ASTStmt> stmts;
    virtual std::string toJSON() override;
};

struct ASTExprStmt : public ASTNodeBase {
    ASTExpr expr;
    virtual std::string toJSON() override;
};

struct ASTIfStmt : public ASTNodeBase {
    ASTExpr expr;
    ASTStmt bodyStmt;
    ASTStmt elseStmt;
    virtual std::string toJSON() override;
};

struct ASTEmptyStmt : public ASTNodeBase {
    virtual std::string toJSON() override;
};

struct ASTBreakStmt : public ASTNodeBase {
	int num;
	virtual std::string toJSON() override;
};

struct ASTBinaryOp : public ASTNodeBase {
    enum {
        PLUS,
        MINUS,
        STAR,
        SLASH,
        DIV,
		MOD,
        BIT_OPERATION,
		AND = BIT_OPERATION,
		OR,
        START_CONDITION,
		LT = START_CONDITION,
		LE,
		EQUAL,
		NOT_EQUAL,
		GT,
        GE
    };
    ASTExpr left;
    ASTExpr right;
    int op;
    virtual std::string toJSON() override;
};

struct ASTUnaryOp : public ASTNodeBase {
    enum {
        PLUS,
        MINUS,
		BIT_OPERATION,
		NOT = BIT_OPERATION,
		POINTER,
        AT
    };
    ASTExpr expr;
    int op;
    virtual std::string toJSON() override;
};

struct ASTFuncCall : public ASTNodeBase {
    ASTExpr func;
    std::vector<ASTExpr> params;
    virtual std::string toJSON() override;
};

struct ASTArrayAccess : public ASTNodeBase {
    ASTExpr array;
    ASTExpr index;
    virtual std::string toJSON() override;
};

#define YYSTYPE std::shared_ptr<ASTNodeBase>

#endif
