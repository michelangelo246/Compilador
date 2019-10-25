/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         GOLparse
#define yylex           GOLlex
#define yyerror         GOLerror
#define yydebug         GOLdebug
#define yynerrs         GOLnerrs

#define yylval          GOLlval
#define yychar          GOLchar

/* Copy the first part of user declarations.  */
#line 4 "GOL.y" /* yacc.c:339  */

	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Syntactic.h"
#define initialize_lexer GOL_initialize_lexer

extern int yyparse(void);
extern int yylex(void);
int yy_mylinenumber;
int yy_mycolumnnumber;
extern int initialize_lexer(FILE * inp);

void yyerror(const char *str)
{
	extern char *GOLtext;
	fprintf(stderr,"Erro: line %d column %d: %s at %s \n",
	yy_mylinenumber + 1, (int)(yy_mycolumnnumber - strlen(GOLtext)), str, GOLtext);
	error = 1;
}

Trans_Unit YY_RESULT_Trans_Unit_ = 0;
Trans_Unit pTrans_Unit(FILE *inp)
{
	initialize_lexer(inp);
	if (yyparse())
	{ /* Failure */
		return 0;
	}
	else
	{ /* Success */
		return YY_RESULT_Trans_Unit_;
	}
}


#line 112 "Parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int GOLdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    _ERROR_ = 258,
    ASG_OP = 259,
    INS_OP = 260,
    SUB_OP = 261,
    NOT_OP = 262,
    COMMA = 263,
    OPN_PRTS = 264,
    CLS_PRTS = 265,
    OPN_BRK = 266,
    CLS_BRK = 267,
    AT_SYM = 268,
    SHARP = 269,
    ADR_OP = 270,
    MUL_OP = 271,
    DIV_OP = 272,
    ADD_OP = 273,
    LT_OP = 274,
    GT_OP = 275,
    LE_OP = 276,
    GE_OP = 277,
    EQ_OP = 278,
    NE_OP = 279,
    AND_OP = 280,
    OR_OP = 281,
    SEMICOLN = 282,
    OPN_CRLY = 283,
    CLS_CRLY = 284,
    DOUBLE = 285,
    ELSE = 286,
    GRAPH = 287,
    IF = 288,
    INT = 289,
    RETURN = 290,
    VOID = 291,
    WHILE = 292,
    _STRING_ = 293,
    _INTEGER_ = 294,
    _DOUBLE_ = 295,
    _IDENT_ = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 43 "GOL.y" /* yacc.c:355  */

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


#line 230 "Parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE GOLlval;

int GOLparse (void);



/* Copy the second part of user declarations.  */

#line 247 "Parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   360

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   159,   159,   160,   164,   165,   169,   170,   171,   175,
     176,   180,   181,   182,   183,   187,   188,   192,   193,   194,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   212,   213,   217,   218,   219,   223,   224,   225,   229,
     230,   231,   232,   233,   237,   238,   239,   243,   244,   248,
     249,   253,   254,   255,   256,   257,   261,   262,   266,   267,
     271,   272,   276,   277,   281,   282,   286,   287,   291,   292,
     296,   297,   298,   299,   300,   301,   302,   303,   307,   308,
     309,   310,   314,   315,   319,   320,   324,   325,   326,   327,
     328,   332,   333,   334,   338,   339,   340,   341,   345,   352,
     353
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_ERROR_", "\"=\"", "\"<<\"", "\"-\"",
  "\"!\"", "\",\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"@\"", "\"#\"",
  "\"&\"", "\"*\"", "\"/\"", "\"+\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"",
  "\"==\"", "\"!=\"", "\"&&\"", "\"||\"", "\";\"", "\"{\"", "\"}\"",
  "\"double\"", "\"else\"", "\"graph\"", "\"if\"", "\"int\"", "\"return\"",
  "\"void\"", "\"while\"", "_STRING_", "_INTEGER_", "_DOUBLE_", "_IDENT_",
  "$accept", "Trans_Unit", "Assign_Operator", "Constant", "Unary_Operator",
  "Type", "Arg_Exp_List", "Primary_Exp", "Posfix_Exp", "Unary_Exp",
  "Multi_Exp", "Add_Exp", "Rel_Exp", "Eq_Exp", "Log_And_Exp", "Log_Or_Exp",
  "Expression", "Init_Decl_List", "Init_Declarator", "Var_Declaration",
  "Var_Decl_List", "Parameter_List", "Statement_List", "Statement",
  "Open_Stm", "Block_Stm", "Return_Stm", "Exp_Stm", "Closed_Stm",
  "Simple_Stm", "Declarator", "Function_Def", "Ext_Var_Decl", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -55

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-55)))

