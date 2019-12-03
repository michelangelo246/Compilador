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

void SymbolTable_ins_Var(Ident identificador, int linha, int coluna, int tipo)
{
	Symbol_Table *contexto = SymbolTable;
	Table_Line *tmp = (Table_Line*) malloc(sizeof(Table_Line));
	if (!tmp)
    {
        fprintf(stderr, "Erro: Faltou memoria ao tentar inserir uma linha na tabela de simbolos!\n");
        exit(1);
    }
	tmp->Kind = Is_Ident;
	tmp->u.ident.temp = -1;
	tmp->u.ident.value = strdup(identificador);
	tmp->u.ident.line = linha;
	tmp->u.ident.column = coluna;
	tmp->u.ident.Kind = Is_Var;
	tmp->u.ident.Type = tipo;
	tmp->next = contexto->lines;
	contexto->lines = tmp;
}

/*Usada na regra de definição de função. recebe o identificador a ser inserido e uma
  lista de parametros, que será utilizada para inserir um a um os parametros na tabela*/
void SymbolTable_ins_Fun(String identificador, int linha, int coluna, int tipo, No parametros)
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
	nova_linha->u.ident.temp = -1;
	nova_linha->u.ident.value = strdup(identificador);
	nova_linha->u.ident.line = linha;
	nova_linha->u.ident.column = coluna;
	nova_linha->u.ident.Kind = Is_Proc;
	nova_linha->u.ident.Type = tipo;
	nova_linha->u.ident.param = NULL;
	
	//insere os parametros um a um na linha da declaração da função
	curr_param = parametros;
	while(curr_param)
	{
		if(curr_param->kind == is_ParamList)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(curr_param->u.ident_.ident_);
			//aux->Type = curr_param->filhos->next->no->kind-9;
			switch(curr_param->filhos->next->no->kind)
			{
			case is_TypeVoid:
				aux->Type = Is_TypeVoid;
				break;
			case is_TypeInt:
				aux->Type = Is_TypeInt;
				break;
			case is_TypeDouble:
				aux->Type = Is_TypeDouble;
				break;
			case is_TypeGraph:
				aux->Type = Is_TypeGraph;
				break;
			default:
				aux->Type = Is_TypeVoid;
				break;
			}
			
			aux->next = nova_linha->u.ident.param;
			nova_linha->u.ident.param = aux;
			
			curr_param = curr_param->filhos->no;
		}
		else if(curr_param->kind == is_ParamListId)
		{
			aux = (Function_Param*) malloc(sizeof(Function_Param));
			aux->name = strdup(curr_param->u.ident_.ident_);
			//aux->Type = curr_param->filhos->no->kind-9;
			switch(curr_param->filhos->no->kind)
			{
			case is_TypeVoid:
				aux->Type = Is_TypeVoid;
				break;
			case is_TypeInt:
				aux->Type = Is_TypeInt;
				break;
			case is_TypeDouble:
				aux->Type = Is_TypeDouble;
				break;
			case is_TypeGraph:
				aux->Type = Is_TypeGraph;
				break;
			default:
				aux->Type = Is_TypeVoid;
				break;
			}
			
			aux->next = nova_linha->u.ident.param;
			nova_linha->u.ident.param = aux;
			curr_param = NULL;
		}
	}
	
	nova_linha->next = contexto->lines;
	contexto->lines = nova_linha;
}

int verifica_Params_Args(Function_Param * param, No no, Ident p1)
{
	Function_Param *aux = NULL, *aux2;
	int igual = 1, count = 0, i;
	char buffer[31][99] = {{0}};

	
	while(no)
	{
		aux2 = (Function_Param*)malloc(sizeof(struct Function_Param_));

		if(no->kind == is_ArgExpList)
		{//se ainda não está no final da lista, olha o filho

			//geraçao de código 3-addr
			getAddr1(no->filhos->next->no);
			sprintf(buffer[count++],"param %s\n", lastAddr1);
			aux2->Type = no->filhos->next->no->type;
			aux2->next = aux;
			aux = aux2;
		}
		else
		{//se chegou ao fim da lista de argumentos
			
			//geraçao de código 3-addr
			getAddr1(no);
			sprintf(buffer[count++],"param %s\n", lastAddr1);

			aux2->Type = no->type;
			aux2->next = aux;
			aux = aux2;
			break;
		}
		no = no->filhos->no;
	}

	//geraçao de código 3-addr
	for(i=count;i>=0;i--)
	{
		bufAppendCode(buffer[i]);
	}

	sprintf(buffer[0],"call %s, %d\n", p1, count);
	bufAppendCode(buffer[0]);

	//verifica se tipos são iguais, não verifica antes pois a leitura é invertida
	aux2 = aux;
	while(param && aux2)
	{
		if(param->Type != aux2->Type)
		{
			igual = 0;
			break;
		}
		param = param->next;
		aux2 = aux2->next;
	}
	if((param && !aux2) || (aux2 && !param))
	{
		igual = 0;
	}
	while(aux)
	{
		aux2 = aux->next;
		free(aux);
		aux = aux2;
	}
	return (igual==1?1:0);
}

