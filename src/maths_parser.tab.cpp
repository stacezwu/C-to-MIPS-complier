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




/* Copy the first part of user declarations.  */

#line 67 "src/maths_parser.tab.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "maths_parser.tab.hpp".  */
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
#line 1 "src/maths_parser.y" /* yacc.c:355  */

  #include "ast.hpp"

  #include <cassert>

  extern const ASTNode* g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 111 "src/maths_parser.tab.cpp" /* yacc.c:355  */

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
#line 17 "src/maths_parser.y" /* yacc.c:355  */

  ASTNode* astNode; // (Horace) should this be const?
  TranslationUnit* translationUnit; // (Horace) should this be const?
  Statement *statement; // (Horace) should this be const?
  StatementSequence *statementSequence; // (Horace) should this be const?
  Expression *expr;
  double number;
  std::string *string;

#line 186 "src/maths_parser.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 203 "src/maths_parser.tab.cpp" /* yacc.c:358  */

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  103

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    66,    66,    68,    69,    70,    71,    73,    75,    78,
      79,    81,    82,    83,    84,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   111,   112,
     113,   115,   116,   117,   118,   120,   121,   122,   125,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   144,
     145
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ST_BREAK", "ST_CONTINUE", "ST_RETURN",
  "ST_DO", "ST_ELSE", "ST_FOR", "ST_IF", "ST_WHILE", "T_TYPEDEF", "T_VOID",
  "T_BOOL", "T_SIGNED", "T_UNSIGNED", "T_CHAR", "T_INT", "T_SHORT",
  "T_LONG", "T_FLOAT", "T_DOUBLE", "OP_PLUS", "OP_MINUS", "OP_TIMES",
  "OP_DIVIDE", "OP_MOD", "OP_INCREMENT", "OP_DECREMENT", "OP_LOGICAL_NOT",
  "OP_LOGICAL_OR", "OP_LOGICAL_AND", "OP_EQ_EQ", "OP_NEQ", "OP_LT",
  "OP_GT", "OP_LTE", "OP_GTE", "OP_EQ", "OP_PLUS_EQ", "OP_MINUS_EQ",
  "OP_TIMES_EQ", "OP_DIVIDE_EQ", "OP_MOD_EQ", "OP_LBRACKET", "OP_RBRACKET",
  "T_SEMICOLON", "T_COMMA", "T_LBRACE", "T_RBRACE", "T_NUMBER", "T_STRING",
  "T_IDENTIFIER", "$accept", "ROOT", "TRANSLATION_UNIT", "FUNC_DEF",
  "COMPND_STATMNT", "STATMNTS", "STATMNT", "EXPR", "PRIMARY_EXPR",
  "JUMP_STATMNT", "SELECTION_STATMNT", "SPECIFIERS", "TYPE_SPECIFIER",
  "DECLARATION", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF -94

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-94)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     271,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,     2,   271,   -94,   -46,   -45,   -94,   -94,   -94,   -94,
     -37,   -34,    31,   -94,   -11,    31,   -94,   -94,    -9,    67,
     -94,   -12,   189,    21,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,   -94,   -94,   -94,   -94,   117,   245,   245,
     263,   263,   263,   189,   189,   189,   189,   189,   189,   189,
     189,   230,   211,   211,   189,   189,   189,    28,   -94,   -94,
     -94,    31,    -2,    -1,   -94,   -94,   -94,    92,     1,   -94,
     189,    31,    31,   -94,   -94,   141,   165,    36,    36,    37,
     -94,    36,   -94
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,     0,     2,     3,     0,     0,     4,     1,     5,     6,
       0,     0,     0,    59,     0,     0,    38,    39,    40,     0,
      15,     0,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,     9,     7,    36,     0,    16,    17,
      18,    19,    20,    29,    28,    25,    26,    21,    22,    23,
      24,    30,    31,    32,    33,    34,    35,     0,    37,    41,
      42,    44,     0,     0,     8,    12,    10,     0,     0,    14,
      43,     0,     0,    11,    13,     0,     0,     0,     0,    45,
      47,     0,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -94,   -94,   -94,    39,    17,   -94,   -93,   -22,   -94,   -94,
     -94,   -94,   -94,    40
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    11,    12,    13,    85,    77,    86,    87,    30,    88,
      89,    14,    15,    16
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      29,    22,    17,    32,    99,   100,    20,    21,   102,    23,
      24,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    79,    80,    81,    31,    33,    54,    82,    83,    79,
      80,    81,    91,    92,   101,    82,    83,    94,    55,     0,
      25,    18,    19,     0,     0,     0,     0,    25,     0,    90,
      25,     0,     0,     0,     0,    25,    56,     0,     0,    95,
      96,    26,    27,    28,     0,     0,    54,    84,    26,    27,
      28,    26,    27,    28,    54,     0,    26,    27,    28,    34,
      35,    36,    37,    38,     0,     0,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,     0,     0,    53,    34,    35,    36,    37,    38,     0,
       0,     0,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     0,     0,    93,    34,
      35,    36,    37,    38,     0,     0,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,     0,    78,    34,    35,    36,    37,    38,     0,     0,
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,     0,    97,    34,    35,    36,
      37,    38,     0,     0,     0,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,     0,
      98,    34,    35,    36,    37,    38,     0,     0,     0,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    34,    35,    36,    37,    38,     0,     0,
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    34,    35,    36,    37,    38,     0,     0,     0,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    36,
      37,    38,     0,     0,     0,    39,    40,    41,    42,    43,
      44,    45,    46,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    39,    40,    41,    42,    43,    44,    45,
      46
};

