/**	Michelangelo da R. Machado - 14/0156089 **/

#ifndef SYNTACTIC_HEADER
#define SYNTACTIC_HEADER
#include <stdio.h>

/********************   TypeDefs    ********************/

typedef int Integer;
typedef double Double;
typedef char* String;
typedef char* Ident;

/********************   Declarações    ********************/

int error;
struct Trans_Unit_;
typedef struct Trans_Unit_ *Trans_Unit;
struct Assign_Operator_;
typedef struct Assign_Operator_ *Assign_Operator;
struct Constant_;
typedef struct Constant_ *Constant;
struct Unary_Operator_;
typedef struct Unary_Operator_ *Unary_Operator;
struct Type_;
typedef struct Type_ *Type;
struct Arg_Exp_List_;
typedef struct Arg_Exp_List_ *Arg_Exp_List;
struct Primary_Exp_;
typedef struct Primary_Exp_ *Primary_Exp;
struct Posfix_Exp_;
typedef struct Posfix_Exp_ *Posfix_Exp;
struct Unary_Exp_;
typedef struct Unary_Exp_ *Unary_Exp;
struct Multi_Exp_;
typedef struct Multi_Exp_ *Multi_Exp;
struct Add_Exp_;
typedef struct Add_Exp_ *Add_Exp;
struct Rel_Exp_;
typedef struct Rel_Exp_ *Rel_Exp;
struct Eq_Exp_;
typedef struct Eq_Exp_ *Eq_Exp;
struct Log_And_Exp_;
typedef struct Log_And_Exp_ *Log_And_Exp;
struct Log_Or_Exp_;
typedef struct Log_Or_Exp_ *Log_Or_Exp;
struct Expression_;
typedef struct Expression_ *Expression;
struct Init_Decl_List_;
typedef struct Init_Decl_List_ *Init_Decl_List;
struct Init_Declarator_;
typedef struct Init_Declarator_ *Init_Declarator;
struct Var_Declaration_;
typedef struct Var_Declaration_ *Var_Declaration;
struct Var_Decl_List_;
typedef struct Var_Decl_List_ *Var_Decl_List;
struct Parameter_List_;
typedef struct Parameter_List_ *Parameter_List;
struct Statement_List_;
typedef struct Statement_List_ *Statement_List;
struct Statement_;
typedef struct Statement_ *Statement;
struct Open_Stm_;
typedef struct Open_Stm_ *Open_Stm;
struct Block_Stm_;
typedef struct Block_Stm_ *Block_Stm;
struct Return_Stm_;
typedef struct Return_Stm_ *Return_Stm;
struct Exp_Stm_;
typedef struct Exp_Stm_ *Exp_Stm;
struct Closed_Stm_;
typedef struct Closed_Stm_ *Closed_Stm;
struct Simple_Stm_;
typedef struct Simple_Stm_ *Simple_Stm;
struct Declarator_;
typedef struct Declarator_ *Declarator;
struct Function_Def_;
typedef struct Function_Def_ *Function_Def;
struct Ext_Var_Decl_;
typedef struct Ext_Var_Decl_ *Ext_Var_Decl;


/********************   Tabela de simbolos    ********************/
typedef enum { Is_TypeVoid, Is_TypeInt, Is_TypeDouble, Is_TypeGraph } _Type;

typedef struct Function_Param_
{
	Ident name;
	_Type Type;
	struct Function_Param_ *next;
	
}Function_Param;

typedef struct Table_Line_
{
	enum { Is_ConstInt, Is_ConstDouble, Is_ConstStr, Is_Ident } Kind;
	
	union
	{
		struct { int value; int line; int column; } constint;
		struct { double value; int line, column; } constdouble;
		struct { char* value; int line, column; } conststr;
		struct
		{
			char* value;
			_Type Type; 
			enum { Is_Var, Is_Proc } Kind; 
			Function_Param *param;
			int line;
			int column;
		} ident;
	} u;
	
	struct Table_Line_ *next;
	
}Table_Line;

typedef struct Symbol_Table_
{
	struct Table_Line_ *lines;
	struct Symbol_Table_ *next;
	
}Symbol_Table;