void print_Arg_Exp_List(No no)
{
	Function_Param *aux = NULL, *aux2;
	
	while(no)
	{
		aux2 = (Function_Param*)malloc(sizeof(struct Function_Param_));

		if(no->kind == is_ArgExpList)
		{//se ainda não está no final da lista, olha o filho
			aux2->Type = no->filhos->next->no->type;
			aux2->next = aux;
			aux = aux2;
		}
		else
		{//se chegou ao fim da lista de argumentos
			aux2->Type = no->type;
			aux2->next = aux;
			aux = aux2;
			break;
		}
		no = no->filhos->no;
	}
	while(aux)
	{
		printf("%s",printType(aux->Type));
		if(aux->next)
		{
			printf(", ");
		}
		aux2 = aux->next;
		free(aux);
		aux = aux2;
	}
}

/*copia os argumentos da função lida mais recentemente para dentro do seu escopo*/
void SymbolTable_copy_args(String recent_identifier)
{
	char buffer[99] = "";
	Table_Line *funcao = NULL;
	Function_Param *parametros = NULL;
	int aux = 0;
	
	funcao = SymbolTable_lookup(recent_identifier).linha;
	if(funcao)
	{
		parametros = funcao->u.ident.param;
	}
	
	while(parametros)
	{
		SymbolTable_ins_Var(parametros->name,funcao->u.ident.line,funcao->u.ident.column,parametros->Type);
		
		//geração de código 3-addr
		Table_Line *linha = SymbolTable_lookup(parametros->name).linha;
		linha->u.ident.temp = genTemp();
		sprintf(buffer,"mov $%d, #%d\n", linha->u.ident.temp, aux++);
		bufAppendCode(buffer);

		parametros = parametros->next;
	}
}

/*busca o identificador informado em todos os contextos partindo do atual "para cima".
  retorno: referência para a linha correspondente ao identificador ou NULL*/
LookUp_Return SymbolTable_lookup(Ident p1)
{
	Table_Line *linha;
	Symbol_Table *contexto = SymbolTable;
	LookUp_Return retorno;

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
					retorno.contexto = contexto;
					retorno.linha = linha;
					return retorno;
				}
			}
			linha = linha->next;
		}
		contexto = contexto->next;
	}
	//nao encontrou o identificador
	retorno.contexto = NULL;
	retorno.linha = NULL;
	return retorno;
}

/*busca o identificador informado em todos os contextos já criados.
  retorno: referência para a linha correspondente ao identificador ou NULL*/
