#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

float list[1000] = {0.0};

int main()
{
    int n, a;
    for (int i = 0; i < 1000; i++)
    {
        list[i] = 1.0 / (i + 1);
    }
    for (int i = 1; i < 1000; i++)
    {
        if (i % 2 == 0)
        {
            list[i] = list[i - 1] + list[i];
        }
        else
        {
            list[i] = list[i - 1] - list[i];
        }
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        printf("%.2f\n", list[a - 1]);
    }
}