/**	Michelangelo da R. Machado - 14/0156089 **/

#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int _n_;
char *buf_;
int cur_;
int buf_size;

char *showTrans_Unit(Trans_Unit p)
{
  _n_ = 0;
  bufReset();
  shTrans_Unit(p);
  return buf_;
}

void shTrans_Unit(Trans_Unit _p_)
{
  switch(_p_->kind)
  {
  case is_TraUniExtVar:
    bufAppendC('(');

    bufAppendS("TraUniExtVar");

    bufAppendC(' ');

    shExt_Var_Decl(_p_->u.trauniextvar_.ext_var_decl_);

    bufAppendC(')');

    break;
  case is_TraUniList:
    bufAppendC('(');

    bufAppendS("TraUniList");

    bufAppendC(' ');

    shTrans_Unit(_p_->u.traunilist_.trans_unit_);
	
	bufAppendC(' ');
	
    shExt_Var_Decl(_p_->u.traunilist_.ext_var_decl_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Trans_Unit!\n");
    exit(1);
  }
}

void shAssign_Operator(Assign_Operator _p_)
{
  switch(_p_->kind)
  {
  case is_AssOpEQ:
	bufAppendC('(');
  
    bufAppendS("AssOpEQ");
	
	bufAppendS(" \"=\" ");
	
	bufAppendC(')');
	
    break;
  case is_AssOpINS:
	bufAppendC('(');
  
    bufAppendS("AssOpINS");
	
	bufAppendS(" \"<<\" ");
	
	bufAppendC(')');
	
    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Assign_Operator!\n");
    exit(1);
  }
}

void shConstant(Constant _p_)
{
  switch(_p_->kind)
  {
  case is_ConstInt:
    bufAppendC('(');

    bufAppendS("ConstInt");

    bufAppendC(' ');

    shInteger(_p_->u.constint_.integer_);

    bufAppendC(')');

    break;
  case is_ConstDouble:
    bufAppendC('(');

    bufAppendS("ConstDouble");

    bufAppendC(' ');

    shDouble(_p_->u.constdouble_.double_);

    bufAppendC(')');

    break;
  case is_ConstStr:
    bufAppendC('(');

    bufAppendS("ConstStr");

    bufAppendC(' ');

    shString(_p_->u.conststr_.string_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Constant!\n");
    exit(1);
  }
}

void shUnary_Operator(Unary_Operator _p_)
{
  switch(_p_->kind)
  {
  case is_UnaOpMinus:
	bufAppendC('(');
  
    bufAppendS("UnaOpMinus");
	
	bufAppendS(" \"-\" ");
	
	bufAppendC(')');
	
    break;
  case is_UnaOpNot:
	bufAppendC('(');
  
    bufAppendS("UnaOpNot");
	
	bufAppendS(" \"!\" ");
	
	bufAppendC(')');
	
    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Unary_Operator!\n");
    exit(1);
  }
}

void shType(Type _p_)
{
  switch(_p_->kind)
  {
  case is_TypeVoid:
	bufAppendC('(');
  
    bufAppendS("TypeVoid");
	
	bufAppendS( " \"void\" ");
	
	bufAppendC(')');
	
    break;
  case is_TypeInt:
	bufAppendC('(');
  
    bufAppendS("TypeInt");
	
	bufAppendS(" \"int\" ");
	
	bufAppendC(')');
	
    break;
  case is_TypeDouble:
	bufAppendC('(');
  
    bufAppendS("TypeDouble");
	
	bufAppendS(" \"double\" ");
	
	bufAppendC(')');
	
    break;
  case is_TypeGraph:
	bufAppendC('(');
  
    bufAppendS("TypeGraph");
	
	bufAppendS(" \"graph\" ");
	
	bufAppendC(')');
	
    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Type!\n");
    exit(1);
  }
}

void shArg_Exp_List(Arg_Exp_List _p_)
{
  switch(_p_->kind)
  {
  case is_ArgExpListExp:
    bufAppendC('(');

    bufAppendS("ArgExpListExp");

    bufAppendC(' ');

    shExpression(_p_->u.argexplistexp_.expression_);

    bufAppendC(')');

    break;
  case is_ArgExpList:
    bufAppendC('(');

    bufAppendS("ArgExpList");

    bufAppendC(' ');

    shArg_Exp_List(_p_->u.argexplist_.arg_exp_list_);

	bufAppendC(' ');
	
    shExpression(_p_->u.argexplist_.expression_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Arg_Exp_List!\n");
    exit(1);
  }
}

void shPrimary_Exp(Primary_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_PriExpId:
    bufAppendC('(');

    bufAppendS("PriExpId");

    bufAppendC(' ');

    shIdent(_p_->u.priexpid_.ident_);

    bufAppendC(')');

    break;
  case is_PriExpConst:
    bufAppendC('(');

    bufAppendS("PriExpConst");

    bufAppendC(' ');

    shConstant(_p_->u.priexpconst_.constant_);

    bufAppendC(')');

    break;
  case is_PriExpExp:
    bufAppendC('(');

    bufAppendS("PriExpExp");

    bufAppendC(' ');
	
	bufAppendS(" \"(\" ");

    shExpression(_p_->u.priexpexp_.expression_);
	
	bufAppendS(" \")\" ");

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Primary_Exp!\n");
    exit(1);
  }
}

void shPosfix_Exp(Posfix_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_PosExpPri:
    bufAppendC('(');

    bufAppendS("PosExpPri");

    bufAppendC(' ');

    shPrimary_Exp(_p_->u.posexppri_.primary_exp_);

    bufAppendC(')');

    break;
  case is_PosExpSub:
    bufAppendC('(');

    bufAppendS("PosExpSub");

    bufAppendS(" \"[\" ");

    shIdent(_p_->u.posexpsub_.ident_);

	bufAppendS(" \"]\" ");
	
    shPrimary_Exp(_p_->u.posexpsub_.primary_exp_);

    bufAppendC(')');

    break;
  case is_PosExpIn:
    bufAppendC('(');

    bufAppendS("PosExpIn");

    bufAppendS(" \"@\" ");

    shIdent(_p_->u.posexpin_.ident_);

	bufAppendS(" \"#\" ");
	
    shPrimary_Exp(_p_->u.posexpin_.primary_exp_);

    bufAppendC(')');

    break;
  case is_PosExpOut:
    bufAppendC('(');

    bufAppendS("PosExpOut");

    bufAppendS(" \"#\" ");

    shIdent(_p_->u.posexpout_.ident_);

	bufAppendS(" \"@\" ");
	
    shPrimary_Exp(_p_->u.posexpout_.primary_exp_);

    bufAppendC(')');

    break;
  case is_PosExpNeig:
    bufAppendC('(');

    bufAppendS("PosExpNeig");

    bufAppendS(" \"&\" ");

    shIdent(_p_->u.posexpneig_.ident_);

	bufAppendS(" \"&\" ");
	
    shPrimary_Exp(_p_->u.posexpneig_.primary_exp_);

    bufAppendC(')');

    break;
  case is_PosExpCal:
    bufAppendC('(');

    bufAppendS("PosExpCal");

    shIdent(_p_->u.posexpcal_.ident_);

    bufAppendS(" \"(\" ");
	
	bufAppendS(" \")\" ");

    bufAppendC(')');

    break;
  case is_PosExpCalArg:
    bufAppendC('(');

    bufAppendS("PosExpCalArg");

    bufAppendS(" \"(\" ");

    shIdent(_p_->u.posexpcalarg_.ident_);

	bufAppendS(" \")\" ");
	
    shArg_Exp_List(_p_->u.posexpcalarg_.arg_exp_list_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Posfix_Exp!\n");
    exit(1);
  }
}

void shUnary_Exp(Unary_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_UnaExpPos:
    bufAppendC('(');

    bufAppendS("UnaExpPos");

    bufAppendC(' ');

    shPosfix_Exp(_p_->u.unaexppos_.posfix_exp_);

    bufAppendC(')');

    break;
  case is_UnaExpOp:
    bufAppendC('(');

    bufAppendS("UnaExpOp");

    bufAppendC(' ');

    shUnary_Operator(_p_->u.unaexpop_.unary_operator_);

	bufAppendC(' ');
	
    shUnary_Exp(_p_->u.unaexpop_.unary_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Unary_Exp!\n");
    exit(1);
  }
}

void shMulti_Exp(Multi_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_MulExpUna:
    bufAppendC('(');

    bufAppendS("MulExpUna");

    bufAppendC(' ');

    shUnary_Exp(_p_->u.mulexpuna_.unary_exp_);

    bufAppendC(')');

    break;
  case is_MulExpMul:
    bufAppendC('(');

    bufAppendS("MulExpMul");

    bufAppendC(' ');

    shMulti_Exp(_p_->u.mulexpmul_.multi_exp_);

	bufAppendS(" \"*\" ");
	
    shUnary_Exp(_p_->u.mulexpmul_.unary_exp_);

    bufAppendC(')');

    break;
  case is_MulExpDiv:
    bufAppendC('(');

    bufAppendS("MulExpDiv");

    bufAppendC(' ');

    shMulti_Exp(_p_->u.mulexpdiv_.multi_exp_);

	bufAppendS(" \"/\" ");
	
    shUnary_Exp(_p_->u.mulexpdiv_.unary_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Multi_Exp!\n");
    exit(1);
  }
}

void shAdd_Exp(Add_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_AddExpMul:
    bufAppendC('(');

    bufAppendS("AddExpMul");

    bufAppendC(' ');

    shMulti_Exp(_p_->u.addexpmul_.multi_exp_);

    bufAppendC(')');

    break;
  case is_AddExpAdd:
    bufAppendC('(');

    bufAppendS("AddExpAdd");

    bufAppendC(' ');

    shAdd_Exp(_p_->u.addexpadd_.add_exp_);

	bufAppendS(" \"+\" ");
	
    shMulti_Exp(_p_->u.addexpadd_.multi_exp_);

    bufAppendC(')');

    break;
  case is_AddExpSub:
    bufAppendC('(');

    bufAppendS("AddExpSub");

    bufAppendC(' ');

    shAdd_Exp(_p_->u.addexpsub_.add_exp_);

	bufAppendS(" \"-\" ");
	
    shMulti_Exp(_p_->u.addexpsub_.multi_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Add_Exp!\n");
    exit(1);
  }
}

void shRel_Exp(Rel_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_RelExpAdd:
    bufAppendC('(');

    bufAppendS("RelExpAdd");

    bufAppendC(' ');

    shAdd_Exp(_p_->u.relexpadd_.add_exp_);

    bufAppendC(')');

    break;
  case is_RelExpLT:
    bufAppendC('(');

    bufAppendS("RelExpLT");

    bufAppendC(' ');

    shRel_Exp(_p_->u.relexplt_.rel_exp_);

	bufAppendS(" \"<\" ");
	
    shAdd_Exp(_p_->u.relexplt_.add_exp_);

    bufAppendC(')');

    break;
  case is_RelExpGT:
    bufAppendC('(');

    bufAppendS("RelExpGT");

    bufAppendC(' ');

    shRel_Exp(_p_->u.relexpgt_.rel_exp_);

	bufAppendS(" \">\" ");
	
    shAdd_Exp(_p_->u.relexpgt_.add_exp_);

    bufAppendC(')');

    break;
  case is_RelExpLE:
    bufAppendC('(');

    bufAppendS("RelExpLE");

    bufAppendC(' ');

    shRel_Exp(_p_->u.relexple_.rel_exp_);

	bufAppendS(" \"<=\" ");
	
    shAdd_Exp(_p_->u.relexple_.add_exp_);

    bufAppendC(')');

    break;
  case is_RelExpGE:
    bufAppendC('(');

    bufAppendS("RelExpGE");

    bufAppendC(' ');

    shRel_Exp(_p_->u.relexpge_.rel_exp_);

	bufAppendS(" \">=\" ");
	
    shAdd_Exp(_p_->u.relexpge_.add_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Rel_Exp!\n");
    exit(1);
  }
}

void shEq_Exp(Eq_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_EqExpRel:
    bufAppendC('(');

    bufAppendS("EqExpRel");

    bufAppendC(' ');

    shRel_Exp(_p_->u.eqexprel_.rel_exp_);

    bufAppendC(')');

    break;
  case is_EqExpEQ:
    bufAppendC('(');

    bufAppendS("EqExpEQ");

    bufAppendC(' ');

    shEq_Exp(_p_->u.eqexpeq_.eq_exp_);

	bufAppendS(" \"==\" ");
	
    shRel_Exp(_p_->u.eqexpeq_.rel_exp_);

    bufAppendC(')');

    break;
  case is_EqExpNE:
    bufAppendC('(');

    bufAppendS("EqExpNE");

    bufAppendC(' ');

    shEq_Exp(_p_->u.eqexpne_.eq_exp_);

	bufAppendS(" \"!=\" ");
	
    shRel_Exp(_p_->u.eqexpne_.rel_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Eq_Exp!\n");
    exit(1);
  }
}

void shLog_And_Exp(Log_And_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_LogAndExpEq:
    bufAppendC('(');

    bufAppendS("LogAndExpEq");

    bufAppendC(' ');

    shEq_Exp(_p_->u.logandexpeq_.eq_exp_);

    bufAppendC(')');

    break;
  case is_LogAndExpAnd:
    bufAppendC('(');

    bufAppendS("LogAndExpAnd");

    bufAppendC(' ');

    shLog_And_Exp(_p_->u.logandexpand_.log_and_exp_);

	bufAppendS(" \"&&\" ");
	
    shEq_Exp(_p_->u.logandexpand_.eq_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Log_And_Exp!\n");
    exit(1);
  }
}

void shLog_Or_Exp(Log_Or_Exp _p_)
{
  switch(_p_->kind)
  {
  case is_LogOrExpLogAnd:
    bufAppendC('(');

    bufAppendS("LogOrExpLogAnd");

    bufAppendC(' ');

    shLog_And_Exp(_p_->u.logorexplogand_.log_and_exp_);

    bufAppendC(')');

    break;
  case is_LogOrExpLogOr:
    bufAppendC('(');

    bufAppendS("LogOrExpLogOr");

    bufAppendC(' ');

    shLog_Or_Exp(_p_->u.logorexplogor_.log_or_exp_);

	bufAppendS(" \"||\" ");
	
    shLog_And_Exp(_p_->u.logorexplogor_.log_and_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Log_Or_Exp!\n");
    exit(1);
  }
}

void shExpression(Expression _p_)
{
  switch(_p_->kind)
  {
  case is_ExpLogOr:
    bufAppendC('(');

    bufAppendS("ExpLogOr");

    bufAppendC(' ');

    shLog_Or_Exp(_p_->u.explogor_.log_or_exp_);

    bufAppendC(')');

    break;
  case is_ExpAss:
    bufAppendC('(');

    bufAppendS("ExpAss");

    bufAppendC(' ');

    shIdent(_p_->u.expass_.ident_);

	bufAppendC(' ');
	
    shAssign_Operator(_p_->u.expass_.assign_operator_);

	bufAppendC(' ');
	
    shExpression(_p_->u.expass_.expression_);

    bufAppendC(')');

    break;
  case is_ExpAssGraph:
    bufAppendC('(');

    bufAppendS("ExpAssGraph");

    bufAppendC(' ');

    shIdent(_p_->u.expassgraph_.ident_);

	bufAppendC(' ');
	
    shAssign_Operator(_p_->u.expassgraph_.assign_operator_);

	bufAppendS(" \"(\" ");
	
    shExpression(_p_->u.expassgraph_.expression_1);

	bufAppendS(" \",\" ");
	
    shExpression(_p_->u.expassgraph_.expression_2);
	
	bufAppendS(" \")\" ");

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Expression!\n");
    exit(1);
  }
}

void shInit_Decl_List(Init_Decl_List _p_)
{
  switch(_p_->kind)
  {
  case is_IniDecListIni:
    bufAppendC('(');

    bufAppendS("IniDecListIni");

    bufAppendC(' ');

    shInit_Declarator(_p_->u.inideclistini_.init_declarator_);

    bufAppendC(')');

    break;
  case is_IniDecList:
    bufAppendC('(');

    bufAppendS("IniDecList");

    bufAppendC(' ');

    shInit_Decl_List(_p_->u.inideclist_.init_decl_list_);

	bufAppendS(" \",\" ");
	
    shInit_Declarator(_p_->u.inideclist_.init_declarator_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Init_Decl_List!\n");
    exit(1);
  }
}

void shInit_Declarator(Init_Declarator _p_)
{
  switch(_p_->kind)
  {
  case is_IniDecId:
    bufAppendC('(');

    bufAppendS("IniDecId");

    bufAppendC(' ');

    shIdent(_p_->u.inidecid_.ident_);

    bufAppendC(')');

    break;
  case is_IniDecIdE:
    bufAppendC('(');

    bufAppendS("IniDecIdE");

    bufAppendC(' ');

    shIdent(_p_->u.inidecide_.ident_);

	bufAppendC(' ');

    shAssign_Operator(_p_->u.inidecide_.assign_operator_);

	bufAppendC(' ');

    shLog_Or_Exp(_p_->u.inidecide_.log_or_exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Init_Declarator!\n");
    exit(1);
  }
}

void shVar_Declaration(Var_Declaration _p_)
{
  switch(_p_->kind)
  {
  case is_VarDec:
    bufAppendC('(');

    bufAppendS("VarDec");

    bufAppendC(' ');

    shType(_p_->u.vardec_.type_);

	bufAppendC(' ');

    shInit_Decl_List(_p_->u.vardec_.init_decl_list_);
	
	bufAppendS(" \";\" ");

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Var_Declaration!\n");
    exit(1);
  }
}

void shVar_Decl_List(Var_Decl_List _p_)
{
  switch(_p_->kind)
  {
  case is_VarDecListVar:
    bufAppendC('(');

    bufAppendS("VarDecListVar");

    bufAppendC(' ');

    shVar_Declaration(_p_->u.vardeclistvar_.var_declaration_);

    bufAppendC(')');

    break;
  case is_VarDecList:
    bufAppendC('(');

    bufAppendS("VarDecList");

    bufAppendC(' ');

    shVar_Decl_List(_p_->u.vardeclist_.var_decl_list_);

	bufAppendC(' ');

    shVar_Declaration(_p_->u.vardeclist_.var_declaration_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Var_Decl_List!\n");
    exit(1);
  }
}

void shParameter_List(Parameter_List _p_)
{
  switch(_p_->kind)
  {
  case is_ParamListId:
    bufAppendC('(');

    bufAppendS("ParamListId");

    bufAppendC(' ');

    shType(_p_->u.paramlistid_.type_);

	bufAppendC(' ');

    shIdent(_p_->u.paramlistid_.ident_);

    bufAppendC(')');

    break;
  case is_ParamList:
    bufAppendC('(');

    bufAppendS("ParamList");

    bufAppendC(' ');

    shParameter_List(_p_->u.paramlist_.parameter_list_);

	bufAppendS(" \",\" ");

    shType(_p_->u.paramlist_.type_);

	bufAppendC(' ');

    shIdent(_p_->u.paramlist_.ident_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Parameter_List!\n");
    exit(1);
  }
}

void shStatement_List(Statement_List _p_)
{
  switch(_p_->kind)
  {
  case is_StmListStm:
    bufAppendC('(');

    bufAppendS("StmListStm");

    bufAppendC(' ');

    shStatement(_p_->u.stmliststm_.statement_);

    bufAppendC(')');

    break;
  case is_StmList:
    bufAppendC('(');

    bufAppendS("StmList");

    bufAppendC(' ');

    shStatement_List(_p_->u.stmlist_.statement_list_);

	bufAppendC(' ');

    shStatement(_p_->u.stmlist_.statement_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Statement_List!\n");
    exit(1);
  }
}

void shStatement(Statement _p_)
{
  switch(_p_->kind)
  {
  case is_StmOpen:
    bufAppendC('(');

    bufAppendS("StmOpen");

    bufAppendC(' ');

    shOpen_Stm(_p_->u.stmopen_.open_stm_);

    bufAppendC(')');

    break;
  case is_StmClosed:
    bufAppendC('(');

    bufAppendS("StmClosed");

    bufAppendC(' ');

    shClosed_Stm(_p_->u.stmclosed_.closed_stm_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Statement!\n");
    exit(1);
  }
}

void shOpen_Stm(Open_Stm _p_)
{
  switch(_p_->kind)
  {
  case is_OpnStmIfSmp:
    bufAppendC('(');

    bufAppendS("OpnStmIfSmp");

    bufAppendS(" \"if\" ");
	
	bufAppendS(" \"(\" ");

    shExpression(_p_->u.opnstmifsmp_.expression_);

	bufAppendS(" \")\" ");

    shSimple_Stm(_p_->u.opnstmifsmp_.simple_stm_);

    bufAppendC(')');

    break;
  case is_OpnStmIfOpn:
    bufAppendC('(');

    bufAppendS("OpnStmIfOpn");

    bufAppendS(" \"if\" ");
	
	bufAppendS(" \"(\" ");

    shExpression(_p_->u.opnstmifopn_.expression_);

	bufAppendS(" \")\" ");

    shOpen_Stm(_p_->u.opnstmifopn_.open_stm_);

    bufAppendC(')');

    break;
  case is_OpnStmIfCls:
    bufAppendC('(');

    bufAppendS("OpnStmIfCls");

    bufAppendS(" \"if\" ");
	
	bufAppendS(" \"(\" ");

    shExpression(_p_->u.opnstmifcls_.expression_);

	bufAppendS(" \")\" ");

    shClosed_Stm(_p_->u.opnstmifcls_.closed_stm_);

	bufAppendS(" \"else\" ");

    shOpen_Stm(_p_->u.opnstmifcls_.open_stm_);

    bufAppendC(')');

    break;
  case is_OpnStmWhile:
    bufAppendC('(');

    bufAppendS("OpnStmWhile");

    bufAppendS(" \"while\" ");
	
	bufAppendS(" \"(\" ");

    shExpression(_p_->u.opnstmwhile_.expression_);

	bufAppendS(" \")\" ");

    shOpen_Stm(_p_->u.opnstmwhile_.open_stm_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Open_Stm!\n");
    exit(1);
  }
}

void shBlock_Stm(Block_Stm _p_)
{
  switch(_p_->kind)
  {
  case is_BlkStm:
	bufAppendC('(');
  
    bufAppendS("BlkStm");
	
	bufAppendS(" \"{\" ");
	
	bufAppendS(" \"}\" ");
	
	bufAppendC(')');
	
    break;
  case is_BlkStmList:
    bufAppendC('(');

    bufAppendS("BlkStmList");

    bufAppendS(" \"{\" ");

    shStatement_List(_p_->u.blkstmlist_.statement_list_);
	
	bufAppendS(" \"}\" ");

    bufAppendC(')');

    break;
  case is_BlkStmVar:
    bufAppendC('(');

    bufAppendS("BlkStmVar");

    bufAppendS(" \"{\" ");

    shVar_Decl_List(_p_->u.blkstmvar_.var_decl_list_);
	
	bufAppendS(" \"}\" ");

    bufAppendC(')');

    break;
  case is_BlkStmVarStm:
    bufAppendC('(');

    bufAppendS("BlkStmVarStm");

    bufAppendS(" \"{\" ");

    shVar_Decl_List(_p_->u.blkstmvarstm_.var_decl_list_);

	bufAppendC(' ');

    shStatement_List(_p_->u.blkstmvarstm_.statement_list_);
	
	bufAppendS(" \"}\" ");

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Block_Stm!\n");
    exit(1);
  }
}

void shReturn_Stm(Return_Stm _p_)
{
  switch(_p_->kind)
  {
  case is_RetStmRet:
	bufAppendC('(');
  
    bufAppendS("RetStmRet");
	
	bufAppendS(" \"return\" ");
	
	bufAppendS(" \";\" ");
	
	bufAppendC(')');
	
    break;
  case is_RetStmExp:
    bufAppendC('(');

    bufAppendS("RetStmExp");

    bufAppendS(" \"return\" ");

    shExpression(_p_->u.retstmexp_.expression_);
	
	bufAppendS(" \";\" ");

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Return_Stm!\n");
    exit(1);
  }
}

void shExp_Stm(Exp_Stm _p_)
{
  switch(_p_->kind)
  {
  case is_ExpStmNul:
	bufAppendC('(');
	
    bufAppendS("ExpStmNul");
	
	bufAppendS(" \";\" ");
	
	bufAppendC(')');
	
    break;
  case is_ExpStmExp:
    bufAppendC('(');

    bufAppendS("ExpStmExp");

    bufAppendC(' ');

    shExpression(_p_->u.expstmexp_.expression_);
	
	bufAppendS(" \";\" ");

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Exp_Stm!\n");
    exit(1);
  }
}

void shClosed_Stm(Closed_Stm _p_)
{
  switch(_p_->kind)
  {
  case is_ClosedStmSmp:
    bufAppendC('(');

    bufAppendS("ClosedStmSmp");

    bufAppendC(' ');

    shSimple_Stm(_p_->u.closedstmsmp_.simple_stm_);

    bufAppendC(')');

    break;
  case is_ClosedStmIf:
    bufAppendC('(');

    bufAppendS("ClosedStmIf");

    bufAppendS(" \"if\" ");
	
	bufAppendS(" \"(\" ");

    shExpression(_p_->u.closedstmif_.expression_);

	bufAppendS(" \")\" ");

    shClosed_Stm(_p_->u.closedstmif_.closed_stm_1);

	bufAppendS(" \"else\" ");

    shClosed_Stm(_p_->u.closedstmif_.closed_stm_2);

    bufAppendC(')');

    break;
  case is_ClosedStmWhile:
    bufAppendC('(');

    bufAppendS("ClosedStmWhile");

    bufAppendS(" \"while\" ");
	
	bufAppendS(" \"(\" ");

    shExpression(_p_->u.closedstmwhile_.expression_);

	bufAppendS(" \")\" ");

    shClosed_Stm(_p_->u.closedstmwhile_.closed_stm_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Closed_Stm!\n");
    exit(1);
  }
}

void shSimple_Stm(Simple_Stm _p_)
{
  switch(_p_->kind)
  {
  case is_SmpStmBlock:
    bufAppendC('(');

    bufAppendS("SmpStmBlock");

    bufAppendC(' ');

    shBlock_Stm(_p_->u.smpstmblock_.block_stm_);

    bufAppendC(')');

    break;
  case is_SmpStmExp:
    bufAppendC('(');

    bufAppendS("SmpStmExp");

    bufAppendC(' ');

    shExp_Stm(_p_->u.smpstmexp_.exp_stm_);

    bufAppendC(')');

    break;
  case is_SmpStmRet:
    bufAppendC('(');

    bufAppendS("SmpStmRet");

    bufAppendC(' ');

    shReturn_Stm(_p_->u.smpstmret_.return_stm_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Simple_Stm!\n");
    exit(1);
  }
}

void shDeclarator(Declarator _p_)
{
  switch(_p_->kind)
  {
  case is_DecIdParam:
    bufAppendC('(');

    bufAppendS("DecIdParam");

    bufAppendC(' ');

    shIdent(_p_->u.decidparam_.ident_);

	bufAppendS(" \"(\" ");

    shParameter_List(_p_->u.decidparam_.parameter_list_);
	
	bufAppendS(" \")\" ");

    bufAppendC(')');

    break;
  case is_DecId:
    bufAppendC('(');

    bufAppendS("DecId");

    bufAppendC(' ');

    shIdent(_p_->u.decid_.ident_);
	
	bufAppendS(" \"(\" ");
	
	bufAppendS(" \")\" ");

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Declarator!\n");
    exit(1);
  }
}

void shFunction_Def(Function_Def _p_)
{
  switch(_p_->kind)
  {
  case is_FunDef:
    bufAppendC('(');

    bufAppendS("FunDef");

    bufAppendC(' ');

    shType(_p_->u.fundef_.type_);

	bufAppendC(' ');

    shDeclarator(_p_->u.fundef_.declarator_);

	bufAppendC(' ');

    shBlock_Stm(_p_->u.fundef_.block_stm_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Function_Def!\n");
    exit(1);
  }
}

void shExt_Var_Decl(Ext_Var_Decl _p_)
{
  switch(_p_->kind)
  {
  case is_ExtVarDecFun:
    bufAppendC('(');

    bufAppendS("ExtVarDecFun");

    bufAppendC(' ');

    shFunction_Def(_p_->u.extvardecfun_.function_def_);

    bufAppendC(')');

    break;
  case is_ExtVarDecVar:
    bufAppendC('(');

    bufAppendS("ExtVarDecVar");

    bufAppendC(' ');

    shVar_Declaration(_p_->u.extvardecvar_.var_declaration_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Erro: kind nao identificado ao analisar Ext_Var_Decl!\n");
    exit(1);
  }
}

void shInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppendS(tmp);
}
void shDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppendS(tmp);
}
void shString(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}
void shIdent(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}

void bufAppendS(const char *s)
{
  int len = strlen(s);
  int n;
  while (cur_ + len > buf_size)
  {
    buf_size *= 2; /* Dobra tamanho do buffer */
    resizeBuffer();
  }
  for(n = 0; n < len; n++)
  {
    buf_[cur_ + n] = s[n];
  }
  cur_ += len;
  buf_[cur_] = 0;
}
void bufAppendC(const char c)
{
  if (cur_ == buf_size)
  {
    buf_size *= 2; /* Dobra tamanho do buffer */
    resizeBuffer();
  }
  buf_[cur_] = c;
  cur_++;
  buf_[cur_] = 0;
}
void bufReset(void)
{
  cur_ = 0;
  buf_size = BUFFER_INITIAL;
  resizeBuffer();
  memset(buf_, 0, buf_size);
}
void resizeBuffer(void)
{
  char *temp = (char *) malloc(buf_size);
  if (!temp)
  {
    fprintf(stderr, "Erro: Faltou memoria ao tentar expandir buffer!\n");
    exit(1);
  }
  if (buf_)
  {
    strncpy(temp, buf_, buf_size);
    free(buf_);
  }
  buf_ = temp;
}
char *buf_;
int cur_, buf_size;

