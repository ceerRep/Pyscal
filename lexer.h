#ifndef _LEXER_H
#define _LEXER_H

#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "ast.h"

extern YYSTYPE* yylval;

template <typename T, typename K>
inline K valueOf(const char* str, int len)
{
    T ret;

    std::string source(str, len);

    if constexpr (std::is_same<T, int>::value) {
        ret = std::stoi(source);
    } else if constexpr (std::is_same<T, double>::value) {
        ret = std::stof(source);
    } else if constexpr (std::is_same<T, char>::value) {
        ret = source[0];
    } else if constexpr (std::is_same<T, std::string>::value) {
        ret = source;
    } else if constexpr (std::is_same<T, T>::value) {
        static_assert(!std::is_same<T, T>::value);
    }

    return ret;
}

template <>
inline int valueOf<void, int>(const char* str, int len)
{
    return 0;
}

class TokenBase : public ASTNodeBase {
    std::vector<std::shared_ptr<TokenBase>> children;

public:
    TokenBase() = default;
    TokenBase(int linum, int column)
    {
        ASTNodeBase::column = column;
        ASTNodeBase::lino = linum;
    }

    auto& setLinum(int l)
    {
        ASTNodeBase::lino = l;
        return *this;
    }

    auto& setColumn(int c)
    {
        ASTNodeBase::column = c;
        return *this;
    }

    auto& addChildren(std::shared_ptr<TokenBase> child)
    {
        children.push_back(child);
        return *this;
    }

    auto getLinum() const
    {
        return ASTNodeBase::lino;
    }

    auto getColumn() const
    {
        return ASTNodeBase::column;
    }

    const auto& getChildren() const
    {
        return children;
    }

    virtual std::string name()
    {
        return "TokenBase";
    }

    virtual std::string toString() = 0;

    static std::shared_ptr<TokenBase> process(const char* data, int leng, int linum, int column)
    {
        return nullptr;
    }
};

class NamedToken : public TokenBase {
    std::string val;

    static inline std::shared_ptr<TokenBase> top;

public:
    NamedToken(int linum, int column, std::string val)
        : TokenBase(linum, column)
        , val(val)
    {
        // std::cout << val << std::endl;
    }

    virtual std::string name() override
    {
        return val;
    }

    virtual std::string toString() override
    {
        return val;
    }

    static auto getTop()
    {
        return top;
    }
};

template <typename valuetype>
class ValueToken : public TokenBase {
    valuetype value;

public:
    using value_type = valuetype;
    ValueToken() = default;
    ValueToken(int linum, int column, value_type value)
        : TokenBase(linum, column)
        , value(value)
    {
    }
    auto& setValue(value_type val)
    {
        val = value;
        return *this;
    }
    auto getValue() const { return value; }
    virtual std::string name() override
    {
        return "ValueToken<?>";
    }

    static std::shared_ptr<TokenBase> process(const char* data, int leng, int linum, int column);
};

template <>
class ValueToken<void> : public TokenBase {
    inline static int value;

public:
    using value_type = int;
    ValueToken() = default;
    ValueToken(int linum, int column, int value)
        : TokenBase(linum, column)
    {
    }
    auto& setValue(value_type val)
    {
        val = value;
        return *this;
    }
    auto getValue() const { return value; }
    virtual std::string name() override
    {
        return "ValueToken<void>";
    }

    static std::shared_ptr<TokenBase> process(const char* data, int leng, int linum, int column);
};

#define DEFINE_SIMPLE_TOKEN(classname, tokenname, valuetype)                                         \
    class classname : public ValueToken<valuetype> {                                                 \
                                                                                                     \
    public:                                                                                          \
        classname() = default;                                                                       \
        classname(int linum, int column, ValueToken<valuetype>::value_type value)                    \
            : ValueToken<valuetype>(linum, column, value)                                            \
        {                                                                                            \
        }                                                                                            \
        virtual std::string name() override                                                          \
        {                                                                                            \
            return #tokenname;                                                                       \
        }                                                                                            \
        static std::shared_ptr<TokenBase> process(const char* data, int leng, int linum, int column) \
        {                                                                                            \
            std::shared_ptr<TokenBase> ret = std::make_shared<classname>(linum, column,              \
                valueOf<valuetype, ValueToken<valuetype>::value_type>(data, leng));                  \
            return ret;                                                                              \
        }                                                                                            \
        virtual std::string toString() override;                                                     \
    };

