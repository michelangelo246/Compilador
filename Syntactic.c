/**	Michelangelo da R. Machado - 14/0156089 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Syntactic.h"


/********************    Funcoes da tabela de simbolos    ********************/
/*Empilha uma nova tabela de símbolos que aponta para as anteriores.
  Recebe um nome de contexto e indice (para os casos de contextos internos em uma mesma funcao)*/
Symbol_Table *newSymbol_Table(String nome, int index)
{
	Symbol_Table *tabela = (Symbol_Table*) malloc(sizeof(Symbol_Table));
	if (!tabela)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar alocar tabela de simbolos!\n");
        exit(1);
    }

	tabela->name = strdup(nome);
	tabela->index_name = index;

	tabela->next = SymbolTable;
	tabela->lines = NULL;
	
	Symbol_Table_Set *aux = (Symbol_Table_Set *) malloc(sizeof(Symbol_Table_Set));
	aux->table = tabela;
	aux->next = SymbolTableSet;
	SymbolTableSet = aux;
	
	return tabela;
}

void SymbolTable_ins_ConstInt(Integer symbol, int linha, int coluna)
{
	Symbol_Table *contexto = SymbolTable;
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_ConstInt;
	tmp->u.constint.value = symbol;
	tmp->u.constint.line = linha;
	tmp->u.constint.column = coluna;
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

void SymbolTable_ins_ConstDouble(Double symbol, int linha, int coluna)
{
	Symbol_Table *contexto = SymbolTable;
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_ConstDouble;
	tmp->u.constdouble.value = symbol;
	tmp->u.constdouble.line = linha;
	tmp->u.constdouble.column = coluna;
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

void SymbolTable_ins_constStr(String symbol, int linha, int coluna)
{
	Symbol_Table *contexto = SymbolTable;
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_ConstStr;
	tmp->u.conststr.value = strdup(symbol);
	tmp->u.conststr.line = linha;
	tmp->u.conststr.column = coluna;
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

void SymbolTable_ins_Var(String symbol, int linha, int coluna, No tipo)
{
	Symbol_Table *contexto = SymbolTable;
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_Ident;
	tmp->u.ident.value = strdup(symbol);
	tmp->u.ident.line = linha;
	tmp->u.ident.column = coluna;
	tmp->u.ident.Kind = Is_Var;
	switch(tipo->kind)
	{
	case is_TypeVoid:
		tmp->u.ident.Type = Is_TypeVoid;
		break;
	case is_TypeInt:
		tmp->u.ident.Type = Is_TypeInt;
		break;
	case is_TypeDouble:
		tmp->u.ident.Type = Is_TypeDouble;
		break;
	case is_TypeGraph:
		tmp->u.ident.Type = Is_TypeGraph;
		break;
	default:
		tmp->u.ident.Type = Is_TypeVoid;
		break;
	}
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

/*Usada na regra de definição de função. recebe o identificador a ser inserido e uma
  lista de parametros, que será utilizada para inserir um a um os parametros na tabela*/
void SymbolTable_ins_Fun(String identificador, int linha, int coluna, No tipo, No parametros)
{
	No curr_param;
	Function_Param *aux;
	Symbol_Table *contexto = SymbolTable;
	Table_Line *nova_linha = (Table_Line*) malloc(sizeof(Table_Line));
	if (!nova_linha)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }

	nova_linha->Kind = Is_Ident;
	nova_linha->u.ident.value = strdup(identificador);
	nova_linha->u.ident.line = linha;
	nova_linha->u.ident.column = coluna;
	nova_linha->u.ident.Kind = Is_Proc;
	nova_linha->u.ident.Type = tipo->kind-9;
	nova_linha->u.ident.param = NULL;
	
	//insere os parametros um a um na linha da declaração da função
	curr_param = parametros;
	while(curr_param)
	{
		if(curr_param->kind == is_ParamList)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(curr_param->u.ident_.ident_);
			aux->Type = curr_param->filhos->next->no->kind-9;
			
			aux->next = nova_linha->u.ident.param;
			nova_linha->u.ident.param = aux;
			
			curr_param = curr_param->filhos->no;
		}
		else if(curr_param->kind == is_ParamListId)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(curr_param->u.ident_.ident_);
			aux->Type = curr_param->filhos->no->kind-9;
			
			aux->next = nova_linha->u.ident.param;
			nova_linha->u.ident.param = aux;
			curr_param = NULL;
		}
	}
	
	nova_linha->next = contexto->lines;
	contexto->lines = nova_linha;
}

/*Usada na regra de declaração de variavel. Percorre a lista de declarações 
  do código fonte (e.g. int a,b,c), inserindo na tabela de simbolos todos 
  identificadores da lista com o tipo encontrado no comando de declaração*/
void SymbolTable_ins_VarList(No tipo, No lista_dec_var, int linha, int coluna)
{
	No dec_atual = lista_dec_var;
	String name;
	while(dec_atual)
	{
		switch(dec_atual->kind)
		{
		case is_IniDecListIni:
			if(dec_atual->filhos->no->kind == is_IniDecId)
			{
				name = dec_atual->filhos->no->u.ident_.ident_;
			}
			else
			{
				name = dec_atual->filhos->no->u.ident_.ident_;
			}
			SymbolTable_ins_Var(name , linha, coluna, tipo);
			dec_atual = NULL;
			break;
		case is_IniDecList:
			if(dec_atual->filhos->next->no->kind == is_IniDecId)
			{
				name = dec_atual->filhos->next->no->u.ident_.ident_;
			}
			else
			{
				name = dec_atual->filhos->next->no->u.ident_.ident_;
			}
			SymbolTable_ins_Var(name , linha, coluna, tipo);
			dec_atual = dec_atual->filhos->no;
			break;
		default:
			break;
		}
	}
}

/*busca o identificador informado em todos os contextos partindo do atual "para cima".
  retorno: referência para a linha correspondente ao identificador ou NULL*/
Table_Line *SymbolTable_lookup(Ident p1)
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
					return linha;
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
		printf("\n[ Tabela %s %d]\n",contexto->table->name,contexto->table->index_name);
		
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
