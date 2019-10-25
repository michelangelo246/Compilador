/**	Michelangelo da R. Machado - 14/0156089 **/

#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Syntactic.h"

/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000

char *showTrans_Unit(Trans_Unit p);

void shTrans_Unit(Trans_Unit p);
void shAssign_Operator(Assign_Operator p);
void shConstant(Constant p);
void shUnary_Operator(Unary_Operator p);
void shType(Type p);
void shArg_Exp_List(Arg_Exp_List p);
void shPrimary_Exp(Primary_Exp p);
void shPosfix_Exp(Posfix_Exp p);
void shUnary_Exp(Unary_Exp p);
void shMulti_Exp(Multi_Exp p);
void shAdd_Exp(Add_Exp p);
void shRel_Exp(Rel_Exp p);
void shEq_Exp(Eq_Exp p);
void shLog_And_Exp(Log_And_Exp p);
void shLog_Or_Exp(Log_Or_Exp p);
void shExpression(Expression p);
void shInit_Decl_List(Init_Decl_List p);
void shInit_Declarator(Init_Declarator p);
void shVar_Declaration(Var_Declaration p);
void shVar_Decl_List(Var_Decl_List p);
void shParameter_List(Parameter_List p);
void shStatement_List(Statement_List p);
void shStatement(Statement p);
void shOpen_Stm(Open_Stm p);
void shBlock_Stm(Block_Stm p);
void shReturn_Stm(Return_Stm p);
void shExp_Stm(Exp_Stm p);
void shClosed_Stm(Closed_Stm p);
void shSimple_Stm(Simple_Stm p);
void shDeclarator(Declarator p);
void shFunction_Def(Function_Def p);
void shExt_Var_Decl(Ext_Var_Decl p);

void shInteger(Integer n);
void shDouble(Double d);
void shString(String s);
void shIdent(String s);
void bufAppendS(const char *s);
void bufAppendC(const char c);
void bufReset(void);
void resizeBuffer(void);

#endif

