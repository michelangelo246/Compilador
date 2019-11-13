/**	Michelangelo da R. Machado - 14/0156089
**/

%option noyywrap
%option nounput
%option noinput

%{
#define yylval GOLlval
/*#define yylloc GOLlcoc*/
#define YY_BUFFER_APPEND GOL_BUFFER_APPEND
#define YY_BUFFER_RESET GOL_BUFFER_RESET
#define initialize_lexer GOL_initialize_lexer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#define YY_BUFFER_LENGTH 4096
#define MAXIMUM_ID_SIZE 31
#define TAB_LENGTH 4
#define COMENTARIO_ 1
#define STRING_ 2
#define UNDEFINED_ 3
#define ID_TRUC_ 4

void count();
extern void yyerror(int tipo);
extern int yy_mylinenumber, yy_mycolumnnumber;
extern char *recent_identifier;
extern int recent_identifier_index ;

int yy_comment_line, yy_comment_column;
int yy_string_line, yy_string_column;
char YY_PARSED_STRING[YY_BUFFER_LENGTH+1];
void YY_BUFFER_APPEND(char *s)
{
	if((YY_BUFFER_LENGTH - strlen(YY_PARSED_STRING)) > strlen(s))
	{
		strcat(YY_PARSED_STRING, s);
	}
	else
	{
		strncat(YY_PARSED_STRING, s, YY_BUFFER_LENGTH - strlen(YY_PARSED_STRING));
	}
	YY_PARSED_STRING[YY_BUFFER_LENGTH] = '\0';
}
void YY_BUFFER_RESET(void)
{
	int x;
	for(x = 0; x < YY_BUFFER_LENGTH; x++) /*<=?*/
	{
		YY_PARSED_STRING[x] = 0;
	}
}

%}