static const yytype_int8 yycheck[] =
{
      22,    38,     0,    25,    97,    98,    52,    52,   101,    46,
      44,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,     3,     4,     5,    45,    44,    48,     9,    10,     3,
       4,     5,    44,    44,     7,     9,    10,    46,    31,    -1,
      29,    12,    12,    -1,    -1,    -1,    -1,    29,    -1,    81,
      29,    -1,    -1,    -1,    -1,    29,    45,    -1,    -1,    91,
      92,    50,    51,    52,    -1,    -1,    48,    49,    50,    51,
      52,    50,    51,    52,    48,    -1,    50,    51,    52,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    46,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    46,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    45,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    45,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    22,    23,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    30,    31,    32,    33,    34,    35,    36,
      37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    54,    55,    56,    64,    65,    66,     0,    56,    66,
      52,    52,    38,    46,    44,    29,    50,    51,    52,    60,
      61,    45,    60,    44,    22,    23,    24,    25,    26,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    46,    48,    57,    45,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    58,    45,     3,
       4,     5,     9,    10,    49,    57,    59,    60,    62,    63,
      60,    44,    44,    46,    46,    60,    60,    45,    45,    59,
      59,     7,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    55,    55,    56,    57,    58,
      58,    59,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    63,    63,    63,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    66,
      66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     5,     3,     0,
       2,     2,     1,     2,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     1,     1,
       1,     1,     1,     2,     1,     5,     7,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       5
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
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
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
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
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
  switch (yyn)
    {
        case 2:
#line 66 "src/maths_parser.y" /* yacc.c:1646  */
    { g_root = (yyvsp[0].translationUnit); }
#line 1399 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 68 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.translationUnit) = new TranslationUnit((yyvsp[0].astNode)); }
#line 1405 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 69 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.translationUnit) = new TranslationUnit((yyvsp[0].astNode)); }
#line 1411 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 70 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.translationUnit) = (yyvsp[-1].translationUnit)->insertExternalDeclaration((yyvsp[0].astNode)); }
#line 1417 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 71 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.translationUnit) = (yyvsp[-1].translationUnit)->insertExternalDeclaration((yyvsp[0].astNode)); }
#line 1423 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 73 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new FunctionDefinition((yyvsp[-4].astNode), (yyvsp[-3].string), (yyvsp[0].statement)); }
#line 1429 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 75 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new CompoundStatement((yyvsp[-1].statementSequence)); }
#line 1435 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 78 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statementSequence) = new StatementSequence(); }
#line 1441 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statementSequence) = (yyvsp[-1].statementSequence)->addStatementToSequence((yyvsp[0].statement)); }
#line 1447 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 81 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ExpressionStatement((yyvsp[-1].expr)); }
#line 1453 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 82 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 1459 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 83 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[-1].statement); }
#line 1465 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 84 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 1471 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 87 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1477 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 88 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new AddOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1483 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 89 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new SubOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1489 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 90 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new MulOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1495 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 91 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new DivOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1501 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 92 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new ModOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1507 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 93 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new LessThanOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1513 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 94 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new GreaterThanOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1519 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 95 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new LessThanEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1525 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 96 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new GreaterThanEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1531 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 97 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new EqEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1537 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 98 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new NotEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1543 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 99 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new LogicalNotOperator((yyvsp[0].expr));}
#line 1549 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 100 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new LogicalAndOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1555 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 101 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new LogicalOrOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1561 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 102 "src/maths_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new EqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1567 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 103 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new PlusEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1573 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 104 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new MinusEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1579 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 105 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new TimesEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1585 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 106 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new DivideEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1591 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 107 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ModEqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1597 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 108 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new FunctionCall((yyvsp[-2].string), NULL); }
#line 1603 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 109 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new FunctionCall((yyvsp[-3].string), (yyvsp[-1].expr)); }
#line 1609 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 111 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Number((yyvsp[0].number)); }
#line 1615 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 112 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new StringLiteral((yyvsp[0].string)); }
#line 1621 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 113 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Variable((yyvsp[0].string)); }
#line 1627 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 115 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new BreakStatement(); }
#line 1633 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 116 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ContinueStatement(); }
#line 1639 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 117 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ReturnStatement((yyvsp[0].expr)); }
#line 1645 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 118 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ReturnStatement(NULL); }
#line 1651 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 120 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new IfStatement((yyvsp[-2].expr), (yyvsp[0].statement)); }
#line 1657 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 121 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new IfElseStatement((yyvsp[-4].expr), (yyvsp[-2].statement), (yyvsp[0].statement));}
#line 1663 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 122 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new WhileStatement((yyvsp[-2].expr), (yyvsp[0].statement)); }
#line 1669 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 125 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1675 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 132 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1681 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 133 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1687 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 134 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1693 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 135 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1699 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 136 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1705 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 137 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1711 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 138 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1717 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 139 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1723 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 140 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1729 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 141 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new ASTSpecifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1735 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 144 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new Declaration((yyvsp[-2].astNode), (yyvsp[-1].string), NULL); std::cout << "SPECIFIERS T_IDENTIFIER T_SEMICOLON" << std::endl; }
#line 1741 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 145 "src/maths_parser.y" /* yacc.c:1646  */
    { (yyval.astNode) = new Declaration((yyvsp[-4].astNode), (yyvsp[-3].string), (yyvsp[-1].expr)); }
#line 1747 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 1751 "src/maths_parser.tab.cpp" /* yacc.c:1646  */
      default: break;
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
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
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

#if !defined yyoverflow || YYERROR_VERBOSE
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
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 148 "src/maths_parser.y" /* yacc.c:1906  */


const ASTNode* g_root; // Definition of variable (to match declaration earlier)

const ASTNode* parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
