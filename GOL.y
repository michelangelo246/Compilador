/**	Michelangelo da R. Machado - 14/0156089
**/

%error-verbose
%define parse.lac full
%{
	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Syntactic.h"
#define initialize_lexer GOL_initialize_lexer

extern int yyparse(void);
extern int yylex(void);

int yy_mylinenumber;
int yy_mycolumnnumber;

int recent_type;
//utilizados para nomear as tabelas. 1. No léxico, ao identificar '{', empilha um contexto
//com o último nome guardado no recent_identifier 2. No sintático é definido o valor de
//recent_identifier ao ler uma regra no estilo int num(), com o nome da função declarada
//com o index, pode-se manter o mesmo recent_identifier mas diferenciando o escopo interno
char *recent_identifier = NULL;
int recent_identifier_index = 0;

extern int initialize_lexer(FILE * inp);

void yyerror(const char *str)
{
	extern char *GOLtext;
	fprintf(stderr,"%s em: \"%s\", linha: %d, coluna: %d. \n",
	str, GOLtext, yy_mylinenumber + 1, (int)(yy_mycolumnnumber - strlen(GOLtext)));
	error = 1;
}

No YY_RESULT_Trans_Unit_ = 0;
No pTrans_Unit(FILE *inp)
{
	initialize_lexer(inp);
	if (yyparse())
	{ /* Falha */
		return 0;
	}
	else
	{ /* Sucesso */
		return YY_RESULT_Trans_Unit_;
	}
}

%}

%union
{
  int int_;
  double double_;
  char* string_;
  No no_;
}

%token _ERROR_
%token ASG_OP  		"="
%token INS_OP  		"<<"
%token SUB_OP  		"-"
%token NOT_OP  		"!"
%token COMMA   		","
%token OPN_PRTS		"("
%token CLS_PRTS		")"
%token OPN_BRK 		"["
%token CLS_BRK 		"]"
%token AT_SYM  		"@"
%token SHARP   		"#"
%token ADR_OP  		"&"
%token MUL_OP  		"*"
%token DIV_OP  		"/"
%token ADD_OP  		"+"
%token LT_OP   		"<"
%token GT_OP   		">"
%token LE_OP   		"<="
%token GE_OP   		">="
%token EQ_OP   		"=="
%token NE_OP   		"!="
%token AND_OP  		"&&"
%token OR_OP   		"||"
%token SEMICOLN		";"
%token OPN_CRLY		"{"
%token CLS_CRLY		"}"
%token DOUBLE  		"double"
%token ELSE    		"else"
%token GRAPH   		"graph"
%token IF    		"if"
%token INT    		"int"
%token RETURN  		"return"
%token VOID    		"void"
%token WHILE   		"while"

%token <string_> _STRING_
%token <int_> 	 _INTEGER_
%token <double_> _DOUBLE_
%token <string_> _IDENT_

%type <no_> Trans_Unit
%type <no_> Assign_Operator
%type <no_> Constant
%type <no_> Unary_Operator
%type <no_> Type
%type <no_> Arg_Exp_List
%type <no_> Primary_Exp
%type <no_> Posfix_Exp
%type <no_> Unary_Exp
%type <no_> Multi_Exp
%type <no_> Add_Exp
%type <no_> Rel_Exp
%type <no_> Eq_Exp
%type <no_> Log_And_Exp
%type <no_> Log_Or_Exp
%type <no_> Expression
%type <no_> Init_Decl_List
%type <no_> Init_Declarator
%type <no_> Var_Declaration
%type <no_> Var_Decl_List
%type <no_> Parameter_List
%type <no_> Statement_List
%type <no_> Statement
%type <no_> Open_Stm
%type <no_> Block_Stm
%type <no_> Return_Stm
%type <no_> Exp_Stm
%type <no_> Closed_Stm
%type <no_> Simple_Stm
%type <no_> Declarator
%type <no_> Function_Def
%type <no_> Ext_Var_Decl

