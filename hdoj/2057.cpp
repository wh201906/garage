#include <stdio.h>

int main()
{
    long long a, b, sum;
    while (scanf("%llx %llx", &a, &b) != EOF)
    {
        sum = a + b;
        if (sum < 0)
        {
            sum = -sum;
            printf("-");
        }
        printf("%llX\n", sum);
    }

    return 0;
}