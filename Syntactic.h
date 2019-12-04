/**	Michelangelo da R. Machado - 14/0156089 **/

#ifndef SYNTACTIC_HEADER
#define SYNTACTIC_HEADER
#include <stdio.h>

/********************   TypeDefs    ********************/

typedef int Integer;
typedef double Double;
typedef char *String;
typedef char *Ident;

/********************   Declarações Adiantadas   ********************/

struct No_;
typedef struct No_ *No;
int error;

/********************   Tabela de simbolos    ********************/

typedef enum { Is_TypeVoid, Is_TypeInt, Is_TypeDouble, Is_TypeGraph, Is_TypeString, Is_TypeBool } _Type;
typedef enum { Is_ConstInt, Is_ConstDouble, Is_ConstStr, Is_Ident, Is_No } _Kind;

typedef struct Function_Param_
{
	Ident name;
	_Type Type;
	struct Function_Param_ *next;
	
}Function_Param;

typedef struct Table_Line_
{
	_Kind Kind;
	
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
			int temp;
			int line;
			int column;
		} ident;
	} u;
	
	struct Table_Line_ *next;
	
}Table_Line;

typedef struct Symbol_Table_
{
	String name;
	int index_name;
	struct Table_Line_ *lines;
	struct Symbol_Table_ *next;
	
}Symbol_Table;

/*Mantem referencia para todas os contextos criados*/
typedef struct Symbol_Table_Set_
{
	Symbol_Table *table;
	struct Symbol_Table_Set_ *next;
	
}Symbol_Table_Set;

/*Container para retornar linha e contexto da função lookup*/
typedef struct LookUp_Return_
{
	Table_Line *linha;
	Symbol_Table *contexto;
}LookUp_Return;


Symbol_Table *newSymbol_Table(String nome, int index);

void SymbolTable_ins_ConstInt(Integer symbol, int linha, int coluna);
void SymbolTable_ins_ConstDouble(Double symbol, int linha, int coluna);
void SymbolTable_ins_constStr(String symbol, int linha, int coluna);

void SymbolTable_ins_Var(Ident identificador, int linha, int coluna, int tipo);
void SymbolTable_ins_Fun(String identificador, int linha, int coluna, int tipo, No parametros);

void SymbolTable_copy_args(String recent_identifier);
LookUp_Return SymbolTable_lookup(Ident p1);
LookUp_Return SymbolTable_lookup_all(Ident p1);
void SymbolTable_Show();


Symbol_Table *SymbolTable;
Symbol_Table_Set *SymbolTableSet;

/********************   Arvore    ********************/

typedef struct Nos_ *Nos;
typedef struct Args_ *Args;

struct Args_
{
	enum { t_int, t_double, t_string, t_ident } kind;
	
	union
	{
		Integer int_;
		Double double_;
		String str_;
		Ident ident_;
	} u;
	
	struct Args_ *next;
};

struct Nos_
{
	No no;
	
	struct Nos_ *next;
};

struct No_
{
	enum { is_TraUniExtVar, is_TraUniList, is_AssOpEQ, is_AssOpINS, is_ConstInt, is_ConstDouble, 
		   is_ConstStr, is_UnaOpMinus, is_UnaOpNot, is_TypeVoid, is_TypeInt, is_TypeDouble, is_TypeGraph, 
		   is_ArgExpListExp, is_ArgExpList, is_PriExpId, is_PriExpConst, is_PriExpExp, is_PosExpPri, 
		   is_PosExpSub, is_PosExpIn, is_PosExpOut, is_PosExpNeig, is_PosExpCal, is_PosExpCalArg, 
		   is_UnaExpPos, is_UnaExpOp, is_MulExpUna, is_MulExpMul, is_MulExpDiv, is_AddExpMul, is_AddExpAdd, 
		   is_AddExpSub, is_RelExpAdd, is_RelExpLT, is_RelExpGT, is_RelExpLE, is_RelExpGE, is_EqExpRel, 
		   is_EqExpEQ, is_EqExpNE, is_LogAndExpEq, is_LogAndExpAnd, is_LogOrExpLogAnd, is_LogOrExpLogOr, is_ExpPRINTA,
		   is_ExpLogOr, is_ExpAss, is_ExpAssGraph, is_IniDecListIni, is_IniDecList, is_IniDecId, is_ExpPRINT,
		   is_IniDecIdE, is_VarDec, is_VarDecListVar, is_VarDecList, is_ParamListId, is_ParamList, is_ExpStmNul,
		   is_StmListStm, is_StmList, is_BlkStm, is_BlkStmList, is_BlkStmVar, is_BlkStmVarStm, is_RetStmRet, is_RetStmExp, 
		   is_ExpStmExp, is_IfStmIf, is_IfStmElse, is_WhileStm, is_StmBlock, is_ExpSCAN, is_ExpPRINTV, is_ExpPRINTVN,
		   is_StmExp, is_StmRet, is_DecIdParam, is_DecId, is_FunDef, is_ExtVarDecFun, is_ExtVarDecVar } kind;
		   
	union
	{
		struct { Ident ident_; } ident_;
		struct { Integer integer_; } constint_;
		struct { Double double_; } constdouble_;
		struct { String string_; } conststr_;
	} u;

	int temp;
	int aux;

	_Type type;
	
	Nos filhos;
};

No make_No(int p1, Nos p2, Args p3, _Type type);
Nos ins_No(No p1, Nos p2);
Args ins_Args_Int(int kind, Integer p1, Args p2);
Args ins_Args_Double(int kind, Double p1, Args p2);
Args ins_Args_Str(int kind, String p1, Args p2);
Args ins_Args_Ident(int kind, Ident p1, Args p2);
extern char* printType(_Type type);
int verifica_Params_Args(Function_Param * param, No no, Ident p1);
void print_Arg_Exp_List(No no);


/********************   3 Addr Code    ********************/


int TempCount;
int _n_Code;
int _n_Table;
char *buf_Code;
char *buf_Table;
int cur_Code;
int cur_Table;
int buf_code_size;
int buf_table_size;
int whileCont;
int IfCont;
int while_grafo;
int retorno;
char lastAddr1[99];
char lastAddr2[99];

int genTemp();
void bufAppendCode(char *s);
void bufAppendTable(char *s);
void bufCodeResize(void);
void bufTableResize(void);
void getAddr1(No no);
void getAddr2(No no);
void getAddrIdent(Ident ident);
void getLabelWhile();
int widen(No p0,No p1, No p3, int kind);
void inicializaPRINTVN();
void inicializaPRINTV();
void inicializaPRINTA();
void inicializaInsNo();
void inicializaInsAresta();
void inicializaGetGrauIn();
void inicializaGetGrauOut();
void inicializaNeig();

#endif