DEFINE_SIMPLE_TOKEN(Cls_TOK_div, div, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_mod, mod, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_and, and, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_or, or, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_not, not, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_to, to, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_downto, downto, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_with, with, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_do, do, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_begin, begin, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_end, end, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_if, if, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_then, then, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_else, else, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_case, case, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_of, of, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_while, while, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_repeat, repeat, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_until, until, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_for, for, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_array, array, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_const, const, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_procedure, procedure, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_var, var, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_function, function, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_goto, goto, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_call, call, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_break, break, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_SEMI, SEMI, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_POINTER, POINTER, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_PLUS, PLUS, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_MINUS, MINUS, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_LPAREN, LPAREN, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_RPAREN, RPAREN, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_EQUAL, EQUAL, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_COLON, COLON, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_COMMA, COMMA, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_ASSIGN, ASSIGN, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_NOT_EQUAL, NOT_EQUAL, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_LT, LT, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_LE, LE, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_GE, GE, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_GT, GT, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_AT, AT, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_LBRACK, LBRACK, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_RBRACK, RBRACK, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_LBRACK2, LBRACK2, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_RBRACK2, RBRACK2, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_DOT, DOT, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_STAR, STAR, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_SLASH, SLASH, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_MOD2, MOD2, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_AND, AND, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_OR, OR, void)
DEFINE_SIMPLE_TOKEN(Cls_TOK_DOTDOT, DOTDOT, void)

DEFINE_SIMPLE_TOKEN(Cls_TOK_IDENTIFIER, IDENTIFIER, std::string)
DEFINE_SIMPLE_TOKEN(Cls_TOK_STRING, STRING, std::string)
DEFINE_SIMPLE_TOKEN(Cls_TOK_NUM_INT, NUM_INT, int)
DEFINE_SIMPLE_TOKEN(Cls_TOK_NUM_REAL, NUM_REAL, double)
DEFINE_SIMPLE_TOKEN(Cls_TOK_UNKNOWN, UNKNOWN, char)

DEFINE_SIMPLE_TOKEN(Cls_TOK_EOF, __EOF__, void)

#define PROCESS(state)                                                 \
	{                                                                  \
		*yylval = Cls_##state::process(yytext, yyleng, linum, column); \
		column += yyleng;                                              \
		return yy::parser::token::state;                               \
	}

std::shared_ptr<ASTConstLiteral> toLiteral(std::shared_ptr<ASTNodeBase> base);
std::shared_ptr<ASTIdentifier> toIdentifier(std::shared_ptr<ASTNodeBase> base);
void yyprocess(std::string name, std::shared_ptr<TokenBase>& self, std::vector<std::shared_ptr<TokenBase>> children);
std::string toMermaid(std::shared_ptr<TokenBase> ptb);
std::string toJSON(std::shared_ptr<TokenBase> ptb);

constexpr const inline char* html_header = R"(<!doctype html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">
    <title></title>
    <!-- stylesheets -->
    <link rel="stylesheet" href="Treant.css" type="text/css" />

    <style type="text/css">
        .chart {
            margin: 5px;
            margin: 5px auto;
            border: 3px solid #DDD;
            border-radius: 3px;
        }

        .node {
            color: #9CB5ED;
            border: 2px solid #C8C8C8;
            border-radius: 3px;
        }

        .node p {
            padding: 3px;
            margin: 0;
        }
    </style>

    <script src="dragscroll.js"></script>
</head>

<body class="">
    <div class="dragscroll" id="tree-simple" style="height: 100%"> </div>
    <!-- javascript -->
    <script src="vendor/jquery.min.js"></script>
    <script src="vendor/raphael.js"></script>
    <script src="Treant.js"></script>

    <script>
        simple_chart_config = {
            chart: {
                container: "#tree-simple",
                scrollbar: "native"
            },

            nodeStructure: )";

constexpr const inline char* html_footer = R"(};
        var my_chart = new Treant(simple_chart_config);

    </script>
</body>

</html>)";

#endif
