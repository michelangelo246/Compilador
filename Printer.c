/**	Michelangelo da R. Machado - 14/0156089 **/

#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int _n_;
char *buf_;
int cur_;
int buf_size;
char buffer [99];

char *showTrans_Unit(No p)
{
  _n_ = 0;
  bufReset();
  bufAppendS("digraph { ");
  shTree(p,0);
  bufAppendS(" }");
  return buf_;
}

int aux_pos;

void shTree(No p, int pos)
{
	Nos aux;
	
	printKind(p->kind,0);
	
	switch(p->kind)
	{
	case is_ConstInt:
		printf(" %d ",p->u.constint_.integer_);
		break;
	case is_ConstDouble:
		printf(" %g ",p->u.constdouble_.double_);
		break;
	case is_ConstStr:
		printf(" %s ",p->u.conststr_.string_);
		break;
	default:
		break;
	}
	
	//Caso regra possua um identificador no corpo, imprime um nó para o identificador
	if((p->kind == is_PosExpSub ) || (p->kind == is_ExpPRINTV) || 
	(p->kind == is_PosExpIn ) || (p->kind == is_PosExpOut ) || (p->kind == is_ExpPRINTVN) ||
	(p->kind == is_PosExpNeig ) || (p->kind == is_PosExpCal ) || (p->kind == is_PosExpCalArg ) ||
	(p->kind == is_ExpAss ) || (p->kind == is_ExpAssGraph ) || (p->kind == is_IniDecIdE ) || 
	(p->kind == is_ParamListId ) || (p->kind == is_ParamList ) || (p->kind == is_DecIdParam ) || (p->kind == is_DecId ))
	{
		printf(" %s ",p->u.ident_.ident_);
		
		aux_pos = pos+1;
		sprintf(buffer, "\"%s [%s] (%d)\"", printKind(p->kind,1), printType(p->type), pos);
		bufAppendS(buffer);
		bufAppendS(" -> ");
		sprintf(buffer, "\"%s [%s] (%d)\"", p->u.ident_.ident_, printType(SymbolTable_lookup_all(p->u.ident_.ident_).linha!=NULL?SymbolTable_lookup_all(p->u.ident_.ident_).linha->u.ident.Type:Is_TypeVoid), aux_pos);
		bufAppendS(buffer);
		bufAppendS("; ");
		sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(p->kind,1), printType(p->type), pos, printKind(p->kind,1), printType(p->type));
		bufAppendS(buffer);
		sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", p->u.ident_.ident_, printType(SymbolTable_lookup_all(p->u.ident_.ident_).linha!=NULL?SymbolTable_lookup_all(p->u.ident_.ident_).linha->u.ident.Type:Is_TypeVoid), aux_pos, p->u.ident_.ident_, printType(SymbolTable_lookup_all(p->u.ident_.ident_).linha!=NULL?SymbolTable_lookup_all(p->u.ident_.ident_).linha->u.ident.Type:Is_TypeVoid));
		bufAppendS(buffer);
		aux_pos++;
	}
	
	aux_pos = pos+1;
	aux = p->filhos;
	while(aux)
	{
		switch(aux->no->kind)
		{
		case is_ConstInt:
			aux_pos = pos+1;
			sprintf(buffer, "\"%s [%s] (%d)\"", printKind(p->kind,1), printType(p->type), pos);
			bufAppendS(buffer);
			bufAppendS(" -> ");
			sprintf(buffer, "\"%d [%s] (%d)\"", aux->no->u.constint_.integer_, printType(aux->no->type), aux_pos);
			bufAppendS(buffer);
			bufAppendS("; ");
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(p->kind,1), printType(p->type), pos, printKind(p->kind,1), printType(p->type));
			bufAppendS(buffer);
			sprintf(buffer, "\"%d [%s] (%d)\" [label = \" %d [%s] \"];", aux->no->u.constint_.integer_, printType(aux->no->type), aux_pos, aux->no->u.constint_.integer_, printType(aux->no->type));
			bufAppendS(buffer);
			aux_pos++;
			break;
		case is_ConstDouble:
			aux_pos = pos+1;
			sprintf(buffer, "\"%s [%s] (%d)\"", printKind(p->kind,1), printType(p->type), pos);
			bufAppendS(buffer);
			bufAppendS(" -> ");
			sprintf(buffer, "\"%g [%s] (%d)\"", aux->no->u.constdouble_.double_, printType(aux->no->type), aux_pos);
			bufAppendS(buffer);
			bufAppendS("; ");
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(p->kind,1), printType(p->type), pos, printKind(p->kind,1), printType(p->type));
			bufAppendS(buffer);
			sprintf(buffer, "\"%g [%s] (%d)\" [label = \" %g [%s] \"];", aux->no->u.constdouble_.double_, printType(aux->no->type), aux_pos, aux->no->u.constdouble_.double_, printType(aux->no->type));
			bufAppendS(buffer);
			aux_pos++;
			break;
		case is_ConstStr:
			aux_pos = pos+1;
			sprintf(buffer, "\"%s [%s] (%d)\"", printKind(p->kind,1), printType(p->type), pos);
			bufAppendS(buffer);
			bufAppendS(" -> ");
			sprintf(buffer, "\"%s [%s] (%d)\"", aux->no->u.conststr_.string_, printType(aux->no->type), aux_pos);
			bufAppendS(buffer);
			bufAppendS("; ");
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(p->kind,1), printType(p->type), pos, printKind(p->kind,1), printType(p->type));
			bufAppendS(buffer);
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", aux->no->u.conststr_.string_, printType(aux->no->type), aux_pos, aux->no->u.conststr_.string_, printType(aux->no->type));
			bufAppendS(buffer);
			aux_pos++;
			break;
		case is_IniDecId:
			aux_pos = pos+1;
			sprintf(buffer, "\"%s [%s] (%d)\"", printKind(p->kind,1), printType(p->type), pos);
			bufAppendS(buffer);
			bufAppendS(" -> ");
			sprintf(buffer, "\"%s [%s] (%d)\"", aux->no->u.ident_.ident_, printType(aux->no->type), aux_pos);
			bufAppendS(buffer);
			bufAppendS("; ");
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(p->kind,1), printType(p->type), pos, printKind(p->kind,1), printType(p->type));
			bufAppendS(buffer);
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", aux->no->u.ident_.ident_, printType(aux->no->type), aux_pos, aux->no->u.ident_.ident_, printType(aux->no->type));
			bufAppendS(buffer);
			aux_pos++;
			break;
		case is_PriExpId:
			aux_pos = pos+1;
			sprintf(buffer, "\"%s [%s] (%d)\"", printKind(p->kind,1), printType(p->type), pos);
			bufAppendS(buffer);
			bufAppendS(" -> ");
			sprintf(buffer, "\"%s [%s] (%d)\"", aux->no->u.ident_.ident_, printType(aux->no->type), aux_pos);
			bufAppendS(buffer);
			bufAppendS("; ");
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(p->kind,1), printType(p->type), pos, printKind(p->kind,1), printType(p->type));
			bufAppendS(buffer);
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", aux->no->u.ident_.ident_, printType(aux->no->type), aux_pos, aux->no->u.ident_.ident_, printType(aux->no->type));
			bufAppendS(buffer);
			aux_pos++;
			break;
		default:
			sprintf(buffer, "\"%s [%s] (%d)\"", printKind(p->kind,1), printType(p->type), pos);
			bufAppendS(buffer);
			bufAppendS(" -> ");
			sprintf(buffer, "\"%s [%s] (%d)\"", printKind(aux->no->kind,1), printType(aux->no->type), aux_pos);
			bufAppendS(buffer);
			bufAppendS("; ");
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(p->kind,1), printType(p->type), pos, printKind(p->kind,1), printType(p->type));
			bufAppendS(buffer);
			sprintf(buffer, "\"%s [%s] (%d)\" [label = \" %s [%s] \"];", printKind(aux->no->kind,1), printType(aux->no->type), aux_pos, printKind(aux->no->kind,1), printType(aux->no->type));
			bufAppendS(buffer);
			
			shTree(aux->no,aux_pos);
			aux_pos++;
		}
		
		aux = aux->next;
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

