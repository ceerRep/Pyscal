#include "lexer.h"

std::string Cls_TOK_IDENTIFIER::toString()
{
	return name() + " " + getValue();
}

std::string Cls_TOK_STRING::toString()
{
	return name() + " " + getValue();
}

std::string Cls_TOK_NUM_INT::toString()
{
	return name() + " " + std::to_string(getValue());
}

std::string Cls_TOK_NUM_REAL::toString()
{
	return name() + " " + std::to_string(getValue());
}

std::string Cls_TOK_UNKNOWN::toString()
{
	return name() + " " + std::to_string(getValue());
}

#define SIMPLE_TO_STRING_DECL(clsname) \
	std::string clsname::toString()    \
	{                                  \
		return name();                 \
	}

SIMPLE_TO_STRING_DECL(Cls_TOK_div)
SIMPLE_TO_STRING_DECL(Cls_TOK_mod)
SIMPLE_TO_STRING_DECL(Cls_TOK_and)
SIMPLE_TO_STRING_DECL(Cls_TOK_or)
SIMPLE_TO_STRING_DECL(Cls_TOK_not)
SIMPLE_TO_STRING_DECL(Cls_TOK_to)
SIMPLE_TO_STRING_DECL(Cls_TOK_downto)
SIMPLE_TO_STRING_DECL(Cls_TOK_with)
SIMPLE_TO_STRING_DECL(Cls_TOK_do)
SIMPLE_TO_STRING_DECL(Cls_TOK_begin)
SIMPLE_TO_STRING_DECL(Cls_TOK_end)
SIMPLE_TO_STRING_DECL(Cls_TOK_if)
SIMPLE_TO_STRING_DECL(Cls_TOK_then)
SIMPLE_TO_STRING_DECL(Cls_TOK_else)
SIMPLE_TO_STRING_DECL(Cls_TOK_case)
SIMPLE_TO_STRING_DECL(Cls_TOK_of)
SIMPLE_TO_STRING_DECL(Cls_TOK_while)
SIMPLE_TO_STRING_DECL(Cls_TOK_repeat)
SIMPLE_TO_STRING_DECL(Cls_TOK_until)
SIMPLE_TO_STRING_DECL(Cls_TOK_for)
SIMPLE_TO_STRING_DECL(Cls_TOK_array)
SIMPLE_TO_STRING_DECL(Cls_TOK_const)
SIMPLE_TO_STRING_DECL(Cls_TOK_procedure)
SIMPLE_TO_STRING_DECL(Cls_TOK_var)
SIMPLE_TO_STRING_DECL(Cls_TOK_function)
SIMPLE_TO_STRING_DECL(Cls_TOK_goto)
SIMPLE_TO_STRING_DECL(Cls_TOK_call)
SIMPLE_TO_STRING_DECL(Cls_TOK_break)
SIMPLE_TO_STRING_DECL(Cls_TOK_SEMI)
SIMPLE_TO_STRING_DECL(Cls_TOK_POINTER)
SIMPLE_TO_STRING_DECL(Cls_TOK_PLUS)
SIMPLE_TO_STRING_DECL(Cls_TOK_MINUS)
SIMPLE_TO_STRING_DECL(Cls_TOK_LPAREN)
SIMPLE_TO_STRING_DECL(Cls_TOK_RPAREN)
SIMPLE_TO_STRING_DECL(Cls_TOK_EQUAL)
SIMPLE_TO_STRING_DECL(Cls_TOK_COLON)
SIMPLE_TO_STRING_DECL(Cls_TOK_COMMA)
SIMPLE_TO_STRING_DECL(Cls_TOK_ASSIGN)
SIMPLE_TO_STRING_DECL(Cls_TOK_NOT_EQUAL)
SIMPLE_TO_STRING_DECL(Cls_TOK_LT)
SIMPLE_TO_STRING_DECL(Cls_TOK_LE)
SIMPLE_TO_STRING_DECL(Cls_TOK_GE)
SIMPLE_TO_STRING_DECL(Cls_TOK_GT)
SIMPLE_TO_STRING_DECL(Cls_TOK_AT)
SIMPLE_TO_STRING_DECL(Cls_TOK_LBRACK)
SIMPLE_TO_STRING_DECL(Cls_TOK_RBRACK)
SIMPLE_TO_STRING_DECL(Cls_TOK_LBRACK2)
SIMPLE_TO_STRING_DECL(Cls_TOK_RBRACK2)
SIMPLE_TO_STRING_DECL(Cls_TOK_DOT)
SIMPLE_TO_STRING_DECL(Cls_TOK_STAR)
SIMPLE_TO_STRING_DECL(Cls_TOK_SLASH)
SIMPLE_TO_STRING_DECL(Cls_TOK_MOD2)
SIMPLE_TO_STRING_DECL(Cls_TOK_AND)
SIMPLE_TO_STRING_DECL(Cls_TOK_OR)
SIMPLE_TO_STRING_DECL(Cls_TOK_DOTDOT)
SIMPLE_TO_STRING_DECL(Cls_TOK_EOF)

std::shared_ptr<ASTConstLiteral> toLiteral(std::shared_ptr<ASTNodeBase> base)
{
	auto ret = std::make_shared<ASTConstLiteral>();
	*(ASTNodeBase*)(ret.get()) = *base;

	ASTNodeBase* p = base.get();

	if (auto str = dynamic_cast<Cls_TOK_STRING*>(p); str)
	{
		ret->value = str->getValue().substr(1, str->getValue().size() - 2);
	}
	else if (auto num_real = dynamic_cast<Cls_TOK_NUM_REAL*>(p); num_real)
	{
		ret->value = num_real->getValue();
	}
	else if (auto num_int = dynamic_cast<Cls_TOK_NUM_INT*>(p); num_int)
	{
		ret->value = num_int->getValue();
	}
	else
	{
		throw std::invalid_argument("Not a literal");
	}

	return ret;
}

std::shared_ptr<ASTIdentifier> toIdentifier(std::shared_ptr<ASTNodeBase> base)
{
	auto ret = std::make_shared<ASTIdentifier>();
	*(ASTNodeBase*)(ret.get()) = *base;

	ASTNodeBase* p = base.get();

	if (auto identifier = dynamic_cast<Cls_TOK_IDENTIFIER*>(p); identifier)
		ret->name = identifier->getValue();
	else
		throw std::invalid_argument("Not an identifier");

	return ret;
}

void yyprocess(std::string name, std::shared_ptr<TokenBase>& self, std::vector<std::shared_ptr<TokenBase>> children)
{
	self = std::make_shared<NamedToken>(0, 0, name);

	for (auto child : children)
	{
		self->addChildren(child);
		self->setLinum(child->getLinum());
		self->setColumn(child->getColumn());
	}
}

std::string toMermaid(std::shared_ptr<TokenBase> ptb)
{
	std::stringstream ss;

	ss << ptb->name() << "_" << ptb.get() << "[" << ptb->name() << "]"
	   << "\n";

	auto&& children = ptb->getChildren();

	for (auto child : children)
	{
		ss << toMermaid(child);
		ss << ptb->name() << "_" << ptb.get() << " --> " << child->name() << "_" << child.get() << "\n";
	}

	return ss.str();
}

std::string toJSON(std::shared_ptr<TokenBase> ptb)
{
	std::stringstream ss;

	ss << "{ text: { name: \"";

	ss << ptb->toString();

	ss << "\" }, \n";

	ss << "children: [\n";

	for (auto&& child : ptb->getChildren())
		ss << toJSON(child) << ",";
	
	ss << "]\n}\n";

	return ss.str();
}
