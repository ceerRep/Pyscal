%option c++ noyywrap 
%{
#include <stdlib.h>
#include <stdio.h>

int column = 1, linum = 1;

#include "lexer.h"

%}

ASC     [\x00-\x7f]
ASCN    [\x00-\t\v-\x7f]
U       [\x80-\xbf]
U2      [\xc2-\xdf]
U3      [\xe0-\xef]
U4      [\xf0-\xf4]

UANY    {ASC}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UANYN   {ASCN}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U} 
UONLY   {U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}

ALPHABET    [A-Za-z]|{UONLY}
DIGIT       [0-9]
SEMI        ;
POINTER     \^
PLUS        \+
MINUS       -
LPAREN      \(
RPAREN      \)
EQUAL       =
COLON       :
COMMA       ,
ASSIGN      :=
NOT_EQUAL   <>
LT          <
LE          <=
GE          >=
GT          >
AT          @
LBRACK      \[
RBRACK      \]
LBRACK2     \(\.
RBRACK2     \.\)
DOT         \.
STAR        \*
SLASH       \/
MOD2        %
AND         &
OR          \|
DOTDOT      \.\.
UNDERLINE   _
QUOTE       '


DIGITd      {DIGIT}|{UNDERLINE}

STRING      {QUOTE}([^'\n]|\\{QUOTE})*{QUOTE}

IDENTIFIER  ({ALPHABET}|{UNDERLINE})({ALPHABET}|{DIGIT}|{UNDERLINE})*

NUM_INT     {DIGIT}+
EXPONENT    e({PLUS}|{MINUS})?{NUM_INT}
NUM_REAL    (({NUM_INT}{EXPONENT})|((({NUM_INT}{DOT}{NUM_INT})|({DOT}{NUM_INT})){EXPONENT}?))

BLANK       [ \t]        
%%

<<EOF>>         { PROCESS(TOK_EOF); }

\n              {column = 1, linum++;}

{BLANK}         {column += yyleng; }

"div"			{ PROCESS(TOK_div); }
"mod"			{ PROCESS(TOK_mod); }
"and"			{ PROCESS(TOK_and); }
"or"			{ PROCESS(TOK_or); }
"not"			{ PROCESS(TOK_not); }
"to"			{ PROCESS(TOK_to); }
"downto"		{ PROCESS(TOK_downto); }
"with"			{ PROCESS(TOK_with); }
"do"			{ PROCESS(TOK_do); }
"begin"			{ PROCESS(TOK_begin); }
"end"			{ PROCESS(TOK_end); }
"if"			{ PROCESS(TOK_if); }
"then"			{ PROCESS(TOK_then); }
"else"			{ PROCESS(TOK_else); }
"case"			{ PROCESS(TOK_case); }
"of"			{ PROCESS(TOK_of); }
"while"			{ PROCESS(TOK_while); }
"repeat"		{ PROCESS(TOK_repeat); }
"until"			{ PROCESS(TOK_until); }
"for"			{ PROCESS(TOK_for); }
"array"			{ PROCESS(TOK_array); }
"const"			{ PROCESS(TOK_const); }
"procedure"		{ PROCESS(TOK_procedure); }
"var"			{ PROCESS(TOK_var); }
"function"		{ PROCESS(TOK_function); }
"goto"			{ PROCESS(TOK_goto); }
"call"          { PROCESS(TOK_call); }
"break"         { PROCESS(TOK_break); }
";"				{ PROCESS(TOK_SEMI); }
"^"				{ PROCESS(TOK_POINTER); }
"+"				{ PROCESS(TOK_PLUS); }
"-"				{ PROCESS(TOK_MINUS); }
"("				{ PROCESS(TOK_LPAREN); }
")"				{ PROCESS(TOK_RPAREN); }
"="				{ PROCESS(TOK_EQUAL); }
":"				{ PROCESS(TOK_COLON); }
","				{ PROCESS(TOK_COMMA); }
":="			{ PROCESS(TOK_ASSIGN); }
"<>"			{ PROCESS(TOK_NOT_EQUAL); }
"<"				{ PROCESS(TOK_LT); }
"<="			{ PROCESS(TOK_LE); }
">="			{ PROCESS(TOK_GE); }
">"				{ PROCESS(TOK_GT); }
"@"				{ PROCESS(TOK_AT); }
"["				{ PROCESS(TOK_LBRACK); }
"]"				{ PROCESS(TOK_RBRACK); }
"(."			{ PROCESS(TOK_LBRACK2); }
".)"			{ PROCESS(TOK_RBRACK2); }
"."				{ PROCESS(TOK_DOT); }
"*"				{ PROCESS(TOK_STAR); }
"/"				{ PROCESS(TOK_SLASH); }
"%"				{ PROCESS(TOK_MOD2); }
"&"				{ PROCESS(TOK_AND); }
"|"				{ PROCESS(TOK_OR); }
".."			{ PROCESS(TOK_DOTDOT); }

{IDENTIFIER}    { PROCESS(TOK_IDENTIFIER); }
{NUM_REAL}      { PROCESS(TOK_NUM_REAL); }
{NUM_INT}       { PROCESS(TOK_NUM_INT); }

{STRING}        { PROCESS(TOK_STRING); }

.               { PROCESS(TOK_UNKNOWN); }

%%
// NUM_INT     {DIGIT}|{DIGIT}{DIGITd}*{DIGIT}

/*
int main()
{
    dictionary_init();

    FlexLexer *lexer = new yyFlexLexer;
    while (lexer->yylex() != 0)
        ;
    return 0;
}
*/
