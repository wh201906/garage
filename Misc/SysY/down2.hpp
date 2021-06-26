#include <vector>
#include <stdio.h>
#include "common.h"

using namespace std;

extern vector<element> elementList; // input series
int ptr;
int tp;
int errorFlag = 0;

void Down2_E();
void Down2_e();
void Down2_T();
void Down2_t();
void Down2_F();
void Down2_A();
void Down2_M();

void Down2_error()
{
    printf("Error\n");
    errorFlag = 1;
}

void Down2_match(int type)
{
    if (errorFlag)
        return;
    if (elementList[ptr].type == type)
        ptr++;
    else
    {
        Down2_error();
    }
}

void Down2_E()
{
    if (errorFlag)
        return;
    tp = elementList[ptr].type;
    if (tp == '(' || tp == IDENTIFIER)
    {
        printf("Using: E, Te\n");
        Down2_T();
        Down2_e();
    }
    else
    {
        Down2_error();
    }
}
void Down2_e()
{
    if (errorFlag)
        return;
    tp = elementList[ptr].type;
    if (tp == '+' || tp == '-')
    {
        printf("Using: e, ATe\n");
        Down2_A();
        Down2_T();
        Down2_e();
    }
    else if (tp == '$' || tp == ')')
    {
        printf("Using: e, #\n");
        ; // do nothing, skipped
    }
    else
    {
        Down2_error();
    }
}
void Down2_T()
{
    if (errorFlag)
        return;
    tp = elementList[ptr].type;
    if (tp == '(' || tp == IDENTIFIER)
    {
        printf("Using: T, Ft\n");
        Down2_F();
        Down2_t();
    }
    else
    {
        Down2_error();
    }
}
void Down2_t()
{
    if (errorFlag)
        return;
    tp = elementList[ptr].type;
    if (tp == '*' || tp == '/')
    {
        printf("Using: t, MFt\n");
        Down2_M();
        Down2_F();
        Down2_t();
    }
    else if (tp == '+' || tp == '-' || tp == '$' || tp == ')')
    {
        printf("Using: t, #\n");
        ; // do nothing, skipped
    }
    else
    {
        Down2_error();
    }
}
void Down2_F()
{
    if (errorFlag)
        return;
    tp = elementList[ptr].type;
    if (tp == '(')
    {
        printf("Using: F, (E)\n");
        Down2_match('(');
        Down2_E();
        Down2_match(')');
    }
    else if (tp == IDENTIFIER)
    {
        printf("Using: F, i\n");
        Down2_match(IDENTIFIER);
    }
    else
    {
        Down2_error();
    }
}
void Down2_A()
{
    if (errorFlag)
        return;
    tp = elementList[ptr].type;
    if (tp == '+')
    {
        printf("Using: A, +\n");
        Down2_match('+');
    }
    else if (tp == '-')
    {
        printf("Using: A, -\n");
        Down2_match('-');
    }
    else
    {
        Down2_error();
    }
}
void Down2_M()
{
    if (errorFlag)
        return;
    tp = elementList[ptr].type;
    if (tp == '*')
    {
        printf("Using: M, *\n");
        Down2_match('*');
    }
    else if (tp == '/')
    {
        printf("Using: M, /\n");
        Down2_match('/');
    }
    else
    {
        Down2_error();
    }
}

bool Down2_Start()
{
    errorFlag = 0;
    elementList.push_back({'$', 0}); // end symbol
    Down2_E();
    if (elementList[ptr].type != '$')
        errorFlag = 1;
    return !errorFlag;
}