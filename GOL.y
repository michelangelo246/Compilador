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

int yy_mylinenumber = 1;
int yy_mycolumnnumber = 1;

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
	str, GOLtext, yy_mylinenumber, (int)(yy_mycolumnnumber - strlen(GOLtext)));
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
/*TraUniList*/		| Trans_Unit Ext_Var_Decl	{ $$ = make_No(is_TraUniList, ins_No($1, ins_No($2, NULL)), NULL, Is_TypeVoid); 
												  YY_RESULT_Trans_Unit_= $$; }
					;

Assign_Operator 
/*AssOpEQ*/			: "="	{ $$ = make_No(is_AssOpEQ, NULL, NULL, Is_TypeVoid); } 
/*AssOpINS*/		| "<<"	{ $$ = make_No(is_AssOpINS, NULL, NULL, Is_TypeVoid); }
					;
	
Constant 	
/*ConstInt*/		: _INTEGER_	{ $$ = make_No(is_ConstInt, NULL, ins_Args_Int(is_ConstInt, $1, NULL), Is_TypeInt); 
								  SymbolTable_ins_ConstInt($1, yy_mylinenumber, yy_mycolumnnumber); } 
/*ConstDouble*/		| _DOUBLE_	{ $$ = make_No(is_ConstDouble, NULL, ins_Args_Double(is_ConstDouble, $1, NULL), Is_TypeDouble); 
								  SymbolTable_ins_ConstDouble($1, yy_mylinenumber, yy_mycolumnnumber); }
/*ConstStr*/		| _STRING_	{ $$ = make_No(is_ConstStr, NULL, ins_Args_Str(is_ConstStr, $1, NULL), Is_TypeString); 
								  SymbolTable_ins_constStr($1, yy_mylinenumber, yy_mycolumnnumber); }
					;
	
Unary_Operator 	
/*UnaOpMinus*/		: "-"	{ $$ = make_No(is_UnaOpMinus, NULL, NULL, Is_TypeVoid); } 
/*UnaOpNot*/		| "!"	{ $$ = make_No(is_UnaOpNot, NULL, NULL, Is_TypeVoid); }
					;
	
Type 	
/*TypeVoid*/		: "void"	{ $$ = make_No(is_TypeVoid, NULL, NULL, Is_TypeVoid); } 
/*TypeInt*/			| "int" 	{ $$ = make_No(is_TypeInt, NULL, NULL, Is_TypeInt); }
/*TypeDouble*/		| "double" 	{ $$ = make_No(is_TypeDouble, NULL, NULL, Is_TypeDouble); }
/*TypeGraph*/		| "graph" 	{ $$ = make_No(is_TypeGraph, NULL, NULL, Is_TypeGraph); }
					;
	
Arg_Exp_List 	
/*ArgExpListExp*/	: Expression 					{ $$ = $1; } 
/*ArgExpList*/		| Arg_Exp_List "," Expression 	{ $$ = make_No(is_ArgExpList, ins_No($1, ins_No($3, NULL)), NULL, $3->type); }
					;
	
Primary_Exp 	
/*PriExpId*/		: _IDENT_				{ 
												$$ = make_No(is_PriExpId, NULL, ins_Args_Ident(Is_Ident, $1, NULL), (SymbolTable_lookup($1).linha?SymbolTable_lookup($1).linha->u.ident.Type:Is_TypeVoid));
												if(!SymbolTable_lookup($1).linha)
												{//erro ao referenciar identificador nao declarado
													yyerror("error"); 
													printf("o identificador \"%s\" nao foi declarado\n",$1);
												}
											}
/*PriExpConst*/		| Constant 				{ $$ = $1; }
/*PriExpExp*/		| "(" Expression ")" 	{ $$ = $2; }
					;

Posfix_Exp 	
/*PosExpPri*/		: Primary_Exp 					{ $$ = $1; } 
/*PosExpSub*/		| _IDENT_ "[" Primary_Exp "]" 	{
														$$ = make_No(is_PosExpSub, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL), Is_TypeGraph);
													  	Table_Line *linha = SymbolTable_lookup($1).linha;
														if(!linha)
														{//erro ao referenciar identificador nao declarado
															yyerror("error"); 
															printf("o identificador \"%s\" nao foi declarado\n",$1);
														}
														else if(linha->u.ident.Type != Is_TypeGraph)
														{
															yyerror("error"); 
															printf("Operador aplicado a identificador de tipo incorreto. Esperado: 'graph', Usado: '%s'\n",printType(linha->u.ident.Type));
														}
													  	if($3->type != Is_TypeGraph)
														{//erro ao utilizar operação utilizando tipo diferente de grafo
															yyerror("error"); 
															printf("A operacao espera uma expressao do tipo 'graph'\n"); 
														} 
													}
