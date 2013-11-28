/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ENDLINE = 258,
     CASSIGN_ADD = 259,
     CASSIGN_SUB = 260,
     CASSIGN_MULT = 261,
     CASSIGN_DIV = 262,
     CASSIGN_MOD = 263,
     COMP_EQU = 264,
     COMP_NEQU = 265,
     COMP_LESS = 266,
     COMP_LTE = 267,
     COMP_GTR = 268,
     COMP_GTE = 269,
     BOOL_AND = 270,
     BOOL_OR = 271,
     COMMAND_PRINT = 272,
     COMMAND_IF = 273,
     COMMAND_ELSE = 274,
     COMMAND_WHILE = 275,
     COMMAND_BREAK = 276,
     COMMAND_RANDOM = 277,
     FUNCTION_DEFINE = 278,
     FUNCTION_RETURN = 279,
     INT_LIT = 280,
     CHAR_LIT = 281,
     STRING_LIT = 282,
     TYPE = 283,
     META_TYPE = 284,
     ID = 285,
     UMINUS = 286,
     NOELSE = 287
   };
#endif
/* Tokens.  */
#define ENDLINE 258
#define CASSIGN_ADD 259
#define CASSIGN_SUB 260
#define CASSIGN_MULT 261
#define CASSIGN_DIV 262
#define CASSIGN_MOD 263
#define COMP_EQU 264
#define COMP_NEQU 265
#define COMP_LESS 266
#define COMP_LTE 267
#define COMP_GTR 268
#define COMP_GTE 269
#define BOOL_AND 270
#define BOOL_OR 271
#define COMMAND_PRINT 272
#define COMMAND_IF 273
#define COMMAND_ELSE 274
#define COMMAND_WHILE 275
#define COMMAND_BREAK 276
#define COMMAND_RANDOM 277
#define FUNCTION_DEFINE 278
#define FUNCTION_RETURN 279
#define INT_LIT 280
#define CHAR_LIT 281
#define STRING_LIT 282
#define TYPE 283
#define META_TYPE 284
#define ID 285
#define UMINUS 286
#define NOELSE 287




/* Copy the first part of user declarations.  */
#line 1 "tube5.y"

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

#include "symbol_table.h"
#include "ast.h"
#include "type_info.h"

extern int line_num;
extern int yylex();
extern string out_filename;
 
symbolTable symbol_table;
int error_count = 0;
tableEntry * current_function = NULL;

// Create an error function to call when the current line has an error
void yyerror(string err_string) {
  cout << "ERROR(line " << line_num << "): "
       << err_string << endl;
  error_count++;
}