Symbol_Table *newSymbol_Table();
void insConstIntSymbol_Table(Symbol_Table *p1, Integer p2, int p3, int p4);
void insConstDoubleSymbol_Table(Symbol_Table *p1, Double p2, int p3, int p4);
void insConstStrSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4);
void insVarSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4, Type p5);
void insFuncSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4, Type p5, Parameter_List p6);
void showSymbolTable(Symbol_Table *p1);

void insTableSymbol_VarDec(Type p1, Init_Decl_List p2, int p3, int p4);

Symbol_Table *SymbolTable;

/********************   Classes    ********************/

struct Trans_Unit_
{
  enum { is_TraUniExtVar, is_TraUniList } kind;
  union
  {
    struct { Ext_Var_Decl ext_var_decl_; } trauniextvar_;
    struct { Ext_Var_Decl ext_var_decl_; Trans_Unit trans_unit_; } traunilist_;
  } u;
};

Trans_Unit make_TraUniExtVar(Ext_Var_Decl p0);
Trans_Unit make_TraUniList(Trans_Unit p0, Ext_Var_Decl p1);

struct Assign_Operator_
{
  enum { is_AssOpEQ, is_AssOpINS } kind;
  union
  {
  } u;
};

Assign_Operator make_AssOpEQ(void);
Assign_Operator make_AssOpINS(void);

struct Constant_
{
  enum { is_ConstInt, is_ConstDouble, is_ConstStr } kind;
  union
  {
    struct { Integer integer_; } constint_;
    struct { Double double_; } constdouble_;
    struct { String string_; } conststr_;
  } u;
};

Constant make_ConstInt(Integer p0);
Constant make_ConstDouble(Double p0);
Constant make_ConstStr(String p0);

struct Unary_Operator_
{
  enum { is_UnaOpMinus, is_UnaOpNot } kind;
  union
  {
  } u;
};

Unary_Operator make_UnaOpMinus(void);
Unary_Operator make_UnaOpNot(void);

struct Type_
{
  enum { is_TypeVoid, is_TypeInt, is_TypeDouble, is_TypeGraph } kind;
  union
  {
  } u;
};

Type make_TypeVoid(void);
Type make_TypeInt(void);
Type make_TypeDouble(void);
Type make_TypeGraph(void);

struct Arg_Exp_List_
{
  enum { is_ArgExpListExp, is_ArgExpList } kind;
  union
  {
    struct { Expression expression_; } argexplistexp_;
    struct { Arg_Exp_List arg_exp_list_; Expression expression_; } argexplist_;
  } u;
};

Arg_Exp_List make_ArgExpListExp(Expression p0);
Arg_Exp_List make_ArgExpList(Arg_Exp_List p0, Expression p1);

struct Primary_Exp_
{
  enum { is_PriExpId, is_PriExpConst, is_PriExpExp } kind;
  union
  {
    struct { Ident ident_; } priexpid_;
    struct { Constant constant_; } priexpconst_;
    struct { Expression expression_; } priexpexp_;
  } u;
};

Primary_Exp make_PriExpId(Ident p0);
Primary_Exp make_PriExpConst(Constant p0);
Primary_Exp make_PriExpExp(Expression p0);

struct Posfix_Exp_
{
  enum { is_PosExpPri, is_PosExpSub, is_PosExpIn, is_PosExpOut, is_PosExpNeig, is_PosExpCal, is_PosExpCalArg } kind;
  union
  {
    struct { Primary_Exp primary_exp_; } posexppri_;
    struct { Ident ident_; Primary_Exp primary_exp_; } posexpsub_;
    struct { Ident ident_; Primary_Exp primary_exp_; } posexpin_;
    struct { Ident ident_; Primary_Exp primary_exp_; } posexpout_;
    struct { Ident ident_; Primary_Exp primary_exp_; } posexpneig_;
    struct { Ident ident_; } posexpcal_;
    struct { Arg_Exp_List arg_exp_list_; Ident ident_; } posexpcalarg_;
  } u;
};

Posfix_Exp make_PosExpPri(Primary_Exp p0);
Posfix_Exp make_PosExpSub(Ident p0, Primary_Exp p1);
Posfix_Exp make_PosExpIn(Ident p0, Primary_Exp p1);
Posfix_Exp make_PosExpOut(Ident p0, Primary_Exp p1);
Posfix_Exp make_PosExpNeig(Ident p0, Primary_Exp p1);
Posfix_Exp make_PosExpCal(Ident p0);
Posfix_Exp make_PosExpCalArg(Ident p0, Arg_Exp_List p1);

