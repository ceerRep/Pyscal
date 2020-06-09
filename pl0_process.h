#include "ast.h"
#include "lexer.h"

extern int column;
extern int linum;

//program: subprogram DOT EOF
void yyprocess_program_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTProgram>();
	ret->lino = children[0]->lino;
	ret->column = children[0]->column;
	ret->subprogram = std::dynamic_pointer_cast<ASTSubprogram>(children[0]);
	self = ret;
}

//subprogram: opt_const_decl opt_val_decl opt_proc_decl stmt
void yyprocess_subprogram_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTSubprogram>();
	ret->lino = children[0]->lino;
	ret->column = children[0]->column;

	for (int i = 0; i < 3; i++)
	{
		auto decls = std::dynamic_pointer_cast<ASTDecls>(children[i]);

		for (auto decl : decls->decls)
		{
			ret->decls.push_back(decl);
		}
	}

	ret->stmt = convertToStmt(children[3]);
	self = ret;
}

//opt_const_decl:
void yyprocess_opt_const_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	ret->column = ::column;
	ret->lino = ::linum;
	self = ret;
}

//opt_const_decl: const const_decl SEMI
void yyprocess_opt_const_decl_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	ret->column = children[0]->column;
	ret->lino = children[0]->lino;
	ret->decls = std::move(std::dynamic_pointer_cast<ASTDecls>(children[1])->decls);
	self = ret;
}

//const_decl: IDENTIFIER EQUAL const_literal
void yyprocess_const_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	ret->column = children[0]->column;
	ret->lino = children[0]->lino;

	auto decl = std::make_shared<ASTConstDecl>();
	decl->column = children[0]->column;
	decl->lino = children[0]->lino;

	decl->name = toIdentifier(children[0]);
	decl->value = std::dynamic_pointer_cast<ASTConstLiteral>(children[2]);

	ret->decls.push_front(decl);

	self = ret;
}

//const_decl: IDENTIFIER EQUAL const_literal COMMA const_decl
void yyprocess_const_decl_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	*(ASTNodeBase*)(ret.get()) = *children[0];
	ret->decls = std::move(std::dynamic_pointer_cast<ASTDecls>(children[4])->decls);

	auto decl = std::make_shared<ASTConstDecl>();
	*(ASTNodeBase*)(decl.get()) = *children[0];
	decl->name = toIdentifier(children[0]);
	decl->value = std::dynamic_pointer_cast<ASTConstLiteral>(children[2]);

	ret->decls.push_front(decl);

	self = ret;
}

//const_literal: NUM_INT
void yyprocess_const_literal_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = toLiteral(children[0]);
}

//const_literal: NUM_REAL
void yyprocess_const_literal_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = toLiteral(children[0]);
}

//const_literal: STRING
void yyprocess_const_literal_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = toLiteral(children[0]);
}

//opt_val_decl:
void yyprocess_opt_val_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	ret->column = ::column;
	ret->lino = ::linum;
	self = ret;
}

//opt_val_decl: var_name_decls
void yyprocess_opt_val_decl_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//var_name_decls: var_name_decl
void yyprocess_var_name_decls_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//var_name_decls: var_name_decl var_name_decls
void yyprocess_var_name_decls_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[1];
	*(ASTNodeBase*)(self.get()) = *children[0];
	auto decls = std::dynamic_pointer_cast<ASTDecls>(self);
	auto decls0 = std::dynamic_pointer_cast<ASTDecls>(children[0]);
	decls->decls.splice(decls->decls.begin(), decls0->decls);
}

//var_name_decl: var var_name_list COLON typename SEMI
void yyprocess_var_name_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto identifiers = std::dynamic_pointer_cast<ASTIdentifiers>(children[1]);
	auto type = convertToType(children[3]);

	for (auto id : identifiers->identifiers)
	{
		auto decl = std::make_shared<ASTVarDecl>();
		decl->name = id;
		decl->type = type;
		ret->decls.push_back(decl);
	}
	self = ret;
}

//var_name_list: IDENTIFIER
void yyprocess_var_name_list_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTIdentifiers>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->identifiers.push_back(toIdentifier(children[0]));

	self = ret;
}

//var_name_list: IDENTIFIER COMMA var_name_list
void yyprocess_var_name_list_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[2];
	*(ASTNodeBase*)(self.get()) = *children[0];

	auto identifiers = std::dynamic_pointer_cast<ASTIdentifiers>(self);
	identifiers->identifiers.push_front(toIdentifier(children[0]));
}

//typename: IDENTIFIER
void yyprocess_typename_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = toIdentifier(children[0]);
}

