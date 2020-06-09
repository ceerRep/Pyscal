%language "c++"
%{
#include <iostream>
#include <typeinfo>
#include "lexer.h"
YYSTYPE* yylval;
int yylex(YYSTYPE*);
YYSTYPE result;

#include "pl0_process.h"

%}

%define api.token.prefix {TOK_}
//%define api.value.type variant

%token
  div
  mod
  and
  or
  not
  to
  downto
  with
  do
  begin
  end
  if
  then
  else
  case
  of
  while
  repeat
  until
  for
  array
  const
  procedure
  var
  function
  goto
  call
  break
  SEMI
  POINTER
  PLUS
  MINUS
  LPAREN
  RPAREN
  EQUAL
  COLON
  COMMA
  ASSIGN
  NOT_EQUAL
  LT
  LE
  GE
  GT
  AT
  LBRACK
  RBRACK
  LBRACK2
  RBRACK2
  DOT
  STAR
  SLASH
  MOD2
  AND
  OR
  DOTDOT
  IDENTIFIER
  NUM_INT
  NUM_REAL
  STRING
  UNKNOWN
  EOF
;

%precedence COLON
%precedence LBRACK LPAREN
%precedence typename_pointer

%left and or
%left LE LT GE GT EQUAL NOT_EQUAL
%left PLUS MINUS
%left STAR SLASH div MOD2
%precedence AT

%precedence then
%precedence else


%%


program: subprogram DOT EOF {/*puts("program: subprogram DOT EOF");*/ yyprocess_program_0("program", $$, {$1, $2, $3}); result = $$; YYACCEPT;}
subprogram: opt_const_decl opt_val_decl opt_proc_decl stmt {/*puts("subprogram: opt_const_decl opt_val_decl opt_proc_decl stmt");*/ yyprocess_subprogram_0("subprogram", $$, {$1, $2, $3, $4}); }

opt_const_decl: {/*puts("opt_const_decl: ");*/ yyprocess_opt_const_decl_0("opt_const_decl", $$, {}); }
| const const_decl SEMI {/*puts("opt_const_decl: const const_decl SEMI");*/ yyprocess_opt_const_decl_1("opt_const_decl", $$, {$1, $2, $3}); }

const_decl: IDENTIFIER EQUAL const_literal {/*puts("const_decl: IDENTIFIER EQUAL const_literal");*/ yyprocess_const_decl_0("const_decl", $$, {$1, $2, $3}); }
| IDENTIFIER EQUAL const_literal COMMA const_decl {/*puts("const_decl: IDENTIFIER EQUAL const_literal COMMA const_decl");*/ yyprocess_const_decl_1("const_decl", $$, {$1, $2, $3, $4, $5}); }

const_literal: NUM_INT {/*puts("const_literal: NUM_INT");*/ yyprocess_const_literal_0("const_literal", $$, {$1}); }
| NUM_REAL {/*puts("const_literal: NUM_REAL");*/ yyprocess_const_literal_1("const_literal", $$, {$1}); }
| STRING {/*puts("const_literal: STRING");*/ yyprocess_const_literal_2("const_literal", $$, {$1}); }

opt_val_decl: {/*puts("opt_val_decl: ");*/ yyprocess_opt_val_decl_0("opt_val_decl", $$, {}); }
| var_name_decls {/*puts("opt_val_decl: var_name_decls");*/ yyprocess_opt_val_decl_1("opt_val_decl", $$, {$1}); }

var_name_decls: var_name_decl {/*puts("var_name_decls: var_name_decl");*/ yyprocess_var_name_decls_0("var_name_decls", $$, {$1}); }
| var_name_decl var_name_decls {/*puts("var_name_decls: var_name_decl var_name_decls");*/ yyprocess_var_name_decls_1("var_name_decls", $$, {$1, $2}); }

