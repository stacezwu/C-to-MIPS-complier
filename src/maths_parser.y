%code requires{
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
}

// Represents the value associated with any kind of
// AST node.
%union{
  ASTNode* astNode; // (Horace) should this be const?
  ASTNodeList* astNodeList; // (Horace) should this be const?
  ASTSpecifierList* astSpecifierList;
  Statement* statement; // (Horace) should this be const?
  InitDeclaratorList* initDeclaratorList;
  ParameterList* parameterList;
  ArgumentList* argumentList;
  ArrayInitializerList* arrayInitializerList;
  Enumerator* enumerator;
  EnumeratorList* enumeratorList;
  EnumSpecifier* enumSpecifier;
  Expression *expr;
  ModifiableLValue *modifiableLValue;
  double number;
  std::string *string;
}

%token ST_BREAK ST_CONTINUE ST_RETURN
%token ST_DO ST_ELSE ST_FOR ST_IF ST_WHILE ST_SWITCH 
%token ST_CASE ST_DEFAULT

%token T_TYPEDEF T_VOID T_BOOL T_SIGNED T_UNSIGNED T_CHAR T_INT T_SHORT T_LONG T_FLOAT T_DOUBLE

%token OP_PLUS OP_MINUS OP_TIMES OP_DIVIDE OP_MOD
%token OP_INCREMENT OP_DECREMENT
%token OP_LOGICAL_NOT OP_LOGICAL_OR OP_LOGICAL_AND
%token OP_EQ_EQ OP_NEQ OP_LT OP_GT OP_LTE OP_GTE
%token OP_EQ OP_PLUS_EQ OP_MINUS_EQ OP_TIMES_EQ OP_DIVIDE_EQ OP_MOD_EQ OP_BITWISE_AND_EQ OP_BITWISE_OR_EQ OP_BITWISE_XOR_EQ OP_LEFTSHIFT_EQ OP_RIGHTSHIFT_EQ
%token OP_BITWISE_AND OP_BITWISE_NOT OP_BITWISE_OR OP_BITWISE_XOR OP_LEFTSHIFT OP_RIGHTSHIFT
%token OP_LBRACKET OP_RBRACKET OP_L_SQUAREBRACKET OP_R_SQUAREBRACKET

%token T_SEMICOLON T_COMMA T_COLON
%token T_ENUM
%token T_LBRACE T_RBRACE // left and right curly brackets
%token T_SIZEOF
// T_DOT T_COLON T_QUESTION

%token T_NUMBER T_STRING T_IDENTIFIER

%type <astNode> FUNC_DEF DECLARATION PARAMETER 
%type <astNodeList> TRANSLATION_UNIT BLOCK_ITEM_LIST 
%type <astSpecifierList> SPECIFIERS TYPE_SPECIFIER
%type <statement> COMPND_STATMNT STATMNT JUMP_STATMNT SELECTION_STATMNT ITERATION_STATMNT LABELED_STATMNT
%type <initDeclaratorList> INIT_DECLARATOR_LIST INIT_DECLARATOR
%type <parameterList> PARAMETER_LIST
%type <argumentList> ARGUMENT_LIST
%type <arrayInitializerList> ARRAY_INITIALIZER_LIST
%type <enumerator> ENUMERATOR
%type <enumeratorList> ENUM_LIST
%type <enumSpecifier> ENUM_SPECIFIER
%type <expr> EXPR PRIMARY_EXPR PTR_UNARY_EXPR
%type <modifiableLValue> MODIFIABLE_LVALUE_EXPR VARIABLE
%type <number> T_NUMBER
%type <string> T_STRING T_IDENTIFIER
%type <string> T_TYPEDEF T_VOID T_BOOL T_SIGNED T_UNSIGNED T_CHAR T_INT T_SHORT T_LONG T_FLOAT T_DOUBLE T_SIZEOF