//typename: POINTER typename
void yyprocess_typename_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTPointerType>();
	*(ASTNodeBase*)(ret.get()) = *children[0];
	ret->targetType = convertToType(children[1]);

	self = ret;
}

//typename: LPAREN opt_param_decl RPAREN opt_ret
void yyprocess_typename_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTFunctionType>();
	*(ASTNodeBase*)(ret.get()) = *children[0];
	ret->retType = convertToType(children[3]);

	auto params = std::dynamic_pointer_cast<ASTParams>(children[1]);

	for (auto pair : params->params)
	{
		ret->params.push_back(pair);
	}

	self = ret;
}

//typename: typename LBRACK NUM_INT DOTDOT NUM_INT RBRACK
void yyprocess_typename_3(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTArrayType>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->elementType = convertToType(children[0]);
	ret->begin = std::get<int>(toLiteral(children[2])->value);
	ret->end = std::get<int>(toLiteral(children[4])->value);

	self = ret;
}

//typename: LPAREN typename RPAREN
void yyprocess_typename_4(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[1];
}

//opt_ret:
void yyprocess_opt_ret_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = std::make_shared<ASTNull>();
	self->column = ::column;
	self->lino = ::linum;
}

//opt_ret: COLON typename
void yyprocess_opt_ret_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[1];
}

//opt_proc_decl:
void yyprocess_opt_proc_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	ret->column = ::column;
	ret->lino = ::linum;
	self = ret;
}

//opt_proc_decl: proc_decls
void yyprocess_opt_proc_decl_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//proc_decls: proc_decl
void yyprocess_proc_decls_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto decl = std::dynamic_pointer_cast<ASTDecl>(children[0]);
	ret->decls.push_front(decl);

	self = ret;
}

//proc_decls: func_decl
void yyprocess_proc_decls_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTDecls>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto decl = std::dynamic_pointer_cast<ASTDecl>(children[0]);
	ret->decls.push_front(decl);

	self = ret;
}

//proc_decls: proc_decl proc_decls
void yyprocess_proc_decls_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[1];
	*(ASTNodeBase*)(self.get()) = *children[0];

	auto decl = std::dynamic_pointer_cast<ASTDecl>(children[0]);
	auto ret = std::dynamic_pointer_cast<ASTDecls>(self);

	ret->decls.push_front(decl);
}

//proc_decls: func_decl proc_decls
void yyprocess_proc_decls_3(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[1];
	*(ASTNodeBase*)(self.get()) = *children[0];

	auto decl = std::dynamic_pointer_cast<ASTDecl>(children[0]);
	auto ret = std::dynamic_pointer_cast<ASTDecls>(self);

	ret->decls.push_front(decl);
}

//func_decl: func_head subprogram
void yyprocess_func_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];

	auto decl = std::dynamic_pointer_cast<ASTFuncDecl>(self);
	auto sub = std::dynamic_pointer_cast<ASTSubprogram>(children[1]);

	decl->body = sub;
}

//func_head: function IDENTIFIER LPAREN opt_param_decl RPAREN COLON typename
void yyprocess_func_head_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTFuncDecl>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto params = std::dynamic_pointer_cast<ASTParams>(children[3]);

	ret->name = toIdentifier(children[1]);
	ret->params.insert(ret->params.begin(), params->params.begin(), params->params.end());
	ret->retType = convertToType(children[6]);

	self = ret;
}

//func_head: function IDENTIFIER LPAREN opt_param_decl RPAREN
void yyprocess_func_head_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTFuncDecl>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto params = std::dynamic_pointer_cast<ASTParams>(children[3]);

	ret->name = toIdentifier(children[1]);
	ret->params.insert(ret->params.begin(), params->params.begin(), params->params.end());
	ret->retType = std::make_shared<ASTNull>();

	self = ret;
}

//proc_decl: proc_head subprogram
void yyprocess_proc_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];

	auto decl = std::dynamic_pointer_cast<ASTFuncDecl>(self);
	auto sub = std::dynamic_pointer_cast<ASTSubprogram>(children[1]);

	decl->body = sub;
}

//proc_head: procedure IDENTIFIER
void yyprocess_proc_head_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTFuncDecl>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->name = toIdentifier(children[1]);
	ret->retType = std::make_shared<ASTNull>();

	self = ret;
}

//opt_param_decl:
void yyprocess_opt_param_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = std::make_shared<ASTParams>();
	self->lino = ::linum;
	self->column = ::column;
}

//opt_param_decl: param_decl
void yyprocess_opt_param_decl_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//param_decl: IDENTIFIER COLON typename
void yyprocess_param_decl_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTParams>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->params.emplace_front();
	ret->params.front().first = toIdentifier(children[0]);
	ret->params.front().second = convertToType(children[2]);

	self = ret;
}

