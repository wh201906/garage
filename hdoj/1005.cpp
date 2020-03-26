#include <stdio.h>

int list[1000002];

int main()
{
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    list[1] = 1;
    list[2] = 1;
    while (a != 0 || b != 0 || n != 0)
    {
        for (int i = 3; i <= n;i++)
        {
            list[i] = (a * list[i - 1] + b * list[i - 2]) % 7;
        }
        printf("%d\n",list[n]);
        scanf("%d %d %d", &a, &b, &n);
    }
}