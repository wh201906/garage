#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int getchild(int n)
{
    if (n == 1 || n == 2 || n == 3)
    {
        return n;
    }
    else
    {
        return getchild(n - 1) + getchild(n - 3);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n > 0)
    {
        printf("%d\n", getchild(n));
        scanf("%d", &n);
    }
}