LETTER 	[a-zA-Z]
CAPITAL [A-Z]
SMALL 	[a-z]
DIGIT 	[0-9]
IDENT 	[a-zA-Z0-9'_]
EOL		[\r\n]

%START YYINITIAL COMMENT STRING

%%

<YYINITIAL>"="      		count(); return ASG_OP;
<YYINITIAL>"<<"      		count(); return INS_OP;
<YYINITIAL>"-"      		count(); return SUB_OP;
<YYINITIAL>"!"      		count(); return NOT_OP;
<YYINITIAL>","      		count(); return COMMA;
<YYINITIAL>"("      		count(); return OPN_PRTS;
<YYINITIAL>")"      		count(); return CLS_PRTS;
<YYINITIAL>"["      		count(); return OPN_BRK;
<YYINITIAL>"]"      		count(); return CLS_BRK;
<YYINITIAL>"@"      		count(); return AT_SYM;
<YYINITIAL>"#"      		count(); return SHARP;
<YYINITIAL>"&"      		count(); return ADR_OP;
<YYINITIAL>"*"      		count(); return MUL_OP;
<YYINITIAL>"/"      		count(); return DIV_OP;
<YYINITIAL>"+"      		count(); return ADD_OP;
<YYINITIAL>"<"      		count(); return LT_OP;
<YYINITIAL>">"      		count(); return GT_OP;
<YYINITIAL>"<="      		count(); return LE_OP;
<YYINITIAL>">="      		count(); return GE_OP;
<YYINITIAL>"=="      		count(); return EQ_OP;
<YYINITIAL>"!="      		count(); return NE_OP;
<YYINITIAL>"&&"      		count(); return AND_OP;
<YYINITIAL>"||"      		count(); return OR_OP;
<YYINITIAL>";"      		count(); return SEMICOLN;
<YYINITIAL>"{"      		count(); SymbolTable = newSymbol_Table(recent_identifier,recent_identifier_index++); return OPN_CRLY;
<YYINITIAL>"}"      		count(); SymbolTable = SymbolTable->next; return CLS_CRLY;
<YYINITIAL>"double"     	count(); return DOUBLE;
<YYINITIAL>"else"      		count(); return ELSE;
<YYINITIAL>"graph"      	count(); return GRAPH;
<YYINITIAL>"if"      		count(); return IF;
<YYINITIAL>"int"      		count(); return INT;
<YYINITIAL>"return"     	count(); return RETURN;
<YYINITIAL>"void"      		count(); return VOID;
<YYINITIAL>"while"      	count(); return WHILE;

<YYINITIAL>"//"[^\n]*\n 	count(); /*Comentário de linha única.*/
<YYINITIAL>"/*" 			count(); yy_comment_line = yy_mylinenumber; yy_comment_column = yy_mycolumnnumber; BEGIN COMMENT;
<COMMENT>"*/" 				count(); BEGIN YYINITIAL;
<COMMENT>. 					count(); /* Ignora tudo */
<COMMENT>[\n] 				count();
<COMMENT><<EOF>>			yyerror(COMENTARIO_);BEGIN YYINITIAL;

<YYINITIAL>"\""      								count(); yy_string_line = yy_mylinenumber; yy_string_column = yy_mycolumnnumber; BEGIN STRING;
<STRING>\"  										count(); yylval.string_ = strdup(YY_PARSED_STRING); YY_BUFFER_RESET(); BEGIN YYINITIAL; return _STRING_;
<STRING>{EOL}										count(); yyerror(STRING_); yylval.string_ = strdup(YY_PARSED_STRING); YY_BUFFER_RESET(); BEGIN YYINITIAL; return _STRING_;
<STRING><<EOF>>									    count(); yyerror(STRING_); yylval.string_ = strdup(YY_PARSED_STRING); YY_BUFFER_RESET(); BEGIN YYINITIAL; return _STRING_;
<STRING>.      										count(); YY_BUFFER_APPEND(yytext);
<YYINITIAL>{DIGIT}+"."{DIGIT}+("e"(\-)?{DIGIT}+)?   count(); yylval.double_ = atof(yytext); return _DOUBLE_;
<YYINITIAL>{DIGIT}+      	 						count(); yylval.int_ = atoi(yytext); return _INTEGER_;
<YYINITIAL>{LETTER}{IDENT}*      	 				count(); if(yyleng > MAXIMUM_ID_SIZE){yytext[MAXIMUM_ID_SIZE] = '\0'; yyerror(ID_TRUC_);}; yylval.string_ = strdup(yytext); return _IDENT_;
\n 													count(); 
<YYINITIAL>[ \t\r\n\f]      	 					count(); /* Ignora espaço em branco. */;
<YYINITIAL>.      	 								count(); yyerror(UNDEFINED_); return _ERROR_;

%%

void initialize_lexer(FILE *inp)
{
	yyrestart(inp);
	BEGIN YYINITIAL;
}

void yyerror(int tipo)
{
	extern char *GOLtext;
	switch(tipo)
	{
	case STRING_:
		fprintf(stderr,"Erro: linha %d coluna %d em string nao fechado\n",
		yy_string_line + 1, yy_string_column); error = 1;
		break;
	case COMENTARIO_:
		fprintf(stderr,"Erro: linha %d coluna %d em comentario nao fechada\n",
		yy_comment_line + 1, yy_comment_column); error = 1;
		break;
	case UNDEFINED_:
		fprintf(stderr,"Erro: linha %d coluna %d em token nao definido\n",
		yy_mylinenumber + 1, yy_mycolumnnumber); error = 1;
		break;
	case ID_TRUC_:
		fprintf(stderr,"Warning: linha %d coluna %d em identificador ultrapassou tamanho maximo e foi truncado\n",
		yy_mylinenumber + 1, yy_mycolumnnumber);
		break;
	}
}

/*Conta o número de linhas e colunas consumidas da entrada. Tab está definido como TAB_LENGTH espaços.*/
void count()
{
	int i;
	
	for(i = 0; yytext[i] != '\0'; i++)
	{
		if(yytext[i] == '\n')
		{
			yy_mycolumnnumber = 1;
			yy_mylinenumber++;
		}
		else if(yytext[i] == '\t')
			yy_mycolumnnumber += TAB_LENGTH - (yy_mycolumnnumber % TAB_LENGTH)+1;
		else
			yy_mycolumnnumber++;
	}
	return;
}