char* printType(_Type type)
{
	switch(type)
	{
	case Is_TypeVoid:
		return "void";
		break;
	case Is_TypeInt:
		return "int";
		break;
	case Is_TypeDouble:
		return "double";
		break;
	case Is_TypeGraph:
		return "graph";
		break;
	case Is_TypeString:
		return "string";
		break;
	case Is_TypeBool:
		return "bool";
		break;
	default:
		return "void";
		break;
	}
}

char* printKind(int kind, int modo)
{
	switch(kind)
	{
	case is_TraUniExtVar: if(modo==0)printf(" TraUniExtVar ");else return" TraUniExtVar "; break; 
	case is_TraUniList: if(modo==0)printf(" TraUniList ");else return " TraUniList "; break; 
	case is_AssOpEQ: if(modo==0)printf(" \"=\" ");else return " = "; break; 
	case is_AssOpINS: if(modo==0)printf(" \"<<\" ");else return " << "; break; 
	case is_ConstInt: if(modo==0)printf(" ConstInt ");else return " ConstInt "; break; 
	case is_ConstDouble: if(modo==0)printf(" ConstDouble ");else return " ConstDouble "; break; 
	case is_ConstStr: if(modo==0)printf(" ConstStr ");else return " ConstStr "; break; 
	case is_UnaOpMinus: if(modo==0)printf(" \"-\" ");else return " - "; break; 
	case is_UnaOpNot: if(modo==0)printf(" \"!\" ");else return " ! "; break; 
	case is_TypeVoid: if(modo==0)printf(" \"void\" ");else return " void "; break; 
	case is_TypeInt: if(modo==0)printf(" \"int\" ");else return " int "; break; 
	case is_TypeDouble: if(modo==0)printf(" \"double\" ");else return " double "; break; 
	case is_TypeGraph: if(modo==0)printf(" \"graph\" ");else return " graph "; break; 
	case is_ArgExpListExp: if(modo==0)printf(" ArgExpListExp ");else return " ArgExpListExp "; break; 
	case is_ArgExpList: if(modo==0)printf(" ArgExpList ");else return " ArgExpList "; break; 
	case is_PriExpId: if(modo==0)printf(" PriExpId ");else return " PriExpId "; break; 
	case is_PriExpConst: if(modo==0)printf(" PriExpConst ");else return " PriExpConst "; break; 
	case is_PriExpExp: if(modo==0)printf(" PriExpExp ");else return " PriExpExp "; break; 
	case is_PosExpPri: if(modo==0)printf(" PosExpPri ");else return " PosExpPri "; break; 
	case is_PosExpSub: if(modo==0)printf(" PosExpSub ");else return " PosExpSub "; break; 
	case is_PosExpIn: if(modo==0)printf(" PosExpIn ");else return " @()# "; break; 
	case is_PosExpOut: if(modo==0)printf(" PosExpOut ");else return " #()@ "; break; 
	case is_PosExpNeig: if(modo==0)printf(" PosExpNeig ");else return " &()& "; break; 
	case is_PosExpCal: if(modo==0)printf(" PosExpCal ");else return " PosExpCal "; break; 
	case is_PosExpCalArg: if(modo==0)printf(" PosExpCalArg ");else return " PosExpCalArg "; break; 
	case is_UnaExpPos: if(modo==0)printf(" UnaExpPos ");else return " UnaExpPos "; break; 
	case is_UnaExpOp: if(modo==0)printf(" UnaExpOp ");else return " UnaExpOp "; break; 
	case is_MulExpUna: if(modo==0)printf(" MulExpUna ");else return " MulExpUna "; break; 
	case is_MulExpMul: if(modo==0)printf(" MulExpMul ");else return " * "; break; 
	case is_MulExpDiv: if(modo==0)printf(" MulExpDiv ");else return " / "; break; 
	case is_AddExpMul: if(modo==0)printf(" AddExpMul ");else return " AddExpMul "; break; 
	case is_AddExpAdd: if(modo==0)printf(" AddExpAdd ");else return " + "; break; 
	case is_AddExpSub: if(modo==0)printf(" AddExpSub ");else return " - "; break; 
	case is_RelExpAdd: if(modo==0)printf(" RelExpAdd ");else return " RelExpAdd "; break; 
	case is_RelExpLT: if(modo==0)printf(" RelExpLT ");else return " < "; break; 
	case is_RelExpGT: if(modo==0)printf(" RelExpGT ");else return " > "; break; 
	case is_RelExpLE: if(modo==0)printf(" RelExpLE ");else return " <= "; break; 
	case is_RelExpGE: if(modo==0)printf(" RelExpGE ");else return " >= "; break; 
	case is_EqExpRel: if(modo==0)printf(" EqExpRel ");else return " EqExpRel "; break; 
	case is_EqExpEQ: if(modo==0)printf(" EqExpEQ ");else return " == "; break; 
	case is_EqExpNE: if(modo==0)printf(" EqExpNE ");else return " != "; break; 
	case is_LogAndExpEq: if(modo==0)printf(" LogAndExpEq ");else return " LogAndExpEq "; break; 
	case is_LogAndExpAnd: if(modo==0)printf(" LogAndExpAnd ");else return " && "; break; 
	case is_LogOrExpLogAnd: if(modo==0)printf(" LogOrExpLogAnd ");else return " LogOrExpLogAnd "; break; 
	case is_LogOrExpLogOr: if(modo==0)printf(" LogOrExpLogOr ");else return " || "; break; 
	case is_ExpLogOr: if(modo==0)printf(" ExpLogOr ");else return " ExpLogOr "; break; 
	case is_ExpAss: if(modo==0)printf(" ExpAss ");else return " ExpAss "; break; 
	case is_ExpAssGraph: if(modo==0)printf(" ExpAssGraph ");else return " ExpAssGraph "; break; 
	case is_IniDecListIni: if(modo==0)printf(" IniDecListIni ");else return " IniDecListIni "; break; 
	case is_ExpPRINT: if(modo==0)printf(" PRINT ");else return " PRINT "; break; 
	case is_ExpPRINTV: if(modo==0)printf(" PRINTV ");else return " PRINTV "; break; 
	case is_ExpPRINTVN: if(modo==0)printf(" PRINTVN ");else return " PRINTVN "; break; 
	case is_ExpPRINTA: if(modo==0)printf(" PRINTA ");else return " PRINTA "; break; 
	case is_ExpPRINTAD: if(modo==0)printf(" PRINTD ");else return " PRINTD "; break; 
	case is_ExpSCAN: if(modo==0)printf(" SCAN ");else return " SCAN "; break; 
	case is_IniDecList: if(modo==0)printf(" IniDecList ");else return " IniDecList "; break; 
	case is_IniDecId: if(modo==0)printf(" IniDecId ");else return " IniDecId "; break; 
	case is_IniDecIdE: if(modo==0)printf(" IniDecIdE ");else return " IniDecIdE "; break; 
	case is_VarDec: if(modo==0)printf(" VarDec ");else return " VarDec "; break; 
	case is_VarDecListVar: if(modo==0)printf(" VarDecListVar ");else return " VarDecListVar "; break; 
	case is_VarDecList: if(modo==0)printf(" VarDecList ");else return " VarDecList "; break; 
	case is_ParamListId: if(modo==0)printf(" ParamListId ");else return " ParamListId "; break; 
	case is_ParamList: if(modo==0)printf(" ParamList ");else return " ParamList "; break; 
	case is_StmListStm: if(modo==0)printf(" StmListStm ");else return " StmListStm "; break; 
	case is_StmList: if(modo==0)printf(" StmList ");else return " StmList "; break; 
	case is_BlkStm: if(modo==0)printf(" BlkStm \"{}\"");else return " BlkStm {}"; break; 
	case is_BlkStmList: if(modo==0)printf(" BlkStmList ");else return " BlkStmList "; break; 
	case is_BlkStmVar: if(modo==0)printf(" BlkStmVar ");else return " BlkStmVar "; break; 
	case is_BlkStmVarStm: if(modo==0)printf(" BlkStmVarStm ");else return " BlkStmVarStm "; break; 
	case is_RetStmRet: if(modo==0)printf(" RetStmRet ");else return " RetStmRet "; break; 
	case is_RetStmExp: if(modo==0)printf(" RetStmExp ");else return " return "; break; 
	case is_ExpStmNul: if(modo==0)printf(" ExpStmNul \";\" ");else return " ExpStmNul ; "; break; 
	case is_ExpStmExp: if(modo==0)printf(" ExpStmExp ");else return " ExpStmExp "; break; 
	case is_WhileStm: if(modo==0)printf(" WhileStm ");else return " WhileStm "; break; 
	case is_StmBlock: if(modo==0)printf(" StmBlock ");else return " StmBlock "; break; 
	case is_StmExp: if(modo==0)printf(" StmExp ");else return " StmExp "; break; 
	case is_StmRet: if(modo==0)printf(" StmRet ");else return " StmRet "; break; 
	case is_DecIdParam: if(modo==0)printf(" DecIdParam ");else return " DecIdParam "; break; 
	case is_DecId: if(modo==0)printf(" DecId ");else return " DecId "; break; 
	case is_FunDef: if(modo==0)printf(" FunDef ");else return " FunDef "; break; 
	case is_ExtVarDecFun: if(modo==0)printf(" ExtVarDecFun ");else return " ExtVarDecFun "; break; 
	case is_ExtVarDecVar : if(modo==0)printf(" ExtVarDecVar  ");else return " ExtVarDecVar  "; break; 
	case is_IfStmIf : if(modo==0)printf(" IfStmIf  ");else return " IfStmIf  "; break; 
	case is_IfStmElse : if(modo==0)printf(" IfStmElse  ");else return " IfStmElse  "; break; 
	} 
	return NULL; 
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
