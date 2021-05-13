#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main()
{
    int n, list[101], tmp;
    scanf("%d", &n);
    while (n != 0)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &list[i]);
        }
        for (int i = n-1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (abs(list[j]) < abs(list[j + 1]))
                {
                    tmp = list[j + 1];
                    list[j + 1] = list[j];
                    list[j] = tmp;
                }
            }
        }
        printf("%d", list[0]);
        for (int i = 1; i < n; i++)
        {
            printf(" %d", list[i]);
        }
        printf("\n");
        scanf("%d", &n);
    }
}
