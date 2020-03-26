#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    long a, b,c, ji,ou;
    while (scanf("%ld %ld", &a, &b) != EOF)
    {
        if (a > b)
        {
            c = b;
            b = a;
            a = c;
        }
        ji = ou = 0;
        if (a % 2 != 0)
        {
            for (long i = a; i <= b; i += 2)
            {
                ji += i * i * i;
            }
            for (long i = (a + 1); i <= b; i += 2)
            {
                ou += i * i;
            }
        }
        else
        {
            for (long i = a; i <= b; i += 2)
            {
                ou += i * i ;
            }
            for (long i = (a + 1); i <= b; i += 2)
            {
                ji += i * i * i;
            }
        }
        printf("%ld %ld\n", ou, ji);
    }
}

//给定数据大小关系不确定时，需先判断后使用