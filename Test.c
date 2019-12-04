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
	FILE *codigo;
	No parse_tree;
	char *filename = NULL;
	int pick, ok;
	char *aux;
	extern int retorno;
	
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
	while_grafo = 0;
	retorno = 0;

	bufAppendCode("\n.code\n");
	bufAppendTable("\n.table\n");
	inicializaPRINTV(); TempCount = 0;
	inicializaPRINTVN(); TempCount = 0;
	inicializaPRINTA(); TempCount = 0;
	inicializaInsNo(); TempCount = 0;
	inicializaInsAresta(); TempCount = 0;
	inicializaGetGrauIn(); TempCount = 0;
	inicializaGetGrauOut(); TempCount = 0;
	inicializaNeig(); TempCount = 0;
	inicializaDot(); TempCount = 0;
	parse_tree = pTrans_Unit(input);
	bufAppendCode("nop\n");

	codigo = fopen("code.tac","w");
	aux = buf_Table;
	while(aux && *aux != '\0')
	{
		fputc(*aux,codigo);
		//printf("%c",*aux);
		aux++;
	}
	aux = buf_Code;
	while(aux && *aux != '\0')
	{
		fputc(*aux,codigo);
		//printf("%c",*aux);
		aux++;
	}
	fclose(codigo);

	if(parse_tree)
	{
		printf("\nAnalise concluida!\n");
		if(error == 0)
		{
			printf("\nA arvore pode ser vista de 3 formas:\n\n");
			printf(" 1 - Texto puro no terminal;\n");
			printf(" 2 - Grafico na Web; \n (Copiar manualmente codigo dot gerado e colar no site: http://www.webgraphviz.com/)\n");
			printf(" 3 - Grafico em arquivo .png; \n (Adicione suporte a extensao .dot com o comando: \" sudo apt install graphviz \")\n");
			printf("\n Além disso, caso deseje executar o código, digite 4 (requer a presença do interpretador TAC)\n");
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
					printf("\n\n/!\\Arquivo TAC ('code.tac') gerado com sucesso/!\\ \n\n");
					ok = 1;
					break;
				case 2:
					printf("\n[GraphViz]\n");
					printf("%s\n", showTrans_Unit(parse_tree));
					printf("\n /!\\ Copie e cole em http://www.webgraphviz.com/ /!\\");
					printf("\n\n/!\\Arquivo TAC ('code.tac') gerado com sucesso/!\\ \n\n");
					ok = 1;
					break;
				case 3:
					arvore = fopen("Arvore.dot","w");
					printf("\n[Plain text]\n");
					fputs(showTrans_Unit(parse_tree),arvore);
					fclose(arvore);
					system("dot -Tpng Arvore.dot -o Arvore.png");
					system("dot -Tpdf Arvore.dot -o Arvore.pdf");
					printf("\n\n /!\\ Arquivos .dot, .png e .pdf gerados com sucesso! /!\\\n");
					printf("Caso os arquivos .dot e .png não tenham sido criados, utilize o comando\n \" dot -Tpng Arvore.dot -o Arvore.png \" para a geração. ");
					printf("\n/!\\Arquivo TAC ('code.tac') gerado com sucesso/!\\ \n\n");
					ok = 1;
					break;
				case 4:
					arvore = fopen("Arvore.dot","w");
					printf("\n[Plain text]\n");
					fputs(showTrans_Unit(parse_tree),arvore);
					fclose(arvore);
					system("dot -Tpng Arvore.dot -o Arvore.png");
					printf("\n\n /!\\ Arquivos .dot, .png e .pdf gerados com sucesso! /!\\\n");
					printf("Caso os arquivos .dot e .png não tenham sido criados, utilize o comando\n \" dot -Tpng Arvore.dot -o Arvore.png \" para a geração. ");
					printf("\n\n/!\\Arquivo TAC ('code.tac') gerado com sucesso/!\\ \n");
					printf("\n[Execução TAC]\n");
					system("tac code.tac");
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
	return 1;
}

