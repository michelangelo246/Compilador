/**	Michelangelo da R. Machado - 14/0156089 **/

#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include "Syntactic.h"

typedef union
{
  int int_;
  double double_;
  char* string_;
  Trans_Unit trans_unit_;
  Assign_Operator assign_operator_;
  Constant constant_;
  Unary_Operator unary_operator_;
  Type type_;
  Arg_Exp_List arg_exp_list_;
  Primary_Exp primary_exp_;
  Posfix_Exp posfix_exp_;
  Unary_Exp unary_exp_;
  Multi_Exp multi_exp_;
  Add_Exp add_exp_;
  Rel_Exp rel_exp_;
  Eq_Exp eq_exp_;
  Log_And_Exp log_and_exp_;
  Log_Or_Exp log_or_exp_;
  Expression expression_;
  Init_Decl_List init_decl_list_;
  Init_Declarator init_declarator_;
  Var_Declaration var_declaration_;
  Var_Decl_List var_decl_list_;
  Parameter_List parameter_list_;
  Statement_List statement_list_;
  Statement statement_;
  Open_Stm open_stm_;
  Block_Stm block_stm_;
  Return_Stm return_stm_;
  Exp_Stm exp_stm_;
  Closed_Stm closed_stm_;
  Simple_Stm simple_stm_;
  Declarator declarator_;
  Function_Def function_def_;
  Ext_Var_Decl ext_var_decl_;
} YYSTYPE;

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
#define _STRING_ 293
#define _INTEGER_ 294
#define _DOUBLE_ 295
#define _IDENT_ 296

extern YYSTYPE yylval;
Trans_Unit pTrans_Unit(FILE *inp);


#endif
