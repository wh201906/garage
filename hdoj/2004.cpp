#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    double a;
    while (scanf("%lf", &a) != EOF)
    {
        if (a >= 0 && a < 60)
        {
            printf("E\n");
        }
        else if (a >= 60 && a < 70)
        {
            printf("D\n");
        }
        else if (a >= 70 && a < 80)
        {
            printf("C\n");
        }
        else if (a >= 80 && a < 90)
        {
            printf("B\n");
        }
        else if (a >= 90 && a <= 100)
        {
            printf("A\n");
        }
        else
        {
            printf("Score is error!\n");
        }
    }
}