%start Trans_Unit
%%
Trans_Unit 
/*TraUniExtVar*/	: Ext_Var_Decl				{ $$ = $1; YY_RESULT_Trans_Unit_= $$; } 
/*TraUniList*/		| Trans_Unit Ext_Var_Decl	{ $$ = make_No(is_TraUniList, ins_No($1, ins_No($2, NULL)), NULL); YY_RESULT_Trans_Unit_= $$; }
					;

Assign_Operator 
/*AssOpEQ*/			: "="	{ $$ = make_No(is_AssOpEQ, NULL, NULL); } 
/*AssOpINS*/		| "<<"	{ $$ = make_No(is_AssOpINS, NULL, NULL); }
					;
	
Constant 	
/*ConstInt*/		: _INTEGER_	{ $$ = make_No(is_ConstInt, NULL, ins_Args_Int(is_ConstInt, $1, NULL)); 
								  SymbolTable_ins_ConstInt($1, yy_mylinenumber+1, yy_mycolumnnumber); } 
/*ConstDouble*/		| _DOUBLE_	{ $$ = make_No(is_ConstDouble, NULL, ins_Args_Double(is_ConstDouble, $1, NULL)); 
								  SymbolTable_ins_ConstDouble($1, yy_mylinenumber+1, yy_mycolumnnumber); }
/*ConstStr*/		| _STRING_	{ $$ = make_No(is_ConstStr, NULL, ins_Args_Str(is_ConstStr, $1, NULL)); 
								  SymbolTable_ins_constStr($1, yy_mylinenumber+1, yy_mycolumnnumber); }
					;
	
Unary_Operator 	
/*UnaOpMinus*/		: "-"	{ $$ = make_No(is_UnaOpMinus, NULL, NULL); } 
/*UnaOpNot*/		| "!"	{ $$ = make_No(is_UnaOpNot, NULL, NULL); }
					;
	
Type 	
/*TypeVoid*/		: "void"	{ $$ = make_No(is_TypeVoid, NULL, NULL); } 
/*TypeInt*/			| "int" 	{ $$ = make_No(is_TypeInt, NULL, NULL); }
/*TypeDouble*/		| "double" 	{ $$ = make_No(is_TypeDouble, NULL, NULL); }
/*TypeGraph*/		| "graph" 	{ $$ = make_No(is_TypeGraph, NULL, NULL); }
					;
	
