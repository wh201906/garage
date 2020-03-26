#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int list[110];

int main()
{
    int n, a, l;
    scanf("%d", &n);
    while (n != 0)
    {
        l = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a);
            list[i] = a;
            if (a < list[l])
            {
                l = i;
            }
        }
        printf("%d", list[l]);
        for (int i = 1; i < n; i++)
        {
            if (i != l)
            {
                printf("% d", list[i]);
            }
            else
            {
                printf("% d", list[0]);
            }
        }
        printf("\n");
        scanf("%d", &n);
    }
}