var_name_decl: var var_name_list COLON typename SEMI {/*puts("var_name_decl: var var_name_list COLON typename SEMI");*/ yyprocess_var_name_decl_0("var_name_decl", $$, {$1, $2, $3, $4, $5}); }

var_name_list: IDENTIFIER {/*puts("var_name_list: IDENTIFIER");*/ yyprocess_var_name_list_0("var_name_list", $$, {$1}); }
| IDENTIFIER COMMA var_name_list {/*puts("var_name_list: IDENTIFIER COMMA var_name_list");*/ yyprocess_var_name_list_1("var_name_list", $$, {$1, $2, $3}); }

typename: IDENTIFIER {/*puts("typename: IDENTIFIER");*/ yyprocess_typename_0("typename", $$, {$1}); }
| POINTER typename %prec typename_pointer {/*puts("typename: POINTER typename");*/ yyprocess_typename_1("typename", $$, {$1, $2}); }
| LPAREN opt_param_decl RPAREN opt_ret {/*puts("typename: LPAREN opt_param_decl RPAREN opt_ret");*/ yyprocess_typename_2("typename", $$, {$1, $2, $3, $4}); }
| typename LBRACK NUM_INT DOTDOT NUM_INT RBRACK {/*puts("typename: typename LBRACK NUM_INT DOTDOT NUM_INT RBRACK");*/ yyprocess_typename_3("typename", $$, {$1, $2, $3, $4, $5, $6}); }
| LPAREN typename RPAREN {/*puts("typename: LPAREN typename RPAREN");*/ yyprocess_typename_4("typename", $$, {$1, $2, $3}); }

opt_ret: {/*puts("opt_ret: ");*/ yyprocess_opt_ret_0("opt_ret", $$, {}); }
| COLON typename {/*puts("opt_ret: COLON typename");*/ yyprocess_opt_ret_1("opt_ret", $$, {$1, $2}); }

opt_proc_decl: {/*puts("opt_proc_decl: ");*/ yyprocess_opt_proc_decl_0("opt_proc_decl", $$, {}); }
| proc_decls {/*puts("opt_proc_decl: proc_decls");*/ yyprocess_opt_proc_decl_1("opt_proc_decl", $$, {$1}); }

proc_decls: proc_decl {/*puts("proc_decls: proc_decl");*/ yyprocess_proc_decls_0("proc_decls", $$, {$1}); }
| func_decl {/*puts("proc_decls: func_decl");*/ yyprocess_proc_decls_1("proc_decls", $$, {$1}); }
| proc_decl proc_decls {/*puts("proc_decls: proc_decl proc_decls");*/ yyprocess_proc_decls_2("proc_decls", $$, {$1, $2}); }
| func_decl proc_decls {/*puts("proc_decls: func_decl proc_decls");*/ yyprocess_proc_decls_3("proc_decls", $$, {$1, $2}); }

func_decl: func_head subprogram {/*puts("func_decl: func_head subprogram");*/ yyprocess_func_decl_0("func_decl", $$, {$1, $2}); }

func_head: function IDENTIFIER LPAREN opt_param_decl RPAREN COLON typename {/*puts("func_head: function IDENTIFIER LPAREN opt_param_decl RPAREN COLON typename");*/ yyprocess_func_head_0("func_head", $$, {$1, $2, $3, $4, $5, $6, $7}); }
| function IDENTIFIER LPAREN opt_param_decl RPAREN {/*puts("func_head: function IDENTIFIER LPAREN opt_param_decl RPAREN");*/ yyprocess_func_head_1("func_head", $$, {$1, $2, $3, $4, $5}); }

proc_decl: proc_head subprogram {/*puts("proc_decl: proc_head subprogram");*/ yyprocess_proc_decl_0("proc_decl", $$, {$1, $2}); }

proc_head: procedure IDENTIFIER {/*puts("proc_head: procedure IDENTIFIER");*/ yyprocess_proc_head_0("proc_head", $$, {$1, $2}); }

