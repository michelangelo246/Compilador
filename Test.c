/**	Michelangelo da R. Machado - 14/0156089 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Printer.h"
#include "Syntactic.h"

int main(int argc, char ** argv)
{
	FILE *input, *arvore;
	No parse_tree;
	char *filename = NULL;
	int pick,ok;
	char *aux;
	
	if(argc > 1)
	{
		filename = argv[1];
	}
	
	if(filename)
	{
		input = fopen(filename, "r");
		if(!input)
		{
			printf("Erro ao abrir o arquivo!\n (!) A leitura pode ser feita por arquivo ou pela entrada padrao (!)");
			exit(1);
		}
	}
	else
	{
		input = stdin;
	}
	
	/** BEGIN **/
	SymbolTable = NULL;
	SymbolTableSet = NULL;
	SymbolTable = newSymbol_Table("global",0);
	error = 0;
	TempCount = 0;
	whileCont = 0;
	IfCont = 0;
	_n_Code = 0;
	_n_Table = 0;
	buf_Code = NULL;
	buf_Table = NULL;
	cur_Code = 0;
	cur_Table = 0;
	buf_code_size = 1;
	buf_table_size = 1;

	bufAppendCode("\n.code\n");
	bufAppendTable("\n.table\n");
	parse_tree = pTrans_Unit(input);
	bufAppendCode("nop\n");

	aux = buf_Table;
	while(aux && *aux != '\0')
	{
		printf("%c",*aux);
		aux++;
	}
	aux = buf_Code;
	while(aux && *aux != '\0')
	{
		printf("%c",*aux);
		aux++;
	}

	if(0)//if(parse_tree)
	{
		printf("\nAnalise concluida!\n");
		if(error == 0)
		{
			printf("\nA arvore pode ser vista de 3 formas:\n\n");
			printf(" 1 - Texto puro no terminal;\n");
			printf(" 2 - Grafico na Web; \n (Copiar manualmente codigo dot gerado e colar no site: http://www.webgraphviz.com/)\n");
			printf(" 3 - Grafico em arquivo .png; \n (Adicione suporte a extensao .dot com o comando: \" sudo apt install graphviz \")\n");
			ok = 0;
			while(!ok)
			{
				printf("\nEscolha uma das opções acima: ");
				scanf("%d",&pick);
				printf("\n");
				switch(pick)
				{
				case 1:
					printf("\n[Plain text]\n");
					showTrans_Unit(parse_tree);
					ok = 1;
					break;
				case 2:
					printf("\n[GraphViz]\n");
					printf("%s\n", showTrans_Unit(parse_tree));
					printf("\n /!\\ Copie e cole em http://www.webgraphviz.com/ /!\\");
					ok = 1;
					break;
				case 3:
					arvore = fopen("Arvore.dot","w");
					printf("\n[Plain text]\n");
					fputs(showTrans_Unit(parse_tree),arvore);
					fclose(arvore);
					printf("\n\n /!\\ Arquivo .dot gerado com sucesso! /!\\\nUtilize o comando \" dot -Tpng Arvore.dot -o Arvore.png \" para gerar a imagem \n");
					system("dot -Tpng Arvore.dot -o Arvore.png");
					ok = 1;
					break;
				default:
					printf("\nEscolha uma das opções acima (1, 2 ou 3): ");
					break;
				}
			}
		}
		printf("\n[Tabela de simbolos]");
		SymbolTable_Show(SymbolTable);
		return 0;
	}
	return 0;//retornar 1!
}

