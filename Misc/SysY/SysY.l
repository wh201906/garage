%{
#include <stdio.h>
#include "common.h"

FILE *file;

int errorLine = 0;
int currLine = 1;

int finishedFlag = 0;

void blockComment();
void printSingle();
void handleDec();
void handleOct();
void handleHex();
void handleError();
void handleID();
%}

IntConst_dec [1-9][0-9]*
IntConst_oct 0[0-7]*
IntConst_hex 0[xX][0-9a-fA-F]*

Identifier_head ([_a-zA-Z])
Identifier {Identifier_head}({Identifier_head}|[0-9])*

LineComment "//".+$

%%

{LineComment}   { printf("Comment: "); ECHO; }
"/*"            { blockComment(); }

"break"         { printSingle(); /*return(BREAK);*/ }
"const"         { printSingle(); /*return(CONST);*/ }
"continue"      { printSingle(); /*return(CONTINUE);*/ }
"else"          { printSingle(); /*return(ELSE);*/ }
"if"            { printSingle(); /*return(IF);*/ }
"int"           { printSingle(); /*return(INT);*/ }
"return"        { printSingle(); /*return(RETURN);*/ }
"void"          { printSingle(); /*return(VOID);*/ }
"while"         { printSingle(); /*return(WHILE);*/ }

{Identifier}    { handleID(); /*return(yytext)*/ }

{IntConst_dec}  { handleDec(); /*return(INTCONST);*/ }
{IntConst_oct}  { handleOct(); /*return(INTCONST);*/ }
{IntConst_hex}  { handleHex(); /*return(INTCONST);*/ }


"&&"            { printSingle(); /*return(OP_L_AND);*/ }
"||"            { printSingle(); /*return(OP_L_OR);*/ }
"!"             { printSingle(); /*return('!');*/ }

"<="            { printSingle(); /*return(OP_N_LE);*/ }
">="            { printSingle(); /*return(OP_N_GE);*/ }
"=="            { printSingle(); /*return(OP_N_EQ);*/ }
"!="            { printSingle(); /*return(OP_N_NE);*/ }
"<"             { printSingle(); /*return('<');*/ }
">"             { printSingle(); /*return('>');*/ }

"-"             { printSingle(); /*return('-');*/ }
"+"             { printSingle(); /*return('+');*/ }
"*"             { printSingle(); /*return('*');*/ }
"/"             { printSingle(); /*return('/');*/ }
"%"             { printSingle(); /*return('%');*/ }
 
"="             { printSingle(); /*return('=');*/ }
";"             { printSingle(); /*return(';');*/ }
","             { printSingle(); /*return(',');*/ }
"("             { printSingle(); /*return('(');*/ }
")"             { printSingle(); /*return(')');*/ }
"["             { printSingle(); /*return('[');*/ }
"]"             { printSingle(); /*return(']');*/ }
"{"             { printSingle(); /*return('{');*/ }
"}"             { printSingle(); /*return('}');*/ }
 
"\n"|"\r\n"     { printf("\n%4d: ", ++currLine); }

[ \t\v\r\n\f]   { /* do nothing */ }

.               { handleError(); }

%%

int yywrap()
{
    printf("\nScan finished\n");
    finishedFlag = 1;
    return(1);
}


void blockComment()
{
	char ch;
    int flag, startLine;
    startLine = currLine;
    printf("Comment: \n      /");
    putchar('*');
    flag = 0;
	while ((ch = input()) != '\0')
	{
		putchar(ch);
		if (ch == '*')
		{
            flag = 1;
        }
        else if(flag && ch == '/')
        {
            break;
        }
        else
        {
            flag = 0;
        }
        if(ch == '\n')
        {
            printf("      "); // align
            currLine++;
        }
	}
    if (!(flag && ch == '/'))
        printf("\nError at line %d: Incomplete comment\n", startLine);
}

void printSingle()
{
    putchar('<');
    ECHO;
    printf("> ");
}

void handleDec()
{
    int tmp;
    sscanf(yytext, "%d", &tmp);
    yylval = tmp;
    printf("<IntConst, dec, %s, %d> ", yytext, yylval);
}
void handleOct()
{
    int tmp;
    sscanf(yytext, "%o", &tmp);
    yylval = tmp;
    printf("<IntConst, oct, %s, %d> ", yytext, yylval);
}
void handleHex()
{
    int tmp;
    sscanf(yytext, "%x", &tmp);
    yylval = tmp;
    printf("<IntConst, hex, %s, %d> ", yytext, yylval);
}

void handleError()
{
    if(currLine > errorLine)
    {
        errorLine = currLine;
        printf("\nError at line %d: Undefined symbol\n", currLine);
    }
}

void handleID()
{
    printf("<ID, %s> ", yytext);
}

int main(int argc, char *argv[])
{
    if(argc <= 1)
    {
        printf("Processing stdin\n");
    }
    else
    {
        if((file = fopen(argv[1], "r")) == NULL)
        {
            printf("Failed to open %s\n", argv[1]);
            return 0;
        }
        else
        {
            printf("Processing %s\n", argv[1]);
            yyin = file;
        }
    }
    finishedFlag = 0;
    printf("\n%4d: ", 1);
    while(!finishedFlag)
        yylex();
    return 0;
}