/*PosExpIn*/		| _IDENT_ "@" Primary_Exp "#" 	{
														$$ = make_No(is_PosExpIn, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL), Is_TypeInt);
													  	Table_Line *linha = SymbolTable_lookup($1).linha;
														if(!linha)
														{//erro ao referenciar identificador nao declarado
															yyerror("error"); 
															printf("o identificador \"%s\" nao foi declarado\n",$1);
														}
														else if(linha->u.ident.Type != Is_TypeGraph)
														{
															yyerror("error"); 
															printf("Operador aplicado a identificador de tipo incorreto. Esperado: 'graph', Usado: '%s'\n",printType(linha->u.ident.Type));
														}
													  	if($3->type != Is_TypeInt)
														{ //erro ao utilizar operação utilizando tipo diferente de int
															yyerror("error");
															printf("A operacao espera uma expressao do tipo 'int'\n");
														}
													}
/*PosExpOut*/		| _IDENT_ "#" Primary_Exp "@" 	{
														$$ = make_No(is_PosExpOut, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL), Is_TypeInt);
													  	Table_Line *linha = SymbolTable_lookup($1).linha;
														if(!linha)
														{//erro ao referenciar identificador nao declarado
															yyerror("error"); 
															printf("o identificador \"%s\" nao foi declarado\n",$1);
														}
														else if(linha->u.ident.Type != Is_TypeGraph)
														{
															yyerror("error"); 
															printf("Operador aplicado a identificador de tipo incorreto. Esperado: 'graph', Usado: '%s'\n",printType(linha->u.ident.Type));
														}
													  	if($3->type != Is_TypeInt)
														{ //erro ao utilizar operação utilizando tipo diferente de int
															yyerror("error"); 
															printf("A operacao espera uma expressao do tipo 'int'\n"); 
														}
													}
/*PosExpNeig*/		| _IDENT_ "&" Primary_Exp "&" 	{
														$$ = make_No(is_PosExpNeig, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL), Is_TypeGraph);
													  	Table_Line *linha = SymbolTable_lookup($1).linha;
														if(!linha)
														{//erro ao referenciar identificador nao declarado
															yyerror("error"); 
															printf("o identificador \"%s\" nao foi declarado\n",$1);
														}
														else if(linha->u.ident.Type != Is_TypeGraph)
														{
															yyerror("error"); 
															printf("Operador aplicado a identificador de tipo incorreto. Esperado: 'graph', Usado: '%s'\n",printType(linha->u.ident.Type));
														}
													  	if($3->type != Is_TypeInt)
														{ 
															yyerror("error"); 
															printf("A operacao espera uma expressao do tipo 'int'\n"); 
														}
													}
/*PosExpCal*/		| _IDENT_ "(" ")" 			  	{
														$$ = make_No(is_PosExpCal, NULL, ins_Args_Ident(Is_Ident, $1, NULL), (SymbolTable_lookup($1).linha?SymbolTable_lookup($1).linha->u.ident.Type:Is_TypeVoid)); 
													  	Table_Line *linha = SymbolTable_lookup($1).linha;
														if(!linha)
														{//erro ao referenciar identificador nao declarado
															yyerror("error"); 
															printf("o identificador \"%s\" nao foi declarado\n",$1);
														}
														else if(linha->u.ident.param != NULL)
														{//funcao chamada precisa de argumentos
															yyerror("error"); 
															printf("Função chamada com número incorreto de argumentos. Argumentos esperados: (");
															Function_Param *param = linha->u.ident.param;
															while(param)
															{
																printf("%s",printType(param->Type));
																if(param->next) printf(", ");
																param = param->next;
															}
															printf(")\n");
														}
													}
