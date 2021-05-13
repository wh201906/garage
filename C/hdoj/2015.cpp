#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
    int n,m,i;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        printf("%d", 2 * m - m + 1);
        for (i = 2; i*m <= n; i++)
        {
            printf(" %d", 2*m*i-m+1);
        }
        i--;
        if ((n - (i * m)) % m != 0)
        {
            printf(" %d", (i * m + 1 + n));
        }
        printf("\n");
    }
}