%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "maths_parser.tab.hpp"
%}

%%


"+"             { return OP_PLUS; }
"-"             { return OP_MINUS; }
"*"             { return OP_TIMES; }
"/"             { return OP_DIVIDE; }
"%"             { return OP_MOD; }
"++"            { return OP_INCREMENT; }
"--"            { return OP_DECREMENT; }
"!"             { return OP_LOGICAL_NOT; }
"||"            { return OP_LOGICAL_OR; }
"&&"            { return OP_LOGICAL_AND; }
"=="            { return OP_EQ_EQ; }
"!="            { return OP_NEQ; }
"<"             { return OP_LT; }
">"             { return OP_GT; }
"<="            { return OP_LTE; }
">="            { return OP_GTE; }
"="             { return OP_EQ; }
"+="            { return OP_PLUS_EQ; }
"-="            { return OP_MINUS_EQ; }
"*="            { return OP_TIMES_EQ; }
"/="            { return OP_DIVIDE_EQ; }
"%="            { return OP_MOD_EQ; }
"("             { return OP_LBRACKET; }
")"             { return OP_RBRACKET; }
";"             { return T_SEMICOLON; }
","             { return T_COMMA; }
"{"             { return T_LBRACE; }
"}"             { return T_RBRACE; }

break           { return ST_BREAK; }
continue        { return ST_CONTINUE; }
return          { return ST_RETURN; }   /* jump statement */


do              { return ST_DO; }
else            { return ST_ELSE; }
for             { return ST_FOR; }
if              { return ST_IF; }
while           { return ST_WHILE; } /* selection/iteration statement */


typedef         { yylval.string=new std::string(yytext); return T_TYPEDEF; }
void            { yylval.string=new std::string(yytext); return T_VOID; }
bool            { yylval.string=new std::string(yytext); return T_BOOL; }
signed          { yylval.string=new std::string(yytext); return T_SIGNED; }
unsigned        { yylval.string=new std::string(yytext); return T_UNSIGNED; }
char            { yylval.string=new std::string(yytext); return T_CHAR; }
int             { yylval.string=new std::string(yytext); return T_INT; }
short           { yylval.string=new std::string(yytext); return T_SHORT; }
long            { yylval.string=new std::string(yytext); return T_LONG; }
float           { yylval.string=new std::string(yytext); return T_FLOAT; }
double          { yylval.string=new std::string(yytext); return T_DOUBLE; } /* declaration */


[0-9]+([.][0-9]*)?      { yylval.number=strtod(yytext, 0); return T_NUMBER; }
\".*\"                  { yylval.string=new std::string(yytext); return T_STRING; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.string=new std::string(yytext); return T_IDENTIFIER; }


[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