/*PosExpCalArg*/	| _IDENT_ "(" Arg_Exp_List ")"  {
														$$ = make_No(is_PosExpCalArg, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL), (SymbolTable_lookup($1).linha?SymbolTable_lookup($1).linha->u.ident.Type:Is_TypeVoid));
													  	Table_Line *linha = SymbolTable_lookup($1).linha;
														if(!linha)
														{//erro ao referenciar identificador nao declarado
															yyerror("error"); 
															printf("o identificador \"%s\" nao foi declarado\n",$1);
														}
														else if(linha->u.ident.param != NULL)
														{//funcao chamada precisa de argumentos
															if(!verifica_Params_Args(linha->u.ident.param,$3))
															{//se parametros não batem com número ou tipo de argumentos, reporta erro
																yyerror("error"); 
																printf("Função chamada com número ou tipo incorreto de argumentos. Argumentos esperados: (");
																Function_Param *param = linha->u.ident.param;
																while(param)
																{
																	printf("%s",printType(param->Type));
																	if(param->next) printf(", ");
																	param = param->next;
																}
																printf("), ");
																printf("Argumentos passados: (");
																print_Arg_Exp_List($3);
																printf(")\n");
															}
														}
														else
														{//funcao chamada nao possui parametros
															yyerror("error"); 
															printf("Função chamada com número incorreto de argumentos. Argumentos esperados: nenhum\n");
														}
														
													}
					| _IDENT_ "[" error "]" 		{ printf("sem expressao para subgrafo"); }
					| _IDENT_ "@" error "#" 		{ printf("sem expressao para grau de entrada"); }
					| _IDENT_ "#" error "@" 		{ printf("sem expressao para grau de saida"); }
					| _IDENT_ "&" error "&" 		{ printf("sem expressao para vizinhanca"); }
					;
	
Unary_Exp 	
/*UnaExpPos*/		: Posfix_Exp 				{ $$ = $1; }
/*UnaExpOp*/		| Unary_Operator Unary_Exp	{
													$$ = make_No(is_UnaExpOp, ins_No($1, ins_No($2, NULL)), NULL, $2->type);
													if($1->kind == is_UnaOpMinus)
													{
														if(($2->type != Is_TypeInt) && ($2->type != Is_TypeDouble))
														{
															yyerror("error"); 
															printf("Operador unario '-' com operando de tipo invalido. Esperado: 'int' ou 'double', Usado: '%s'\n", printType($2->type));
														}
													}
													else if($1->kind == is_UnaOpNot)
													{
														if($2->type != Is_TypeBool)
														{
															yyerror("error"); 
															printf("Operador unario '!' com operando de tipo invalido. Esperado: 'bool', Usado: '%s'\n", printType($2->type));
														}
													}
												}
					;
	
