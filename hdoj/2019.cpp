#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    while (n != 0 || m != 0)
    {
        bool handled = false;
        int a;
        scanf("%d", &a);
        if (m <= a && handled == false)
        {
            printf("%d ", m);
            handled = true;
        }
        printf("%d", a);
        for (int i = 1; i < n; i++)
        {
            scanf("%d", &a);
            if (m <= a && handled == false)
            {
                printf(" %d", m);
                handled = true;
            }
            printf(" %d", a);
        }
        printf("\n");
        scanf("%d %d", &n, &m);
    }
}