Arg_Exp_List 	
/*ArgExpListExp*/	: Expression 					{ $$ = $1; } 
/*ArgExpList*/		| Arg_Exp_List "," Expression 	{ $$ = make_No(is_ArgExpList, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Primary_Exp 	
/*PriExpId*/		: _IDENT_				{ $$ = make_No(is_PriExpId, NULL, ins_Args_Ident(Is_Ident, $1, NULL));
											  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
/*PriExpConst*/		| Constant 				{ $$ = $1; }
/*PriExpExp*/		| "(" Expression ")" 	{ $$ = make_No(is_PriExpExp, ins_No($2, NULL), NULL); }
					;
	
Posfix_Exp 	
/*PosExpPri*/		: Primary_Exp 					{ $$ = $1; } 
/*PosExpSub*/		| _IDENT_ "[" Primary_Exp "]" 	{ $$ = make_No(is_PosExpSub, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL));
													  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
/*PosExpIn*/		| _IDENT_ "@" Primary_Exp "#" 	{ $$ = make_No(is_PosExpIn, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL));
													  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
/*PosExpOut*/		| _IDENT_ "#" Primary_Exp "@" 	{ $$ = make_No(is_PosExpOut, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL));
													  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
/*PosExpNeig*/		| _IDENT_ "&" Primary_Exp "&" 	{ $$ = make_No(is_PosExpNeig, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL));
													  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
/*PosExpCal*/		| _IDENT_ "(" ")" 			  	{ $$ = make_No(is_PosExpCal, NULL, ins_Args_Ident(Is_Ident, $1, NULL)); 
													  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
/*PosExpCalArg*/	| _IDENT_ "(" Arg_Exp_List ")"  { $$ = make_No(is_PosExpCalArg, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL));
													  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
					| _IDENT_ "[" error "]" 		{ printf("sem expressao para subgrafo"); }
					| _IDENT_ "@" error "#" 		{ printf("sem expressao para grau de entrada"); }
					| _IDENT_ "#" error "@" 		{ printf("sem expressao para grau de saida"); }
					| _IDENT_ "&" error "&" 		{ printf("sem expressao para vizinhanca"); }
					;
	
Unary_Exp 	
/*UnaExpPos*/		: Posfix_Exp 				{ $$ = $1; } 
/*UnaExpOp*/		| Unary_Operator Unary_Exp	{ $$ = make_No(is_UnaExpOp, ins_No($1, ins_No($2, NULL)), NULL); }
					;
	
Multi_Exp 	
/*MulExpUna*/		: Unary_Exp 				{ $$ = $1; } 
/*MulExpMul*/		| Multi_Exp "*" Unary_Exp 	{ $$ = make_No(is_MulExpMul, ins_No($1, ins_No($3, NULL)), NULL); }
/*MulExpDiv*/		| Multi_Exp "/" Unary_Exp 	{ $$ = make_No(is_MulExpDiv, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Add_Exp 	
/*AddExpMul*/		: Multi_Exp 			{ $$ = $1; } 
/*AddExpAdd*/		| Add_Exp "+" Multi_Exp	{ $$ = make_No(is_AddExpAdd, ins_No($1, ins_No($3, NULL)), NULL); }
/*AddExpSub*/		| Add_Exp "-" Multi_Exp	{ $$ = make_No(is_AddExpSub, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Rel_Exp 	
/*RelExpAdd*/		: Add_Exp 				{ $$ = $1; } 
/*RelExpLT*/		| Rel_Exp "<" Add_Exp 	{ $$ = make_No(is_RelExpLT, ins_No($1, ins_No($3, NULL)), NULL); }
/*RelExpGT*/		| Rel_Exp ">" Add_Exp 	{ $$ = make_No(is_RelExpGT, ins_No($1, ins_No($3, NULL)), NULL); }
/*RelExpLE*/		| Rel_Exp "<=" Add_Exp 	{ $$ = make_No(is_RelExpLE, ins_No($1, ins_No($3, NULL)), NULL); }
/*RelExpGE*/		| Rel_Exp ">=" Add_Exp 	{ $$ = make_No(is_RelExpGE, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Eq_Exp 	
/*EqExpRel*/		: Rel_Exp 				{ $$ = $1; } 
/*EqExpEQ*/			| Eq_Exp "==" Rel_Exp 	{ $$ = make_No(is_EqExpEQ, ins_No($1, ins_No($3, NULL)), NULL); }
/*EqExpNE*/			| Eq_Exp "!=" Rel_Exp	{ $$ = make_No(is_EqExpNE, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Log_And_Exp 	
/*LogAndExpEq*/		: Eq_Exp 					{ $$ = $1; } 
/*LogAndExpAnd*/	| Log_And_Exp "&&" Eq_Exp 	{ $$ = make_No(is_LogAndExpAnd, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Log_Or_Exp 	
/*LogOrExpLogAnd*/	: Log_And_Exp 					{ $$ = $1; } 
/*LogOrExpLogOr*/	| Log_Or_Exp "||" Log_And_Exp 	{ $$ = make_No(is_LogOrExpLogOr, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Expression 	
/*ExpLogOr*/		: Log_Or_Exp 												{ $$ = $1; } 
/*ExpAss*/			| _IDENT_ Assign_Operator Expression						{ $$ = make_No(is_ExpAssGraph, ins_No($2, ins_No($3, NULL)), ins_Args_Ident(Is_Ident, $1, NULL));
																				  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
/*ExpAssGraph*/		| _IDENT_ Assign_Operator "(" Expression "," Expression ")" { $$ = make_No(is_ExpAssGraph, ins_No($2, ins_No($4, ins_No($6, NULL))), ins_Args_Ident(Is_Ident, $1, NULL));
																				  if(!SymbolTable_lookup($1)){ yyerror("syntax error"); printf("o identificador \"%s\" nao foi declarado\n",$1); } }
					| _IDENT_ error Expression 									{ printf("Sem operador de atribuição"); }
					| _IDENT_ error "(" Expression "," Expression ")" 			{ printf("Sem operador de atribuição"); }
					;
	
Init_Decl_List 	
/*IniDecListIni*/	: Init_Declarator						{ $$ = make_No(is_IniDecListIni, ins_No($1, NULL), NULL); } 
/*IniDecList*/		| Init_Decl_List "," Init_Declarator 	{ $$ = make_No(is_IniDecList, ins_No($1, ins_No($3, NULL)), NULL); }
					;
	
Init_Declarator 	
/*IniDecId*/		: _IDENT_ 								{ $$ = make_No(is_IniDecId, NULL, ins_Args_Ident(Is_Ident, $1, NULL)); } 
/*IniDecIdE*/		| _IDENT_ Assign_Operator Log_Or_Exp 	{ $$ = make_No(is_IniDecIdE, ins_No($2, ins_No($3, NULL)), ins_Args_Ident(Is_Ident, $1, NULL)); }
					;
	
Var_Declaration 	
/*VarDec*/			: Type Init_Decl_List ";" 	{ $$ = make_No(is_VarDec, ins_No($1, ins_No($2, NULL)), NULL); SymbolTable_ins_VarList($1, $2, yy_mylinenumber+1, yy_mycolumnnumber); } 
					| error Init_Decl_List ";" 	{ printf("Declarações de variáveis devem ser feitas no início do bloco.\n"); }
					;
	
Var_Decl_List 	
/*VarDecListVar*/	: Var_Declaration 				{ $$ = $1; } 
/*VarDecList*/		| Var_Decl_List Var_Declaration { $$ = make_No(is_VarDecList, ins_No($1, ins_No($2, NULL)), NULL); }
					;
	
Parameter_List 	
/*ParamListId*/		: Type _IDENT_ 						{ $$ = make_No(is_ParamListId, ins_No($1, NULL), ins_Args_Ident(Is_Ident, $2, NULL)); } 
/*ParamList*/		| Parameter_List "," Type _IDENT_ 	{ $$ = make_No(is_ParamList, ins_No($1, ins_No($3, NULL)), ins_Args_Ident(Is_Ident, $4, NULL)); }
					;
	
Statement_List 	
/*StmListStm*/		: Statement 				{ $$ = $1; } 
/*StmList*/			| Statement_List Statement 	{ $$ = make_No(is_StmList, ins_No($1, ins_No($2, NULL)), NULL); }
					;
	
Statement 	
/*StmOpen*/			: Open_Stm 		{ $$ = $1; } 
/*StmClosed*/		| Closed_Stm 	{ $$ = $1; }
					;
	
Open_Stm 	
/*OpnStmIfSmp*/		: "if" "(" Expression ")" Simple_Stm 					{ $$ = make_No(is_OpnStmIfSmp, ins_No($3, ins_No($5, NULL)), NULL); } 
/*OpnStmIfOpn*/		| "if" "(" Expression ")" Open_Stm 						{ $$ = make_No(is_OpnStmIfOpn, ins_No($3, ins_No($5, NULL)), NULL); }
/*OpnStmIfCls*/		| "if" "(" Expression ")" Closed_Stm "else" Open_Stm 	{ $$ = make_No(is_OpnStmIfCls, ins_No($3, ins_No($5, ins_No($7, NULL))), NULL); }
/*OpnStmWhile*/		| "while" "(" Expression ")" Open_Stm 					{ $$ = make_No(is_OpnStmWhile, ins_No($3, ins_No($5, NULL)), NULL); }
					| "if" "(" error ")" Simple_Stm 						{ printf("If sem expressao"); } 
					| "if" "(" error ")" Open_Stm 							{ printf("If sem expressao"); }
					| "if" "(" error ")" Closed_Stm "else" Open_Stm 		{ printf("If sem expressao"); } 
					| "while" "(" error ")" Open_Stm 						{ printf("While sem expressao"); }
					;
	
Block_Stm 	
/*BlkStm*/			: "{" "}"								{ $$ = make_No(is_BlkStm, NULL, NULL); } 
/*BlkStmList*/		| "{" Statement_List "}"				{ $$ = $2; }
/*BlkStmVar*/		| "{" Var_Decl_List "}"					{ $$ = $2; }
/*BlkStmVarStm*/	| "{" Var_Decl_List Statement_List "}"	{ $$ = make_No(is_BlkStmVarStm, ins_No($2, ins_No($3, NULL)), NULL); }
					;
	
Return_Stm 	
/*RetStmRet*/		: "return" ";"				{ $$ = make_No(is_RetStmRet, NULL, NULL); } 
/*RetStmExp*/		| "return" Expression ";"	{ $$ = make_No(is_RetStmExp, ins_No($2, NULL), NULL); }
					;
	
Exp_Stm 	
/*ExpStmNul*/		: ";"				{ $$ = make_No(is_ExpStmNul, NULL, NULL); } 
/*ExpStmExp*/		| Expression ";" 	{ $$ = make_No(is_ExpStmExp, ins_No($1, NULL), NULL); }
					;
	
Closed_Stm 	
/*ClosedStmSmp*/	: Simple_Stm 											{ $$ = $1; } 
/*ClosedStmIf*/		| "if" "(" Expression ")" Closed_Stm "else" Closed_Stm	{ $$ = make_No(is_ClosedStmIf, ins_No($3, ins_No($5, ins_No($7, NULL))), NULL); }
/*ClosedStmWhile*/	| "while" "(" Expression ")" Closed_Stm 				{ $$ = make_No(is_ClosedStmWhile, ins_No($3, ins_No($5, NULL)), NULL); }
					| "if" "(" error ")" Closed_Stm "else" Closed_Stm 		{ printf("If sem expressao"); }
					| "while" "(" error ")" Closed_Stm 						{ printf("While sem expressao"); }
					;
	
Simple_Stm 	
/*SmpStmBlock*/		: Block_Stm { $$ = $1; } 
/*SmpStmExp*/		| Exp_Stm { $$ = $1; }
/*SmpStmRet*/		| Return_Stm { $$ = $1; }
					;
	
Declarator 	
/*DecIdParam*/		: _IDENT_ "(" Parameter_List ")"	{ $$ = make_No(is_DecIdParam, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL)); recent_identifier = $1; recent_identifier_index = 0; 
														  SymbolTable_ins_Fun( $1, yy_mylinenumber+1, yy_mycolumnnumber, recent_type, $3); } 
/*DecId*/			| _IDENT_ "(" ")" 					{ $$ = make_No(is_DecId, NULL, ins_Args_Ident(Is_Ident, $1, NULL)); recent_identifier = $1; recent_identifier_index = 0;
														  SymbolTable_ins_Fun( $1, yy_mylinenumber+1, yy_mycolumnnumber, recent_type, NULL); }
					| error "(" Parameter_List ")" 		{ printf("Declaracao de funcao sem identificador"); }
					| error "(" ")" 					{ printf("Declaracao de funcao sem identificador"); }
					;
	
Function_Def 	
/*FunDef*/			: Type Declarator Block_Stm	{ $$ = make_No(is_FunDef, ins_No($1, ins_No($2, ins_No($3, NULL))), NULL); }
					;
	
Ext_Var_Decl 	
/*ExtVarDecFun*/	: Function_Def 		{ $$ = $1; } 
/*ExtVarDecVar*/	| Var_Declaration 	{ $$ = $1; }
					;