opt_param_decl: {/*puts("opt_param_decl: ");*/ yyprocess_opt_param_decl_0("opt_param_decl", $$, {}); }
| param_decl {/*puts("opt_param_decl: param_decl");*/ yyprocess_opt_param_decl_1("opt_param_decl", $$, {$1}); }

param_decl: IDENTIFIER COLON typename {/*puts("param_decl: IDENTIFIER COLON typename");*/ yyprocess_param_decl_0("param_decl", $$, {$1, $2, $3}); }
| COLON typename {/*puts("param_decl: COLON typename");*/ yyprocess_param_decl_1("param_decl", $$, {$1, $2}); }
| IDENTIFIER COLON typename COMMA param_decl {/*puts("param_decl: IDENTIFIER COLON typename COMMA param_decl");*/ yyprocess_param_decl_2("param_decl", $$, {$1, $2, $3, $4, $5}); }
| COLON typename COMMA param_decl {/*puts("param_decl: COLON typename COMMA param_decl");*/ yyprocess_param_decl_3("param_decl", $$, {$1, $2, $3, $4}); }

stmt: assign_stmt {/*puts("stmt: assign_stmt");*/ yyprocess_stmt_0("stmt", $$, {$1}); }
| cond_stmt {/*puts("stmt: cond_stmt");*/ yyprocess_stmt_1("stmt", $$, {$1}); }
| loop_stmt {/*puts("stmt: loop_stmt");*/ yyprocess_stmt_2("stmt", $$, {$1}); }
| proc_call_stmt {/*puts("stmt: proc_call_stmt");*/ yyprocess_stmt_3("stmt", $$, {$1}); }
| compl_stmt {/*puts("stmt: compl_stmt");*/ yyprocess_stmt_4("stmt", $$, {$1}); }
| expr_stmt {/*puts("stmt: expr_stmt");*/ yyprocess_stmt_5("stmt", $$, {$1}); }
| empty_stmt {/*puts("stmt: empty_stmt");*/ yyprocess_stmt_6("stmt", $$, {$1}); }
| break_stmt {/*puts("stmt: break_stmt");*/ yyprocess_stmt_7("stmt", $$, {$1}); }

assign_stmt: expr ASSIGN expr SEMI {/*puts("assign_stmt: expr ASSIGN expr SEMI");*/ yyprocess_assign_stmt_0("assign_stmt", $$, {$1, $2, $3, $4}); }

compl_stmt: begin opt_stmts end {/*puts("compl_stmt: begin opt_stmts end");*/ yyprocess_compl_stmt_0("compl_stmt", $$, {$1, $2, $3}); }

opt_stmts: {/*puts("opt_stmts: ");*/ yyprocess_opt_stmts_0("opt_stmts", $$, {}); }
| stmts {/*puts("opt_stmts: stmts");*/ yyprocess_opt_stmts_1("opt_stmts", $$, {$1}); }

stmts: stmt {/*puts("stmts: stmt");*/ yyprocess_stmts_0("stmts", $$, {$1}); }
| stmt stmts {/*puts("stmts: stmt stmts");*/ yyprocess_stmts_1("stmts", $$, {$1, $2}); }

expr_stmt: expr SEMI {/*puts("expr_stmt: expr SEMI");*/ yyprocess_expr_stmt_0("expr_stmt", $$, {$1, $2}); }