LookUp_Return SymbolTable_lookup_all(Ident p1)
{
	Table_Line *linha;
	Symbol_Table *contexto;
	LookUp_Return retorno;
	Symbol_Table_Set *SymbolTableSet_search = SymbolTableSet;

	while(SymbolTableSet_search)
	{
		contexto = SymbolTableSet_search->table;
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
						retorno.contexto = contexto;
						retorno.linha = linha;
						return retorno;
					}
				}
				linha = linha->next;
			}
			contexto = contexto->next;
		}
		SymbolTableSet_search = SymbolTableSet_search->next;
	}
	//nao encontrou o identificador
	retorno.contexto = NULL;
	retorno.linha = NULL;
	return retorno;
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
				default:
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
						default:
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
No make_No(int p1, Nos p2, Args p3, _Type type)
{
	No no = (No) malloc(sizeof(struct No_));
	Args aux;
	
	no->kind = p1;
	no->filhos = p2;
	no->type = type;
	no->temp = -1;
	
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

char UltimoEscopo[30];

int genTemp()
{
	/*if(strcmp(SymbolTable->name,UltimoEscopo))
	{
		TempCount = 0;
	}*/
	return TempCount++;
}

void bufAppendCode(char *s)
{
	int len = strlen(s);
	int n;
	while (cur_Code + len > buf_code_size)
	{
		buf_code_size *= 2; /* Dobra tamanho do buffer */
		bufCodeResize();
	}
	for(n = 0; n < len; n++)
	{
		buf_Code[cur_Code + n] = s[n];
	}
	cur_Code += len;
	buf_Code[cur_Code] = 0;
}

void bufAppendTable(char *s)
{
	int len = strlen(s);
	int n;
	while (cur_Table + len > buf_table_size)
	{
		buf_table_size *= 2; /* Dobra tamanho do buffer */
		bufTableResize();
	}
	for(n = 0; n < len; n++)
	{
		buf_Table[cur_Table + n] = s[n];
	}
	cur_Table += len;
	buf_Table[cur_Table] = 0;
}

void bufCodeResize(void)
{
	char *temp = (char *) malloc(buf_code_size);
	if (!temp)
	{
		fprintf(stderr, "Erro: Faltou memoria ao tentar expandir buffer!\n");
		exit(1);
	}
	if (buf_Code)
	{
		strncpy(temp, buf_Code, buf_code_size);
		free(buf_Code);
	}
	buf_Code = temp;
}

void bufTableResize(void)
{
	char *temp = (char *) malloc(buf_table_size);
	if (!temp)
	{
		fprintf(stderr, "Erro: Faltou memoria ao tentar expandir buffer!\n");
		exit(1);
	}
	if (buf_Table)
	{
		strncpy(temp, buf_Table, buf_table_size);
		free(buf_Table);
	}
	buf_Table = temp;
}

void getAddr1(No no)
{
	LookUp_Return retorno;

	if(no->temp > -1)
	{//é expressão
		sprintf(lastAddr1, "$%d",no->temp);
	}
	else
	{
		retorno = SymbolTable_lookup(no->u.ident_.ident_);
		if(retorno.linha)
		{//é variável
			if(!strcmp(retorno.contexto->name,"global"))
			{//é global
				sprintf(lastAddr1, "%s",retorno.linha->u.ident.value);
			}
			else
			{//é local
				sprintf(lastAddr1, "$%d",retorno.linha->u.ident.temp);
			}
		}
		else
		{//?
			printf("ERRO!\n");
			exit(-3);
		}
	}
}

void getAddr2(No no)
{
	LookUp_Return retorno;

	if(no->temp > -1)
	{//é expressão
		sprintf(lastAddr2, "$%d",no->temp);
	}
	else
	{
		retorno = SymbolTable_lookup(no->u.ident_.ident_);
		if(retorno.linha)
		{//é variável
			if(!strcmp(retorno.contexto->name,"global"))
			{//é global
				sprintf(lastAddr2, "%s",retorno.linha->u.ident.value);
			}
			else
			{//é local
				sprintf(lastAddr2, "$%d",retorno.linha->u.ident.temp);
			}
		}
		else
		{//?
			printf("ERRO!\n");
			exit(-3);
		}
	}
}

void getAddrIdent(Ident ident)
{
	LookUp_Return retorno = SymbolTable_lookup(ident);
	if(!strcmp(retorno.contexto->name,"global"))
	{//é global
		sprintf(lastAddr1, "%s",retorno.linha->u.ident.value);
	}
	else
	{//é local
		sprintf(lastAddr1, "$%d",retorno.linha->u.ident.temp);
	}
}

int widen(No p0,No p1, No p3, int kind)
{
	char buffer[99] = "";

	if(((p1->type == Is_TypeInt) && (p3->type == Is_TypeInt))||((p1->type == Is_TypeDouble) && (p3->type == Is_TypeDouble)))
	{//caso ambos operandos sejam int ou double, expressão retorna o tipo de ambos
		p0->type = p1->type;
		getAddr1(p1);
		getAddr2(p3);
		switch(kind)
		{
		case is_RelExpGE:
			sprintf(buffer,"sleq $%d, %s, %s\n", p0->temp, lastAddr2, lastAddr1);
			p0->type = Is_TypeBool;
			break;
		case is_RelExpLE:
			p0->type = Is_TypeBool;
			sprintf(buffer,"sleq $%d, %s, %s\n", p0->temp, lastAddr1, lastAddr2);
			break;
		case is_RelExpGT:
			sprintf(buffer,"slt $%d, %s, %s\n", p0->temp, lastAddr2, lastAddr1);
			p0->type = Is_TypeBool;
			break;
		case is_RelExpLT:
			sprintf(buffer,"slt $%d, %s, %s\n", p0->temp, lastAddr1, lastAddr2);
			p0->type = Is_TypeBool;
			break;
		case is_AddExpSub:
			sprintf(buffer,"sub $%d, %s, %s\n", p0->temp, lastAddr1, lastAddr2);
			break;
		case is_AddExpAdd:
			sprintf(buffer,"add $%d, %s, %s\n", p0->temp, lastAddr1, lastAddr2);
			break;
		case is_MulExpDiv:
			sprintf(buffer,"div $%d, %s, %s\n", p0->temp, lastAddr1, lastAddr2);
			break;
		case is_MulExpMul:
			sprintf(buffer,"mul $%d, %s, %s\n", p0->temp, lastAddr1, lastAddr2);
			break;
		}
		bufAppendCode(buffer);
	}
	else if((p1->type == Is_TypeDouble && p3->type == Is_TypeInt) || (p1->type == Is_TypeInt && p3->type == Is_TypeDouble))
	{//caso algum dos operandos seja double, expressão retorna double
		p0->type = Is_TypeDouble;
		int temp = genTemp();
		if(p1->type == Is_TypeInt)
		{
			getAddr1(p1);
			sprintf(buffer, "inttofl $%d, %s\n",temp,lastAddr1);
			bufAppendCode(buffer);
			getAddr1(p3);
			switch(kind)
			{
			case is_RelExpGE:
				sprintf(buffer,"sleq $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				p0->type = Is_TypeBool;
				break;
			case is_RelExpLE:
				sprintf(buffer,"sleq $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				p0->type = Is_TypeBool;
				break;
			case is_RelExpGT:
				sprintf(buffer,"slt $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				p0->type = Is_TypeBool;
				break;
			case is_RelExpLT:
				sprintf(buffer,"slt $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				p0->type = Is_TypeBool;
				break;
			case is_AddExpSub:
				sprintf(buffer,"sub $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				break;
			case is_AddExpAdd:
				sprintf(buffer,"add $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				break;
			case is_MulExpDiv:
				sprintf(buffer,"div $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				break;
			case is_MulExpMul:
				sprintf(buffer,"mul $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				break;
			}
			bufAppendCode(buffer);
		}
		else
		{
			getAddr1(p3);
			sprintf(buffer, "inttofl $%d, %s\n",temp,lastAddr1);
			bufAppendCode(buffer);
			getAddr1(p1);
			switch(kind)
			{
			case is_RelExpGE:
				sprintf(buffer,"sleq $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				p0->type = Is_TypeBool;
				break;
			case is_RelExpLE:
				sprintf(buffer,"sleq $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				p0->type = Is_TypeBool;
				break;
			case is_RelExpGT:
				sprintf(buffer,"slt $%d, $%d, %s\n", p0->temp, temp, lastAddr1);
				p0->type = Is_TypeBool;
				break;
			case is_RelExpLT:
				sprintf(buffer,"slt $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				p0->type = Is_TypeBool;
				break;
			case is_AddExpSub:
				sprintf(buffer,"sub $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				break;
			case is_AddExpAdd:
				sprintf(buffer,"add $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				break;
			case is_MulExpDiv:
				sprintf(buffer,"div $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				break;
			case is_MulExpMul:
				sprintf(buffer,"mul $%d, %s, $%d\n", p0->temp, lastAddr1, temp);
				break;
			}
			bufAppendCode(buffer);
		}
	} 
	else 
	{//caso algum dos operandos não seja nem int nem double, expressão retorna void e reporta erro
		return 0;
	}
	return 1;
}

void inicializaPRINTVN()
{
	int temp = genTemp();
	char buffer[99];

	sprintf(buffer, "_printvn:\n");
	bufAppendCode(buffer);

	sprintf(buffer, "mov $%d, #0\n", temp);
	bufAppendCode(buffer);

	sprintf(buffer, "mov $%d, $%d[0]\n", temp, temp);
	bufAppendCode(buffer);

	sprintf(buffer, "mov $%d, *$%d\n", temp, temp);
	bufAppendCode(buffer);

	sprintf(buffer, "println $%d\n", temp);
	bufAppendCode(buffer);

	sprintf(buffer, "return\n\n");
	bufAppendCode(buffer);
}

void inicializaPRINTV()
{
	int temp = genTemp(), temp1 = genTemp(), temp2 = genTemp();
	int temp3 = genTemp(), temp4 = genTemp(), i = genTemp();
	char buffer[99];

	sprintf(buffer,"_printv:\n");
	bufAppendCode(buffer);

	//temp = param0
	sprintf(buffer,"mov $%d, #0\n",temp);
	bufAppendCode(buffer);
	
	//temp1 = temp[0] ((&grafo[nós]) - ponteiro para lista de nós)
	sprintf(buffer,"mov $%d, $%d[0]\n", temp1, temp);
	bufAppendCode(buffer);

	//temp1 = *temp1 (quantidade de nós)
	sprintf(buffer,"mov $%d, *$%d\n", temp1, temp1);
	bufAppendCode(buffer);

	//temp2 = temp[0] (&grafo[nós] - ponteiro para lista de nós) 
	sprintf(buffer,"mov $%d, $%d[0]\n", temp2, temp);
	bufAppendCode(buffer);

	//i = 1
	sprintf(buffer,"mov $%d, 1\n", i);
	bufAppendCode(buffer);

	sprintf(buffer,"_While_Begin__%d:\n", while_grafo);
	bufAppendCode(buffer);

	// slt temp3, i, temp1
	sprintf(buffer,"sleq $%d, $%d, $%d\n", temp3, i, temp1);
	bufAppendCode(buffer);

	// while(i>=0)
	sprintf(buffer,"brz _While_End__%d, $%d\n", while_grafo, temp3);
	bufAppendCode(buffer);

	// temp4 = temp2[i]
	sprintf(buffer,"mov $%d, $%d[$%d]\n", temp4, temp2, i);
	bufAppendCode(buffer);

	// print temp4
	sprintf(buffer,"println $%d\n", temp4);
	bufAppendCode(buffer);

	// i = i + 1 
	sprintf(buffer,"add $%d, $%d, 1\n", i, i);
	bufAppendCode(buffer);

	sprintf(buffer,"jump _While_Begin__%d\n", while_grafo);
	bufAppendCode(buffer);

	sprintf(buffer,"_While_End__%d:\n", while_grafo);
	bufAppendCode(buffer);

	sprintf(buffer,"return\n\n");
	bufAppendCode(buffer);

	while_grafo++;
}

void inicializaInsNo()
{
	int temp0 = genTemp(), temp = genTemp(), temp1 = genTemp(), temp2 = genTemp();
	int temp3 = genTemp(), temp9 = genTemp(), exp = genTemp(), i = genTemp();
	char buffer[99];
	
	sprintf(buffer, "_insNo:\n");
	bufAppendCode(buffer);

	sprintf(buffer, "mov $%d, #0\n",temp0);
	bufAppendCode(buffer);

	sprintf(buffer, "mov $%d, #1\n",exp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d, $%d[0]\n",temp, temp0);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d, *$%d\n", temp, temp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "add $%d, $%d, 2\n",temp, temp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mema $%d, $%d\n", temp1, temp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "sub $%d, $%d, 2\n", temp, temp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d, $%d[0]\n",temp2,temp0);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d, $%d\n", i, temp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "add $%d, $%d, 1\n", temp, temp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d[$%d], $%d\n", temp1, temp, exp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d[0], $%d\n",temp1,temp);
	bufAppendCode(buffer);
	
	sprintf(buffer, "_While_Begin__%d:\n", while_grafo);
	bufAppendCode(buffer);
	
	sprintf(buffer, "slt $%d, 0, $%d\n",temp9,i);
	bufAppendCode(buffer);
	
	sprintf(buffer, "brz _While_End__%d, $%d\n", while_grafo,temp9);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d, $%d[$%d]\n", temp3, temp2, i);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d[$%d], $%d\n", temp1, i, temp3);
	bufAppendCode(buffer);
	
	sprintf(buffer, "sub $%d, $%d, 1\n",i,i);
	bufAppendCode(buffer);
	
	sprintf(buffer, "jump _While_Begin__%d\n", while_grafo);
	bufAppendCode(buffer);
	
	sprintf(buffer, "_While_End__%d:\n", while_grafo);
	bufAppendCode(buffer);
	
	sprintf(buffer, "mov $%d[0], $%d\n",temp0, temp1);
	bufAppendCode(buffer);
	
	sprintf(buffer, "memf $%d\n",temp2);
	bufAppendCode(buffer);

	sprintf(buffer, "return\n\n");
	bufAppendCode(buffer);
	
	while_grafo++;
}