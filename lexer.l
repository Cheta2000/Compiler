%option noyywrap
%option yylineno
%{
#include <iostream>
#include <string>
#include "types.hpp"
#include "parser.tab.hpp"

int yylex();
extern int yyerror(std::string);

%}

%x COMMENT

SPECIAL_SIGNS [\:\;\[\]\,]

%%

"VAR" {return VAR;}
"BEGIN" {return BEGIN_P;}
"END" {return END;}
"ASSIGN" {return ASSIGN;}
"IF" {return IF;}
"THEN" {return THEN;}
"ELSE" {return ELSE;}
"ENDIF" {return ENDIF;}
"WHILE" {return WHILE;}
"DO" {return DO;}
"ENDWHILE" {return ENDWHILE;}
"REPEAT" {return REPEAT;}
"UNTIL" {return UNTIL;}
"FOR" {return FOR;}
"FROM" {return FROM;}
"TO" {return TO;}
"DOWNTO" {return DOWNTO;}
"ENDFOR" {return ENDFOR;}
"READ" {return READ;}
"WRITE" {return WRITE;}
"EQ" {return EQ;}
"NEQ" {return NEQ;}
"LE" {return LE;}
"GE" {return GE;}
"LEQ" {return LEQ;}
"GEQ" {return GEQ;}
"PLUS" {return PLUS;}
"MINUS" {return MINUS;}
"TIMES" {return TIMES;}
"DIV" {return DIV;}
"MOD" {return MOD;}

\-?[0-9]+ {yylval.num =std::stoll(yytext); return num;}
\( BEGIN(COMMENT);
<COMMENT>{
    \) BEGIN(INITIAL);
    \( yyerror("Nested comment");
    . ;
}
[_a-z]+ {yylval.pidentifier=new std::string(yytext); return pidentifier;}
{SPECIAL_SIGNS} {return yytext[0];}
[ \t\n]+ ;
. {yyerror("Invalid sign");}


%%


