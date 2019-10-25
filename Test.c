/**	Michelangelo da R. Machado - 14/0156089 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Printer.h"
#include "Syntactic.h"

int main(int argc, char ** argv)
{
	FILE *input;
	Trans_Unit parse_tree;
	char *filename = NULL;
	
	if(argc > 1)
	{
		filename = argv[1];
	}
	
	if(filename)
	{
		input = fopen(filename, "r");
		if(!input)
		{
			printf("Erro ao abrir o arquivo!\n (?) A leitura pode ser feita por arquivo ou pela entrada padrao(?)");
			exit(1);
		}
	}
	else
	{
		input = stdin;
	}
	
	/** BEGIN **/
	
	SymbolTable = newSymbol_Table();
	error = 0;
	
	parse_tree = pTrans_Unit(input);
	if(parse_tree)
	{
		printf("\nAnalise concluida!\n");
		if(error == 0)
		{	
			printf("\n[Arvore sintatica]\n");
			printf("%s\n\n", showTrans_Unit(parse_tree));
		}
		printf("\n[Tabela de simbolos]\n");
		showSymbolTable(SymbolTable);
		return 0;
	}
	return 1;
}

