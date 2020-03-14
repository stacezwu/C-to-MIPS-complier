%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const ASTNode* g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  ASTNode* astNode; // (Horace) should this be const?
  TranslationUnit* translationUnit; // (Horace) should this be const?
  Statement *statement; // (Horace) should this be const?
  StatementSequence *statementSequence; // (Horace) should this be const?
  Expression *expr;
  double number;
  std::string *string;
}

%token ST_BREAK ST_CONTINUE ST_RETURN
%token ST_DO ST_ELSE ST_FOR ST_IF ST_WHILE

%token T_TYPEDEF T_VOID T_BOOL T_SIGNED T_UNSIGNED T_CHAR T_INT T_SHORT T_LONG T_FLOAT T_DOUBLE

%token OP_PLUS OP_MINUS OP_TIMES OP_DIVIDE OP_MOD
%token OP_INCREMENT OP_DECREMENT
%token OP_LOGICAL_NOT OP_LOGICAL_OR OP_LOGICAL_AND
%token OP_EQ_EQ OP_NEQ OP_LT OP_GT OP_LTE OP_GTE
%token OP_EQ OP_PLUS_EQ OP_MINUS_EQ OP_TIMES_EQ OP_DIVIDE_EQ OP_MOD_EQ
%token OP_LBRACKET OP_RBRACKET

%token T_SEMICOLON T_COMMA
%token T_LBRACE T_RBRACE // left and right curly brackets
// T_DOT T_COLON T_QUESTION

%token T_NUMBER T_STRING T_IDENTIFIER

%type <astNode> FUNC_DEF SPECIFIERS TYPE_SPECIFIER DECLARATION
%type <translationUnit> TRANSLATION_UNIT
%type <statement> COMPND_STATMNT STATMNT JUMP_STATMNT SELECTION_STATMNT
%type <statementSequence> STATMNTS;
%type <expr> EXPR PRIMARY_EXPR
%type <number> T_NUMBER
%type <string> T_STRING T_IDENTIFIER
%type <string> T_TYPEDEF T_VOID T_BOOL T_SIGNED T_UNSIGNED T_CHAR T_INT T_SHORT T_LONG T_FLOAT T_DOUBLE

%right OP_TIMES_EQ OP_DIVIDE_EQ OP_MOD_EQ
%right OP_PLUS_EQ OP_MINUS_EQ
%right OP_EQ
%left OP_PLUS OP_MINUS
%left OP_TIMES OP_DIVIDE OP_MOD

%start ROOT


%%


ROOT : TRANSLATION_UNIT { g_root = $1; }

TRANSLATION_UNIT : FUNC_DEF { $$ = new TranslationUnit($1); }
                | DECLARATION { $$ = new TranslationUnit($1); }
                | TRANSLATION_UNIT FUNC_DEF { $$ = $1->insertExternalDeclaration($2); }
                | TRANSLATION_UNIT DECLARATION { $$ = $1->insertExternalDeclaration($2); }

FUNC_DEF : TYPE_SPECIFIER T_IDENTIFIER OP_LBRACKET OP_RBRACKET COMPND_STATMNT  { $$ = new FunctionDefinition($1, $2, $5); }

COMPND_STATMNT : T_LBRACE STATMNTS T_RBRACE { $$ = new CompoundStatement($2); }

// STATMNTS is a sequence of zero or more STATMNT's
STATMNTS : /* empty */ { $$ = new StatementSequence(); }
            | STATMNTS STATMNT { $$ = $1->addStatementToSequence($2); }
            
STATMNT : EXPR T_SEMICOLON { $$ = new ExpressionStatement($1); }; // expression statement
            | COMPND_STATMNT { $$ = $1; } // compound statement
            | JUMP_STATMNT T_SEMICOLON { $$ = $1; } // jump statement
            | SELECTION_STATMNT{ $$ = $1; } //selection statement 


