/**	Michelangelo da R. Machado - 14/0156089 **/

#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include "Syntactic.h"

typedef union
{
  int int_;
  double double_;
  char* string_;
  No no_;
} YYSTYPE;

/*Permite usar @1.first_line .. @n.first_line / @$.first_line 
Desativado pois torna o parser mais lento
Para usar: setar campos do yylloc no .l
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;*/ 

#define _ERROR_ 258
#define ASG_OP 259
#define INS_OP 260
#define SUB_OP 261
#define NOT_OP 262
#define COMMA 263
#define OPN_PRTS 264
#define CLS_PRTS 265
#define OPN_BRK 266
#define CLS_BRK 267
#define AT_SYM 268
#define SHARP 269
#define ADR_OP 270
#define MUL_OP 271
#define DIV_OP 272
#define ADD_OP 273
#define LT_OP 274
#define GT_OP 275
#define LE_OP 276
#define GE_OP 277
#define EQ_OP 278
#define NE_OP 279
#define AND_OP 280
#define OR_OP 281
#define SEMICOLN 282
#define OPN_CRLY 283
#define CLS_CRLY 284
#define DOUBLE 285
#define ELSE 286
#define GRAPH 287
#define IF 288
#define INT 289
#define RETURN 290
#define VOID 291
#define WHILE 292
#define PRINT 293
#define SCAN 294
#define _STRING_ 295
#define _INTEGER_ 296
#define _DOUBLE_ 297
#define _IDENT_ 298

extern YYSTYPE yylval;
/*extern YYLTYPE yylloc;*/
No pTrans_Unit(FILE *inp);


#endif
