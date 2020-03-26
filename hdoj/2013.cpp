#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int a, s;
    while (scanf("%d", &a) != EOF)
    {
        s = 1;
        for (int i = a; i > 1; i--)
        {
            s = (s + 1) * 2;
        }
        printf("%d\n", s);
    }
}