//param_decl: COLON typename
void yyprocess_param_decl_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTParams>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->params.emplace_front();
	ret->params.front().first = std::make_shared<ASTIdentifier>();
	ret->params.front().second = convertToType(children[1]);

	self = ret;
}

//param_decl: IDENTIFIER COLON typename COMMA param_decl
void yyprocess_param_decl_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::dynamic_pointer_cast<ASTParams>(children[4]);
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->params.emplace_front();
	ret->params.front().first = toIdentifier(children[0]);
	ret->params.front().second = convertToType(children[2]);

	self = ret;
}

//param_decl: COLON typename COMMA param_decl
void yyprocess_param_decl_3(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::dynamic_pointer_cast<ASTParams>(children[3]);
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->params.emplace_front();
	ret->params.front().first = std::make_shared<ASTIdentifier>();
	ret->params.front().second = convertToType(children[1]);

	self = ret;
}

//stmt: assign_stmt
void yyprocess_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmt: cond_stmt
void yyprocess_stmt_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmt: loop_stmt
void yyprocess_stmt_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmt: proc_call_stmt
void yyprocess_stmt_3(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmt: compl_stmt
void yyprocess_stmt_4(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmt: expr_stmt
void yyprocess_stmt_5(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmt: empty_stmt
void yyprocess_stmt_6(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmt: break_stmt
void yyprocess_stmt_7(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//assign_stmt: expr ASSIGN expr SEMI
void yyprocess_assign_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTAssignStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//compl_stmt: begin opt_stmts end
void yyprocess_compl_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTComplStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto stmts = std::dynamic_pointer_cast<ASTStmts>(children[1]);

	ret->stmts.insert(ret->stmts.begin(), stmts->stmts.begin(), stmts->stmts.end());
	self = ret;
}

//opt_stmts:
void yyprocess_opt_stmts_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = std::make_shared<ASTStmts>();
	self->lino = ::linum;
	self->column = ::column;
}

//opt_stmts: stmts
void yyprocess_opt_stmts_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//stmts: stmt
void yyprocess_stmts_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTStmts>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->stmts.push_front(convertToStmt(children[0]));
	self = ret;
}

//stmts: stmt stmts
void yyprocess_stmts_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::dynamic_pointer_cast<ASTStmts>(children[1]);
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->stmts.push_front(convertToStmt(children[0]));
	self = ret;
}

//expr_stmt: expr SEMI
void yyprocess_expr_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTExprStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[0]);
	self = ret;
}