expr: simple_expr {/*puts("expr: simple_expr");*/ yyprocess_expr_0("expr", $$, {$1}); }
| expr PLUS expr {/*puts("expr: expr PLUS expr");*/ yyprocess_expr_1("expr", $$, {$1, $2, $3}); }
| expr MINUS expr {/*puts("expr: expr MINUS expr");*/ yyprocess_expr_2("expr", $$, {$1, $2, $3}); }
| expr STAR expr {/*puts("expr: expr STAR expr");*/ yyprocess_expr_3("expr", $$, {$1, $2, $3}); }
| expr SLASH expr {/*puts("expr: expr SLASH expr");*/ yyprocess_expr_4("expr", $$, {$1, $2, $3}); }
| expr div expr {/*puts("expr: expr div expr");*/ yyprocess_expr_5("expr", $$, {$1, $2, $3}); }
| expr MOD2 expr {/*puts("expr: expr MOD2 expr");*/ yyprocess_expr_6("expr", $$, {$1, $2, $3}); }
| expr and expr {/*puts("expr: expr and expr");*/ yyprocess_expr_7("expr", $$, {$1, $2, $3}); }
| expr or expr {/*puts("expr: expr or expr");*/ yyprocess_expr_8("expr", $$, {$1, $2, $3}); }
| expr EQUAL expr {/*puts("expr: expr EQUAL expr");*/ yyprocess_expr_9("expr", $$, {$1, $2, $3}); }
| expr NOT_EQUAL expr {/*puts("expr: expr NOT_EQUAL expr");*/ yyprocess_expr_10("expr", $$, {$1, $2, $3}); }
| expr LE expr {/*puts("expr: expr LE expr");*/ yyprocess_expr_11("expr", $$, {$1, $2, $3}); }
| expr GE expr {/*puts("expr: expr GE expr");*/ yyprocess_expr_12("expr", $$, {$1, $2, $3}); }
| expr LT expr {/*puts("expr: expr LT expr");*/ yyprocess_expr_13("expr", $$, {$1, $2, $3}); }
| expr GT expr {/*puts("expr: expr GT expr");*/ yyprocess_expr_14("expr", $$, {$1, $2, $3}); }

simple_expr: naive_expr {/*puts("simple_expr: naive_expr");*/ yyprocess_simple_expr_0("simple_expr", $$, {$1}); }
| not simple_expr {/*puts("simple_expr: not simple_expr");*/ yyprocess_simple_expr_1("simple_expr", $$, {$1, $2}); }
| POINTER simple_expr {/*puts("simple_expr: POINTER simple_expr");*/ yyprocess_simple_expr_2("simple_expr", $$, {$1, $2}); }
| PLUS expr {/*puts("simple_expr: PLUS expr");*/ yyprocess_simple_expr_3("simple_expr", $$, {$1, $2}); }
| MINUS expr {/*puts("simple_expr: MINUS expr");*/ yyprocess_simple_expr_4("simple_expr", $$, {$1, $2}); }
| AT expr {/*puts("simple_expr: AT expr");*/ yyprocess_simple_expr_5("simple_expr", $$, {$1, $2}); }

naive_expr: atom_expr {/*puts("naive_expr: atom_expr");*/ yyprocess_naive_expr_0("naive_expr", $$, {$1}); }
| naive_expr LPAREN opt_param_list RPAREN {/*puts("naive_expr: naive_expr LPAREN opt_param_list RPAREN");*/ yyprocess_naive_expr_1("naive_expr", $$, {$1, $2, $3, $4}); }
| naive_expr LBRACK expr RBRACK {/*puts("naive_expr: naive_expr LBRACK expr RBRACK");*/ yyprocess_naive_expr_2("naive_expr", $$, {$1, $2, $3, $4}); }

atom_expr: const_literal {/*puts("atom_expr: const_literal");*/ yyprocess_atom_expr_0("atom_expr", $$, {$1}); }
| LPAREN expr RPAREN {/*puts("atom_expr: LPAREN expr RPAREN");*/ yyprocess_atom_expr_1("atom_expr", $$, {$1, $2, $3}); }
| IDENTIFIER {/*puts("atom_expr: IDENTIFIER");*/ yyprocess_atom_expr_2("atom_expr", $$, {$1}); }

opt_param_list: {/*puts("opt_param_list: ");*/ yyprocess_opt_param_list_0("opt_param_list", $$, {}); }
| param_list {/*puts("opt_param_list: param_list");*/ yyprocess_opt_param_list_1("opt_param_list", $$, {$1}); }