EXPR : PRIMARY_EXPR { $$ = $1; }
     | EXPR OP_PLUS EXPR {$$ = new AddOperator($1, $3);}
     | EXPR OP_MINUS EXPR {$$ = new SubOperator($1, $3);}
     | EXPR OP_TIMES EXPR {$$ = new MulOperator($1, $3);}
     | EXPR OP_DIVIDE EXPR {$$ = new DivOperator($1, $3);}
     | EXPR OP_MOD EXPR {$$ = new ModOperator($1, $3);}
     | EXPR OP_LT EXPR {$$ = new LessThanOperator($1, $3);}
     | EXPR OP_GT EXPR {$$ = new GreaterThanOperator($1, $3);}
     | EXPR OP_LTE EXPR {$$ = new LessThanEqOperator($1, $3);}
     | EXPR OP_GTE EXPR {$$ = new GreaterThanEqOperator($1, $3);}
     | EXPR OP_EQ_EQ EXPR {$$ = new EqEqOperator($1, $3);}
     | EXPR OP_NEQ EXPR {$$ = new NotEqOperator($1, $3);}
     | OP_LOGICAL_NOT EXPR {$$ = new LogicalNotOperator($2);}
     | EXPR OP_LOGICAL_AND EXPR {$$ = new LogicalAndOperator($1, $3);}
     | EXPR OP_LOGICAL_OR EXPR {$$ = new LogicalOrOperator($1, $3);}   
     | EXPR OP_EQ EXPR {$$ = new EqOperator($1, $3);}
     | EXPR OP_PLUS_EQ EXPR { $$ = new PlusEqOperator($1, $3);}
     | EXPR OP_MINUS_EQ EXPR { $$ = new MinusEqOperator($1, $3);}
     | EXPR OP_TIMES_EQ EXPR { $$ = new TimesEqOperator($1, $3);}
     | EXPR OP_DIVIDE_EQ EXPR { $$ = new DivideEqOperator($1, $3);}
     | EXPR OP_MOD_EQ EXPR { $$ = new ModEqOperator($1, $3);}
     | T_IDENTIFIER OP_LBRACKET OP_RBRACKET { $$ = new FunctionCall($1, NULL); }
     | T_IDENTIFIER OP_LBRACKET EXPR OP_RBRACKET { $$ = new FunctionCall($1, $3); }

PRIMARY_EXPR : T_NUMBER { $$ = new Number($1); }
             | T_STRING { $$ = new StringLiteral($1); }
             | T_IDENTIFIER { $$ = new Variable($1); }

JUMP_STATMNT : ST_BREAK { $$ = new BreakStatement(); }
             | ST_CONTINUE { $$ = new ContinueStatement(); }
             | ST_RETURN EXPR { $$ = new ReturnStatement($2); }
             | ST_RETURN { $$ = new ReturnStatement(NULL); }
             
SELECTION_STATMNT : ST_IF OP_LBRACKET EXPR OP_RBRACKET STATMNT{ $$ = new IfStatement($3, $5); } 
                  | ST_IF OP_LBRACKET EXPR OP_RBRACKET STATMNT ST_ELSE STATMNT { $$ = new IfElseStatement($3, $5, $7);}
                  | ST_WHILE OP_LBRACKET EXPR OP_RBRACKET STATMNT { $$ = new WhileStatement($3, $5); }


SPECIFIERS : TYPE_SPECIFIER { $$ = $1; }
                | T_TYPEDEF { $$ = new ASTSpecifier("typedef"); }
                | TYPE_SPECIFIER SPECIFIERS { $$ = new ASTSpecifier($1, $2); }
                | T_TYPEDEF SPECIFIERS { $$ = new ASTSpecifier(new ASTSpecifier("typedef"), $2); }
                

// Note (Horace): TYPE_SPECIFIER is currently incomplete
TYPE_SPECIFIER : T_VOID { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_BOOL { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_SIGNED { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_UNSIGNED { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_CHAR { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_INT { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_SHORT { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_LONG { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_FLOAT { $$ = new ASTSpecifier(*$1); delete $1; }
                | T_DOUBLE { $$ = new ASTSpecifier(*$1); delete $1; }
                
// Partially complete
DECLARATION : SPECIFIERS T_IDENTIFIER T_SEMICOLON { $$ = new Declaration($1, $2, NULL); std::cout << "SPECIFIERS T_IDENTIFIER T_SEMICOLON" << std::endl; }
            | SPECIFIERS T_IDENTIFIER OP_EQ EXPR T_SEMICOLON { $$ = new Declaration($1, $2, $4); }
            // TODO: implement initializer list

%%

const ASTNode* g_root; // Definition of variable (to match declaration earlier)

const ASTNode* parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
