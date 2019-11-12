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
	SymbolTable = newSymbol_Table();
	error = 0;
	parse_tree = pTrans_Unit(input);
	if(parse_tree)
	{
		printf("\nAnalise concluida!\n\n");
		if(error == 0)
		{
			printf("A arvore pode ser vista de 3 formas:\n\n");
			printf(" 1 - Texto puro no terminal;\n");
			printf(" 2 - Grafico na Web; \n (Copiar manualmente codigo dot gerado e colar no site: http://www.webgraphviz.com/)\n");
			printf(" 3 - Grafico em arquivo .png; \n (Digitar os comandos: \"sudo apt install graphviz\" e \"dot -Tpng Arvore.dot -o Arvore.png\")\n");
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
					fprintf(arvore,showTrans_Unit(parse_tree));
					fclose(arvore);
					printf("\n\n /!\\ Arquivo .dot gerado com sucesso! /!\\\nUtilize o comando dot -Tpng Arvore.dot -o Arvore.png para gerar a imagem \n");
					ok = 1;
					break;
				default:
					printf("\nEscolha uma das opções acima (1, 2 ou 3): ");
					break;
				}
			}
		}
		printf("\n\n[Tabela de simbolos]");
		SymbolTable_Show(SymbolTable);
		return 0;
	}
	return 1;
}