struct Unary_Exp_
{
  enum { is_UnaExpPos, is_UnaExpOp } kind;
  union
  {
    struct { Posfix_Exp posfix_exp_; } unaexppos_;
    struct { Unary_Exp unary_exp_; Unary_Operator unary_operator_; } unaexpop_;
  } u;
};

Unary_Exp make_UnaExpPos(Posfix_Exp p0);
Unary_Exp make_UnaExpOp(Unary_Operator p0, Unary_Exp p1);

struct Multi_Exp_
{
  enum { is_MulExpUna, is_MulExpMul, is_MulExpDiv } kind;
  union
  {
    struct { Unary_Exp unary_exp_; } mulexpuna_;
    struct { Multi_Exp multi_exp_; Unary_Exp unary_exp_; } mulexpmul_;
    struct { Multi_Exp multi_exp_; Unary_Exp unary_exp_; } mulexpdiv_;
  } u;
};

Multi_Exp make_MulExpUna(Unary_Exp p0);
Multi_Exp make_MulExpMul(Multi_Exp p0, Unary_Exp p1);
Multi_Exp make_MulExpDiv(Multi_Exp p0, Unary_Exp p1);

struct Add_Exp_
{
  enum { is_AddExpMul, is_AddExpAdd, is_AddExpSub } kind;
  union
  {
    struct { Multi_Exp multi_exp_; } addexpmul_;
    struct { Add_Exp add_exp_; Multi_Exp multi_exp_; } addexpadd_;
    struct { Add_Exp add_exp_; Multi_Exp multi_exp_; } addexpsub_;
  } u;
};

Add_Exp make_AddExpMul(Multi_Exp p0);
Add_Exp make_AddExpAdd(Add_Exp p0, Multi_Exp p1);
Add_Exp make_AddExpSub(Add_Exp p0, Multi_Exp p1);

struct Rel_Exp_
{
  enum { is_RelExpAdd, is_RelExpLT, is_RelExpGT, is_RelExpLE, is_RelExpGE } kind;
  union
  {
    struct { Add_Exp add_exp_; } relexpadd_;
    struct { Add_Exp add_exp_; Rel_Exp rel_exp_; } relexplt_;
    struct { Add_Exp add_exp_; Rel_Exp rel_exp_; } relexpgt_;
    struct { Add_Exp add_exp_; Rel_Exp rel_exp_; } relexple_;
    struct { Add_Exp add_exp_; Rel_Exp rel_exp_; } relexpge_;
  } u;
};

Rel_Exp make_RelExpAdd(Add_Exp p0);
Rel_Exp make_RelExpLT(Rel_Exp p0, Add_Exp p1);
Rel_Exp make_RelExpGT(Rel_Exp p0, Add_Exp p1);
Rel_Exp make_RelExpLE(Rel_Exp p0, Add_Exp p1);
Rel_Exp make_RelExpGE(Rel_Exp p0, Add_Exp p1);

struct Eq_Exp_
{
  enum { is_EqExpRel, is_EqExpEQ, is_EqExpNE } kind;
  union
  {
    struct { Rel_Exp rel_exp_; } eqexprel_;
    struct { Eq_Exp eq_exp_; Rel_Exp rel_exp_; } eqexpeq_;
    struct { Eq_Exp eq_exp_; Rel_Exp rel_exp_; } eqexpne_;
  } u;
};

Eq_Exp make_EqExpRel(Rel_Exp p0);
Eq_Exp make_EqExpEQ(Eq_Exp p0, Rel_Exp p1);
Eq_Exp make_EqExpNE(Eq_Exp p0, Rel_Exp p1);

struct Log_And_Exp_
{
  enum { is_LogAndExpEq, is_LogAndExpAnd } kind;
  union
  {
    struct { Eq_Exp eq_exp_; } logandexpeq_;
    struct { Eq_Exp eq_exp_; Log_And_Exp log_and_exp_; } logandexpand_;
  } u;
};

Log_And_Exp make_LogAndExpEq(Eq_Exp p0);
Log_And_Exp make_LogAndExpAnd(Log_And_Exp p0, Eq_Exp p1);

