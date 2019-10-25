/**	Michelangelo da R. Machado - 14/0156089 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Syntactic.h"


/********************   Funcoes da tabela de simbolos    ********************/
Symbol_Table *newSymbol_Table()
{
	Symbol_Table *tmp = (Symbol_Table*) malloc(sizeof(Symbol_Table));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar tabela de simbolos!\n");
        exit(1);
    }
	tmp->next = NULL;
	tmp->lines = NULL;
	return tmp;
}

void insConstIntSymbol_Table(Symbol_Table *p1, Integer p2, int p3, int p4)
{
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_ConstInt;
	tmp->u.constint.value = p2;
	tmp->u.constint.line = p3;
	tmp->u.constint.column = p4;
	tmp->next = p1->lines;
	p1->lines = tmp;
}

void insConstDoubleSymbol_Table(Symbol_Table *p1, Double p2, int p3, int p4)
{
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_ConstDouble;
	tmp->u.constdouble.value = p2;
	tmp->u.constdouble.line = p3;
	tmp->u.constdouble.column = p4;
	tmp->next = p1->lines;
	p1->lines = tmp;
}

void insConstStrSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4)
{
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_ConstStr;
	tmp->u.conststr.value = strdup(p2);
	tmp->u.conststr.line = p3;
	tmp->u.conststr.column = p4;
	tmp->next = p1->lines;
	p1->lines = tmp;
}

void insVarSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4, Type p5)
{
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_Ident;
	tmp->u.ident.value = strdup(p2);
	tmp->u.ident.line = p3;
	tmp->u.ident.column = p4;
	tmp->u.ident.Kind = Is_Var;
	tmp->u.ident.Type = p5->kind;
	tmp->next = p1->lines;
	p1->lines = tmp;
}

void insFuncSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4, Type p5, Parameter_List p6)
{
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_Ident;
	tmp->u.ident.value = strdup(p2);
	tmp->u.ident.line = p3;
	tmp->u.ident.column = p4;
	tmp->u.ident.Kind = Is_Proc;
	tmp->u.ident.Type = p5->kind;
	tmp->u.ident.param = NULL;
	
	Parameter_List tmp2 = p6;
	Function_Param *aux;
	while(tmp2)
	{
		if(tmp2->kind == is_ParamList)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(tmp2->u.paramlist_.ident_);
			aux->Type = tmp2->u.paramlist_.type_->kind;
			
			aux->next = tmp->u.ident.param;
			tmp->u.ident.param = aux;
			
			tmp2 = tmp2->u.paramlist_.parameter_list_;
		}
		else if(tmp2->kind == is_ParamListId)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(tmp2->u.paramlistid_.ident_);
			aux->Type = tmp2->u.paramlistid_.type_->kind;
			
			aux->next = tmp->u.ident.param;
			tmp->u.ident.param = aux;
			tmp2 = NULL;
		}
	}
	
	tmp->next = p1->lines;
	p1->lines = tmp;
}

void showSymbolTable(Symbol_Table *p1)
{
	Table_Line *aux = p1->lines;
	Function_Param *aux2;
	while(aux)
	{
		switch(aux->Kind)
		{
		case Is_Ident:
			printf("  [ Identifier | tipo: %s ",(aux->u.ident.Kind == Is_Proc? "Funcao  " : "Variavel"));
			printf("| value: %s \t", aux->u.ident.value);
			switch(aux->u.ident.Type)
			{
			case Is_TypeVoid:
				printf("| type: void   ");
				break;
			case Is_TypeInt:
				printf("| type: int    ");
				break;
			case Is_TypeDouble:
				printf("| type: double ");
				break;
			case Is_TypeGraph:
				printf("| type: graph  ");
				break;
			}
			printf("| line: %d | column: %d ]\n",aux->u.ident.line, aux->u.ident.column);
			if(aux->u.ident.Kind == Is_Proc)
			{
				printf("  [ %s params: (",aux->u.ident.value);
				aux2 = aux->u.ident.param;
				while(aux2)
				{
					switch(aux2->Type)
					{
					case Is_TypeVoid:
						printf(" void ");
						break;
					case Is_TypeInt:
						printf(" int ");
						break;
					case Is_TypeDouble:
						printf(" double ");
						break;
					case Is_TypeGraph:
						printf(" graph ");
						break;
					}
					printf("%s",aux2->name);
					if(aux2->next)
					{
						printf(", ");
					}
					aux2 = aux2->next;
				}
				printf(") ]\n");
			}
			
			break;
		case Is_ConstInt:
			printf("  [ Constant   | tipo: int      | value: %d \t| line: %d | column: %d ]\n", aux->u.constint.value, aux->u.constint.line, aux->u.constint.column);
			break;
		case Is_ConstDouble:
			printf("  [ Constant   | tipo: double   | value: %g \t| line: %d | column: %d ]\n", aux->u.constdouble.value, aux->u.constdouble.line, aux->u.constdouble.column);
			break;
		case Is_ConstStr:
			printf("  [ Constant   | tipo: string   | value: %s \t| line: %d | column: %d ]\n", aux->u.conststr.value, aux->u.conststr.line, aux->u.conststr.column);
			break;
		}
		aux = aux->next;
	}
}