//expr: simple_expr
void yyprocess_expr_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//expr: expr PLUS expr
void yyprocess_expr_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::PLUS;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr MINUS expr
void yyprocess_expr_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::MINUS;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr STAR expr
void yyprocess_expr_3(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::STAR;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr SLASH expr
void yyprocess_expr_4(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::SLASH;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr div expr
void yyprocess_expr_5(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::DIV;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr MOD2 expr
void yyprocess_expr_6(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::MOD;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr and expr
void yyprocess_expr_7(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::AND;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr or expr
void yyprocess_expr_8(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::OR;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr EQUAL expr
void yyprocess_expr_9(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::EQUAL;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr NOT_EQUAL expr
void yyprocess_expr_10(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::NOT_EQUAL;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr LE expr
void yyprocess_expr_11(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::LE;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr GE expr
void yyprocess_expr_12(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::GE;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr LT expr
void yyprocess_expr_13(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::LT;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//expr: expr GT expr
void yyprocess_expr_14(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBinaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->left = convertToExpr(children[0]);
	ret->op = ASTBinaryOp::GT;
	ret->right = convertToExpr(children[2]);

	self = ret;
}

//simple_expr: naive_expr
void yyprocess_simple_expr_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//simple_expr: not simple_expr
void yyprocess_simple_expr_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTUnaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->op = ASTUnaryOp::NOT;

	self = ret;
}

//simple_expr: POINTER simple_expr
void yyprocess_simple_expr_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTUnaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->op = ASTUnaryOp::POINTER;

	self = ret;
}

//simple_expr: PLUS expr
void yyprocess_simple_expr_3(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTUnaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->op = ASTUnaryOp::PLUS;

	self = ret;
}

//simple_expr: MINUS expr
void yyprocess_simple_expr_4(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTUnaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->op = ASTUnaryOp::MINUS;

	self = ret;
}

//simple_expr: AT expr
void yyprocess_simple_expr_5(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTUnaryOp>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->op = ASTUnaryOp::AT;

	self = ret;
}

//naive_expr: atom_expr
void yyprocess_naive_expr_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//naive_expr: naive_expr LPAREN opt_param_list RPAREN
void yyprocess_naive_expr_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTFuncCall>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto params = std::dynamic_pointer_cast<ASTExprs>(children[2]);

	ret->func = convertToExpr(children[0]);
	ret->params.insert(ret->params.begin(), params->exprs.begin(), params->exprs.end());

	self = ret;
}

//naive_expr: naive_expr LBRACK expr RBRACK
void yyprocess_naive_expr_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTArrayAccess>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto params = std::dynamic_pointer_cast<ASTExprs>(children[2]);

	ret->array = convertToExpr(children[0]);
	ret->index = convertToExpr(children[2]);

	self = ret;
}

//atom_expr: const_literal
void yyprocess_atom_expr_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//atom_expr: LPAREN expr RPAREN
void yyprocess_atom_expr_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[1];
}

//atom_expr: IDENTIFIER
void yyprocess_atom_expr_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = toIdentifier(children[0]);
}

//opt_param_list:
void yyprocess_opt_param_list_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = std::make_shared<ASTExprs>();
	self->lino = ::linum;
	self->column = ::column;
}

//opt_param_list: param_list
void yyprocess_opt_param_list_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//param_list: expr
void yyprocess_param_list_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTExprs>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->exprs.push_front(convertToExpr(children[0]));

	self = ret;
}

//param_list: expr COMMA param_list
void yyprocess_param_list_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::dynamic_pointer_cast<ASTExprs>(children[2]);

	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->exprs.push_front(convertToExpr(children[0]));

	self = ret;
}

//cond_stmt: if expr then stmt
void yyprocess_cond_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTIfStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->bodyStmt = convertToStmt(children[3]);
	ret->elseStmt = std::make_shared<ASTNull>();

	self = ret;
}

//cond_stmt: if expr then stmt else stmt
void yyprocess_cond_stmt_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTIfStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->bodyStmt = convertToStmt(children[3]);
	ret->elseStmt = convertToStmt(children[5]);

	self = ret;
}

//proc_call_stmt: call IDENTIFIER SEMI
void yyprocess_proc_call_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTCallStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->identifier = toIdentifier(children[1]);

	self = ret;
}

//loop_stmt: while_stmt
void yyprocess_loop_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//loop_stmt: for_stmt
void yyprocess_loop_stmt_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//loop_stmt: repeat_stmt
void yyprocess_loop_stmt_2(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = children[0];
}

//repeat_stmt: repeat opt_stmts until expr SEMI
void yyprocess_repeat_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTRepeatStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	auto stmts = std::dynamic_pointer_cast<ASTStmts>(children[1]);

	ret->stmts.insert(ret->stmts.begin(), stmts->stmts.begin(), stmts->stmts.end());
	ret->expr = convertToExpr(children[3]);

	self = ret;
}

//while_stmt: while expr do stmt
void yyprocess_while_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTWhileStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->expr = convertToExpr(children[1]);
	ret->stmt = convertToStmt(children[3]);

	self = ret;
}

//for_stmt: for IDENTIFIER ASSIGN expr to expr do stmt
void yyprocess_for_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTForStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->varname = toIdentifier(children[1]);
	ret->begin = convertToExpr(children[3]);
	ret->end = convertToExpr(children[5]);
	ret->step = 1;
	ret->stmt = convertToStmt(children[7]);

	self = ret;
}

//for_stmt: for IDENTIFIER ASSIGN expr downto expr do stmt
void yyprocess_for_stmt_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTForStmt>();
	*(ASTNodeBase*)(ret.get()) = *children[0];

	ret->varname = toIdentifier(children[1]);
	ret->begin = convertToExpr(children[3]);
	ret->end = convertToExpr(children[5]);
	ret->step = -1;
	ret->stmt = convertToStmt(children[7]);

	self = ret;
}

//empty_stmt: SEMI
void yyprocess_empty_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	self = std::make_shared<ASTEmptyStmt>();
	*self = *children[0];
}

//break_stmt: break SEMI
void yyprocess_break_stmt_0(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBreakStmt>();
	ret->num = 1;

	self = ret;
	*self = *children[0];
}

//break_stmt: break NUM_INT SEMI
void yyprocess_break_stmt_1(std::string name, YYSTYPE& self, std::vector<YYSTYPE> children)
{
	auto ret = std::make_shared<ASTBreakStmt>();
	ret->num = std::get<int>(toLiteral(children[1])->value);

	if (ret->num <= 0)
		throw std::logic_error("Num of loop block breaks should be positive");

	self = ret;
	*self = *children[0];
}
