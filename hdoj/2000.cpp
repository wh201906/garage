#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void compare(char a, char b, char c)
{
    char res[3] = { 0 };
    if (a < b && a < c)
    {
        res[0] = a;
        if(b<c)
        {
            res[1] = b;
            res[2] = c;
        }
        else
        {
            res[1] = c;
            res[2] = b;
        }
    }
    else
    {
        if (b < a && b < c)
        {
            res[0] = b;
            if (a < c)
            {
                res[1] = a;
                res[2] = c;
            }
            else
            {
                res[1] = c;
                res[2] = a;
            }
        }
        else
        {
            res[0] = c;
            if (b < a)
            {
                res[1] = b;
                res[2] = a;
            }
            else
            {
                res[1] = a;
                res[2] = b;
            }
        }
    }
    printf("%c %c %c\n", res[0], res[1], res[2]);
}

int main() 
{
    char a, b, c;
    while (scanf("%c%c%c", &a, &b, &c) != EOF) {
        compare(a,b,c);
        scanf("%c", &a);
    }
    return 0;
}

//使用%c读取字符时会读入换行符，需要处理