struct Log_Or_Exp_
{
  enum { is_LogOrExpLogAnd, is_LogOrExpLogOr } kind;
  union
  {
    struct { Log_And_Exp log_and_exp_; } logorexplogand_;
    struct { Log_And_Exp log_and_exp_; Log_Or_Exp log_or_exp_; } logorexplogor_;
  } u;
};

Log_Or_Exp make_LogOrExpLogAnd(Log_And_Exp p0);
Log_Or_Exp make_LogOrExpLogOr(Log_Or_Exp p0, Log_And_Exp p1);

struct Expression_
{
  enum { is_ExpLogOr, is_ExpAss, is_ExpAssGraph } kind;
  union
  {
    struct { Log_Or_Exp log_or_exp_; } explogor_;
    struct { Assign_Operator assign_operator_; Expression expression_; Ident ident_; } expass_;
    struct { Assign_Operator assign_operator_; Expression expression_1, expression_2; Ident ident_; } expassgraph_;
  } u;
};

Expression make_ExpLogOr(Log_Or_Exp p0);
Expression make_ExpAss(Ident p0, Assign_Operator p1, Expression p2);
Expression make_ExpAssGraph(Ident p0, Assign_Operator p1, Expression p2, Expression p3);

struct Init_Decl_List_
{
  enum { is_IniDecListIni, is_IniDecList } kind;
  union
  {
    struct { Init_Declarator init_declarator_; } inideclistini_;
    struct { Init_Decl_List init_decl_list_; Init_Declarator init_declarator_; } inideclist_;
  } u;
};

Init_Decl_List make_IniDecListIni(Init_Declarator p0);
Init_Decl_List make_IniDecList(Init_Decl_List p0, Init_Declarator p1);

struct Init_Declarator_
{
  enum { is_IniDecId, is_IniDecIdE } kind;
  union
  {
    struct { Ident ident_; } inidecid_;
    struct { Assign_Operator assign_operator_; Ident ident_; Log_Or_Exp log_or_exp_; } inidecide_;
  } u;
};

Init_Declarator make_IniDecId(Ident p0);
Init_Declarator make_IniDecIdE(Ident p0, Assign_Operator p1, Log_Or_Exp p2);

struct Var_Declaration_
{
  enum { is_VarDec } kind;
  union
  {
    struct { Init_Decl_List init_decl_list_; Type type_; } vardec_;
  } u;
};

Var_Declaration make_VarDec(Type p0, Init_Decl_List p1);

struct Var_Decl_List_
{
  enum { is_VarDecListVar, is_VarDecList } kind;
  union
  {
    struct { Var_Declaration var_declaration_; } vardeclistvar_;
    struct { Var_Decl_List var_decl_list_; Var_Declaration var_declaration_; } vardeclist_;
  } u;
};

Var_Decl_List make_VarDecListVar(Var_Declaration p0);
Var_Decl_List make_VarDecList(Var_Decl_List p0, Var_Declaration p1);

struct Parameter_List_
{
  enum { is_ParamListId, is_ParamList } kind;
  union
  {
    struct { Ident ident_; Type type_; } paramlistid_;
    struct { Ident ident_; Parameter_List parameter_list_; Type type_; } paramlist_;
  } u;
};

Parameter_List make_ParamListId(Type p0, Ident p1);
Parameter_List make_ParamList(Parameter_List p0, Type p1, Ident p2);

struct Statement_List_
{
  enum { is_StmListStm, is_StmList } kind;
  union
  {
    struct { Statement statement_; } stmliststm_;
    struct { Statement statement_; Statement_List statement_list_; } stmlist_;
  } u;
};

Statement_List make_StmListStm(Statement p0);
Statement_List make_StmList(Statement_List p0, Statement p1);

struct Statement_
{
  enum { is_StmOpen, is_StmClosed } kind;
  union
  {
    struct { Open_Stm open_stm_; } stmopen_;
    struct { Closed_Stm closed_stm_; } stmclosed_;
  } u;
};

Statement make_StmOpen(Open_Stm p0);
Statement make_StmClosed(Closed_Stm p0);

struct Open_Stm_
{
  enum { is_OpnStmIfSmp, is_OpnStmIfOpn, is_OpnStmIfCls, is_OpnStmWhile } kind;
  union
  {
    struct { Expression expression_; Simple_Stm simple_stm_; } opnstmifsmp_;
    struct { Expression expression_; Open_Stm open_stm_; } opnstmifopn_;
    struct { Closed_Stm closed_stm_; Expression expression_; Open_Stm open_stm_; } opnstmifcls_;
    struct { Expression expression_; Open_Stm open_stm_; } opnstmwhile_;
  } u;
};

