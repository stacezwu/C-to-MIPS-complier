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
"&="             { return OP_BITWISE_AND_EQ; }
"|="             { return OP_BITWISE_OR_EQ; }
"^="             { return OP_BITWISE_XOR_EQ; }
"<<="            { return OP_LEFTSHIFT_EQ; }
">>="            { return OP_RIGHTSHIFT_EQ; }
"("             { return OP_LBRACKET; }
")"             { return OP_RBRACKET; }
"["             { return OP_L_SQUAREBRACKET; }
"]"             { return OP_R_SQUAREBRACKET; }
"~"             { return OP_BITWISE_NOT; }
"&"             { return OP_BITWISE_AND; }
"|"             { return OP_BITWISE_OR; }
"^"             { return OP_BITWISE_XOR; }
"<<"            { return OP_LEFTSHIFT; }
">>"            { return OP_RIGHTSHIFT; }
";"             { return T_SEMICOLON; }
":"             { return T_COLON; }
","             { return T_COMMA; }
"{"             { return T_LBRACE; }
"}"             { return T_RBRACE; }
"?"             { return T_QUESTION; }

break           { return ST_BREAK; }
continue        { return ST_CONTINUE; }
return          { return ST_RETURN; }   /* jump statement */


do              { return ST_DO; }
switch          { return ST_SWITCH; }
case            { return ST_CASE; }
default         { return ST_DEFAULT; }
else            { return ST_ELSE; }
for             { return ST_FOR; }
if              { return ST_IF; }
while           { return ST_WHILE; } /* selection/iteration statement */

enum            { return T_ENUM; }
struct          { return T_STRUCT; }

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

sizeof          { return T_SIZEOF; }

0[0-7]+[uUlL]? { yylval.int_type = std::stoi(yytext, NULL, 8); return T_INTEGER_LITERAL; }
0[xX][0-9A-Fa-f]+[uUlL]? { yylval.int_type = std::stoi(yytext, NULL, 16); return T_INTEGER_LITERAL; }
[0-9]+[uUlL]? { yylval.int_type = std::stoi(yytext, NULL, 10); return T_INTEGER_LITERAL; }
[0-9]+"."[0-9]*[fF] { yylval.double_type = std::stod(yytext); return T_DOUBLE_LITERAL; }
[0-9]*"."[0-9]+[fF] { yylval.double_type = std::stod(yytext); return T_DOUBLE_LITERAL; }
[0-9]+"."[0-9]* { yylval.double_type = std::stod(yytext); return T_FLOAT_LITERAL; }
[0-9]*"."[0-9]+ { yylval.double_type = std::stod(yytext); return T_FLOAT_LITERAL; }
[0-9]*"."[0-9]+([Ee][+-]?[0-9]+)?[fF]	{ yylval.double_type = std::stod(yytext); return T_FLOAT_LITERAL; }
[0-9]+"."[0-9]*([Ee][+-]?[0-9]+)?[fF]	{ yylval.double_type = std::stod(yytext); return T_FLOAT_LITERAL; }
[0-9]*"."[0-9]+([Ee][+-]?[0-9]+)?	{ yylval.double_type = std::stod(yytext); return T_DOUBLE_LITERAL; }
[0-9]+"."[0-9]*([Ee][+-]?[0-9]+)?	{ yylval.double_type = std::stod(yytext); return T_DOUBLE_LITERAL; }
\"(\\.|[^\\"])*\"                  {
                                    std::string tmp = std::string(yytext);
                                    tmp = tmp.substr(1, tmp.size()-2);
                                    yylval.string = new std::string(tmp); return T_STRING;
                                    }
'([^'\\\n]|\\.)+'	{
                    std::string str = yytext;
                    if (str == "'\\\\'") { yylval.int_type = '\\'; }
                    else if (str == "'\\b'") { yylval.int_type = '\b'; }
                    else if (str == "'\\n'") { yylval.int_type = '\n'; }
                    else if (str == "'\\r'") { yylval.int_type = '\r'; }
                    else if (str == "'\\t'") { yylval.int_type = '\t'; }
                    else if (str == "'\\0'") { yylval.int_type = '\0'; }
                    else if (str == "'\\\"'") { yylval.int_type = '\"'; }
                    else if (str == "'\\\''") { yylval.int_type = '\''; }
                    else { yylval.int_type = str[1]; }
                    return T_CHAR_LITERAL;
                  }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.string=new std::string(yytext); return T_IDENTIFIER; }


[ \t\r\n]+		{;}
"#".*           {;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%
void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}