/**	Michelangelo da R. Machado - 14/0156089 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Syntactic.h"


/********************    Funcoes da tabela de simbolos    ********************/
Symbol_Table *newSymbol_Table()
{
	Symbol_Table *tmp = (Symbol_Table*) malloc(sizeof(Symbol_Table));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar tabela de simbolos!\n");
        exit(1);
    }
	tmp->next = SymbolTable;
	tmp->lines = NULL;
	
	Symbol_Table_Set *aux = (Symbol_Table_Set *) malloc(sizeof(Symbol_Table_Set));
	aux->table = tmp;
	aux->next = SymbolTableSet;
	SymbolTableSet = aux;
	
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

void insVarSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4, No p5)
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
	tmp->u.ident.Type = p5->kind-9;
	tmp->next = p1->lines;
	p1->lines = tmp;
}

/*Usada */
void insFuncSymbol_Table(Symbol_Table *p1, String p2, int p3, int p4, No p5, No p6)
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
	tmp->u.ident.Type = p5->kind-9;
	tmp->u.ident.param = NULL;
	
	No tmp2 = p6;
	Function_Param *aux;
	while(tmp2)
	{
		if(tmp2->kind == is_ParamList)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(tmp2->u.ident_.ident_);
			aux->Type = tmp2->filhos->next->no->kind-9;
			
			aux->next = tmp->u.ident.param;
			tmp->u.ident.param = aux;
			
			tmp2 = tmp2->filhos->no;
		}
		else if(tmp2->kind == is_ParamListId)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(tmp2->u.ident_.ident_);
			aux->Type = tmp2->filhos->no->kind-9;
			
			aux->next = tmp->u.ident.param;
			tmp->u.ident.param = aux;
			tmp2 = NULL;
		}
	}
	
	tmp->next = p1->lines;
	p1->lines = tmp;
}

/*Usada na regra de declaração de variavel. Percorre a lista de declarações 
  do código fonte (e.g. int a,b,c), inserindo na tabela de simbolos todos 
  identificadores da lista com o tipo encontrado no comando de declaração*/
void insTableSymbol_VarDec(No p1, No p2, int line, int column)
{
	No tmp = p2;
	String name;
	while(tmp)
	{
		switch(tmp->kind)
		{
		case is_IniDecListIni:
			if(tmp->filhos->no->kind == is_IniDecId)
			{
				name = tmp->filhos->no->u.ident_.ident_;
			}
			else
			{
				name = tmp->filhos->no->u.ident_.ident_;
			}
			insVarSymbol_Table(SymbolTable, name , line, column, p1);
			tmp = NULL;
			break;
		case is_IniDecList:
			if(tmp->filhos->next->no->kind == is_IniDecId)
			{
				name = tmp->filhos->next->no->u.ident_.ident_;
			}
			else
			{
				name = tmp->filhos->next->no->u.ident_.ident_;
			}
			insVarSymbol_Table(SymbolTable, name , line, column, p1);
			tmp = tmp->filhos->no;
			break;
		default:
			break;
		}
	}
}

/*Imprime todas as tabelas de símbolos criadas*/
void showSymbolTable()
{
	Table_Line *aux;
	Function_Param *aux2;
	Symbol_Table_Set *aux3 = SymbolTableSet;
	
	
	while(aux3)
	{
		printf("\n[ Tabela ]\n");
		
		aux = aux3->table->lines;
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
			default:
				break;
			}
			aux = aux->next;
		}
		aux3 = aux3->next;
	}
}

/********************   Arvore    ********************/

/* Cria um nó com as informações passadas
Argumentos:
   p1: Inteiro que identifica a regra que gerou o no.
   p2: Filhos do no.
   p3: Outros argumentos que possam ser relevantes ao no.
*/
No make_No(int p1, Nos p2, Args p3)
{
	No no = (No) malloc(sizeof(struct No_));
	Args aux;
	
	no->kind = p1;
	no->filhos = p2;
	
	switch(p1)
	{
	case is_ConstInt:
		no->u.constint_.integer_ = p3->u.int_;
		break;
	case is_ConstDouble:
		no->u.constdouble_.double_ = p3->u.double_;
		break;
	case is_ConstStr:
		no->u.conststr_.string_ = p3->u.str_;
		break;
	default:
		break;
	}
	
	//Regras que possuem um identificador no corpo recebem um nó com esse identificador armazenado*
	if((p1 == is_PriExpId) ||
	(p1 == is_PosExpSub ) || (p1 == is_PosExpIn ) || (p1 == is_PosExpOut ) ||
	(p1 == is_PosExpNeig ) || (p1 == is_PosExpCal ) || (p1 == is_PosExpCalArg ) ||
	(p1 == is_ExpAss ) || (p1 == is_ExpAssGraph ) || (p1 == is_IniDecId ) ||
	(p1 == is_IniDecIdE ) || (p1 == is_ParamListId ) || (p1 == is_ParamList ) ||
	(p1 == is_DecIdParam ) || (p1 == is_DecId ))
	{
		no->u.ident_.ident_ = p3->u.ident_;
	}
	
	//Libera a memória alocada pela lista de argumentos, a qual serve apenas de container, seus valores são armazenados no nó retornado
	while(p3)
	{
		aux = p3;
		p3 = p3->next;
		free(aux);
	}
	
	return no;
}

/*Recebe um no unitário p1 e uma lista de nos p2 (ou NULL), insere o no unitário na frente da lista e retorna a lista resultante*/
Nos ins_No(No p1, Nos p2)
{
	Nos nos = (Nos) malloc(sizeof(struct Nos_));
	
	nos->no = p1;
	
	nos->next = p2;
	
	return nos;
}

union{
	int int_;
	double double_;
	String string_;
	Ident ident_;
}any;

/*Recebe um no unitário de int p1 e uma lista de nos de int p2 (ou NULL), insere o no unitário na frente da lista e retorna a lista resultante*/
Args ins_Args_Int(int kind, Integer p1, Args p2)
{
	Args args = (Args) malloc(sizeof(struct Args_));
	
	args->kind = kind;
	
	args->u.int_ = p1;
	
	args->next = p2;
	
	return args;
}

/*Recebe um no unitário de double p1 e uma lista de nos de double p2 (ou NULL), insere o no unitário na frente da lista e retorna a lista resultante*/
Args ins_Args_Double(int kind, Double p1, Args p2)
{
	Args args = (Args) malloc(sizeof(struct Args_));
	
	args->kind = kind;
	
	args->u.double_ = p1;
	
	args->next = p2;
	
	return args;
}

/*Recebe um no unitário de string p1 e uma lista de nos de string p2 (ou NULL), insere o no unitário na frente da lista e retorna a lista resultante*/
Args ins_Args_Str(int kind, String p1, Args p2)
{
	Args args = (Args) malloc(sizeof(struct Args_));
	
	args->kind = kind;
	
	args->u.str_ = p1;
	
	args->next = p2;
	
	return args;
}

/*Recebe um no unitário de ident p1 e uma lista de nos de ident p2 (ou NULL), insere o no unitário na frente da lista e retorna a lista resultante*/
Args ins_Args_Ident(int kind, Ident p1, Args p2)
{
	Args args = (Args) malloc(sizeof(struct Args_));
	
	args->kind = kind;
	
	args->u.ident_ = p1;
	
	args->next = p2;
	
	return args;
}
