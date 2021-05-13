#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n;i++)
    {
        int a, b,sum;
        scanf("%d %d", &a, &b);
        a %= 100;
        b %= 100;
        sum = a + b;
        sum %= 100;
        printf("%d\n", sum);
    }
}