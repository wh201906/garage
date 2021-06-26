%option noyywrap

%{
#include <stdio.h>
#include "common.h"
#include <vector>
#include "down.hpp"

using namespace std;
vector<element> elementList;

FILE *file;

int errorLine = 0;
int currLine = 1;

int blockComment();
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

{LineComment}   { printf("Comment: "); ECHO; return(COMMENT); }
"/*"            { return(blockComment() ? COMMENT : ERROR); }

"break"         { printSingle(); return(BREAK); }
"const"         { printSingle(); return(CONST); }
"continue"      { printSingle(); return(CONTINUE); }
"else"          { printSingle(); return(ELSE); }
"if"            { printSingle(); return(IF); }
"int"           { printSingle(); return(INT); }
"return"        { printSingle(); return(RETURN); }
"void"          { printSingle(); return(VOID); }
"while"         { printSingle(); return(WHILE); }

{Identifier}    { handleID(); return(IDENTIFIER); }

{IntConst_dec}  { handleDec(); return(INTCONST); }
{IntConst_oct}  { handleOct(); return(INTCONST); }
{IntConst_hex}  { handleHex(); return(INTCONST); }


"&&"            { printSingle(); return(OP_L_AND); }
"||"            { printSingle(); return(OP_L_OR); }
"!"             { printSingle(); return('!'); }

"<="            { printSingle(); return(OP_N_LE); }
">="            { printSingle(); return(OP_N_GE); }
"=="            { printSingle(); return(OP_N_EQ); }
"!="            { printSingle(); return(OP_N_NE); }
"<"             { printSingle(); return('<'); }
">"             { printSingle(); return('>'); }

"-"             { printSingle(); return('-'); }
"+"             { printSingle(); return('+'); }
"*"             { printSingle(); return('*'); }
"/"             { printSingle(); return('/'); }
"%"             { printSingle(); return('%'); }
 
"="             { printSingle(); return('='); }
";"             { printSingle(); return(';'); }
","             { printSingle(); return(','); }
"("             { printSingle(); return('('); }
")"             { printSingle(); return(')'); }
"["             { printSingle(); return('['); }
"]"             { printSingle(); return(']'); }
"{"             { printSingle(); return('{'); }
"}"             { printSingle(); return('}'); }
 
"\n"|"\r\n"     { printf("\n%4d: ", ++currLine); }

[ \t\v\r\n\f]   { /* do nothing */ }

.               { handleError(); return(ERROR); }

%%

int blockComment()
{
    char ch;
    int flag, startLine;
    startLine = currLine;
    printf("Comment: \n      /");
    putchar('*');
    flag = 0;
    while ((ch = yyinput()) != '\0')
    {
        putchar(ch);
        if (ch == '*')
        {
            flag = 1;
        }
        else if (flag && ch == '/')
        {
            break;
        }
        else
        {
            flag = 0;
        }
        if (ch == '\n')
        {
            printf("      "); // align
            currLine++;
        }
    }
    if (!(flag && ch == '/'))
    {
        printf("\nError at line %d: Incomplete comment\n", startLine);
        return 0;
    }
    return 1;
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
    if (currLine > errorLine)
    {
        errorLine = currLine;
        printf("\nError at line %d: Undefined symbol\n", currLine);
    }
}

void handleID()
{
    printf("<ID, %s> ", yytext);
}

// arg[0]: path of the program
// (arg[1]): target .sy file. If not provided, use stdin
// arg[2]: parser mode
// not provided: disable
// 0: disable
// 1: table based
// 2: iteration based
int main(int argc, char *argv[])
{
    int currToken;
    int type;
#ifdef DEBUG
    yyin = fopen("exp.sy", "r");

#else
    if (argc <= 1)
    {
        printf("Processing stdin\n");
    }
    else
    {
        if ((file = fopen(argv[1], "r")) == NULL)
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
#endif
    printf("\n%4d: ", 1);
    while ((currToken = yylex()) != 0)
    {
        if (currToken != ERROR && currToken != COMMENT)
            elementList.push_back({currToken, yylval});
    }
    putchar('\n');
    if (argc >= 3)
    {
        sscanf(argv[2], "%d", &type);
        if(type == 1)
            if(Down_Start())
                printf("valid expression\n");
    }
#ifdef DEBUG
    if(Down_Start())
                printf("valid expression\n");
#endif
    return 0;
}