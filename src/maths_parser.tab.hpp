/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/maths_parser.y" /* yacc.c:1909  */

  #include "ast.hpp"

  #include <cassert>
  #include <fstream>
  
  extern FILE* yyin;
  extern const ASTNode* g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 60 "src/maths_parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ST_BREAK = 258,
    ST_CONTINUE = 259,
    ST_RETURN = 260,
    ST_DO = 261,
    ST_ELSE = 262,
    ST_FOR = 263,
    ST_IF = 264,
    ST_WHILE = 265,
    T_TYPEDEF = 266,
    T_VOID = 267,
    T_BOOL = 268,
    T_SIGNED = 269,
    T_UNSIGNED = 270,
    T_CHAR = 271,
    T_INT = 272,
    T_SHORT = 273,
    T_LONG = 274,
    T_FLOAT = 275,
    T_DOUBLE = 276,
    OP_PLUS = 277,
    OP_MINUS = 278,
    OP_TIMES = 279,
    OP_DIVIDE = 280,
    OP_MOD = 281,
    OP_INCREMENT = 282,
    OP_DECREMENT = 283,
    OP_LOGICAL_NOT = 284,
    OP_LOGICAL_OR = 285,
    OP_LOGICAL_AND = 286,
    OP_EQ_EQ = 287,
    OP_NEQ = 288,
    OP_LT = 289,
    OP_GT = 290,
    OP_LTE = 291,
    OP_GTE = 292,
    OP_EQ = 293,
    OP_PLUS_EQ = 294,
    OP_MINUS_EQ = 295,
    OP_TIMES_EQ = 296,
    OP_DIVIDE_EQ = 297,
    OP_MOD_EQ = 298,
    OP_LBRACKET = 299,
    OP_RBRACKET = 300,
    T_SEMICOLON = 301,
    T_COMMA = 302,
    T_LBRACE = 303,
    T_RBRACE = 304,
    T_NUMBER = 305,
    T_STRING = 306,
    T_IDENTIFIER = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "src/maths_parser.y" /* yacc.c:1909  */

  ASTNode* astNode; // (Horace) should this be const?
  ASTNodeList* astNodeList; // (Horace) should this be const?
  Statement* statement; // (Horace) should this be const?
  ParameterList* parameterList;
  ArgumentList* argumentList;
  Expression *expr;
  double number;
  std::string *string;

#line 136 "src/maths_parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED  */
