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

void SymbolTable_ins_ConstInt(Integer p2, int p3, int p4)
{
	Symbol_Table *contexto = SymbolTable;
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
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

void SymbolTable_ins_ConstDouble(Double p2, int p3, int p4)
{
	Symbol_Table *contexto = SymbolTable;
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
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

void SymbolTable_ins_constStr(String p2, int p3, int p4)
{
	Symbol_Table *contexto = SymbolTable;
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
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

void SymbolTable_ins_Var(String p2, int p3, int p4, No p5)
{
	Symbol_Table *contexto = SymbolTable;
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
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

/*Usada na regra de definição de função. */
void SymbolTable_ins_Fun(String p2, int p3, int p4, No p5, No p6)
{
	Symbol_Table *contexto = SymbolTable;
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
	
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

/*Usada na regra de declaração de variavel. Percorre a lista de declarações 
  do código fonte (e.g. int a,b,c), inserindo na tabela de simbolos todos 
  identificadores da lista com o tipo encontrado no comando de declaração*/
void SymbolTable_ins_VarList(No p1, No p2, int line, int column)
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
			SymbolTable_ins_Var(name , line, column, p1);
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
			SymbolTable_ins_Var(name , line, column, p1);
			tmp = tmp->filhos->no;
			break;
		default:
			break;
		}
	}
}

/*busca o identificador informado em todos os contextos partindo do atual "para cima"
  retorno: 1: achou; 0: nao achou*/
int SymbolTable_lookup(Ident p1)
{
	Table_Line *linha;
	Symbol_Table *contexto = SymbolTable;

	//percorre os contextos
	while(contexto)
	{
		linha = contexto->lines;
		
		//percorre as linha do contexto atual
		while(linha)
		{
			//se o simbolo atual for do tipo identificador
			if(linha->Kind == Is_Ident)
			{
				//se o identificador na linha analisada for igual ao procurado, retorna 1
				if(!strcmp(linha->u.ident.value,p1))
				{
					return 1;
				}
			}
			linha = linha->next;
		}
		contexto = contexto->next;
	}
	//nao encontrou o identificador
	return 0;
}

/*Imprime todas as tabelas de símbolos criadas*/
void SymbolTable_Show()
{
	Table_Line *linha;
	Function_Param *params;
	Symbol_Table_Set *contexto = SymbolTableSet;
	
	
	while(contexto)
	{
		printf("\n[ Tabela ]\n");
		
		linha = contexto->table->lines;
		while(linha)
		{
			switch(linha->Kind)
			{
			case Is_Ident:
				printf("  [ Identifier | tipo: %s ",(linha->u.ident.Kind == Is_Proc? "Funcao  " : "Variavel"));
				printf("| value: %s \t", linha->u.ident.value);
				switch(linha->u.ident.Type)
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
				printf("| line: %d | column: %d ]\n",linha->u.ident.line, linha->u.ident.column);
				if(linha->u.ident.Kind == Is_Proc)
				{
					printf("  [ %s params: (",linha->u.ident.value);
					params = linha->u.ident.param;
					while(params)
					{
						switch(params->Type)
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
						printf("%s",params->name);
						if(params->next)
						{
							printf(", ");
						}
						params = params->next;
					}
					printf(") ]\n");
				}
				
				break;
			case Is_ConstInt:
				printf("  [ Constant   | tipo: int      | value: %d \t| line: %d | column: %d ]\n", linha->u.constint.value, linha->u.constint.line, linha->u.constint.column);
				break;
			case Is_ConstDouble:
				printf("  [ Constant   | tipo: double   | value: %g \t| line: %d | column: %d ]\n", linha->u.constdouble.value, linha->u.constdouble.line, linha->u.constdouble.column);
				break;
			case Is_ConstStr:
				printf("  [ Constant   | tipo: string   | value: %s \t| line: %d | column: %d ]\n", linha->u.conststr.value, linha->u.conststr.line, linha->u.conststr.column);
				break;
			default:
				break;
			}
			linha = linha->next;
		}
		contexto = contexto->next;
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