%right OP_EQ OP_PLUS_EQ OP_MINUS_EQ OP_TIMES_EQ OP_DIVIDE_EQ OP_MOD_EQ OP_BITWISE_OR_EQ OP_BITWISE_XOR_EQ OP_BITWISE_AND_EQ OP_LEFTSHIFT_EQ OP_RIGHTSHIFT_EQ
%left OP_LOGICAL_OR
%left OP_LOGICAL_AND
%left OP_BITWISE_OR
%left OP_BITWISE_XOR
%left OP_BITWISE_AND
%left OP_EQ_EQ OP_NEQ
%left OP_GT OP_GTE
%left OP_LT OP_LTE
%left OP_LEFTSHIFT OP_RIGHTSHIFT
%left OP_PLUS OP_MINUS
%left OP_TIMES OP_DIVIDE OP_MOD
%right OP_LOGICAL_NOT OP_BITWISE_NOT T_SIZEOF
%left OP_DECREMENT OP_INCREMENT OP_L_SQUAREBRACKET OP_R_SQUAREBRACKET

%nonassoc NOELSE
%nonassoc ST_ELSE

%nonassoc NOBREAK
%nonassoc ST_BREAK


%start ROOT


%%


ROOT : TRANSLATION_UNIT { g_root = $1; }

TRANSLATION_UNIT : FUNC_DEF { $$ = new TranslationUnit($1); }
                | DECLARATION { $$ = new TranslationUnit($1); }
                | TRANSLATION_UNIT FUNC_DEF { $$ = $1->insert($2); }
                | TRANSLATION_UNIT DECLARATION { $$ = $1->insert($2); }

FUNC_DEF : T_IDENTIFIER OP_LBRACKET OP_RBRACKET COMPND_STATMNT { $$ = new FunctionDefinition(new ASTSpecifierList("int"), $1, NULL, $4); } // implicit return type
         | SPECIFIERS T_IDENTIFIER OP_LBRACKET OP_RBRACKET COMPND_STATMNT  { $$ = new FunctionDefinition($1, $2, NULL, $5); }
         | T_IDENTIFIER OP_LBRACKET T_VOID OP_RBRACKET COMPND_STATMNT { $$ = new FunctionDefinition(new ASTSpecifierList("int"), $1, NULL, $5); } // implicit return type
         | SPECIFIERS T_IDENTIFIER OP_LBRACKET T_VOID OP_RBRACKET COMPND_STATMNT { $$ = new FunctionDefinition($1, $2, NULL, $6); }
         | T_IDENTIFIER OP_LBRACKET PARAMETER_LIST OP_RBRACKET COMPND_STATMNT { $$ = new FunctionDefinition(new ASTSpecifierList("int"), $1, $3, $5); } // implicit return type
         | SPECIFIERS T_IDENTIFIER OP_LBRACKET PARAMETER_LIST OP_RBRACKET COMPND_STATMNT { $$ = new FunctionDefinition($1, $2, $4, $6); }
         
PARAMETER_LIST : PARAMETER { $$ = new ParameterList($1); }
               | PARAMETER_LIST T_COMMA PARAMETER{ $$ = $1->addNewParameter($3); }
               
PARAMETER: SPECIFIERS T_IDENTIFIER { $$ = new Parameter($1, $2); }
            | SPECIFIERS OP_TIMES T_IDENTIFIER { $$ = new Parameter($1, $3); } // pointer
         
COMPND_STATMNT : T_LBRACE T_RBRACE { $$ = new CompoundStatement(NULL); }
                | T_LBRACE BLOCK_ITEM_LIST T_RBRACE { $$ = new CompoundStatement($2); }

// BLOCK_ITEM_LIST is a sequence of statements and declarations (see here: http://port70.net/~nsz/c/c99/n1256.html#6.8.2 - this is from the C99 specification but it should still work for C89/C90)
BLOCK_ITEM_LIST : STATMNT { $$ = new BlockItemList($1); }
                | DECLARATION { $$ = new BlockItemList($1); }
                | BLOCK_ITEM_LIST STATMNT { $$ = $1->insert($2); }
                | BLOCK_ITEM_LIST DECLARATION { $$ = $1->insert($2); }

