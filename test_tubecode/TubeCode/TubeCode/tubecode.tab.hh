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
     INST_VAL_COPY = 258,
     INST_ADD = 259,
     INST_SUB = 260,
     INST_MULT = 261,
     INST_DIV = 262,
     INST_MOD = 263,
     INST_TEST_LESS = 264,
     INST_TEST_GTR = 265,
     INST_TEST_EQU = 266,
     INST_TEST_NEQU = 267,
     INST_TEST_GTE = 268,
     INST_TEST_LTE = 269,
     INST_JUMP = 270,
     INST_JUMP_IF_0 = 271,
     INST_JUMP_IF_N0 = 272,
     INST_NOP = 273,
     INST_RANDOM = 274,
     INST_OUT_INT = 275,
     INST_OUT_FLOAT = 276,
     INST_OUT_CHAR = 277,
     INST_LOAD = 278,
     INST_STORE = 279,
     INST_MEM_COPY = 280,
     ENDLINE = 281,
     ARG_INT = 282,
     ARG_CHAR = 283,
     ARG_REG = 284,
     ARG_IP = 285,
     ARG_LABEL = 286
   };
#endif
/* Tokens.  */
#define INST_VAL_COPY 258
#define INST_ADD 259
#define INST_SUB 260
#define INST_MULT 261
#define INST_DIV 262
#define INST_MOD 263
#define INST_TEST_LESS 264
#define INST_TEST_GTR 265
#define INST_TEST_EQU 266
#define INST_TEST_NEQU 267
#define INST_TEST_GTE 268
#define INST_TEST_LTE 269
#define INST_JUMP 270
#define INST_JUMP_IF_0 271
#define INST_JUMP_IF_N0 272
#define INST_NOP 273
#define INST_RANDOM 274
#define INST_OUT_INT 275
#define INST_OUT_FLOAT 276
#define INST_OUT_CHAR 277
#define INST_LOAD 278
#define INST_STORE 279
#define INST_MEM_COPY 280
#define ENDLINE 281
#define ARG_INT 282
#define ARG_CHAR 283
#define ARG_REG 284
#define ARG_IP 285
#define ARG_LABEL 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 24 "tubecode.y"
{
  int int_val;
  float float_val;
  char * lexeme;
  cInst_Base * inst_ptr;
  cInstArg_Base * arg_ptr;
}
/* Line 1529 of yacc.c.  */
#line 119 "tubecode.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