param_list: expr {/*puts("param_list: expr");*/ yyprocess_param_list_0("param_list", $$, {$1}); }
| expr COMMA param_list {/*puts("param_list: expr COMMA param_list");*/ yyprocess_param_list_1("param_list", $$, {$1, $2, $3}); }

cond_stmt: if expr then stmt {/*puts("cond_stmt: if expr then stmt");*/ yyprocess_cond_stmt_0("cond_stmt", $$, {$1, $2, $3, $4}); }
| if expr then stmt else stmt {/*puts("cond_stmt: if expr then stmt else stmt");*/ yyprocess_cond_stmt_1("cond_stmt", $$, {$1, $2, $3, $4, $5, $6}); }

proc_call_stmt: call IDENTIFIER SEMI {/*puts("proc_call_stmt: call IDENTIFIER SEMI");*/ yyprocess_proc_call_stmt_0("proc_call_stmt", $$, {$1, $2, $3}); }

loop_stmt: while_stmt {/*puts("loop_stmt: while_stmt");*/ yyprocess_loop_stmt_0("loop_stmt", $$, {$1}); }
| for_stmt {/*puts("loop_stmt: for_stmt");*/ yyprocess_loop_stmt_1("loop_stmt", $$, {$1}); }
| repeat_stmt {/*puts("loop_stmt: repeat_stmt");*/ yyprocess_loop_stmt_2("loop_stmt", $$, {$1}); }

repeat_stmt: repeat opt_stmts until expr SEMI {/*puts("repeat_stmt: repeat opt_stmts until expr SEMI");*/ yyprocess_repeat_stmt_0("repeat_stmt", $$, {$1, $2, $3, $4, $5}); }

while_stmt: while expr do stmt {/*puts("while_stmt: while expr do stmt");*/ yyprocess_while_stmt_0("while_stmt", $$, {$1, $2, $3, $4}); }

for_stmt: for IDENTIFIER ASSIGN expr to expr do stmt {/*puts("for_stmt: for IDENTIFIER ASSIGN expr to expr do stmt");*/ yyprocess_for_stmt_0("for_stmt", $$, {$1, $2, $3, $4, $5, $6, $7, $8}); }
| for IDENTIFIER ASSIGN expr downto expr do stmt {/*puts("for_stmt: for IDENTIFIER ASSIGN expr downto expr do stmt");*/ yyprocess_for_stmt_1("for_stmt", $$, {$1, $2, $3, $4, $5, $6, $7, $8}); }

empty_stmt: SEMI {/*puts("empty_stmt: SEMI");*/ yyprocess_empty_stmt_0("empty_stmt", $$, {$1}); }

break_stmt: break SEMI {/*puts("break_stmt: break SEMI");*/ yyprocess_break_stmt_0("break_stmt", $$, {$1, $2}); }
| break NUM_INT SEMI {/*puts("break_stmt: break NUM_INT SEMI");*/ yyprocess_break_stmt_1("break_stmt", $$, {$1, $2, $3}); }


%%


#include "lex.yy.cc"

int yylex(YYSTYPE* yylval)
{
  ::yylval = yylval;
  static FlexLexer *lexer = new yyFlexLexer;
  int ret = lexer->yylex();
  // std::cout << typeid(**yylval).name() << std::endl;
  return ret;
}

namespace yy
{
  // Report an error to the user.
  auto parser::error (const std::string& msg) -> void
  {
    std::cerr << msg << '\n';
  }
}

void naive(YYSTYPE, char*);

int main(int argc, char **argv)
{
	try 
	{
		yy::parser parse;
		int ret = parse();

		if (result != nullptr)
		{
			// std::cerr << html_header << result->toJSON() << html_footer << std::endl;
			naive(result, argv[1]);
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