#define YYTABLE_NINF -87

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     251,   -26,   -55,   -55,   -55,   -55,   145,     5,   -55,   -55,
     -55,   127,     4,   -55,   -55,   -55,    29,   118,     9,    -5,
     -55,   -55,   148,   -26,   -55,    -2,     3,   -55,    20,   -55,
     -55,   -55,   227,   -55,   -55,   -55,    64,   -55,   148,   -55,
     -55,   -55,    -7,     1,   128,   112,    37,    19,   -55,   -55,
      42,    14,   -55,    55,   -55,   -55,    78,   231,    87,   308,
     -26,    19,    84,   -55,    65,   176,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,    80,   253,   120,   124,   129,   133,   -55,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   -55,   -16,   -55,   -55,    75,   -55,   101,    79,
     239,   267,   -55,   -55,   -55,   191,   -55,   -55,   -55,   -55,
      81,   -55,   125,   -55,   141,   142,   152,   126,   163,   165,
     169,   -55,   -55,    -7,    -7,     1,     1,     1,     1,   128,
     128,   112,    37,   137,   186,   189,   -55,   192,   196,   227,
     -55,   227,   -55,   -55,   227,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,   -55,   -55,   216,   216,   216,   216,   100,
     116,   -55,   -55,   170,   177,   -55,   179,   177,   -55,   -55,
     -55,   -55,   227,   227,   216,   216,   197,   202,   -55,   -55,
     -55,   -55,   -55,   -55
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    13,    14,    12,    11,     0,     0,   100,    99,
       2,    58,     0,    56,     1,     3,     0,    58,     0,     0,
       4,     5,     0,     0,    61,     0,     0,    60,     0,    98,
       9,    10,     0,     8,     6,     7,    17,    18,     0,    20,
      31,    33,    36,    39,    44,    47,    49,    59,    57,    97,
       0,     0,    95,     0,    84,    78,     0,     0,     0,     0,
       0,    51,     0,    62,     0,     0,    66,    68,    91,    93,
      92,    69,    86,     0,     0,     0,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,    96,    94,     0,    82,     0,     0,
       0,     0,    85,    80,    63,     0,    79,    67,    19,    25,
       0,    15,     0,    17,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    38,    37,    40,    41,    42,    43,    45,
      46,    48,    50,     0,     0,     0,    83,     0,     0,     0,
      54,     0,    52,    81,     0,    26,    27,    21,    28,    22,
      29,    23,    30,    24,    65,     0,     0,     0,     0,     0,
       0,    16,    75,     0,    74,    71,     0,    70,    77,    90,
      73,    88,     0,     0,     0,     0,     0,     0,    76,    89,
      72,    87,    55,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -55,   -55,   162,   -55,   -55,   -23,   -55,   115,   -55,   -37,
      61,   211,    63,   149,   136,   213,   -32,   240,   219,   -24,
     -55,   221,   200,   -54,   181,   242,   -55,   -55,   185,    39,
     -55,   -55,   244
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,    22,    37,    38,     7,   110,    39,    40,    41,
      42,    43,    44,    45,    46,    61,    62,    18,    13,     8,
      64,    51,    65,    66,    67,    68,    69,    70,    71,    72,
      19,     9,    10
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,    79,    50,    50,    63,    60,    16,    82,    49,    80,
      81,   107,    23,    52,     2,    11,     3,    23,     4,    83,
       5,     1,    93,    28,    94,    98,    30,    31,     2,    32,
       3,    24,     4,     2,     5,     3,    27,     4,    25,     5,
     104,    60,   111,   121,   122,    91,    17,    54,    28,    55,
       2,   107,     3,    56,     4,    57,     5,    58,    33,    34,
      35,    59,    90,    93,   135,    95,     1,   138,   140,   142,
     133,    30,    31,    74,    32,    75,   134,    76,    77,    78,
     137,    30,    31,    92,    32,    30,    31,    96,    32,   144,
     108,   145,    54,    28,   103,     2,    99,     3,    56,     4,
      57,     5,    58,    33,    34,    35,    59,   159,   172,   160,
     108,   102,   161,    33,    34,    35,    59,    33,    34,    35,
      59,   112,    20,    21,   173,   115,   108,    26,   136,    32,
     117,    20,    21,    32,   119,    88,    89,   146,    32,   150,
     176,   177,    32,   123,   124,    14,     1,    84,    85,    86,
      87,   129,   130,   147,    30,    31,   148,    32,    33,    34,
      35,   113,    33,    34,    35,   113,   149,    33,    34,    35,
     113,    33,    34,    35,   113,     2,   151,     3,   154,     4,
     152,     5,    30,    31,   153,    32,    33,    34,    35,    36,
     114,   116,   118,   120,   164,   167,   155,    30,    31,   156,
      32,   174,   157,    54,    28,   106,   158,   182,   -86,    56,
     175,    57,   183,    58,    33,    34,    35,    59,    54,    28,
     143,   101,    30,    31,    56,    32,    57,   132,    58,    33,
      34,    35,    59,    30,    31,    47,    32,    30,    31,   131,
      32,    12,    48,    54,    28,    30,    31,    53,   139,    56,
      15,    57,     1,    58,    33,    34,    35,    59,    97,    30,
      31,    29,    32,   109,   105,    33,    34,    35,    59,    33,
      34,    35,    59,    30,    31,     0,   141,    33,    34,    35,
      59,     2,     0,     3,     0,     4,     0,     5,     0,     0,
       0,    33,    34,    35,    59,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,    33,    34,    35,    59,   100,
       0,     0,    20,    21,   -17,     0,   -17,    74,   -17,    75,
       0,    76,    77,    78,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   162,   165,   168,   170,
     163,   166,   169,   171,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   180,     0,     0,   179,
     181
};