// Create an alternate error function when a *different* line than being read in has an error.
void yyerror2(string err_string, int orig_line) {
  cout << "ERROR(line " << orig_line << "): "
       << err_string << endl;
  error_count++;
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 37 "tube5.y"
{
  char * lexeme;
  ASTNode * ast_node;
  ASTNode_BaseChildren * ast_node_children;
}
/* Line 193 of yacc.c.  */
#line 202 "tube5-parser.tab.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 215 "tube5-parser.tab.cc"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   414

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,    36,     2,     2,
      41,    42,    34,    32,    45,    33,    39,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    38,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    15,    18,    21,
      23,    26,    28,    30,    32,    35,    41,    45,    47,    52,
      54,    56,    60,    64,    68,    72,    76,    80,    84,    88,
      92,    96,   100,   104,   108,   112,   116,   120,   124,   128,
     132,   135,   138,   142,   144,   146,   148,   150,   152,   158,
     165,   170,   174,   179,   183,   185,   187,   190,   192,   197,
     202,   207,   210,   213,   217,   222,   225,   227,   231,   233,
     236,   239,   241,   243
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    -1,    50,    51,    -1,    52,
       3,    -1,    53,     3,    -1,    57,     3,    -1,    60,     3,
      -1,    64,    -1,    69,     3,    -1,    63,    -1,    72,    -1,
       3,    -1,    28,    30,    -1,    29,    41,    28,    42,    30,
      -1,    52,    31,    57,    -1,    30,    -1,    54,    43,    57,
      44,    -1,    54,    -1,    55,    -1,    57,    32,    57,    -1,
      57,    33,    57,    -1,    57,    34,    57,    -1,    57,    35,
      57,    -1,    57,    36,    57,    -1,    57,     9,    57,    -1,
      57,    10,    57,    -1,    57,    11,    57,    -1,    57,    12,
      57,    -1,    57,    13,    57,    -1,    57,    14,    57,    -1,
      57,    15,    57,    -1,    57,    16,    57,    -1,    56,    31,
      57,    -1,    56,     4,    57,    -1,    56,     5,    57,    -1,
      56,     6,    57,    -1,    56,     7,    57,    -1,    56,     8,
      57,    -1,    33,    57,    -1,    37,    57,    -1,    41,    57,
      42,    -1,    25,    -1,    26,    -1,    27,    -1,    54,    -1,
      55,    -1,    57,    39,    30,    41,    42,    -1,    57,    39,
      30,    41,    58,    42,    -1,    22,    41,    57,    42,    -1,
      30,    41,    42,    -1,    30,    41,    58,    42,    -1,    58,
      45,    59,    -1,    59,    -1,    57,    -1,    17,    58,    -1,
      21,    -1,    18,    41,    57,    42,    -1,    20,    41,    57,
      42,    -1,    61,    51,    19,    51,    -1,    61,    51,    -1,
      62,    51,    -1,    65,    66,    51,    -1,    23,    28,    30,
      41,    -1,    67,    42,    -1,    42,    -1,    67,    45,    68,
      -1,    68,    -1,    28,    30,    -1,    24,    57,    -1,    46,
      -1,    47,    -1,    70,    50,    71,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    78,    81,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    98,   122,   147,   153,   167,   173,
     174,   177,   181,   185,   189,   193,   197,   201,   205,   209,
     213,   217,   221,   225,   229,   233,   237,   241,   245,   249,
     253,   257,   261,   262,   266,   270,   274,   275,   276,   280,
     288,   292,   313,   341,   346,   354,   357,   363,   369,   375,
     381,   386,   390,   396,   408,   448,   448,   450,   453,   458,
     489,   504,   505,   506
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ENDLINE", "CASSIGN_ADD", "CASSIGN_SUB",
  "CASSIGN_MULT", "CASSIGN_DIV", "CASSIGN_MOD", "COMP_EQU", "COMP_NEQU",
  "COMP_LESS", "COMP_LTE", "COMP_GTR", "COMP_GTE", "BOOL_AND", "BOOL_OR",
  "COMMAND_PRINT", "COMMAND_IF", "COMMAND_ELSE", "COMMAND_WHILE",
  "COMMAND_BREAK", "COMMAND_RANDOM", "FUNCTION_DEFINE", "FUNCTION_RETURN",
  "INT_LIT", "CHAR_LIT", "STRING_LIT", "TYPE", "META_TYPE", "ID", "'='",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "UMINUS", "'.'", "NOELSE",
  "'('", "')'", "'['", "']'", "','", "'{'", "'}'", "$accept", "program",
  "statement_list", "statement", "var_declare", "declare_assign",
  "var_usage", "array_index", "lhs_ok", "expression", "argument_list",
  "argument", "command", "if_start", "while_start", "flow_command",
  "function_definition", "function_start", "function_end",
  "function_argument_list", "function_argument", "function_return",
  "block_start", "block_end", "code_block", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    61,    43,    45,    42,    47,    37,    33,   286,    46,
     287,    40,    41,    91,    93,    44,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    54,    55,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    58,    58,    59,    60,    60,    61,    62,
      63,    63,    63,    64,    65,    66,    66,    67,    67,    68,
      69,    70,    71,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     2,     2,     1,
       2,     1,     1,     1,     2,     5,     3,     1,     4,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     1,     1,     1,     1,     1,     5,     6,
       4,     3,     4,     3,     1,     1,     2,     1,     4,     4,
       4,     2,     2,     3,     4,     2,     1,     3,     1,     2,
       2,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,    13,     0,     0,     0,    57,     0,
       0,     0,    43,    44,    45,     0,     0,    17,     0,     0,
       0,    71,     4,     0,     0,    46,    47,     0,     0,     0,
       0,     0,    11,     9,     0,     0,     3,    12,    55,    56,
      54,     0,     0,     0,     0,    70,    14,     0,     0,    40,
      41,     0,     5,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,    61,    62,
       0,    66,     0,     0,    68,    10,     0,     0,     0,     0,
       0,     0,     0,    51,     0,    42,    16,     0,    35,    36,
      37,    38,    39,    34,    26,    27,    28,    29,    30,    31,
      32,    33,    21,    22,    23,    24,    25,     0,     0,    69,
      63,    65,     0,    72,    73,    53,    58,    59,    50,    64,
       0,    52,    18,     0,    60,    67,    15,    48,     0,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    22,    23,    24,    25,    26,    27,    28,
      39,    40,    29,    30,    31,    32,    33,    34,    82,    83,
      84,    35,    36,   124,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -48
static const yytype_int16 yypact[] =
{
     -48,     4,   112,   -48,   -48,   373,   -36,   -29,   -48,   -10,
     -12,   373,   -48,   -48,   -48,     5,    -8,     0,   373,   373,
     373,   -48,   -48,    -1,    37,     3,    18,    72,   151,    42,
     112,   112,   -48,   -48,   -25,    54,   -48,   -48,   285,    27,
     -48,   373,   373,   373,    43,   285,   -48,    47,   347,    44,
      44,   195,   -48,   373,   -48,   373,   373,   373,   373,   373,
     373,   373,   -48,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,    51,   -48,    65,   -48,
      55,   -48,   112,   -24,   -48,   -48,    71,   373,   206,   240,
     251,    46,    48,   -48,    -3,   -48,   285,   159,   285,   285,
     285,   285,   285,   285,   301,   301,   301,   301,   301,   301,
     332,   293,    -7,    -7,    44,    44,    44,    61,   112,   -48,
     -48,   -48,    77,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
      76,   -48,   -48,   360,   -48,   -48,   -48,   -48,     2,   -48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,    73,   -11,   -48,   -48,   -48,   -48,   -48,    -5,
     -47,    23,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
      -9,   -48,   -48,   -48,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -21
static const yytype_int16 yytable[] =
{
      38,    94,    52,    80,     3,    41,    45,   -19,   -19,   -19,
     -19,   -19,    42,    49,    50,    51,    44,    81,   121,    78,
      79,   122,   -20,   -20,   -20,   -20,   -20,    73,    74,    75,
      53,    43,    76,    47,   -19,    46,    88,    89,    90,   131,
      54,    48,    87,    38,   139,    77,    55,    87,    96,   -20,
      97,    98,    99,   100,   101,   102,   103,    85,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   120,    87,    91,     4,    92,    56,    57,    58,    59,
      60,   117,    38,    76,   118,   119,   138,   129,     5,     6,
     130,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,   133,    61,    18,    80,   136,   134,    19,    86,
     125,     0,    20,   135,     0,     4,     0,    21,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     5,
       6,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,    18,     0,     0,     0,    19,
       0,     0,     0,    20,    62,     0,     0,     0,    21,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    63,    64,
      65,    66,    67,    68,    69,    70,     0,     0,     0,     0,
       0,     0,     0,    71,    72,    73,    74,    75,     0,     0,
      76,    71,    72,    73,    74,    75,     0,     0,    76,     0,
       0,     0,     0,   132,    63,    64,    65,    66,    67,    68,
      69,    70,     0,     0,     0,    63,    64,    65,    66,    67,
      68,    69,    70,     0,     0,     0,     0,    71,    72,    73,
      74,    75,     0,     0,    76,     0,     0,    95,    71,    72,
      73,    74,    75,     0,     0,    76,     0,     0,   126,    63,
      64,    65,    66,    67,    68,    69,    70,     0,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,     0,     0,
       0,     0,    71,    72,    73,    74,    75,     0,     0,    76,
       0,     0,   127,    71,    72,    73,    74,    75,     0,     0,
      76,     0,     0,   128,    63,    64,    65,    66,    67,    68,
      69,    70,    63,    64,    65,    66,    67,    68,    69,     0,
     -21,   -21,   -21,   -21,   -21,   -21,     0,    71,    72,    73,
      74,    75,     0,     0,    76,    71,    72,    73,    74,    75,
       0,     0,    76,    71,    72,    73,    74,    75,     0,     0,
      76,    63,    64,    65,    66,    67,    68,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,    72,    73,    74,    75,     9,
       0,    76,    12,    13,    14,     0,     0,    17,     0,     0,
      18,     0,     9,     0,    19,    12,    13,    14,    20,    93,
      17,     0,     0,    18,     0,     9,     0,    19,    12,    13,
      14,    20,   137,    17,     0,     0,    18,     0,     0,     0,
      19,     0,     0,     0,    20
};

static const yytype_int16 yycheck[] =
{
       5,    48,     3,    28,     0,    41,    11,     4,     5,     6,
       7,     8,    41,    18,    19,    20,    28,    42,    42,    30,
      31,    45,     4,     5,     6,     7,     8,    34,    35,    36,
      31,    41,    39,    41,    31,    30,    41,    42,    43,    42,
       3,    41,    45,    48,    42,     3,    43,    45,    53,    31,
      55,    56,    57,    58,    59,    60,    61,     3,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    82,    45,    30,     3,    28,     4,     5,     6,     7,
       8,    30,    87,    39,    19,    30,   133,    41,    17,    18,
      42,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    41,    31,    33,    28,    30,   118,    37,    36,
      87,    -1,    41,   122,    -1,     3,    -1,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,    17,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    41,     3,    -1,    -1,    -1,    46,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    -1,    -1,
      39,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    44,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    42,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    42,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    42,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    42,     9,    10,    11,    12,    13,    14,
      15,    16,     9,    10,    11,    12,    13,    14,    15,    -1,
       9,    10,    11,    12,    13,    14,    -1,    32,    33,    34,
      35,    36,    -1,    -1,    39,    32,    33,    34,    35,    36,
      -1,    -1,    39,    32,    33,    34,    35,    36,    -1,    -1,
      39,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    22,
      -1,    39,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      33,    -1,    22,    -1,    37,    25,    26,    27,    41,    42,
      30,    -1,    -1,    33,    -1,    22,    -1,    37,    25,    26,
      27,    41,    42,    30,    -1,    -1,    33,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,    50,     0,     3,    17,    18,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    33,    37,
      41,    46,    51,    52,    53,    54,    55,    56,    57,    60,
      61,    62,    63,    64,    65,    69,    70,    72,    57,    58,
      59,    41,    41,    41,    28,    57,    30,    41,    41,    57,
      57,    57,     3,    31,     3,    43,     4,     5,     6,     7,
       8,    31,     3,     9,    10,    11,    12,    13,    14,    15,
      16,    32,    33,    34,    35,    36,    39,     3,    51,    51,
      28,    42,    66,    67,    68,     3,    50,    45,    57,    57,
      57,    30,    28,    42,    58,    42,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    30,    19,    30,
      51,    42,    45,    47,    71,    59,    42,    42,    42,    41,
      42,    42,    44,    41,    51,    68,    30,    42,    58,    42
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 69 "tube5.y"
    {
                 IC_Array ic_array;                         // Array to contain the intermediate code
                 (yyvsp[(1) - (1)].ast_node)->CompileTubeIC(symbol_table, ic_array); // Traverse AST, filling ic_array with code
																	(yyvsp[(1) - (1)].ast_node)->CompileFunctionDefinitionsToIC(symbol_table, ic_array);
                 ofstream out_file(out_filename.c_str());   // Open the output file
                 ic_array.PrintTC(symbol_table, out_file);  // Write TC to output file!
              ;}
    break;

  case 3:
#line 78 "tube5.y"
    {
	           (yyval.ast_node) = new ASTNode_Root;
                 ;}
    break;

  case 4:
#line 81 "tube5.y"
    {
                   if ((yyvsp[(2) - (2)].ast_node) != NULL) (yyvsp[(1) - (2)].ast_node)->AddChild((yyvsp[(2) - (2)].ast_node));
                   (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);
;}
    break;

  case 5:
#line 87 "tube5.y"
    {  (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);   ;}
    break;

  case 6:
#line 88 "tube5.y"
    {  (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);   ;}
    break;

  case 7:
#line 89 "tube5.y"
    {  (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);   ;}
    break;

  case 8:
#line 90 "tube5.y"
    {  (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);   ;}
    break;

  case 9:
#line 91 "tube5.y"
    {  (yyval.ast_node) = NULL; ;}
    break;

  case 10:
#line 92 "tube5.y"
    {  (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);   ;}
    break;

  case 11:
#line 93 "tube5.y"
    {  (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node_children);   ;}
    break;

  case 12:
#line 94 "tube5.y"
    {  (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);   ;}
    break;

  case 13:
#line 95 "tube5.y"
    {  (yyval.ast_node) = NULL; ;}
    break;

  case 14:
#line 98 "tube5.y"
    {
	          if (symbol_table.Lookup((yyvsp[(2) - (2)].lexeme)) != 0) {
		    string err_string = "re-defining variable '";
		    err_string += (yyvsp[(2) - (2)].lexeme);
                    err_string += "'";
                    yyerror(err_string);
		    exit(1);
                  }
		  string type_name = (yyvsp[(1) - (2)].lexeme);
		  int type_id = 0;
		  if (type_name == "int") type_id = Type::INT;
		  else if (type_name == "char") type_id = Type::CHAR;
		  else if (type_name == "string") type_id = Type::STRING;
		  else {
		    string err_string = "unknown type '";
		    err_string += (yyvsp[(1) - (2)].lexeme);
                    err_string += "'";
		    yyerror(err_string);
		  }
	          tableEntry * cur_entry = symbol_table.AddEntry(type_id, (yyvsp[(2) - (2)].lexeme));

	          (yyval.ast_node) = new ASTNode_Variable(cur_entry);
                  (yyval.ast_node)->SetLineNum(line_num);
	        ;}
    break;

  case 15:
#line 122 "tube5.y"
    {
	          if (symbol_table.Lookup((yyvsp[(5) - (5)].lexeme)) != 0) {
		    string err_string = "re-defining variable '";
		    err_string += (yyvsp[(5) - (5)].lexeme);
                    err_string += "'";
                    yyerror(err_string);
		    exit(1);
                  }
		  string type_name = (yyvsp[(3) - (5)].lexeme);
		  int type_id = 0;
		  if (type_name == "int") type_id = Type::INT_ARRAY;
		  else if (type_name == "char") type_id = Type::STRING;
		  else {
		    string err_string = "unknown type 'array(";
		    err_string += (yyvsp[(3) - (5)].lexeme);
                    err_string += ")'";
		    yyerror(err_string);
		  }
	          tableEntry * cur_entry = symbol_table.AddEntry(type_id, (yyvsp[(5) - (5)].lexeme));

	          (yyval.ast_node) = new ASTNode_Variable(cur_entry);
                  (yyval.ast_node)->SetLineNum(line_num);
	        ;}
    break;

  case 16:
#line 147 "tube5.y"
    {
	           (yyval.ast_node) = new ASTNode_Assign((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node));
                   (yyval.ast_node)->SetLineNum(line_num);
	         ;}
    break;

  case 17:
#line 153 "tube5.y"
    {
	       tableEntry * cur_entry = symbol_table.Lookup((yyvsp[(1) - (1)].lexeme));
               if (cur_entry == NULL || cur_entry->GetFunction()) {
		 string err_string = "unknown variable '";
		 err_string += (yyvsp[(1) - (1)].lexeme);
                 err_string += "'";
		 yyerror(err_string);
                 exit(1);
               }
	       (yyval.ast_node) = new ASTNode_Variable(cur_entry);
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 18:
#line 167 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_ArrayAccess((yyvsp[(1) - (4)].ast_node), (yyvsp[(3) - (4)].ast_node));
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 19:
#line 173 "tube5.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 20:
#line 174 "tube5.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 21:
#line 177 "tube5.y"
    { 
	       (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '+');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 22:
#line 181 "tube5.y"
    {
	       (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '-');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 23:
#line 185 "tube5.y"
    {
	       (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '*');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 24:
#line 189 "tube5.y"
    {
	       (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '/');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 25:
#line 193 "tube5.y"
    {
	       (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '%');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 26:
#line 197 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), COMP_EQU);
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 27:
#line 201 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), COMP_NEQU);
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 28:
#line 205 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), COMP_LESS);
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 29:
#line 209 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), COMP_LTE);
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 30:
#line 213 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), COMP_GTR);
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 31:
#line 217 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), COMP_GTE);
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 32:
#line 221 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Bool2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '&');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 33:
#line 225 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Bool2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '|');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 34:
#line 229 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Assign((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node));
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 35:
#line 233 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Assign((yyvsp[(1) - (3)].ast_node), new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '+') );
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 36:
#line 237 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Assign((yyvsp[(1) - (3)].ast_node), new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '-') );
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 37:
#line 241 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Assign((yyvsp[(1) - (3)].ast_node), new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '*') );
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 38:
#line 245 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Assign((yyvsp[(1) - (3)].ast_node), new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '/') );
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 39:
#line 249 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Assign((yyvsp[(1) - (3)].ast_node), new ASTNode_Math2((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), '%') );
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 40:
#line 253 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math1((yyvsp[(2) - (2)].ast_node), '-');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 41:
#line 257 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Math1((yyvsp[(2) - (2)].ast_node), '!');
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 42:
#line 261 "tube5.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); ;}
    break;

  case 43:
#line 262 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Literal(Type::INT, (yyvsp[(1) - (1)].lexeme));
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 44:
#line 266 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Literal(Type::CHAR, (yyvsp[(1) - (1)].lexeme));
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 45:
#line 270 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Literal(Type::STRING, (yyvsp[(1) - (1)].lexeme));
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 46:
#line 274 "tube5.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 47:
#line 275 "tube5.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 48:
#line 276 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Method((yyvsp[(1) - (5)].ast_node), (yyvsp[(3) - (5)].lexeme));
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 49:
#line 280 "tube5.y"
    {
               ASTNode_Method * node = new ASTNode_Method((yyvsp[(1) - (6)].ast_node), (yyvsp[(3) - (6)].lexeme));
	       node->TransferChildren((ASTNode_VarChildren *) (yyvsp[(5) - (6)].ast_node));
	       delete (yyvsp[(5) - (6)].ast_node);
               node->TypeCheckArgs();
               (yyval.ast_node) = node;
               (yyval.ast_node)->SetLineNum(line_num);
             ;}
    break;

  case 50:
#line 288 "tube5.y"
    {
               (yyval.ast_node) = new ASTNode_Random((yyvsp[(3) - (4)].ast_node));
               (yyval.ast_node)->SetLineNum(line_num);
            ;}
    break;

  case 51:
#line 292 "tube5.y"
    {
               tableEntry * curr_function = symbol_table.Lookup((yyvsp[(1) - (3)].lexeme));
               if (curr_function == NULL)
               {
		                  string err_string = "function not defined '";
		                  err_string += (yyvsp[(1) - (3)].lexeme);
                    err_string += "'";
                    yyerror(err_string);
		                  exit(1);
               }
               if (!curr_function->GetFunction())
               {
		                  string err_string = "variable not a function '";
		                  err_string += (yyvsp[(1) - (3)].lexeme);
                    err_string += "'";
                    yyerror(err_string);
		                  exit(1);
               }
  													(yyval.ast_node) = new ASTNode_FunctionInvocation(curr_function);
               (yyval.ast_node)->SetLineNum(line_num);
 ;}
    break;

  case 52:
#line 313 "tube5.y"
    {
               tableEntry * curr_function = symbol_table.Lookup((yyvsp[(1) - (4)].lexeme));
               if (curr_function == NULL)
               {
		                  string err_string = "function not defined '";
		                  err_string += (yyvsp[(1) - (4)].lexeme);
                    err_string += "'";
                    yyerror(err_string);
		                  exit(1);
               }
               if (!curr_function->GetFunction())
               {
		                  string err_string = "not a function '";
		                  err_string += (yyvsp[(1) - (4)].lexeme);
                    err_string += "'";
                    yyerror(err_string);
		                  exit(1);
               }

               ASTNode_FunctionInvocation * node = new ASTNode_FunctionInvocation(curr_function);
               node->TransferChildren((ASTNode_VarChildren *) (yyvsp[(3) - (4)].ast_node));
               delete (yyvsp[(3) - (4)].ast_node);
               node->TypeCheckArgs();
               (yyval.ast_node) = node;
               (yyval.ast_node)->SetLineNum(line_num);
 ;}
    break;

  case 53:
#line 341 "tube5.y"
    {
		  ASTNode * node = (yyvsp[(1) - (3)].ast_node); // Grab the node used for arg list.
		  node->AddChild((yyvsp[(3) - (3)].ast_node));    // Save this argument in the node.
		  (yyval.ast_node) = node;
		;}
    break;

  case 54:
#line 346 "tube5.y"
    {
		  // Create a temporary AST node to hold the arg list.
		  (yyval.ast_node) = new ASTNode_TempNode(Type::VOID);
		  (yyval.ast_node)->AddChild((yyvsp[(1) - (1)].ast_node));   // Save this argument in the temp node.
                  (yyval.ast_node)->SetLineNum(line_num);
		;}
    break;

  case 55:
#line 354 "tube5.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 56:
#line 357 "tube5.y"
    {
	         (yyval.ast_node) = new ASTNode_Print(NULL);
	         (yyval.ast_node)->TransferChildren((ASTNode_VarChildren *) (yyvsp[(2) - (2)].ast_node));
             (yyval.ast_node)->SetLineNum(line_num);
	         delete (yyvsp[(2) - (2)].ast_node);
           ;}
    break;

  case 57:
#line 363 "tube5.y"
    {
             (yyval.ast_node) = new ASTNode_Break();
             (yyval.ast_node)->SetLineNum(line_num);
           ;}
    break;

  case 58:
#line 369 "tube5.y"
    {
             (yyval.ast_node_children) = new ASTNode_If((yyvsp[(3) - (4)].ast_node), NULL, NULL);
             (yyval.ast_node_children)->SetLineNum(line_num);
           ;}
    break;

  case 59:
#line 375 "tube5.y"
    {
                (yyval.ast_node_children) = new ASTNode_While((yyvsp[(3) - (4)].ast_node), NULL);
                (yyval.ast_node_children)->SetLineNum(line_num);
              ;}
    break;

  case 60:
#line 381 "tube5.y"
    {
                 (yyval.ast_node_children)->SetChild(1, (yyvsp[(2) - (4)].ast_node));
                 (yyval.ast_node_children)->SetChild(2, (yyvsp[(4) - (4)].ast_node));
                 (yyval.ast_node_children) = (yyvsp[(1) - (4)].ast_node_children);
               ;}
    break;

  case 61:
#line 386 "tube5.y"
    {
                 (yyval.ast_node_children) = (yyvsp[(1) - (2)].ast_node_children);
                 (yyval.ast_node_children)->SetChild(1, (yyvsp[(2) - (2)].ast_node));
               ;}
    break;

  case 62:
#line 390 "tube5.y"
    {
                 (yyval.ast_node_children) = (yyvsp[(1) - (2)].ast_node_children);
                 (yyval.ast_node_children)->SetChild(1, (yyvsp[(2) - (2)].ast_node));
               ;}
    break;

  case 63:
#line 396 "tube5.y"
    {
    if (current_function == NULL)
    {
       string err_string = "this shouldn't happen...";
       yyerror(err_string);
		     exit(1);
    }

    current_function->SetASTNode_FunctionDefinition(new ASTNode_FunctionDefinition((yyvsp[(3) - (3)].ast_node), current_function));
    current_function = NULL;
;}
    break;

  case 64:
#line 408 "tube5.y"
    {
    symbol_table.IncScope();
    
    tableEntry * curr = symbol_table.Lookup((yyvsp[(3) - (4)].lexeme));
    if (curr != NULL)
    {
      string err_string;

      if (curr->GetFunction())
      {
		      err_string = "re-defining function '";
      }
      else
      {
        err_string = "variable already defined '";
      }

		    err_string += (yyvsp[(3) - (4)].lexeme);
                    err_string += "'";
                    yyerror(err_string);
		    exit(1);
    }

    string return_type_name = (yyvsp[(2) - (4)].lexeme);
    int return_type_id = 0;

    if (return_type_name == "int") return_type_id = Type::INT;
		  else if (return_type_name == "char") return_type_id = Type::CHAR;
		  else if (return_type_name == "string") return_type_id = Type::STRING;
		  else {
		    string err_string = "unknown return type '";
		    err_string += (yyvsp[(2) - (4)].lexeme);
                    err_string += "'";
		    yyerror(err_string);
		  }

    current_function = symbol_table.AddFunction(return_type_id, (yyvsp[(3) - (4)].lexeme));
;}
    break;

  case 67:
#line 450 "tube5.y"
    {

   ;}
    break;

  case 68:
#line 453 "tube5.y"
    {

;}
    break;

  case 69:
#line 458 "tube5.y"
    {
					if (current_function != NULL) //never should happen
     {
       if (symbol_table.Lookup((yyvsp[(2) - (2)].lexeme)) != 0)
       {
		        string err_string = "re-defining variable '";
		        err_string += (yyvsp[(2) - (2)].lexeme);
          err_string += "'";
          yyerror(err_string);
		        exit(1);
       }
		     string type_name = (yyvsp[(1) - (2)].lexeme);
		     int type_id = 0;
		     if (type_name == "int") type_id = Type::INT;
		     else if (type_name == "char") type_id = Type::CHAR;
		     else if (type_name == "string") type_id = Type::STRING;
		     else {
		       string err_string = "unknown type '";
		       err_string += (yyvsp[(1) - (2)].lexeme);
         err_string += "'";
		       yyerror(err_string);
		     }
	      
       tableEntry * cur_entry = symbol_table.AddEntry(type_id, (yyvsp[(2) - (2)].lexeme));
       (yyval.ast_node) = new ASTNode_Variable(cur_entry);
       (yyval.ast_node)->SetLineNum(line_num);
       current_function->AddArg(cur_entry);
	    }
;}
    break;

  case 70:
#line 489 "tube5.y"
    {
  if (current_function == NULL)
  {
     
  }

  if ((yyvsp[(2) - (2)].ast_node)->GetType() != current_function->GetType())
  {
				
  }

		(yyval.ast_node) = new ASTNode_FunctionReturn((yyvsp[(2) - (2)].ast_node), current_function);
;}
    break;

  case 71:
#line 504 "tube5.y"
    { symbol_table.IncScope(); ;}
    break;

  case 72:
#line 505 "tube5.y"
    { symbol_table.DecScope(); ;}
    break;

  case 73:
#line 506 "tube5.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2267 "tube5-parser.tab.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 508 "tube5.y"

void LexMain(int argc, char * argv[]);

int main(int argc, char * argv[])
{
  error_count = 0;
  LexMain(argc, argv);

  yyparse();

  if (error_count == 0) cout << "Parse Successful!" << endl;

  return 0;
}

