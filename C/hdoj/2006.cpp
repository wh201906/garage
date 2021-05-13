#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int n,a=0,m=1;
    while (scanf("%d", &n) != EOF)
    {
        a = 0;
        m = 1;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            if ((a % 2) == 1)
                m *= a;
        }
        printf("%d\n", m);
    }
}