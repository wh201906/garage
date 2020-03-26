#include <stdio.h>

int main()
{
    int n, sum;
    while (scanf("%d", &n) != EOF)
    {
        sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += i;
        }
        printf("%d\n\n", sum);
    }
}