Open_Stm make_OpnStmIfSmp(Expression p0, Simple_Stm p1);
Open_Stm make_OpnStmIfOpn(Expression p0, Open_Stm p1);
Open_Stm make_OpnStmIfCls(Expression p0, Closed_Stm p1, Open_Stm p2);
Open_Stm make_OpnStmWhile(Expression p0, Open_Stm p1);

struct Block_Stm_
{
  enum { is_BlkStm, is_BlkStmList, is_BlkStmVar, is_BlkStmVarStm } kind;
  union
  {
    struct { Statement_List statement_list_; } blkstmlist_;
    struct { Var_Decl_List var_decl_list_; } blkstmvar_;
    struct { Statement_List statement_list_; Var_Decl_List var_decl_list_; } blkstmvarstm_;
  } u;
};

Block_Stm make_BlkStm(void);
Block_Stm make_BlkStmList(Statement_List p0);
Block_Stm make_BlkStmVar(Var_Decl_List p0);
Block_Stm make_BlkStmVarStm(Var_Decl_List p0, Statement_List p1);

struct Return_Stm_
{
  enum { is_RetStmRet, is_RetStmExp } kind;
  union
  {
    struct { Expression expression_; } retstmexp_;
  } u;
};

Return_Stm make_RetStmRet(void);
Return_Stm make_RetStmExp(Expression p0);

struct Exp_Stm_
{
  enum { is_ExpStmNul, is_ExpStmExp } kind;
  union
  {
    struct { Expression expression_; } expstmexp_;
  } u;
};

Exp_Stm make_ExpStmNul(void);
Exp_Stm make_ExpStmExp(Expression p0);

struct Closed_Stm_
{
  enum { is_ClosedStmSmp, is_ClosedStmIf, is_ClosedStmWhile } kind;
  union
  {
    struct { Simple_Stm simple_stm_; } closedstmsmp_;
    struct { Closed_Stm closed_stm_1, closed_stm_2; Expression expression_; } closedstmif_;
    struct { Closed_Stm closed_stm_; Expression expression_; } closedstmwhile_;
  } u;
};

Closed_Stm make_ClosedStmSmp(Simple_Stm p0);
Closed_Stm make_ClosedStmIf(Expression p0, Closed_Stm p1, Closed_Stm p2);
Closed_Stm make_ClosedStmWhile(Expression p0, Closed_Stm p1);

struct Simple_Stm_
{
  enum { is_SmpStmBlock, is_SmpStmExp, is_SmpStmRet } kind;
  union
  {
    struct { Block_Stm block_stm_; } smpstmblock_;
    struct { Exp_Stm exp_stm_; } smpstmexp_;
    struct { Return_Stm return_stm_; } smpstmret_;
  } u;
};

Simple_Stm make_SmpStmBlock(Block_Stm p0);
Simple_Stm make_SmpStmExp(Exp_Stm p0);
Simple_Stm make_SmpStmRet(Return_Stm p0);

struct Declarator_
{
  enum { is_DecIdParam, is_DecId } kind;
  union
  {
    struct { Ident ident_; Parameter_List parameter_list_; } decidparam_;
    struct { Ident ident_; } decid_;
  } u;
};

Declarator make_DecIdParam(Ident p0, Parameter_List p1);
Declarator make_DecId(Ident p0);

struct Function_Def_
{
  enum { is_FunDef } kind;
  union
  {
    struct { Block_Stm block_stm_; Declarator declarator_; Type type_; } fundef_;
  } u;
};

Function_Def make_FunDef(Type p0, Declarator p1, Block_Stm p2);

struct Ext_Var_Decl_
{
  enum { is_ExtVarDecFun, is_ExtVarDecVar } kind;
  union
  {
    struct { Function_Def function_def_; } extvardecfun_;
    struct { Var_Declaration var_declaration_; } extvardecvar_;
  } u;
};

Ext_Var_Decl make_ExtVarDecFun(Function_Def p0);
Ext_Var_Decl make_ExtVarDecVar(Var_Declaration p0);



#endif