STATMNT : EXPR T_SEMICOLON { $$ = new ExpressionStatement($1); }; // expression statement
            | COMPND_STATMNT { $$ = $1; } // compound statement
            | JUMP_STATMNT T_SEMICOLON { $$ = $1; } // jump statement
            | SELECTION_STATMNT { $$ = $1; } //selection statement 
            | ITERATION_STATMNT { $$ = $1; } //iteration statement
            | LABELED_STATMNT { $$ = $1; } //case statement

EXPR : PRIMARY_EXPR { $$ = $1; }
     | MODIFIABLE_LVALUE_EXPR { $$ = $1; }
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
     | MODIFIABLE_LVALUE_EXPR OP_EQ EXPR {$$ = new EqOperator($1, $3);} // (Horace) Incomplete - LHS doesn't have to be a variable; it can be struct, array element, etc.
     | MODIFIABLE_LVALUE_EXPR OP_PLUS_EQ EXPR { $$ = new PlusEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_MINUS_EQ EXPR { $$ = new MinusEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_TIMES_EQ EXPR { $$ = new TimesEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_DIVIDE_EQ EXPR { $$ = new DivideEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_MOD_EQ EXPR { $$ = new ModEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_BITWISE_AND_EQ EXPR { $$ = new AndEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_BITWISE_OR_EQ EXPR { $$ = new OrEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_BITWISE_XOR_EQ EXPR { $$ = new XorEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_LEFTSHIFT_EQ EXPR { $$ = new LeftshiftEqOperator($1, $3);}
     | MODIFIABLE_LVALUE_EXPR OP_RIGHTSHIFT_EQ EXPR { $$ = new RightshiftEqOperator($1, $3);}
     | OP_BITWISE_NOT EXPR { $$ = new BitwiseNotOperator($2);}
     | EXPR OP_BITWISE_AND EXPR { $$ = new BitwiseAndOperator($1, $3);}
     | EXPR OP_BITWISE_OR EXPR { $$ = new BitwiseOrOperator($1, $3);}     
     | EXPR OP_BITWISE_XOR EXPR { $$ = new BitwiseXorOperator($1, $3);}     
     | EXPR OP_LEFTSHIFT EXPR { $$ = new LeftshiftOperator($1, $3);}     
     | EXPR OP_RIGHTSHIFT EXPR { $$ = new RightshiftOperator($1, $3);}
     | OP_MINUS EXPR %prec OP_LOGICAL_NOT{ $$ = new UnaryMinusOperator($2);}
     | OP_PLUS EXPR %prec OP_LOGICAL_NOT{ $$ = new UnaryPlusOperator($2);}
     | T_SIZEOF OP_LBRACKET SPECIFIERS OP_RBRACKET { $$ = new SizeOfOperator($3); }
     | T_SIZEOF OP_LBRACKET SPECIFIERS OP_TIMES OP_RBRACKET { $$ = new SizeOfOperator($3->insert(new ASTSpecifierList("pointer"))); }
     | T_SIZEOF EXPR { $$ = new SizeOfOperator($2); }
     | PTR_UNARY_EXPR { $$ = $1; }

PTR_UNARY_EXPR : MODIFIABLE_LVALUE_EXPR OP_DECREMENT { $$ = new PostfixDecrementOperator($1);}
             | MODIFIABLE_LVALUE_EXPR OP_INCREMENT { $$ = new PostfixIncrementOperator($1);}
             | OP_DECREMENT MODIFIABLE_LVALUE_EXPR %prec OP_LOGICAL_NOT { $$ = new PrefixDecrementOperator($2);}
             | OP_INCREMENT MODIFIABLE_LVALUE_EXPR %prec OP_LOGICAL_NOT { $$ = new PrefixIncrementOperator($2);}
             | OP_BITWISE_AND MODIFIABLE_LVALUE_EXPR %prec OP_LOGICAL_NOT { $$ = new AddressOfOperator($2); }
             | T_IDENTIFIER OP_LBRACKET OP_RBRACKET { $$ = new FunctionCall($1, NULL); }
             | T_IDENTIFIER OP_LBRACKET ARGUMENT_LIST OP_RBRACKET { $$ = new FunctionCall($1, $3); }

MODIFIABLE_LVALUE_EXPR : VARIABLE { $$ = $1; }
            | T_IDENTIFIER OP_L_SQUAREBRACKET EXPR OP_R_SQUAREBRACKET { $$ = new ArrayElement($1, $3); }
            | OP_TIMES MODIFIABLE_LVALUE_EXPR { $$ = new DereferenceOperator($2); }
            | OP_TIMES PRIMARY_EXPR { $$ = new DereferenceOperator($2); }
            | OP_TIMES PTR_UNARY_EXPR { $$ = new DereferenceOperator($2); }

PRIMARY_EXPR : T_NUMBER { $$ = new Number($1); } // TODO: add support for hex, binary, etc. integers
             | T_STRING { $$ = new StringLiteral($1); }
//             | VARIABLE { $$ = $1; } // (Horace) temporarily 'removing' VARIABLE from PRIMARY_EXPR to avoid shift-reduce conflicts with MODIFIABLE_LVALUE_EXPR
             | OP_LBRACKET EXPR OP_RBRACKET { $$ = new ParenthesizedExpression($2); }

VARIABLE : T_IDENTIFIER { $$ = new Variable($1); }

ARGUMENT_LIST : EXPR { $$ = new ArgumentList($1); }
                | ARGUMENT_LIST T_COMMA EXPR { $$ = $1->addArgument($3); }

JUMP_STATMNT : ST_BREAK { $$ = new BreakStatement(); }
             | ST_CONTINUE { $$ = new ContinueStatement(); }
             | ST_RETURN EXPR { $$ = new ReturnStatement($2); }
             | ST_RETURN { $$ = new ReturnStatement(NULL); }
             
SELECTION_STATMNT : ST_IF OP_LBRACKET EXPR OP_RBRACKET STATMNT %prec NOELSE{ $$ = new IfStatement($3, $5); } 
                  | ST_IF OP_LBRACKET EXPR OP_RBRACKET STATMNT ST_ELSE STATMNT { $$ = new IfElseStatement($3, $5, $7);}
                  | ST_SWITCH OP_LBRACKET EXPR OP_RBRACKET STATMNT { $$ = new SwitchStatement($3, $5);}


ITERATION_STATMNT : ST_WHILE OP_LBRACKET EXPR OP_RBRACKET STATMNT { $$ = new WhileStatement($3, $5); }
                  | ST_FOR OP_LBRACKET EXPR T_SEMICOLON EXPR T_SEMICOLON EXPR OP_RBRACKET STATMNT { $$ = new ForStatement($3, $5, $7, $9);} // for(expr,expr,expr)
                  | ST_FOR OP_LBRACKET T_SEMICOLON EXPR T_SEMICOLON EXPR OP_RBRACKET STATMNT { $$ = new ForStatement(NULL, $4, $6, $8);} // for(,expr,expr)
                  | ST_FOR OP_LBRACKET EXPR T_SEMICOLON T_SEMICOLON EXPR OP_RBRACKET STATMNT { $$ = new ForStatement($3, NULL, $6, $8);} // for(expr,,expr)
                  | ST_FOR OP_LBRACKET EXPR T_SEMICOLON EXPR T_SEMICOLON OP_RBRACKET STATMNT { $$ = new ForStatement($3, $5, NULL, $8);} // for(expr,expr,)
                  | ST_FOR OP_LBRACKET T_SEMICOLON T_SEMICOLON EXPR OP_RBRACKET STATMNT { $$ = new ForStatement(NULL, NULL, $5, $7);} // for(,,expr)
                  | ST_FOR OP_LBRACKET T_SEMICOLON EXPR T_SEMICOLON OP_RBRACKET STATMNT { $$ = new ForStatement(NULL, $4, NULL, $7);} // for(,expr,)
                  | ST_FOR OP_LBRACKET EXPR T_SEMICOLON T_SEMICOLON OP_RBRACKET STATMNT { $$ = new ForStatement($3, NULL, NULL, $7);} // for(expr,,)
                  | ST_FOR OP_LBRACKET T_SEMICOLON T_SEMICOLON OP_RBRACKET STATMNT { $$ = new ForStatement(NULL, NULL, NULL, $6);} // for(,,,)
 

SPECIFIERS : TYPE_SPECIFIER { $$ = $1; }
//                | T_TYPEDEF { $$ = new ASTSpecifierList("typedef"); }
                | SPECIFIERS TYPE_SPECIFIER { $$ = $1->insert($2); }
//                | SPECIFIERS T_TYPEDEF { $$ = $1->insert(new ASTSpecifierList("typedef")); }
                

// Note (Horace): TYPE_SPECIFIER is currently incomplete
TYPE_SPECIFIER : T_VOID { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_BOOL { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_SIGNED { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_UNSIGNED { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_CHAR { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_INT { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_SHORT { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_LONG { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_FLOAT { $$ = new ASTSpecifierList(*$1); delete $1; }
                | T_DOUBLE { $$ = new ASTSpecifierList(*$1); delete $1; }
                | ENUM_SPECIFIER { $$ = new ASTSpecifierList($1); }

//    DECLARATION : SPECIFIERS T_IDENTIFIER T_SEMICOLON { $$ = new Declaration($1, $2, NULL); }
//                | SPECIFIERS T_IDENTIFIER OP_EQ EXPR T_SEMICOLON { $$ = new Declaration($1, $2, $4); }
//                | SPECIFIERS OP_TIMES T_IDENTIFIER T_SEMICOLON { $$ = new PointerDeclaration($1, $3, NULL); }
//                | SPECIFIERS OP_TIMES T_IDENTIFIER OP_EQ EXPR T_SEMICOLON { $$ = new PointerDeclaration($1, $3, $5); }
//                | SPECIFIERS T_IDENTIFIER OP_L_SQUAREBRACKET EXPR OP_R_SQUAREBRACKET T_SEMICOLON { $$ = new ArrayDeclaration($1, $2, $4, NULL); }
//                | SPECIFIERS T_IDENTIFIER OP_L_SQUAREBRACKET EXPR OP_R_SQUAREBRACKET OP_EQ T_LBRACE ARRAY_INITIALIZER_LIST T_RBRACE T_SEMICOLON { $$ = new ArrayDeclaration($1, $2, $4, $8); }
//                | ENUM_SPECIFIER T_SEMICOLON { $$ = $1; }
//    //            | T_IDENTIFIER OP_LBRACKET OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration(new ASTSpecifierList("int"), $1, NULL); } // implicit return type (TODO: temporarily commented out due to shift reduce error)
//                | SPECIFIERS T_IDENTIFIER OP_LBRACKET OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration($1, $2, NULL); }
//                | T_IDENTIFIER OP_LBRACKET T_VOID OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration(new ASTSpecifierList("int"), $1, NULL); } // implicit return type
//                | SPECIFIERS T_IDENTIFIER OP_LBRACKET T_VOID OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration($1, $2, NULL); }
//                | T_IDENTIFIER OP_LBRACKET PARAMETER_LIST OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration(new ASTSpecifierList("int"), $1, $3); } // implicit return type
//                | SPECIFIERS T_IDENTIFIER OP_LBRACKET PARAMETER_LIST OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration($1, $2, $4); }


DECLARATION : SPECIFIERS INIT_DECLARATOR_LIST T_SEMICOLON	{ $$ = $2->generateDeclarations($1); }
	| ENUM_SPECIFIER T_SEMICOLON			{ $$ = $1; }
//    | T_IDENTIFIER OP_LBRACKET OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration(new ASTSpecifierList("int"), $1, NULL); } // implicit return type (TODO: temporarily commented out due to shift reduce error)
	| T_IDENTIFIER OP_LBRACKET T_VOID OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration(new ASTSpecifierList("int"), $1, NULL); } // implicit return type
	| T_IDENTIFIER OP_LBRACKET PARAMETER_LIST OP_RBRACKET T_SEMICOLON { $$ = new FunctionDeclaration(new ASTSpecifierList("int"), $1, $3); } // implicit return type
	
INIT_DECLARATOR_LIST : INIT_DECLARATOR { $$ = $1; }
		            | INIT_DECLARATOR_LIST T_COMMA INIT_DECLARATOR { $$ = $1->insert($3); }

INIT_DECLARATOR : T_IDENTIFIER { $$ = new InitDeclaratorList("variable", $1, NULL, NULL, NULL); }
            	| OP_TIMES T_IDENTIFIER { $$ = new InitDeclaratorList("pointer", $2, NULL, NULL, NULL); }
            	| T_IDENTIFIER OP_L_SQUAREBRACKET EXPR OP_R_SQUAREBRACKET { $$ = new InitDeclaratorList("array", $1, $3, NULL, NULL); }
            	| T_IDENTIFIER OP_EQ EXPR { $$ = new InitDeclaratorList("variable", $1, $3, NULL, NULL); }
            	| OP_TIMES T_IDENTIFIER OP_EQ EXPR { $$ = new InitDeclaratorList("pointer", $2, $4, NULL, NULL); }
            	| T_IDENTIFIER OP_L_SQUAREBRACKET EXPR OP_R_SQUAREBRACKET OP_EQ T_LBRACE ARRAY_INITIALIZER_LIST T_RBRACE { $$ = new InitDeclaratorList("array", $1, $3, $7, NULL); }
            	| T_IDENTIFIER OP_LBRACKET OP_RBRACKET { $$ = new InitDeclaratorList("function", $1, NULL, NULL, NULL); }
            	| T_IDENTIFIER OP_LBRACKET T_VOID OP_RBRACKET { $$ = new InitDeclaratorList("function", $1, NULL, NULL, NULL); }
            	| T_IDENTIFIER OP_LBRACKET PARAMETER_LIST OP_RBRACKET { $$ = new InitDeclaratorList("function", $1, NULL, NULL, $3); }

ARRAY_INITIALIZER_LIST : EXPR { $$ = new ArrayInitializerList($1); }
                        | ARRAY_INITIALIZER_LIST T_COMMA EXPR { $$->insert($3); }
            // TODO: implement initializer lists for multi-dimentional arrays

ENUM_SPECIFIER : T_ENUM T_IDENTIFIER T_LBRACE ENUM_LIST T_RBRACE { $$ = new EnumSpecifier($2, $4);}
               | T_ENUM T_LBRACE ENUM_LIST T_RBRACE { $$ = new EnumSpecifier(NULL, $3);}
               | T_ENUM T_IDENTIFIER { $$ = new EnumSpecifier($2, NULL);}
    
ENUM_LIST : ENUMERATOR { $$ = new EnumeratorList($1); }
          | ENUM_LIST T_COMMA ENUMERATOR { $$ = $1->addNewEnumerator($3);}

ENUMERATOR : T_IDENTIFIER { $$ = new Enumerator($1, NULL);}
           | T_IDENTIFIER OP_EQ EXPR {$$ = new Enumerator($1, $3);}

LABELED_STATMNT : ST_CASE EXPR T_COLON STATMNT{ $$ = new CaseStatement($2, $4); }
                | ST_DEFAULT T_COLON STATMNT { $$ = new DefaultCaseStatement($3);}

%%

const ASTNode* g_root; // Definition of variable (to match declaration earlier)

const ASTNode* parseAST() {
  g_root=0;
  yyparse();
  return g_root;
}

const ASTNode* parseAST(char* inFile) {
  g_root = 0;
  yyin = fopen(inFile, "r");
  if(yyin) { 
    yyparse();
  }
  fclose(yyin);
  return g_root;
}