static const yytype_int16 yycheck[] =
{
      32,    38,    25,    26,    28,    28,     1,     6,    10,    16,
      17,    65,     8,    10,    30,    41,    32,     8,    34,    18,
      36,     1,     8,    28,    10,    57,     6,     7,    30,     9,
      32,    27,    34,    30,    36,    32,    27,    34,     9,    36,
      64,    64,    74,    80,    81,    26,    41,    27,    28,    29,
      30,   105,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    25,     8,    96,    10,     1,    99,   100,   101,
      93,     6,     7,     9,     9,    11,     1,    13,    14,    15,
       1,     6,     7,    41,     9,     6,     7,     9,     9,     8,
      10,    10,    27,    28,    29,    30,     9,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,   139,     8,   141,
      10,    27,   144,    38,    39,    40,    41,    38,    39,    40,
      41,     1,     4,     5,     8,     1,    10,     9,    27,     9,
       1,     4,     5,     9,     1,    23,    24,    12,     9,    13,
     172,   173,     9,    82,    83,     0,     1,    19,    20,    21,
      22,    88,    89,    12,     6,     7,    14,     9,    38,    39,
      40,    41,    38,    39,    40,    41,    14,    38,    39,    40,
      41,    38,    39,    40,    41,    30,    13,    32,    41,    34,
      15,    36,     6,     7,    15,     9,    38,    39,    40,    41,
      75,    76,    77,    78,   155,   156,    10,     6,     7,    10,
       9,    31,    10,    27,    28,    29,    10,    10,    31,    33,
      31,    35,    10,    37,    38,    39,    40,    41,    27,    28,
      29,    59,     6,     7,    33,     9,    35,    91,    37,    38,
      39,    40,    41,     6,     7,    22,     9,     6,     7,    90,
       9,     1,    23,    27,    28,     6,     7,    26,     9,    33,
       6,    35,     1,    37,    38,    39,    40,    41,    27,     6,
       7,    19,     9,    10,    64,    38,    39,    40,    41,    38,
      39,    40,    41,     6,     7,    -1,     9,    38,    39,    40,
      41,    30,    -1,    32,    -1,    34,    -1,    36,    -1,    -1,
      -1,    38,    39,    40,    41,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,     1,
      -1,    -1,     4,     5,     6,    -1,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,   155,   156,   157,   158,
     155,   156,   157,   158,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,   174,
     175
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    30,    32,    34,    36,    43,    47,    61,    73,
      74,    41,    59,    60,     0,    74,     1,    41,    59,    72,
       4,     5,    44,     8,    27,     9,     9,    27,    28,    67,
       6,     7,     9,    38,    39,    40,    41,    45,    46,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    60,    10,
      47,    63,    10,    63,    27,    29,    33,    35,    37,    41,
      47,    57,    58,    61,    62,    64,    65,    66,    67,    68,
      69,    70,    71,    58,     9,    11,    13,    14,    15,    51,
      16,    17,     6,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    41,     8,    10,    10,     9,    27,    58,     9,
       1,    44,    27,    29,    61,    64,    29,    65,    10,    10,
      48,    58,     1,    41,    49,     1,    49,     1,    49,     1,
      49,    51,    51,    52,    52,    53,    53,    53,    53,    54,
      54,    55,    56,    47,     1,    58,    27,     1,    58,     9,
      58,     9,    58,    29,     8,    10,    12,    12,    14,    14,
      13,    13,    15,    15,    41,    10,    10,    10,    10,    58,
      58,    58,    66,    70,    71,    66,    70,    71,    66,    70,
      66,    70,     8,     8,    31,    31,    58,    58,    66,    70,
      66,    70,    10,    10
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    45,    45,    45,    46,
      46,    47,    47,    47,    47,    48,    48,    49,    49,    49,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    52,    52,    52,    53,    53,    53,    54,
      54,    54,    54,    54,    55,    55,    55,    56,    56,    57,
      57,    58,    58,    58,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      67,    67,    68,    68,    69,    69,    70,    70,    70,    70,
      70,    71,    71,    71,    72,    72,    72,    72,    73,    74,
      74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     3,
       1,     4,     4,     4,     4,     3,     4,     4,     4,     4,
       4,     1,     2,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     7,     3,     7,     1,     3,     1,     3,
       3,     3,     1,     2,     2,     4,     1,     2,     1,     1,
       5,     5,     7,     5,     5,     5,     7,     5,     2,     3,
       3,     4,     2,     3,     1,     2,     1,     7,     5,     7,
       5,     1,     1,     1,     4,     3,     4,     3,     3,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 2:
#line 159 "GOL.y" /* yacc.c:1646  */
    { (yyval.trans_unit_) = make_TraUniExtVar((yyvsp[0].ext_var_decl_)); YY_RESULT_Trans_Unit_= (yyval.trans_unit_); }
#line 1726 "Parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 160 "GOL.y" /* yacc.c:1646  */
    { (yyval.trans_unit_) = make_TraUniList((yyvsp[-1].trans_unit_), (yyvsp[0].ext_var_decl_)); YY_RESULT_Trans_Unit_= (yyval.trans_unit_); }
#line 1732 "Parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 164 "GOL.y" /* yacc.c:1646  */
    { (yyval.assign_operator_) = make_AssOpEQ();  }
#line 1738 "Parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 165 "GOL.y" /* yacc.c:1646  */
    { (yyval.assign_operator_) = make_AssOpINS();  }
#line 1744 "Parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 169 "GOL.y" /* yacc.c:1646  */
    { (yyval.constant_) = make_ConstInt((yyvsp[0].int_)); insConstIntSymbol_Table(SymbolTable, (yyvsp[0].int_), yy_mylinenumber+1, yy_mycolumnnumber); }
#line 1750 "Parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 170 "GOL.y" /* yacc.c:1646  */
    { (yyval.constant_) = make_ConstDouble((yyvsp[0].double_)); insConstDoubleSymbol_Table(SymbolTable, (yyvsp[0].double_), yy_mylinenumber+1, yy_mycolumnnumber); }
#line 1756 "Parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 171 "GOL.y" /* yacc.c:1646  */
    { (yyval.constant_) = make_ConstStr((yyvsp[0].string_)); insConstStrSymbol_Table(SymbolTable, (yyvsp[0].string_), yy_mylinenumber+1, yy_mycolumnnumber); }
#line 1762 "Parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 175 "GOL.y" /* yacc.c:1646  */
    { (yyval.unary_operator_) = make_UnaOpMinus();  }
#line 1768 "Parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 176 "GOL.y" /* yacc.c:1646  */
    { (yyval.unary_operator_) = make_UnaOpNot();  }
#line 1774 "Parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 180 "GOL.y" /* yacc.c:1646  */
    { (yyval.type_) = make_TypeVoid();  }
#line 1780 "Parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 181 "GOL.y" /* yacc.c:1646  */
    { (yyval.type_) = make_TypeInt();  }
#line 1786 "Parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 182 "GOL.y" /* yacc.c:1646  */
    { (yyval.type_) = make_TypeDouble();  }
#line 1792 "Parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 183 "GOL.y" /* yacc.c:1646  */
    { (yyval.type_) = make_TypeGraph();  }
#line 1798 "Parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 187 "GOL.y" /* yacc.c:1646  */
    { (yyval.arg_exp_list_) = make_ArgExpListExp((yyvsp[0].expression_));  }
#line 1804 "Parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 188 "GOL.y" /* yacc.c:1646  */
    { (yyval.arg_exp_list_) = make_ArgExpList((yyvsp[-2].arg_exp_list_), (yyvsp[0].expression_));  }
#line 1810 "Parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 192 "GOL.y" /* yacc.c:1646  */
    { (yyval.primary_exp_) = make_PriExpId((yyvsp[0].string_));  }
#line 1816 "Parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 193 "GOL.y" /* yacc.c:1646  */
    { (yyval.primary_exp_) = make_PriExpConst((yyvsp[0].constant_));  }
#line 1822 "Parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 194 "GOL.y" /* yacc.c:1646  */
    { (yyval.primary_exp_) = make_PriExpExp((yyvsp[-1].expression_));  }
#line 1828 "Parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 198 "GOL.y" /* yacc.c:1646  */
    { (yyval.posfix_exp_) = make_PosExpPri((yyvsp[0].primary_exp_));  }
#line 1834 "Parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 199 "GOL.y" /* yacc.c:1646  */
    { (yyval.posfix_exp_) = make_PosExpSub((yyvsp[-3].string_), (yyvsp[-1].primary_exp_));  }
#line 1840 "Parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 200 "GOL.y" /* yacc.c:1646  */
    { (yyval.posfix_exp_) = make_PosExpIn((yyvsp[-3].string_), (yyvsp[-1].primary_exp_));  }
#line 1846 "Parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 201 "GOL.y" /* yacc.c:1646  */
    { (yyval.posfix_exp_) = make_PosExpOut((yyvsp[-3].string_), (yyvsp[-1].primary_exp_));  }
#line 1852 "Parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 202 "GOL.y" /* yacc.c:1646  */
    { (yyval.posfix_exp_) = make_PosExpNeig((yyvsp[-3].string_), (yyvsp[-1].primary_exp_));  }
#line 1858 "Parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 203 "GOL.y" /* yacc.c:1646  */
    { (yyval.posfix_exp_) = make_PosExpCal((yyvsp[-2].string_));  }
#line 1864 "Parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 204 "GOL.y" /* yacc.c:1646  */
    { (yyval.posfix_exp_) = make_PosExpCalArg((yyvsp[-3].string_), (yyvsp[-1].arg_exp_list_));  }
#line 1870 "Parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 205 "GOL.y" /* yacc.c:1646  */
    { yyerror("sem expressao para subgrafo"); }
#line 1876 "Parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 206 "GOL.y" /* yacc.c:1646  */
    { yyerror("sem expressao para grau de entrada"); }
#line 1882 "Parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 207 "GOL.y" /* yacc.c:1646  */
    { yyerror("sem expressao para grau de saida"); }
#line 1888 "Parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 208 "GOL.y" /* yacc.c:1646  */
    { yyerror("sem expressao para vizinhanca"); }
#line 1894 "Parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 212 "GOL.y" /* yacc.c:1646  */
    { (yyval.unary_exp_) = make_UnaExpPos((yyvsp[0].posfix_exp_));  }
#line 1900 "Parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 213 "GOL.y" /* yacc.c:1646  */
    { (yyval.unary_exp_) = make_UnaExpOp((yyvsp[-1].unary_operator_), (yyvsp[0].unary_exp_));  }
#line 1906 "Parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 217 "GOL.y" /* yacc.c:1646  */
    { (yyval.multi_exp_) = make_MulExpUna((yyvsp[0].unary_exp_));  }
#line 1912 "Parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 218 "GOL.y" /* yacc.c:1646  */
    { (yyval.multi_exp_) = make_MulExpMul((yyvsp[-2].multi_exp_), (yyvsp[0].unary_exp_));  }
#line 1918 "Parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 219 "GOL.y" /* yacc.c:1646  */
    { (yyval.multi_exp_) = make_MulExpDiv((yyvsp[-2].multi_exp_), (yyvsp[0].unary_exp_));  }
#line 1924 "Parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 223 "GOL.y" /* yacc.c:1646  */
    { (yyval.add_exp_) = make_AddExpMul((yyvsp[0].multi_exp_));  }
#line 1930 "Parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 224 "GOL.y" /* yacc.c:1646  */
    { (yyval.add_exp_) = make_AddExpAdd((yyvsp[-2].add_exp_), (yyvsp[0].multi_exp_));  }
#line 1936 "Parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 225 "GOL.y" /* yacc.c:1646  */
    { (yyval.add_exp_) = make_AddExpSub((yyvsp[-2].add_exp_), (yyvsp[0].multi_exp_));  }
#line 1942 "Parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 229 "GOL.y" /* yacc.c:1646  */
    { (yyval.rel_exp_) = make_RelExpAdd((yyvsp[0].add_exp_));  }
#line 1948 "Parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 230 "GOL.y" /* yacc.c:1646  */
    { (yyval.rel_exp_) = make_RelExpLT((yyvsp[-2].rel_exp_), (yyvsp[0].add_exp_));  }
#line 1954 "Parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 231 "GOL.y" /* yacc.c:1646  */
    { (yyval.rel_exp_) = make_RelExpGT((yyvsp[-2].rel_exp_), (yyvsp[0].add_exp_));  }
#line 1960 "Parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 232 "GOL.y" /* yacc.c:1646  */
    { (yyval.rel_exp_) = make_RelExpLE((yyvsp[-2].rel_exp_), (yyvsp[0].add_exp_));  }
#line 1966 "Parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 233 "GOL.y" /* yacc.c:1646  */
    { (yyval.rel_exp_) = make_RelExpGE((yyvsp[-2].rel_exp_), (yyvsp[0].add_exp_));  }
#line 1972 "Parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 237 "GOL.y" /* yacc.c:1646  */
    { (yyval.eq_exp_) = make_EqExpRel((yyvsp[0].rel_exp_));  }
#line 1978 "Parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 238 "GOL.y" /* yacc.c:1646  */
    { (yyval.eq_exp_) = make_EqExpEQ((yyvsp[-2].eq_exp_), (yyvsp[0].rel_exp_));  }
#line 1984 "Parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 239 "GOL.y" /* yacc.c:1646  */
    { (yyval.eq_exp_) = make_EqExpNE((yyvsp[-2].eq_exp_), (yyvsp[0].rel_exp_));  }
#line 1990 "Parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 243 "GOL.y" /* yacc.c:1646  */
    { (yyval.log_and_exp_) = make_LogAndExpEq((yyvsp[0].eq_exp_));  }
#line 1996 "Parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 244 "GOL.y" /* yacc.c:1646  */
    { (yyval.log_and_exp_) = make_LogAndExpAnd((yyvsp[-2].log_and_exp_), (yyvsp[0].eq_exp_));  }
#line 2002 "Parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 248 "GOL.y" /* yacc.c:1646  */
    { (yyval.log_or_exp_) = make_LogOrExpLogAnd((yyvsp[0].log_and_exp_));  }
#line 2008 "Parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 249 "GOL.y" /* yacc.c:1646  */
    { (yyval.log_or_exp_) = make_LogOrExpLogOr((yyvsp[-2].log_or_exp_), (yyvsp[0].log_and_exp_));  }
#line 2014 "Parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 253 "GOL.y" /* yacc.c:1646  */
    { (yyval.expression_) = make_ExpLogOr((yyvsp[0].log_or_exp_));  }
#line 2020 "Parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 254 "GOL.y" /* yacc.c:1646  */
    { (yyval.expression_) = make_ExpAss((yyvsp[-2].string_), (yyvsp[-1].assign_operator_), (yyvsp[0].expression_));  }
#line 2026 "Parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 255 "GOL.y" /* yacc.c:1646  */
    { (yyval.expression_) = make_ExpAssGraph((yyvsp[-6].string_), (yyvsp[-5].assign_operator_), (yyvsp[-3].expression_), (yyvsp[-1].expression_));  }
#line 2032 "Parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 256 "GOL.y" /* yacc.c:1646  */
    { yyerror("Sem operador de atribuição"); }
#line 2038 "Parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 257 "GOL.y" /* yacc.c:1646  */
    { yyerror("Sem operador de atribuição"); }
#line 2044 "Parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 261 "GOL.y" /* yacc.c:1646  */
    { (yyval.init_decl_list_) = make_IniDecListIni((yyvsp[0].init_declarator_));  }
#line 2050 "Parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 262 "GOL.y" /* yacc.c:1646  */
    { (yyval.init_decl_list_) = make_IniDecList((yyvsp[-2].init_decl_list_), (yyvsp[0].init_declarator_));  }
#line 2056 "Parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 266 "GOL.y" /* yacc.c:1646  */
    { (yyval.init_declarator_) = make_IniDecId((yyvsp[0].string_));  }
#line 2062 "Parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 267 "GOL.y" /* yacc.c:1646  */
    { (yyval.init_declarator_) = make_IniDecIdE((yyvsp[-2].string_), (yyvsp[-1].assign_operator_), (yyvsp[0].log_or_exp_));  }
#line 2068 "Parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 271 "GOL.y" /* yacc.c:1646  */
    { (yyval.var_declaration_) = make_VarDec((yyvsp[-2].type_), (yyvsp[-1].init_decl_list_)); insTableSymbol_VarDec((yyvsp[-2].type_), (yyvsp[-1].init_decl_list_), yy_mylinenumber+1, yy_mycolumnnumber); }
#line 2074 "Parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 272 "GOL.y" /* yacc.c:1646  */
    { yyerror("Sem identificador na declaracao de variavel com inicialização"); }
#line 2080 "Parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 276 "GOL.y" /* yacc.c:1646  */
    { (yyval.var_decl_list_) = make_VarDecListVar((yyvsp[0].var_declaration_));  }
#line 2086 "Parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 277 "GOL.y" /* yacc.c:1646  */
    { (yyval.var_decl_list_) = make_VarDecList((yyvsp[-1].var_decl_list_), (yyvsp[0].var_declaration_));  }
#line 2092 "Parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 281 "GOL.y" /* yacc.c:1646  */
    { (yyval.parameter_list_) = make_ParamListId((yyvsp[-1].type_), (yyvsp[0].string_));  }
#line 2098 "Parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 282 "GOL.y" /* yacc.c:1646  */
    { (yyval.parameter_list_) = make_ParamList((yyvsp[-3].parameter_list_), (yyvsp[-1].type_), (yyvsp[0].string_));  }
#line 2104 "Parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 286 "GOL.y" /* yacc.c:1646  */
    { (yyval.statement_list_) = make_StmListStm((yyvsp[0].statement_));  }
#line 2110 "Parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 287 "GOL.y" /* yacc.c:1646  */
    { (yyval.statement_list_) = make_StmList((yyvsp[-1].statement_list_), (yyvsp[0].statement_));  }
#line 2116 "Parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 291 "GOL.y" /* yacc.c:1646  */
    { (yyval.statement_) = make_StmOpen((yyvsp[0].open_stm_));  }
#line 2122 "Parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 292 "GOL.y" /* yacc.c:1646  */
    { (yyval.statement_) = make_StmClosed((yyvsp[0].closed_stm_));  }
#line 2128 "Parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 296 "GOL.y" /* yacc.c:1646  */
    { (yyval.open_stm_) = make_OpnStmIfSmp((yyvsp[-2].expression_), (yyvsp[0].simple_stm_));  }
#line 2134 "Parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 297 "GOL.y" /* yacc.c:1646  */
    { (yyval.open_stm_) = make_OpnStmIfOpn((yyvsp[-2].expression_), (yyvsp[0].open_stm_));  }
#line 2140 "Parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 298 "GOL.y" /* yacc.c:1646  */
    { (yyval.open_stm_) = make_OpnStmIfCls((yyvsp[-4].expression_), (yyvsp[-2].closed_stm_), (yyvsp[0].open_stm_));  }
#line 2146 "Parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 299 "GOL.y" /* yacc.c:1646  */
    { (yyval.open_stm_) = make_OpnStmWhile((yyvsp[-2].expression_), (yyvsp[0].open_stm_));  }
#line 2152 "Parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 300 "GOL.y" /* yacc.c:1646  */
    { yyerror("If sem expressao");  }
#line 2158 "Parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 301 "GOL.y" /* yacc.c:1646  */
    { yyerror("If sem expressao"); }
#line 2164 "Parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 302 "GOL.y" /* yacc.c:1646  */
    { yyerror("If sem expressao"); }
#line 2170 "Parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 303 "GOL.y" /* yacc.c:1646  */
    { yyerror("While sem expressao"); }
#line 2176 "Parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 307 "GOL.y" /* yacc.c:1646  */
    { (yyval.block_stm_) = make_BlkStm();  }
#line 2182 "Parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 308 "GOL.y" /* yacc.c:1646  */
    { (yyval.block_stm_) = make_BlkStmList((yyvsp[-1].statement_list_));  }
#line 2188 "Parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 309 "GOL.y" /* yacc.c:1646  */
    { (yyval.block_stm_) = make_BlkStmVar((yyvsp[-1].var_decl_list_));  }
#line 2194 "Parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 310 "GOL.y" /* yacc.c:1646  */
    { (yyval.block_stm_) = make_BlkStmVarStm((yyvsp[-2].var_decl_list_), (yyvsp[-1].statement_list_));  }
#line 2200 "Parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 314 "GOL.y" /* yacc.c:1646  */
    { (yyval.return_stm_) = make_RetStmRet();  }
#line 2206 "Parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 315 "GOL.y" /* yacc.c:1646  */
    { (yyval.return_stm_) = make_RetStmExp((yyvsp[-1].expression_));  }
#line 2212 "Parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 319 "GOL.y" /* yacc.c:1646  */
    { (yyval.exp_stm_) = make_ExpStmNul();  }
#line 2218 "Parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 320 "GOL.y" /* yacc.c:1646  */
    { (yyval.exp_stm_) = make_ExpStmExp((yyvsp[-1].expression_));  }
#line 2224 "Parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 324 "GOL.y" /* yacc.c:1646  */
    { (yyval.closed_stm_) = make_ClosedStmSmp((yyvsp[0].simple_stm_));  }
#line 2230 "Parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 325 "GOL.y" /* yacc.c:1646  */
    { (yyval.closed_stm_) = make_ClosedStmIf((yyvsp[-4].expression_), (yyvsp[-2].closed_stm_), (yyvsp[0].closed_stm_));  }
#line 2236 "Parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 326 "GOL.y" /* yacc.c:1646  */
    { (yyval.closed_stm_) = make_ClosedStmWhile((yyvsp[-2].expression_), (yyvsp[0].closed_stm_));  }
#line 2242 "Parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 327 "GOL.y" /* yacc.c:1646  */
    { yyerror("If sem expressao"); }
#line 2248 "Parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 328 "GOL.y" /* yacc.c:1646  */
    { yyerror("While sem expressao"); }
#line 2254 "Parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 332 "GOL.y" /* yacc.c:1646  */
    { (yyval.simple_stm_) = make_SmpStmBlock((yyvsp[0].block_stm_));  }
#line 2260 "Parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 333 "GOL.y" /* yacc.c:1646  */
    { (yyval.simple_stm_) = make_SmpStmExp((yyvsp[0].exp_stm_));  }
#line 2266 "Parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 334 "GOL.y" /* yacc.c:1646  */
    { (yyval.simple_stm_) = make_SmpStmRet((yyvsp[0].return_stm_));  }
#line 2272 "Parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 338 "GOL.y" /* yacc.c:1646  */
    { (yyval.declarator_) = make_DecIdParam((yyvsp[-3].string_), (yyvsp[-1].parameter_list_));  }
#line 2278 "Parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 339 "GOL.y" /* yacc.c:1646  */
    { (yyval.declarator_) = make_DecId((yyvsp[-2].string_));  }
#line 2284 "Parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 340 "GOL.y" /* yacc.c:1646  */
    { yyerror("Declaracao de funcao sem identificar e parametros"); }
#line 2290 "Parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 341 "GOL.y" /* yacc.c:1646  */
    { yyerror("Declaracao de funcao sem identificar e parametros"); }
#line 2296 "Parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 346 "GOL.y" /* yacc.c:1646  */
    { (yyval.function_def_) = make_FunDef((yyvsp[-2].type_), (yyvsp[-1].declarator_), (yyvsp[0].block_stm_)); insFuncSymbol_Table(SymbolTable, 
						((yyvsp[-1].declarator_)->kind == is_DecIdParam ? (yyvsp[-1].declarator_)->u.decidparam_.ident_ : (yyvsp[-1].declarator_)->u.decid_.ident_), yy_mylinenumber, yy_mycolumnnumber, (yyvsp[-2].type_),
						((yyvsp[-1].declarator_)->kind == is_DecIdParam ? (yyvsp[-1].declarator_)->u.decidparam_.parameter_list_ : NULL)); }
#line 2304 "Parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 352 "GOL.y" /* yacc.c:1646  */
    { (yyval.ext_var_decl_) = make_ExtVarDecFun((yyvsp[0].function_def_));  }
#line 2310 "Parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 353 "GOL.y" /* yacc.c:1646  */
    { (yyval.ext_var_decl_) = make_ExtVarDecVar((yyvsp[0].var_declaration_));  }
#line 2316 "Parser.c" /* yacc.c:1646  */
    break;


#line 2320 "Parser.c" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
