/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     INT_LIT = 278,
     CHAR_LIT = 279,
     STRING_LIT = 280,
     TYPE = 281,
     META_TYPE = 282,
     ID = 283,
     UMINUS = 284,
     NOELSE = 285
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
#define INT_LIT 278
#define CHAR_LIT 279
#define STRING_LIT 280
#define TYPE 281
#define META_TYPE 282
#define ID 283
#define UMINUS 284
#define NOELSE 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "tube5.y"
{
  char * lexeme;
  ASTNode * ast_node;
  ASTNode_BaseChildren * ast_node_children;
}
/* Line 1529 of yacc.c.  */
#line 115 "tube5-parser.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

