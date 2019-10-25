/**	Michelangelo da R. Machado - 14/0156089 **/
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
extern int initialize_lexer(FILE * inp);

void yyerror(const char *str)
{
	extern char *GOLtext;
	fprintf(stderr,"Erro: line %d column %d: %s at %s \n",
	yy_mylinenumber + 1, (int)(yy_mycolumnnumber - strlen(GOLtext)), str, GOLtext);
	error = 1;
}

Trans_Unit YY_RESULT_Trans_Unit_ = 0;
Trans_Unit pTrans_Unit(FILE *inp)
{
	initialize_lexer(inp);
	if (yyparse())
	{ /* Failure */
		return 0;
	}
	else
	{ /* Success */
		return YY_RESULT_Trans_Unit_;
	}
}

%}

%union
{
  int int_;
  double double_;
  char* string_;
  Trans_Unit trans_unit_;
  Assign_Operator assign_operator_;
  Constant constant_;
  Unary_Operator unary_operator_;
  Type type_;
  Arg_Exp_List arg_exp_list_;
  Primary_Exp primary_exp_;
  Posfix_Exp posfix_exp_;
  Unary_Exp unary_exp_;
  Multi_Exp multi_exp_;
  Add_Exp add_exp_;
  Rel_Exp rel_exp_;
  Eq_Exp eq_exp_;
  Log_And_Exp log_and_exp_;
  Log_Or_Exp log_or_exp_;
  Expression expression_;
  Init_Decl_List init_decl_list_;
  Init_Declarator init_declarator_;
  Var_Declaration var_declaration_;
  Var_Decl_List var_decl_list_;
  Parameter_List parameter_list_;
  Statement_List statement_list_;
  Statement statement_;
  Open_Stm open_stm_;
  Block_Stm block_stm_;
  Return_Stm return_stm_;
  Exp_Stm exp_stm_;
  Closed_Stm closed_stm_;
  Simple_Stm simple_stm_;
  Declarator declarator_;
  Function_Def function_def_;
  Ext_Var_Decl ext_var_decl_;

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

%type <trans_unit_> Trans_Unit
%type <assign_operator_> Assign_Operator
%type <constant_> Constant
%type <unary_operator_> Unary_Operator
%type <type_> Type
%type <arg_exp_list_> Arg_Exp_List
%type <primary_exp_> Primary_Exp
%type <posfix_exp_> Posfix_Exp
%type <unary_exp_> Unary_Exp
%type <multi_exp_> Multi_Exp
%type <add_exp_> Add_Exp
%type <rel_exp_> Rel_Exp
%type <eq_exp_> Eq_Exp
%type <log_and_exp_> Log_And_Exp
%type <log_or_exp_> Log_Or_Exp
%type <expression_> Expression
%type <init_decl_list_> Init_Decl_List
%type <init_declarator_> Init_Declarator
%type <var_declaration_> Var_Declaration
%type <var_decl_list_> Var_Decl_List
%type <parameter_list_> Parameter_List
%type <statement_list_> Statement_List
%type <statement_> Statement
%type <open_stm_> Open_Stm
%type <block_stm_> Block_Stm
%type <return_stm_> Return_Stm
%type <exp_stm_> Exp_Stm
%type <closed_stm_> Closed_Stm
%type <simple_stm_> Simple_Stm
%type <declarator_> Declarator
%type <function_def_> Function_Def
%type <ext_var_decl_> Ext_Var_Decl

%token<string_> _STRING_
%token<int_> 	_INTEGER_
%token<double_> _DOUBLE_
%token<string_> _IDENT_

%start Trans_Unit
%%
Trans_Unit 
/*TraUniExtVar*/	: Ext_Var_Decl { $$ = make_TraUniExtVar($1); YY_RESULT_Trans_Unit_= $$; } 
/*TraUniList*/		| Trans_Unit Ext_Var_Decl { $$ = make_TraUniList($1, $2); YY_RESULT_Trans_Unit_= $$; }
					;

Assign_Operator 
/*AssOpEQ*/			: "=" { $$ = make_AssOpEQ();  } 
/*AssOpINS*/		| "<<" { $$ = make_AssOpINS();  }
					;
	
Constant 	
/*ConstInt*/		: _INTEGER_ { $$ = make_ConstInt($1); insConstIntSymbol_Table(SymbolTable, $1, yy_mylinenumber+1, yy_mycolumnnumber); } 
/*ConstDouble*/		| _DOUBLE_ { $$ = make_ConstDouble($1); insConstDoubleSymbol_Table(SymbolTable, $1, yy_mylinenumber+1, yy_mycolumnnumber); }
/*ConstStr*/		| _STRING_ { $$ = make_ConstStr($1); insConstStrSymbol_Table(SymbolTable, $1, yy_mylinenumber+1, yy_mycolumnnumber); }
					;
	
Unary_Operator 	
/*UnaOpMinus*/		: "-" { $$ = make_UnaOpMinus();  } 
/*UnaOpNot*/		| "!" { $$ = make_UnaOpNot();  }
					;
	
Type 	
/*TypeVoid*/		: "void" { $$ = make_TypeVoid();  } 
/*TypeInt*/			| "int" { $$ = make_TypeInt();  }
/*TypeDouble*/		| "double" { $$ = make_TypeDouble();  }
/*TypeGraph*/		| "graph" { $$ = make_TypeGraph();  }
					;
	
Arg_Exp_List 	
/*ArgExpListExp*/	: Expression { $$ = make_ArgExpListExp($1);  } 
/*ArgExpList*/		| Arg_Exp_List "," Expression { $$ = make_ArgExpList($1, $3);  }
					;
	
Primary_Exp 	
/*PriExpId*/		: _IDENT_ { $$ = make_PriExpId($1);  } 
/*PriExpConst*/		| Constant { $$ = make_PriExpConst($1);  }
/*PriExpExp*/		| "(" Expression ")" { $$ = make_PriExpExp($2);  }
					;
	
Posfix_Exp 	
/*PosExpPri*/		: Primary_Exp { $$ = make_PosExpPri($1);  } 
/*PosExpSub*/		| _IDENT_ "[" Primary_Exp "]" { $$ = make_PosExpSub($1, $3);  }
/*PosExpIn*/		| _IDENT_ "@" Primary_Exp "#" { $$ = make_PosExpIn($1, $3);  }
/*PosExpOut*/		| _IDENT_ "#" Primary_Exp "@" { $$ = make_PosExpOut($1, $3);  }
/*PosExpNeig*/		| _IDENT_ "&" Primary_Exp "&" { $$ = make_PosExpNeig($1, $3);  }
/*PosExpCal*/		| _IDENT_ "(" ")" { $$ = make_PosExpCal($1);  }
/*PosExpCalArg*/	| _IDENT_ "(" Arg_Exp_List ")" { $$ = make_PosExpCalArg($1, $3);  }
					| _IDENT_ "[" error "]" { yyerror("sem expressao para subgrafo"); }
					| _IDENT_ "@" error "#" { yyerror("sem expressao para grau de entrada"); }
					| _IDENT_ "#" error "@" { yyerror("sem expressao para grau de saida"); }
					| _IDENT_ "&" error "&" { yyerror("sem expressao para vizinhanca"); }
					;
	
Unary_Exp 	
/*UnaExpPos*/		: Posfix_Exp { $$ = make_UnaExpPos($1);  } 
/*UnaExpOp*/		| Unary_Operator Unary_Exp { $$ = make_UnaExpOp($1, $2);  }
					;
	
Multi_Exp 	
/*MulExpUna*/		: Unary_Exp { $$ = make_MulExpUna($1);  } 
/*MulExpMul*/		| Multi_Exp "*" Unary_Exp { $$ = make_MulExpMul($1, $3);  }
/*MulExpDiv*/		| Multi_Exp "/" Unary_Exp { $$ = make_MulExpDiv($1, $3);  }
					;
	
Add_Exp 	
/*AddExpMul*/		: Multi_Exp { $$ = make_AddExpMul($1);  } 
/*AddExpAdd*/		| Add_Exp "+" Multi_Exp { $$ = make_AddExpAdd($1, $3);  }
/*AddExpSub*/		| Add_Exp "-" Multi_Exp { $$ = make_AddExpSub($1, $3);  }
					;
	
Rel_Exp 	
/*RelExpAdd*/		: Add_Exp { $$ = make_RelExpAdd($1);  } 
/*RelExpLT*/		| Rel_Exp "<" Add_Exp { $$ = make_RelExpLT($1, $3);  }
/*RelExpGT*/		| Rel_Exp ">" Add_Exp { $$ = make_RelExpGT($1, $3);  }
/*RelExpLE*/		| Rel_Exp "<=" Add_Exp { $$ = make_RelExpLE($1, $3);  }
/*RelExpGE*/		| Rel_Exp ">=" Add_Exp { $$ = make_RelExpGE($1, $3);  }
					;
	
Eq_Exp 	
/*EqExpRel*/		: Rel_Exp { $$ = make_EqExpRel($1);  } 
/*EqExpEQ*/			| Eq_Exp "==" Rel_Exp { $$ = make_EqExpEQ($1, $3);  }
/*EqExpNE*/			| Eq_Exp "!=" Rel_Exp { $$ = make_EqExpNE($1, $3);  }
					;
	
Log_And_Exp 	
/*LogAndExpEq*/		: Eq_Exp { $$ = make_LogAndExpEq($1);  } 
/*LogAndExpAnd*/	| Log_And_Exp "&&" Eq_Exp { $$ = make_LogAndExpAnd($1, $3);  }
					;
	
Log_Or_Exp 	
/*LogOrExpLogAnd*/	: Log_And_Exp { $$ = make_LogOrExpLogAnd($1);  } 
/*LogOrExpLogOr*/	| Log_Or_Exp "||" Log_And_Exp { $$ = make_LogOrExpLogOr($1, $3);  }
					;
	
Expression 	
/*ExpLogOr*/		: Log_Or_Exp { $$ = make_ExpLogOr($1);  } 
/*ExpAss*/			| _IDENT_ Assign_Operator Expression { $$ = make_ExpAss($1, $2, $3);  }
/*ExpAssGraph*/		| _IDENT_ Assign_Operator "(" Expression "," Expression ")" { $$ = make_ExpAssGraph($1, $2, $4, $6);  }
					| _IDENT_ error Expression { yyerror("Sem operador de atribuição"); }
					| _IDENT_ error "(" Expression "," Expression ")" { yyerror("Sem operador de atribuição"); }
					;
	
Init_Decl_List 	
/*IniDecListIni*/	: Init_Declarator { $$ = make_IniDecListIni($1);  } 
/*IniDecList*/		| Init_Decl_List "," Init_Declarator { $$ = make_IniDecList($1, $3);  }
					;
	
Init_Declarator 	
/*IniDecId*/		: _IDENT_ { $$ = make_IniDecId($1);  } 
/*IniDecIdE*/		| _IDENT_ Assign_Operator Log_Or_Exp { $$ = make_IniDecIdE($1, $2, $3);  }
					;
	
Var_Declaration 	
/*VarDec*/			: Type Init_Decl_List ";" { $$ = make_VarDec($1, $2); insTableSymbol_VarDec($1, $2, yy_mylinenumber+1, yy_mycolumnnumber); } 
					| error Init_Decl_List ";" { yyerror("Sem identificador na declaracao de variavel com inicialização"); }
					;
	
Var_Decl_List 	
/*VarDecListVar*/	: Var_Declaration { $$ = make_VarDecListVar($1);  } 
/*VarDecList*/		| Var_Decl_List Var_Declaration { $$ = make_VarDecList($1, $2);  }
					;
	
Parameter_List 	
/*ParamListId*/		: Type _IDENT_ { $$ = make_ParamListId($1, $2);  } 
/*ParamList*/		| Parameter_List "," Type _IDENT_ { $$ = make_ParamList($1, $3, $4);  }
					;
	
Statement_List 	
/*StmListStm*/		: Statement { $$ = make_StmListStm($1);  } 
/*StmList*/			| Statement_List Statement { $$ = make_StmList($1, $2);  }
					;
	
Statement 	
/*StmOpen*/			: Open_Stm { $$ = make_StmOpen($1);  } 
/*StmClosed*/		| Closed_Stm { $$ = make_StmClosed($1);  }
					;
	
Open_Stm 	
/*OpnStmIfSmp*/		: "if" "(" Expression ")" Simple_Stm { $$ = make_OpnStmIfSmp($3, $5);  } 
/*OpnStmIfOpn*/		| "if" "(" Expression ")" Open_Stm { $$ = make_OpnStmIfOpn($3, $5);  }
/*OpnStmIfCls*/		| "if" "(" Expression ")" Closed_Stm "else" Open_Stm { $$ = make_OpnStmIfCls($3, $5, $7);  }
/*OpnStmWhile*/		| "while" "(" Expression ")" Open_Stm { $$ = make_OpnStmWhile($3, $5);  }
					| "if" "(" error ")" Simple_Stm { yyerror("If sem expressao");  } 
					| "if" "(" error ")" Open_Stm { yyerror("If sem expressao"); }
					| "if" "(" error ")" Closed_Stm "else" Open_Stm { yyerror("If sem expressao"); } 
					| "while" "(" error ")" Open_Stm { yyerror("While sem expressao"); }
					;
	
Block_Stm 	
/*BlkStm*/			: "{" "}" { $$ = make_BlkStm();  } 
/*BlkStmList*/		| "{" Statement_List "}" { $$ = make_BlkStmList($2);  }
/*BlkStmVar*/		| "{" Var_Decl_List "}" { $$ = make_BlkStmVar($2);  }
/*BlkStmVarStm*/	| "{" Var_Decl_List Statement_List "}" { $$ = make_BlkStmVarStm($2, $3);  }
					;
	
Return_Stm 	
/*RetStmRet*/		: "return" ";" { $$ = make_RetStmRet();  } 
/*RetStmExp*/		| "return" Expression ";" { $$ = make_RetStmExp($2);  }
					;
	
Exp_Stm 	
/*ExpStmNul*/		: ";" { $$ = make_ExpStmNul();  } 
/*ExpStmExp*/		| Expression ";" { $$ = make_ExpStmExp($1);  }
					;
	
Closed_Stm 	
/*ClosedStmSmp*/	: Simple_Stm { $$ = make_ClosedStmSmp($1);  } 
/*ClosedStmIf*/		| "if" "(" Expression ")" Closed_Stm "else" Closed_Stm { $$ = make_ClosedStmIf($3, $5, $7);  }
/*ClosedStmWhile*/	| "while" "(" Expression ")" Closed_Stm { $$ = make_ClosedStmWhile($3, $5);  }
					| "if" "(" error ")" Closed_Stm "else" Closed_Stm { yyerror("If sem expressao"); }
					| "while" "(" error ")" Closed_Stm { yyerror("While sem expressao"); }
					;
	
Simple_Stm 	
/*SmpStmBlock*/		: Block_Stm { $$ = make_SmpStmBlock($1);  } 
/*SmpStmExp*/		| Exp_Stm { $$ = make_SmpStmExp($1);  }
/*SmpStmRet*/		| Return_Stm { $$ = make_SmpStmRet($1);  }
					;
	
Declarator 	
/*DecIdParam*/		: _IDENT_ "(" Parameter_List ")" { $$ = make_DecIdParam($1, $3);  } 
/*DecId*/			| _IDENT_ "(" ")" { $$ = make_DecId($1);  }
					| error "(" Parameter_List ")" { yyerror("Declaracao de funcao sem identificar e parametros"); }
					| error "(" ")" { yyerror("Declaracao de funcao sem identificar e parametros"); }
					;
	
Function_Def 	
/*FunDef*/			: Type Declarator Block_Stm 
						{ $$ = make_FunDef($1, $2, $3); insFuncSymbol_Table(SymbolTable, 
						($2->kind == is_DecIdParam ? $2->u.decidparam_.ident_ : $2->u.decid_.ident_), yy_mylinenumber, yy_mycolumnnumber, $1,
						($2->kind == is_DecIdParam ? $2->u.decidparam_.parameter_list_ : NULL)); }
					;
	
Ext_Var_Decl 	
/*ExtVarDecFun*/	: Function_Def { $$ = make_ExtVarDecFun($1);  } 
/*ExtVarDecVar*/	| Var_Declaration { $$ = make_ExtVarDecVar($1);  }
					;