void insTableSymbol_VarDec(Type p1, Init_Decl_List p2, int line, int column)
{
	Init_Decl_List tmp = p2;
	String name;
	while(tmp)
	{
		switch(tmp->kind)
		{
		case is_IniDecListIni:
			if(tmp->u.inideclistini_.init_declarator_->kind == is_IniDecId)
			{
				name = tmp->u.inideclistini_.init_declarator_->u.inidecid_.ident_;
			}
			else
			{
				name = tmp->u.inideclistini_.init_declarator_->u.inidecide_.ident_;
			}
			insVarSymbol_Table(SymbolTable, name , line, column, p1);
			tmp = NULL;
			break;
		case is_IniDecList:
			if(tmp->u.inideclist_.init_declarator_->kind == is_IniDecId)
			{
				name = tmp->u.inideclist_.init_declarator_->u.inidecid_.ident_;
			}
			else
			{
				name = tmp->u.inideclist_.init_declarator_->u.inidecide_.ident_;
			}
			insVarSymbol_Table(SymbolTable, name , line, column, p1);
			tmp = tmp->u.inideclist_.init_decl_list_;
			break;
		}
	}
}

/********************   TraUniExtVar    ********************/
Trans_Unit make_TraUniExtVar(Ext_Var_Decl p1)
{
    Trans_Unit tmp = (Trans_Unit) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra TraUniExtVar!\n");
        exit(1);
    }
    tmp->kind = is_TraUniExtVar;
    tmp->u.trauniextvar_.ext_var_decl_ = p1;
    return tmp;
}
/********************   TraUniList    ********************/
Trans_Unit make_TraUniList(Trans_Unit p1, Ext_Var_Decl p2)
{
    Trans_Unit tmp = (Trans_Unit) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  TraUniList!\n");
        exit(1);
    }
    tmp->kind = is_TraUniList;
    tmp->u.traunilist_.trans_unit_ = p1;
    tmp->u.traunilist_.ext_var_decl_ = p2;
    return tmp;

}/********************   AssOpEQ    ********************/
Assign_Operator make_AssOpEQ()
{
    Assign_Operator tmp = (Assign_Operator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  AssOpEQ!\n");
        exit(1);
    }
    tmp->kind = is_AssOpEQ;
    return tmp;
}
/********************   AssOpINS    ********************/
Assign_Operator make_AssOpINS()
{
    Assign_Operator tmp = (Assign_Operator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  AssOpINS!\n");
        exit(1);
    }
    tmp->kind = is_AssOpINS;
    return tmp;
}/********************   ConstInt    ********************/
Constant make_ConstInt(Integer p1)
{
    Constant tmp = (Constant) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ConstInt!\n");
        exit(1);
    }
    tmp->kind = is_ConstInt;
    tmp->u.constint_.integer_ = p1;
    return tmp;
}
/********************   ConstDouble    ********************/
Constant make_ConstDouble(Double p1)
{
    Constant tmp = (Constant) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ConstDouble!\n");
        exit(1);
    }
    tmp->kind = is_ConstDouble;
    tmp->u.constdouble_.double_ = p1;
    return tmp;
}
/********************   ConstStr    ********************/
Constant make_ConstStr(String p1)
{
    Constant tmp = (Constant) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ConstStr!\n");
        exit(1);
    }
    tmp->kind = is_ConstStr;
    tmp->u.conststr_.string_ = p1;
    return tmp;
}/********************   UnaOpMinus    ********************/
Unary_Operator make_UnaOpMinus()
{
    Unary_Operator tmp = (Unary_Operator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  UnaOpMinus!\n");
        exit(1);
    }
    tmp->kind = is_UnaOpMinus;
    return tmp;
}
/********************   UnaOpNot    ********************/
Unary_Operator make_UnaOpNot()
{
    Unary_Operator tmp = (Unary_Operator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  UnaOpNot!\n");
        exit(1);
    }
    tmp->kind = is_UnaOpNot;
    return tmp;
}/********************   TypeVoid    ********************/
Type make_TypeVoid()
{
    Type tmp = (Type) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  TypeVoid!\n");
        exit(1);
    }
    tmp->kind = is_TypeVoid;
    return tmp;
}
/********************   TypeInt    ********************/
Type make_TypeInt()
{
    Type tmp = (Type) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  TypeInt!\n");
        exit(1);
    }
    tmp->kind = is_TypeInt;
    return tmp;
}
/********************   TypeDouble    ********************/
Type make_TypeDouble()
{
    Type tmp = (Type) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  TypeDouble!\n");
        exit(1);
    }
    tmp->kind = is_TypeDouble;
    return tmp;
}
/********************   TypeGraph    ********************/
Type make_TypeGraph()
{
    Type tmp = (Type) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  TypeGraph!\n");
        exit(1);
    }
    tmp->kind = is_TypeGraph;
    return tmp;
}/********************   ArgExpListExp    ********************/
Arg_Exp_List make_ArgExpListExp(Expression p1)
{
    Arg_Exp_List tmp = (Arg_Exp_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ArgExpListExp!\n");
        exit(1);
    }
    tmp->kind = is_ArgExpListExp;
    tmp->u.argexplistexp_.expression_ = p1;
    return tmp;
}
/********************   ArgExpList    ********************/
Arg_Exp_List make_ArgExpList(Arg_Exp_List p1, Expression p2)
{
    Arg_Exp_List tmp = (Arg_Exp_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ArgExpList!\n");
        exit(1);
    }
    tmp->kind = is_ArgExpList;
    tmp->u.argexplist_.arg_exp_list_ = p1;
    tmp->u.argexplist_.expression_ = p2;
    return tmp;
}/********************   PriExpId    ********************/
Primary_Exp make_PriExpId(Ident p1)
{
    Primary_Exp tmp = (Primary_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PriExpId!\n");
        exit(1);
    }
    tmp->kind = is_PriExpId;
    tmp->u.priexpid_.ident_ = p1;
    return tmp;
}
/********************   PriExpConst    ********************/
Primary_Exp make_PriExpConst(Constant p1)
{
    Primary_Exp tmp = (Primary_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PriExpConst!\n");
        exit(1);
    }
    tmp->kind = is_PriExpConst;
    tmp->u.priexpconst_.constant_ = p1;
    return tmp;
}
/********************   PriExpExp    ********************/
Primary_Exp make_PriExpExp(Expression p1)
{
    Primary_Exp tmp = (Primary_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PriExpExp!\n");
        exit(1);
    }
    tmp->kind = is_PriExpExp;
    tmp->u.priexpexp_.expression_ = p1;
    return tmp;
}/********************   PosExpPri    ********************/
Posfix_Exp make_PosExpPri(Primary_Exp p1)
{
    Posfix_Exp tmp = (Posfix_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PosExpPri!\n");
        exit(1);
    }
    tmp->kind = is_PosExpPri;
    tmp->u.posexppri_.primary_exp_ = p1;
    return tmp;
}
/********************   PosExpSub    ********************/
Posfix_Exp make_PosExpSub(Ident p1, Primary_Exp p2)
{
    Posfix_Exp tmp = (Posfix_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PosExpSub!\n");
        exit(1);
    }
    tmp->kind = is_PosExpSub;
    tmp->u.posexpsub_.ident_ = p1;
    tmp->u.posexpsub_.primary_exp_ = p2;
    return tmp;
}
/********************   PosExpIn    ********************/
Posfix_Exp make_PosExpIn(Ident p1, Primary_Exp p2)
{
    Posfix_Exp tmp = (Posfix_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PosExpIn!\n");
        exit(1);
    }
    tmp->kind = is_PosExpIn;
    tmp->u.posexpin_.ident_ = p1;
    tmp->u.posexpin_.primary_exp_ = p2;
    return tmp;
}
/********************   PosExpOut    ********************/
Posfix_Exp make_PosExpOut(Ident p1, Primary_Exp p2)
{
    Posfix_Exp tmp = (Posfix_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PosExpOut!\n");
        exit(1);
    }
    tmp->kind = is_PosExpOut;
    tmp->u.posexpout_.ident_ = p1;
    tmp->u.posexpout_.primary_exp_ = p2;
    return tmp;
}
/********************   PosExpNeig    ********************/
Posfix_Exp make_PosExpNeig(Ident p1, Primary_Exp p2)
{
    Posfix_Exp tmp = (Posfix_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PosExpNeig!\n");
        exit(1);
    }
    tmp->kind = is_PosExpNeig;
    tmp->u.posexpneig_.ident_ = p1;
    tmp->u.posexpneig_.primary_exp_ = p2;
    return tmp;
}
/********************   PosExpCal    ********************/
Posfix_Exp make_PosExpCal(Ident p1)
{
    Posfix_Exp tmp = (Posfix_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PosExpCal!\n");
        exit(1);
    }
    tmp->kind = is_PosExpCal;
    tmp->u.posexpcal_.ident_ = p1;
    return tmp;
}
/********************   PosExpCalArg    ********************/
Posfix_Exp make_PosExpCalArg(Ident p1, Arg_Exp_List p2)
{
    Posfix_Exp tmp = (Posfix_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  PosExpCalArg!\n");
        exit(1);
    }
    tmp->kind = is_PosExpCalArg;
    tmp->u.posexpcalarg_.ident_ = p1;
    tmp->u.posexpcalarg_.arg_exp_list_ = p2;
    return tmp;
}/********************   UnaExpPos    ********************/
Unary_Exp make_UnaExpPos(Posfix_Exp p1)
{
    Unary_Exp tmp = (Unary_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  UnaExpPos!\n");
        exit(1);
    }
    tmp->kind = is_UnaExpPos;
    tmp->u.unaexppos_.posfix_exp_ = p1;
    return tmp;
}
/********************   UnaExpOp    ********************/
Unary_Exp make_UnaExpOp(Unary_Operator p1, Unary_Exp p2)
{
    Unary_Exp tmp = (Unary_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  UnaExpOp!\n");
        exit(1);
    }
    tmp->kind = is_UnaExpOp;
    tmp->u.unaexpop_.unary_operator_ = p1;
    tmp->u.unaexpop_.unary_exp_ = p2;
    return tmp;
}/********************   MulExpUna    ********************/
Multi_Exp make_MulExpUna(Unary_Exp p1)
{
    Multi_Exp tmp = (Multi_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  MulExpUna!\n");
        exit(1);
    }
    tmp->kind = is_MulExpUna;
    tmp->u.mulexpuna_.unary_exp_ = p1;
    return tmp;
}
/********************   MulExpMul    ********************/
Multi_Exp make_MulExpMul(Multi_Exp p1, Unary_Exp p2)
{
    Multi_Exp tmp = (Multi_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  MulExpMul!\n");
        exit(1);
    }
    tmp->kind = is_MulExpMul;
    tmp->u.mulexpmul_.multi_exp_ = p1;
    tmp->u.mulexpmul_.unary_exp_ = p2;
    return tmp;
}
/********************   MulExpDiv    ********************/
Multi_Exp make_MulExpDiv(Multi_Exp p1, Unary_Exp p2)
{
    Multi_Exp tmp = (Multi_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  MulExpDiv!\n");
        exit(1);
    }
    tmp->kind = is_MulExpDiv;
    tmp->u.mulexpdiv_.multi_exp_ = p1;
    tmp->u.mulexpdiv_.unary_exp_ = p2;
    return tmp;
}/********************   AddExpMul    ********************/
Add_Exp make_AddExpMul(Multi_Exp p1)
{
    Add_Exp tmp = (Add_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  AddExpMul!\n");
        exit(1);
    }
    tmp->kind = is_AddExpMul;
    tmp->u.addexpmul_.multi_exp_ = p1;
    return tmp;
}
/********************   AddExpAdd    ********************/
Add_Exp make_AddExpAdd(Add_Exp p1, Multi_Exp p2)
{
    Add_Exp tmp = (Add_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  AddExpAdd!\n");
        exit(1);
    }
    tmp->kind = is_AddExpAdd;
    tmp->u.addexpadd_.add_exp_ = p1;
    tmp->u.addexpadd_.multi_exp_ = p2;
    return tmp;
}
/********************   AddExpSub    ********************/
Add_Exp make_AddExpSub(Add_Exp p1, Multi_Exp p2)
{
    Add_Exp tmp = (Add_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  AddExpSub!\n");
        exit(1);
    }
    tmp->kind = is_AddExpSub;
    tmp->u.addexpsub_.add_exp_ = p1;
    tmp->u.addexpsub_.multi_exp_ = p2;
    return tmp;
}/********************   RelExpAdd    ********************/
Rel_Exp make_RelExpAdd(Add_Exp p1)
{
    Rel_Exp tmp = (Rel_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  RelExpAdd!\n");
        exit(1);
    }
    tmp->kind = is_RelExpAdd;
    tmp->u.relexpadd_.add_exp_ = p1;
    return tmp;
}
/********************   RelExpLT    ********************/
Rel_Exp make_RelExpLT(Rel_Exp p1, Add_Exp p2)
{
    Rel_Exp tmp = (Rel_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  RelExpLT!\n");
        exit(1);
    }
    tmp->kind = is_RelExpLT;
    tmp->u.relexplt_.rel_exp_ = p1;
    tmp->u.relexplt_.add_exp_ = p2;
    return tmp;
}
/********************   RelExpGT    ********************/
Rel_Exp make_RelExpGT(Rel_Exp p1, Add_Exp p2)
{
    Rel_Exp tmp = (Rel_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  RelExpGT!\n");
        exit(1);
    }
    tmp->kind = is_RelExpGT;
    tmp->u.relexpgt_.rel_exp_ = p1;
    tmp->u.relexpgt_.add_exp_ = p2;
    return tmp;
}
/********************   RelExpLE    ********************/
Rel_Exp make_RelExpLE(Rel_Exp p1, Add_Exp p2)
{
    Rel_Exp tmp = (Rel_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  RelExpLE!\n");
        exit(1);
    }
    tmp->kind = is_RelExpLE;
    tmp->u.relexple_.rel_exp_ = p1;
    tmp->u.relexple_.add_exp_ = p2;
    return tmp;
}
/********************   RelExpGE    ********************/
Rel_Exp make_RelExpGE(Rel_Exp p1, Add_Exp p2)
{
    Rel_Exp tmp = (Rel_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  RelExpGE!\n");
        exit(1);
    }
    tmp->kind = is_RelExpGE;
    tmp->u.relexpge_.rel_exp_ = p1;
    tmp->u.relexpge_.add_exp_ = p2;
    return tmp;
}/********************   EqExpRel    ********************/
Eq_Exp make_EqExpRel(Rel_Exp p1)
{
    Eq_Exp tmp = (Eq_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  EqExpRel!\n");
        exit(1);
    }
    tmp->kind = is_EqExpRel;
    tmp->u.eqexprel_.rel_exp_ = p1;
    return tmp;
}
/********************   EqExpEQ    ********************/
Eq_Exp make_EqExpEQ(Eq_Exp p1, Rel_Exp p2)
{
    Eq_Exp tmp = (Eq_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  EqExpEQ!\n");
        exit(1);
    }
    tmp->kind = is_EqExpEQ;
    tmp->u.eqexpeq_.eq_exp_ = p1;
    tmp->u.eqexpeq_.rel_exp_ = p2;
    return tmp;
}
/********************   EqExpNE    ********************/
Eq_Exp make_EqExpNE(Eq_Exp p1, Rel_Exp p2)
{
    Eq_Exp tmp = (Eq_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  EqExpNE!\n");
        exit(1);
    }
    tmp->kind = is_EqExpNE;
    tmp->u.eqexpne_.eq_exp_ = p1;
    tmp->u.eqexpne_.rel_exp_ = p2;
    return tmp;
}/********************   LogAndExpEq    ********************/
Log_And_Exp make_LogAndExpEq(Eq_Exp p1)
{
    Log_And_Exp tmp = (Log_And_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  LogAndExpEq!\n");
        exit(1);
    }
    tmp->kind = is_LogAndExpEq;
    tmp->u.logandexpeq_.eq_exp_ = p1;
    return tmp;
}
/********************   LogAndExpAnd    ********************/
Log_And_Exp make_LogAndExpAnd(Log_And_Exp p1, Eq_Exp p2)
{
    Log_And_Exp tmp = (Log_And_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  LogAndExpAnd!\n");
        exit(1);
    }
    tmp->kind = is_LogAndExpAnd;
    tmp->u.logandexpand_.log_and_exp_ = p1;
    tmp->u.logandexpand_.eq_exp_ = p2;
    return tmp;
}/********************   LogOrExpLogAnd    ********************/
Log_Or_Exp make_LogOrExpLogAnd(Log_And_Exp p1)
{
    Log_Or_Exp tmp = (Log_Or_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  LogOrExpLogAnd!\n");
        exit(1);
    }
    tmp->kind = is_LogOrExpLogAnd;
    tmp->u.logorexplogand_.log_and_exp_ = p1;
    return tmp;
}
/********************   LogOrExpLogOr    ********************/
Log_Or_Exp make_LogOrExpLogOr(Log_Or_Exp p1, Log_And_Exp p2)
{
    Log_Or_Exp tmp = (Log_Or_Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  LogOrExpLogOr!\n");
        exit(1);
    }
    tmp->kind = is_LogOrExpLogOr;
    tmp->u.logorexplogor_.log_or_exp_ = p1;
    tmp->u.logorexplogor_.log_and_exp_ = p2;
    return tmp;
}/********************   ExpLogOr    ********************/
Expression make_ExpLogOr(Log_Or_Exp p1)
{
    Expression tmp = (Expression) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ExpLogOr!\n");
        exit(1);
    }
    tmp->kind = is_ExpLogOr;
    tmp->u.explogor_.log_or_exp_ = p1;
    return tmp;
}
/********************   ExpAss    ********************/
Expression make_ExpAss(Ident p1, Assign_Operator p2, Expression p3)
{
    Expression tmp = (Expression) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ExpAss!\n");
        exit(1);
    }
    tmp->kind = is_ExpAss;
    tmp->u.expass_.ident_ = p1;
    tmp->u.expass_.assign_operator_ = p2;
    tmp->u.expass_.expression_ = p3;
    return tmp;
}
/********************   ExpAssGraph    ********************/
Expression make_ExpAssGraph(Ident p1, Assign_Operator p2, Expression p3, Expression p4)
{
    Expression tmp = (Expression) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ExpAssGraph!\n");
        exit(1);
    }
    tmp->kind = is_ExpAssGraph;
    tmp->u.expassgraph_.ident_ = p1;
    tmp->u.expassgraph_.assign_operator_ = p2;
    tmp->u.expassgraph_.expression_1 = p3;
    tmp->u.expassgraph_.expression_2 = p4;
    return tmp;
}/********************   IniDecListIni    ********************/
Init_Decl_List make_IniDecListIni(Init_Declarator p1)
{
    Init_Decl_List tmp = (Init_Decl_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  IniDecListIni!\n");
        exit(1);
    }
    tmp->kind = is_IniDecListIni;
    tmp->u.inideclistini_.init_declarator_ = p1;
    return tmp;
}
/********************   IniDecList    ********************/
Init_Decl_List make_IniDecList(Init_Decl_List p1, Init_Declarator p2)
{
    Init_Decl_List tmp = (Init_Decl_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  IniDecList!\n");
        exit(1);
    }
    tmp->kind = is_IniDecList;
    tmp->u.inideclist_.init_decl_list_ = p1;
    tmp->u.inideclist_.init_declarator_ = p2;
    return tmp;
}/********************   IniDecId    ********************/
Init_Declarator make_IniDecId(Ident p1)
{
    Init_Declarator tmp = (Init_Declarator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  IniDecId!\n");
        exit(1);
    }
    tmp->kind = is_IniDecId;
    tmp->u.inidecid_.ident_ = p1;
    return tmp;
}
/********************   IniDecIdE    ********************/
Init_Declarator make_IniDecIdE(Ident p1, Assign_Operator p2, Log_Or_Exp p3)
{
    Init_Declarator tmp = (Init_Declarator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  IniDecIdE!\n");
        exit(1);
    }
    tmp->kind = is_IniDecIdE;
    tmp->u.inidecide_.ident_ = p1;
    tmp->u.inidecide_.assign_operator_ = p2;
    tmp->u.inidecide_.log_or_exp_ = p3;
    return tmp;
}/********************   VarDec    ********************/
Var_Declaration make_VarDec(Type p1, Init_Decl_List p2)
{
    Var_Declaration tmp = (Var_Declaration) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  VarDec!\n");
        exit(1);
    }
    tmp->kind = is_VarDec;
    tmp->u.vardec_.type_ = p1;
    tmp->u.vardec_.init_decl_list_ = p2;
    return tmp;
}/********************   VarDecListVar    ********************/
Var_Decl_List make_VarDecListVar(Var_Declaration p1)
{
    Var_Decl_List tmp = (Var_Decl_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  VarDecListVar!\n");
        exit(1);
    }
    tmp->kind = is_VarDecListVar;
    tmp->u.vardeclistvar_.var_declaration_ = p1;
    return tmp;
}
/********************   VarDecList    ********************/
Var_Decl_List make_VarDecList(Var_Decl_List p1, Var_Declaration p2)
{
    Var_Decl_List tmp = (Var_Decl_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  VarDecList!\n");
        exit(1);
    }
    tmp->kind = is_VarDecList;
    tmp->u.vardeclist_.var_decl_list_ = p1;
    tmp->u.vardeclist_.var_declaration_ = p2;
    return tmp;
}/********************   ParamListId    ********************/
Parameter_List make_ParamListId(Type p1, Ident p2)
{
    Parameter_List tmp = (Parameter_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ParamListId!\n");
        exit(1);
    }
    tmp->kind = is_ParamListId;
    tmp->u.paramlistid_.type_ = p1;
    tmp->u.paramlistid_.ident_ = p2;
    return tmp;
}
/********************   ParamList    ********************/
Parameter_List make_ParamList(Parameter_List p1, Type p2, Ident p3)
{
    Parameter_List tmp = (Parameter_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ParamList!\n");
        exit(1);
    }
    tmp->kind = is_ParamList;
    tmp->u.paramlist_.parameter_list_ = p1;
    tmp->u.paramlist_.type_ = p2;
    tmp->u.paramlist_.ident_ = p3;
    return tmp;
}/********************   StmListStm    ********************/
Statement_List make_StmListStm(Statement p1)
{
    Statement_List tmp = (Statement_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  StmListStm!\n");
        exit(1);
    }
    tmp->kind = is_StmListStm;
    tmp->u.stmliststm_.statement_ = p1;
    return tmp;
}
/********************   StmList    ********************/
Statement_List make_StmList(Statement_List p1, Statement p2)
{
    Statement_List tmp = (Statement_List) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  StmList!\n");
        exit(1);
    }
    tmp->kind = is_StmList;
    tmp->u.stmlist_.statement_list_ = p1;
    tmp->u.stmlist_.statement_ = p2;
    return tmp;
}/********************   StmOpen    ********************/
Statement make_StmOpen(Open_Stm p1)
{
    Statement tmp = (Statement) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  StmOpen!\n");
        exit(1);
    }
    tmp->kind = is_StmOpen;
    tmp->u.stmopen_.open_stm_ = p1;
    return tmp;
}
/********************   StmClosed    ********************/
Statement make_StmClosed(Closed_Stm p1)
{
    Statement tmp = (Statement) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  StmClosed!\n");
        exit(1);
    }
    tmp->kind = is_StmClosed;
    tmp->u.stmclosed_.closed_stm_ = p1;
    return tmp;
}/********************   OpnStmIfSmp    ********************/
Open_Stm make_OpnStmIfSmp(Expression p1, Simple_Stm p2)
{
    Open_Stm tmp = (Open_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  OpnStmIfSmp!\n");
        exit(1);
    }
    tmp->kind = is_OpnStmIfSmp;
    tmp->u.opnstmifsmp_.expression_ = p1;
    tmp->u.opnstmifsmp_.simple_stm_ = p2;
    return tmp;
}
/********************   OpnStmIfOpn    ********************/
Open_Stm make_OpnStmIfOpn(Expression p1, Open_Stm p2)
{
    Open_Stm tmp = (Open_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  OpnStmIfOpn!\n");
        exit(1);
    }
    tmp->kind = is_OpnStmIfOpn;
    tmp->u.opnstmifopn_.expression_ = p1;
    tmp->u.opnstmifopn_.open_stm_ = p2;
    return tmp;
}
/********************   OpnStmIfCls    ********************/
Open_Stm make_OpnStmIfCls(Expression p1, Closed_Stm p2, Open_Stm p3)
{
    Open_Stm tmp = (Open_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  OpnStmIfCls!\n");
        exit(1);
    }
    tmp->kind = is_OpnStmIfCls;
    tmp->u.opnstmifcls_.expression_ = p1;
    tmp->u.opnstmifcls_.closed_stm_ = p2;
    tmp->u.opnstmifcls_.open_stm_ = p3;
    return tmp;
}
/********************   OpnStmWhile    ********************/
Open_Stm make_OpnStmWhile(Expression p1, Open_Stm p2)
{
    Open_Stm tmp = (Open_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  OpnStmWhile!\n");
        exit(1);
    }
    tmp->kind = is_OpnStmWhile;
    tmp->u.opnstmwhile_.expression_ = p1;
    tmp->u.opnstmwhile_.open_stm_ = p2;
    return tmp;
}/********************   BlkStm    ********************/
Block_Stm make_BlkStm()
{
    Block_Stm tmp = (Block_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  BlkStm!\n");
        exit(1);
    }
    tmp->kind = is_BlkStm;
    return tmp;
}
/********************   BlkStmList    ********************/
Block_Stm make_BlkStmList(Statement_List p1)
{
    Block_Stm tmp = (Block_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  BlkStmList!\n");
        exit(1);
    }
    tmp->kind = is_BlkStmList;
    tmp->u.blkstmlist_.statement_list_ = p1;
    return tmp;
}
/********************   BlkStmVar    ********************/
Block_Stm make_BlkStmVar(Var_Decl_List p1)
{
    Block_Stm tmp = (Block_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  BlkStmVar!\n");
        exit(1);
    }
    tmp->kind = is_BlkStmVar;
    tmp->u.blkstmvar_.var_decl_list_ = p1;
    return tmp;
}
/********************   BlkStmVarStm    ********************/
Block_Stm make_BlkStmVarStm(Var_Decl_List p1, Statement_List p2)
{
    Block_Stm tmp = (Block_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  BlkStmVarStm!\n");
        exit(1);
    }
    tmp->kind = is_BlkStmVarStm;
    tmp->u.blkstmvarstm_.var_decl_list_ = p1;
    tmp->u.blkstmvarstm_.statement_list_ = p2;
    return tmp;
}/********************   RetStmRet    ********************/
Return_Stm make_RetStmRet()
{
    Return_Stm tmp = (Return_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  RetStmRet!\n");
        exit(1);
    }
    tmp->kind = is_RetStmRet;
    return tmp;
}
/********************   RetStmExp    ********************/
Return_Stm make_RetStmExp(Expression p1)
{
    Return_Stm tmp = (Return_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  RetStmExp!\n");
        exit(1);
    }
    tmp->kind = is_RetStmExp;
    tmp->u.retstmexp_.expression_ = p1;
    return tmp;
}/********************   ExpStmNul    ********************/
Exp_Stm make_ExpStmNul()
{
    Exp_Stm tmp = (Exp_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ExpStmNul!\n");
        exit(1);
    }
    tmp->kind = is_ExpStmNul;
    return tmp;
}
/********************   ExpStmExp    ********************/
Exp_Stm make_ExpStmExp(Expression p1)
{
    Exp_Stm tmp = (Exp_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ExpStmExp!\n");
        exit(1);
    }
    tmp->kind = is_ExpStmExp;
    tmp->u.expstmexp_.expression_ = p1;
    return tmp;
}/********************   ClosedStmSmp    ********************/
Closed_Stm make_ClosedStmSmp(Simple_Stm p1)
{
    Closed_Stm tmp = (Closed_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ClosedStmSmp!\n");
        exit(1);
    }
    tmp->kind = is_ClosedStmSmp;
    tmp->u.closedstmsmp_.simple_stm_ = p1;
    return tmp;
}
/********************   ClosedStmIf    ********************/
Closed_Stm make_ClosedStmIf(Expression p1, Closed_Stm p2, Closed_Stm p3)
{
    Closed_Stm tmp = (Closed_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ClosedStmIf!\n");
        exit(1);
    }
    tmp->kind = is_ClosedStmIf;
    tmp->u.closedstmif_.expression_ = p1;
    tmp->u.closedstmif_.closed_stm_1 = p2;
    tmp->u.closedstmif_.closed_stm_2 = p3;
    return tmp;
}
/********************   ClosedStmWhile    ********************/
Closed_Stm make_ClosedStmWhile(Expression p1, Closed_Stm p2)
{
    Closed_Stm tmp = (Closed_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ClosedStmWhile!\n");
        exit(1);
    }
    tmp->kind = is_ClosedStmWhile;
    tmp->u.closedstmwhile_.expression_ = p1;
    tmp->u.closedstmwhile_.closed_stm_ = p2;
    return tmp;
}/********************   SmpStmBlock    ********************/
Simple_Stm make_SmpStmBlock(Block_Stm p1)
{
    Simple_Stm tmp = (Simple_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  SmpStmBlock!\n");
        exit(1);
    }
    tmp->kind = is_SmpStmBlock;
    tmp->u.smpstmblock_.block_stm_ = p1;
    return tmp;
}
/********************   SmpStmExp    ********************/
Simple_Stm make_SmpStmExp(Exp_Stm p1)
{
    Simple_Stm tmp = (Simple_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  SmpStmExp!\n");
        exit(1);
    }
    tmp->kind = is_SmpStmExp;
    tmp->u.smpstmexp_.exp_stm_ = p1;
    return tmp;
}
/********************   SmpStmRet    ********************/
Simple_Stm make_SmpStmRet(Return_Stm p1)
{
    Simple_Stm tmp = (Simple_Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  SmpStmRet!\n");
        exit(1);
    }
    tmp->kind = is_SmpStmRet;
    tmp->u.smpstmret_.return_stm_ = p1;
    return tmp;
}/********************   DecIdParam    ********************/
Declarator make_DecIdParam(Ident p1, Parameter_List p2)
{
    Declarator tmp = (Declarator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  DecIdParam!\n");
        exit(1);
    }
    tmp->kind = is_DecIdParam;
    tmp->u.decidparam_.ident_ = p1;
    tmp->u.decidparam_.parameter_list_ = p2;
    return tmp;
}
/********************   DecId    ********************/
Declarator make_DecId(Ident p1)
{
    Declarator tmp = (Declarator) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  DecId!\n");
        exit(1);
    }
    tmp->kind = is_DecId;
    tmp->u.decid_.ident_ = p1;
    return tmp;
}/********************   FunDef    ********************/
Function_Def make_FunDef(Type p1, Declarator p2, Block_Stm p3)
{
    Function_Def tmp = (Function_Def) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  FunDef!\n");
        exit(1);
    }
    tmp->kind = is_FunDef;
    tmp->u.fundef_.type_ = p1;
    tmp->u.fundef_.declarator_ = p2;
    tmp->u.fundef_.block_stm_ = p3;
    return tmp;
}/********************   ExtVarDecFun    ********************/
Ext_Var_Decl make_ExtVarDecFun(Function_Def p1)
{
    Ext_Var_Decl tmp = (Ext_Var_Decl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ExtVarDecFun!\n");
        exit(1);
    }
    tmp->kind = is_ExtVarDecFun;
    tmp->u.extvardecfun_.function_def_ = p1;
    return tmp;
}
/********************   ExtVarDecVar    ********************/
Ext_Var_Decl make_ExtVarDecVar(Var_Declaration p1)
{
    Ext_Var_Decl tmp = (Ext_Var_Decl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar no para a regra  ExtVarDecVar!\n");
        exit(1);
    }
    tmp->kind = is_ExtVarDecVar;
    tmp->u.extvardecvar_.var_declaration_ = p1;
    return tmp;
}