Multi_Exp 	
/*MulExpUna*/		: Unary_Exp 				{ $$ = $1; } 
/*MulExpMul*/		| Multi_Exp "*" Unary_Exp 	{ 
													$$ = make_No(is_MulExpMul, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeVoid);
												  	if(($1->type == Is_TypeDouble && $3->type == Is_TypeInt) || ($1->type == Is_TypeInt && $3->type == Is_TypeDouble))
													{//caso algum dos operandos seja double, expressão retorna double
														$$->type = Is_TypeDouble;
													} 
												  	else if((($1->type == Is_TypeInt) && ($3->type == Is_TypeInt))||(($1->type == Is_TypeDouble) && ($3->type == Is_TypeDouble)))
													{//caso ambos operandos sejam int ou double, expressão retorna o tipo de ambos
														$$->type = $1->type; 
													}
												 	else 
													{//caso algum dos operandos não seja nem int nem double, expressão retorna void e reporta erro
														yyerror("error"); 
														printf("operador binario '*' com operandos de tipos invalidos. Esperados: 'int' ou 'double', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
													}
												}
/*MulExpDiv*/		| Multi_Exp "/" Unary_Exp 	{
													$$ = make_No(is_MulExpDiv, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeVoid);
												  	if(($1->type == Is_TypeDouble && $3->type == Is_TypeInt) || ($1->type == Is_TypeInt && $3->type == Is_TypeDouble))
													{//caso algum dos operandos seja double, expressão retorna double
														$$->type = Is_TypeDouble;
													} 
												  	else if((($1->type == Is_TypeInt) && ($3->type == Is_TypeInt))||(($1->type == Is_TypeDouble) && ($3->type == Is_TypeDouble)))
													{//caso ambos operandos sejam int ou double, expressão retorna o tipo de ambos
														$$->type = $1->type; 
													}
												 	else 
													{//caso algum dos operandos não seja nem int nem double, expressão retorna void e reporta erro
														yyerror("error"); 
														printf("operador binario '/' com operandos de tipos invalidos. Esperados: 'int' ou 'double', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
													}
												}
					;
	
Add_Exp 	
/*AddExpMul*/		: Multi_Exp 			{ $$ = $1; } 
/*AddExpAdd*/		| Add_Exp "+" Multi_Exp	{ 
												$$ = make_No(is_AddExpAdd, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeVoid);
												if(($1->type == Is_TypeDouble && $3->type == Is_TypeInt) || ($1->type == Is_TypeInt && $3->type == Is_TypeDouble))
												{//caso algum dos operandos seja double, expressão retorna double
													$$->type = Is_TypeDouble;
												} 
												else if((($1->type == Is_TypeInt) && ($3->type == Is_TypeInt))||(($1->type == Is_TypeDouble) && ($3->type == Is_TypeDouble)))
												{//caso ambos operandos sejam int ou double, expressão retorna o tipo de ambos
													$$->type = $1->type; 
												}
												else 
												{//caso algum dos operandos não seja nem int nem double, expressão retorna void e reporta erro
													yyerror("error"); 
													printf("operador binario '+' com operandos de tipos invalidos. Esperados: 'int' ou 'double', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
												}
											}
/*AddExpSub*/		| Add_Exp "-" Multi_Exp	{
												$$ = make_No(is_AddExpSub, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeVoid); 
												if(($1->type == Is_TypeDouble && $3->type == Is_TypeInt) || ($1->type == Is_TypeInt && $3->type == Is_TypeDouble))
												{//caso algum dos operandos seja double, expressão retorna double
													$$->type = Is_TypeDouble;
												} 
												else if((($1->type == Is_TypeInt) && ($3->type == Is_TypeInt))||(($1->type == Is_TypeDouble) && ($3->type == Is_TypeDouble)))
												{//caso ambos operandos sejam int ou double, expressão retorna o tipo de ambos
													$$->type = $1->type; 
												}
												else 
												{//caso algum dos operandos não seja nem int nem double, expressão retorna void e reporta erro
													yyerror("error"); 
													printf("operador binario '-' com operandos de tipos invalidos. Esperados: 'int' ou 'double', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
												}
											}
					;
	
Rel_Exp 	
/*RelExpAdd*/		: Add_Exp 				{ $$ = $1; } 
/*RelExpLT*/		| Rel_Exp "<" Add_Exp 	{ 
												$$ = make_No(is_RelExpLT, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool); 
											  	if((($1->type != Is_TypeInt) && ($1->type != Is_TypeDouble)) || (($3->type != Is_TypeInt) && ($3->type != Is_TypeDouble)))
											  	{//caso algum dos operandos não seja nem int nem double, reporta erro
													yyerror("error"); 
													printf("operador binario '<' com operandos de tipos invalidos. Esperado: 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
												}
											}
/*RelExpGT*/		| Rel_Exp ">" Add_Exp 	{
												$$ = make_No(is_RelExpGT, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool); 
											  	if((($1->type != Is_TypeInt) && ($1->type != Is_TypeDouble)) || (($3->type != Is_TypeInt) && ($3->type != Is_TypeDouble)))
											  	{//caso algum dos operandos não seja nem int nem double, reporta erro
													yyerror("error"); 
													printf("operador binario '>' com operandos de tipos invalidos. Esperado: 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
												}
											}
/*RelExpLE*/		| Rel_Exp "<=" Add_Exp 	{
												$$ = make_No(is_RelExpLE, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool); 
											  	if((($1->type != Is_TypeInt) && ($1->type != Is_TypeDouble)) || (($3->type != Is_TypeInt) && ($3->type != Is_TypeDouble)))
											  	{//caso algum dos operandos não seja nem int nem double, reporta erro
													yyerror("error"); 
													printf("operador binario '<=' com operandos de tipos invalidos. Esperado: 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
												}
											}
/*RelExpGE*/		| Rel_Exp ">=" Add_Exp 	{
												$$ = make_No(is_RelExpGE, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool); 
											  	if((($1->type != Is_TypeInt) && ($1->type != Is_TypeDouble)) || (($3->type != Is_TypeInt) && ($3->type != Is_TypeDouble)))
											  	{//caso algum dos operandos não seja nem int nem double, reporta erro
													yyerror("error"); 
													printf("operador binario '>=' com operandos de tipos invalidos. Esperado: 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
												}
											}
					;
	
Eq_Exp 	
/*EqExpRel*/		: Rel_Exp 				{ $$ = $1; } 
/*EqExpEQ*/			| Eq_Exp "==" Rel_Exp 	{ 
												$$ = make_No(is_EqExpEQ, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool);
												if(($1->type != $3->type) && (($1->type != Is_TypeInt && $1->type != Is_TypeDouble)||($3->type != Is_TypeInt && $3->type != Is_TypeDouble)))
												{//se os tipos forem diferentes e, ou $1 nao for nem 'int' e nem 'double' ou $3 nao for nem 'int' e nem 'double', reporta erro
													if($1->type != $3->type)
													{
														yyerror("error"); 
														printf("operador binario '==' com operandos de tipos diferentes. Tipo usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
													}
													else
													{
														yyerror("error"); 
														printf("operador binario '==' com operandos de tipos invalidos. Esperados: 'int', 'double' ou 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
													}
												}
											}
/*EqExpNE*/			| Eq_Exp "!=" Rel_Exp	{
												$$ = make_No(is_EqExpNE, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool);
												if(($1->type != $3->type) && (($1->type != Is_TypeInt && $1->type != Is_TypeDouble)||($3->type != Is_TypeInt && $3->type != Is_TypeDouble)))
												{//se os tipos forem diferentes e, ou $1 nao for nem 'int' e nem 'double' ou $3 nao for nem 'int' e nem 'double', reporta erro
													if($1->type != $3->type)
													{
														yyerror("error"); 
														printf("operador binario '!=' com operandos de tipos diferentes. Tipo usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
													}
													else
													{
														yyerror("error"); 
														printf("operador binario '!=' com operandos de tipos invalidos. Esperados: 'int', 'double' ou 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
													}
												}
											}
					;
	
Log_And_Exp 	
/*LogAndExpEq*/		: Eq_Exp 					{ $$ = $1; } 
/*LogAndExpAnd*/	| Log_And_Exp "&&" Eq_Exp 	{
													$$ = make_No(is_LogAndExpAnd, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool);
													if($1->type != Is_TypeBool || $3->type != Is_TypeBool)
													{//se algum operando não for booleano, reporta erro
														yyerror("error"); 
														printf("operador binario '&&' com operandos de tipos invalidos. Esperados: 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
													}
												}
					;
	
Log_Or_Exp 	
/*LogOrExpLogAnd*/	: Log_And_Exp 					{ $$ = $1; } 
/*LogOrExpLogOr*/	| Log_Or_Exp "||" Log_And_Exp 	{
														$$ = make_No(is_LogOrExpLogOr, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeBool);
														if($1->type != Is_TypeBool || $3->type != Is_TypeBool)
														{//se algum operando não for booleano, reporta erro
															yyerror("error"); 
															printf("operador binario '||' com operandos de tipos invalidos. Esperados: 'bool', Usados: '%s' e '%s'\n",printType($1->type), printType($3->type));
														}
													}
					;
	
Expression 	
/*ExpLogOr*/		: Log_Or_Exp 												{ $$ = $1; } 
/*ExpAss*/			| _IDENT_ Assign_Operator Expression						{
																					$$ = make_No(is_ExpAss, ins_No($2, ins_No($3, NULL)), ins_Args_Ident(Is_Ident, $1, NULL), (SymbolTable_lookup($1).linha?SymbolTable_lookup($1).linha->u.ident.Type:Is_TypeVoid));
																					Table_Line *linha = SymbolTable_lookup($1).linha;
																					if(!linha)
																					{//erro ao referenciar identificador nao declarado
																						yyerror("error"); 
																						printf("o identificador \"%s\" nao foi declarado\n",$1);
																					} 
																					else
																					{
																						if(linha->u.ident.Type != $3->type)
																						{//se tipo de operandos forem distintos
																							if(((linha->u.ident.Type != Is_TypeInt)&&(linha->u.ident.Type != Is_TypeDouble))||(($3->type != Is_TypeInt)&&($3->type != Is_TypeDouble)))
																							{//e algum dos dois for diferente de int e double
																								yyerror("error"); 
																								printf("Atribuição com tipos distintos. Tipos usados: '%s' e '%s'\n",printType(linha->u.ident.Type), printType($3->type));
																							}
																						}
																					}
																				}
/*ExpAssGraph*/		| _IDENT_ Assign_Operator "(" Expression "," Expression ")" {
																					$$ = make_No(is_ExpAssGraph, ins_No($2, ins_No($4, ins_No($6, NULL))), ins_Args_Ident(Is_Ident, $1, NULL), (SymbolTable_lookup($1).linha?SymbolTable_lookup($1).linha->u.ident.Type:Is_TypeVoid));
																					Table_Line *linha = SymbolTable_lookup($1).linha;
																					if(!linha)
																					{//erro ao referenciar identificador nao declarado
																						yyerror("error"); 
																						printf("o identificador \"%s\" nao foi declarado\n",$1);
																					} 
																					else
																					{
																						if((($4->type != Is_TypeInt) && ($4->type != Is_TypeDouble)) || (($6->type != Is_TypeInt) && ($6->type != Is_TypeDouble)))
																						{//se alguma das expressões não forem nem int nem double, reporta erro
																							yyerror("error"); 
																							printf("Inserção de arestas utilizando expressões com tipo não suportado. Esperado: 'int' ou 'double', Usados: '%s' e '%s'\n", printType($4->type), printType($6->type));
																						}
																					}
																					if(linha->u.ident.Type != Is_TypeGraph)
																					{
																						yyerror("error"); 
																						printf("Operador de inserção de arestas aplicado a identificador de tipo não suportado. Esperado: 'graph', Usado: '%s'\n", printType(linha->u.ident.Type));
																					}
																				}
					| _IDENT_ error Expression 									{ printf("Sem operador de atribuição\n"); }
					| _IDENT_ error "(" Expression "," Expression ")" 			{ printf("Sem operador de atribuição\n"); }
					;
	
Init_Decl_List 	
/*IniDecListIni*/	: Init_Declarator						{ $$ = make_No(is_IniDecListIni, ins_No($1, NULL), NULL, Is_TypeVoid); } 
/*IniDecList*/		| Init_Decl_List "," Init_Declarator 	{ $$ = make_No(is_IniDecList, ins_No($1, ins_No($3, NULL)), NULL, Is_TypeVoid); }
					;
	
Init_Declarator 	
/*IniDecId*/		: _IDENT_ 								{
																$$ = make_No(is_IniDecId, NULL, ins_Args_Ident(Is_Ident, $1, NULL), Is_TypeVoid); 
															  	LookUp_Return retorno = SymbolTable_lookup($1);
																if(retorno.contexto == SymbolTable)
																{
																	yyerror("error"); 
															  		printf("o identificador \"%s\" já foi declarado anteriormente, linha: %d coluna: %d\n",$1,
																	 retorno.linha->u.ident.line, retorno.linha->u.ident.column);
																}
															  	SymbolTable_ins_Var($1, yy_mylinenumber, yy_mycolumnnumber-1, recent_type);
															}
/*IniDecIdE*/		| _IDENT_ Assign_Operator Log_Or_Exp 	{
																$$ = make_No(is_IniDecIdE, ins_No($2, ins_No($3, NULL)), ins_Args_Ident(Is_Ident, $1, NULL), Is_TypeVoid); 
															  	LookUp_Return retorno = SymbolTable_lookup($1);
															  	if(retorno.contexto == SymbolTable)
																{
																	yyerror("error"); 
															  		printf("o identificador \"%s\" já foi declarado anteriormente, linha: %d coluna: %d\n",$1,
																	 retorno.linha->u.ident.line, retorno.linha->u.ident.column);
																}
															  	SymbolTable_ins_Var($1, yy_mylinenumber, yy_mycolumnnumber-1, recent_type);
																Table_Line *linha = SymbolTable_lookup($1).linha;
																if(linha->u.ident.Type != $3->type)
																{//se tipo de operandos forem distintos
																	if(((linha->u.ident.Type != Is_TypeInt)&&(linha->u.ident.Type != Is_TypeDouble))||(($3->type != Is_TypeInt)&&($3->type != Is_TypeDouble)))
																	{//e algum dos dois for diferente de int e double
																		yyerror("error"); 
																		printf("Atribuição com tipos distintos. Tipos usados: '%s' e '%s'\n",printType(linha->u.ident.Type), printType($3->type));
																	}
																}
															}
					;
	
Var_Declaration 	
/*VarDec*/			: Type Init_Decl_List ";" 	{ $$ = make_No(is_VarDec, ins_No($1, ins_No($2, NULL)), NULL, Is_TypeVoid); } 
					| error Init_Decl_List ";" 	{ printf("Declarações de variáveis devem ser feitas no início do bloco.\n"); }
					;
	
Var_Decl_List 	
/*VarDecListVar*/	: Var_Declaration 				{ $$ = $1; } 
/*VarDecList*/		| Var_Decl_List Var_Declaration { $$ = make_No(is_VarDecList, ins_No($1, ins_No($2, NULL)), NULL, Is_TypeVoid); }
					;
	
Parameter_List 	
/*ParamListId*/		: Type _IDENT_ 						{ $$ = make_No(is_ParamListId, ins_No($1, NULL), ins_Args_Ident(Is_Ident, $2, NULL), Is_TypeVoid); } 
/*ParamList*/		| Parameter_List "," Type _IDENT_ 	{ $$ = make_No(is_ParamList, ins_No($1, ins_No($3, NULL)), ins_Args_Ident(Is_Ident, $4, NULL), Is_TypeVoid); }
					;
	
Statement_List 	
/*StmListStm*/		: Statement 				{ $$ = $1; } 
/*StmList*/			| Statement_List Statement 	{ $$ = make_No(is_StmList, ins_No($1, ins_No($2, NULL)), NULL, Is_TypeVoid); }
					;
	
Statement 	
/*StmOpen*/			: Open_Stm 		{ $$ = $1; } 
/*StmClosed*/		| Closed_Stm 	{ $$ = $1; }
					;
	
Open_Stm 	
/*OpnStmIfSmp*/		: "if" "(" Expression ")" Simple_Stm 					{
																				$$ = make_No(is_OpnStmIfSmp, ins_No($3, ins_No($5, NULL)), NULL, Is_TypeVoid);
																				if($3->type != Is_TypeBool)
																				{//se condição do if não é booleana, reporta erro.
																					yyerror("error"); 
																					printf("Condição do 'if' não é do tipo 'bool'. Tipo usado: '%s' \n",printType($3->type));
																				}
																			} 
/*OpnStmIfOpn*/		| "if" "(" Expression ")" Open_Stm 						{
																				$$ = make_No(is_OpnStmIfOpn, ins_No($3, ins_No($5, NULL)), NULL, Is_TypeVoid);
																				if($3->type != Is_TypeBool)
																				{//se condição do if não é booleana, reporta erro.
																					yyerror("error"); 
																					printf("Condição do 'if' não é do tipo 'bool'. Tipo usado: '%s' \n",printType($3->type));
																				}
																			}
/*OpnStmIfCls*/		| "if" "(" Expression ")" Closed_Stm "else" Open_Stm 	{
																				$$ = make_No(is_OpnStmIfCls, ins_No($3, ins_No($5, ins_No($7, NULL))), NULL, Is_TypeVoid);
																				if($3->type != Is_TypeBool)
																				{//se condição do if não é booleana, reporta erro.
																					yyerror("error"); 
																					printf("Condição do 'if' não é do tipo 'bool'. Tipo usado: '%s' \n",printType($3->type));
																				}
																			}
/*OpnStmWhile*/		| "while" "(" Expression ")" Open_Stm 					{
																				$$ = make_No(is_OpnStmWhile, ins_No($3, ins_No($5, NULL)), NULL, Is_TypeVoid);
																				if($3->type != Is_TypeBool)
																				{//se condição do while não é booleana, reporta erro.
																					yyerror("error"); 
																					printf("Condição do 'while' não é do tipo 'bool'. Tipo usado: '%s' \n",printType($3->type));
																				}
																			}
					| "if" "(" error ")" Simple_Stm 						{ printf("If sem expressao"); } 
					| "if" "(" error ")" Open_Stm 							{ printf("If sem expressao"); }
					| "if" "(" error ")" Closed_Stm "else" Open_Stm 		{ printf("If sem expressao"); } 
					| "while" "(" error ")" Open_Stm 						{ printf("While sem expressao"); }
					;
	
Block_Stm 	
/*BlkStm*/			: "{" "}"								{ $$ = make_No(is_BlkStm, NULL, NULL, Is_TypeVoid); } 
/*BlkStmList*/		| "{" Statement_List "}"				{ $$ = $2; }
/*BlkStmVar*/		| "{" Var_Decl_List "}"					{ $$ = $2; }
/*BlkStmVarStm*/	| "{" Var_Decl_List Statement_List "}"	{ $$ = make_No(is_BlkStmVarStm, ins_No($2, ins_No($3, NULL)), NULL, Is_TypeVoid); }
					;
	
/*verifica se tipo de ret é igual ao da funcao*/
Return_Stm 	
/*RetStmRet*/		: "return" ";"				{
													$$ = make_No(is_RetStmRet, NULL, NULL, Is_TypeVoid);
													Table_Line *linha= SymbolTable_lookup(SymbolTable->name).linha;
													if(linha->u.ident.Type != Is_TypeVoid)
													{//caso haja retorno vazio em função cujo tipo é diferente de void, reporta erro
														yyerror("error"); 
														printf("Função retornando tipo diferente de sua declaração. Tipo Esperado: '%s', Tipo usado: 'void' \n", printType(linha->u.ident.Type));
													}
												} 
/*RetStmExp*/		| "return" Expression ";"	{
													$$ = make_No(is_RetStmExp, ins_No($2, NULL), NULL, $2->type);
													Table_Line *linha= SymbolTable_lookup(SymbolTable->name).linha;
													if(linha->u.ident.Type != $2->type)
													{//caso haja retorno de expressão em função com tipo diferente da declaração, reporta erro
														yyerror("error"); 
														printf("Função retornando tipo diferente de sua declaração. Tipo Esperado: '%s', Tipo usado: '%s' \n", printType(linha->u.ident.Type),printType($2->type));
													}
												}
					;
	
Exp_Stm 	
/*ExpStmNul*/		: ";"				{ $$ = make_No(is_ExpStmNul, NULL, NULL, Is_TypeVoid); } 
/*ExpStmExp*/		| Expression ";" 	{ $$ = $1; }
					;
	
Closed_Stm 	
/*ClosedStmSmp*/	: Simple_Stm 											{ $$ = $1; } 
/*ClosedStmIf*/		| "if" "(" Expression ")" Closed_Stm "else" Closed_Stm	{
																				$$ = make_No(is_ClosedStmIf, ins_No($3, ins_No($5, ins_No($7, NULL))), NULL, Is_TypeVoid);
																				if($3->type != Is_TypeBool)
																				{//se condição do if não é booleana, reporta erro.
																					yyerror("error"); 
																					printf("Condição do 'if' não é do tipo 'bool'. Tipo usado: '%s' \n",printType($3->type));
																				}
																			}
/*ClosedStmWhile*/	| "while" "(" Expression ")" Closed_Stm 				{
																				$$ = make_No(is_ClosedStmWhile, ins_No($3, ins_No($5, NULL)), NULL, Is_TypeVoid);
																				if($3->type != Is_TypeBool)
																				{//se condição do while não é booleana, reporta erro.
																					yyerror("error"); 
																					printf("Condição do 'while' não é do tipo 'bool'. Tipo usado: '%s' \n",printType($3->type));
																				}
																			}
					| "if" "(" error ")" Closed_Stm "else" Closed_Stm 		{ printf("If sem expressao"); }
					| "while" "(" error ")" Closed_Stm 						{ printf("While sem expressao"); }
					;
	
Simple_Stm 	
/*SmpStmBlock*/		: Block_Stm { $$ = $1; } 
/*SmpStmExp*/		| Exp_Stm { $$ = $1; }
/*SmpStmRet*/		| Return_Stm { $$ = $1; }
					;
	
Declarator 	
/*DecIdParam*/		: _IDENT_ "(" Parameter_List ")"	{ 
															$$ = make_No(is_DecIdParam, ins_No($3, NULL), ins_Args_Ident(Is_Ident, $1, NULL), Is_TypeVoid); 
															recent_identifier = $1; 
															recent_identifier_index = 0; 
														  	SymbolTable_ins_Fun( $1, yy_mylinenumber, yy_mycolumnnumber, recent_type, $3);
														} 
/*DecId*/			| _IDENT_ "(" ")" 					{ 
															$$ = make_No(is_DecId, NULL, ins_Args_Ident(Is_Ident, $1, NULL),Is_TypeVoid);
														  	recent_identifier = $1; recent_identifier_index = 0;
														  	SymbolTable_ins_Fun( $1, yy_mylinenumber, yy_mycolumnnumber, recent_type, NULL);
														}
					| error "(" Parameter_List ")" 		{ printf("Declaracao de funcao sem identificador"); }
					| error "(" ")" 					{ printf("Declaracao de funcao sem identificador"); }
					;
	
Function_Def 	
/*FunDef*/			: Type Declarator Block_Stm	{ $$ = make_No(is_FunDef, ins_No($1, ins_No($2, ins_No($3, NULL))), NULL, Is_TypeVoid); }
					;
	
Ext_Var_Decl 	
/*ExtVarDecFun*/	: Function_Def 		{ $$ = $1; } 
/*ExtVarDecVar*/	| Var_Declaration 	{ $$ = $1; }
					;
