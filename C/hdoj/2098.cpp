#include <stdio.h>

bool PrimePool[10003] = {false};

int main()
{
    PrimePool[2] = true;
    PrimePool[3] = true;
    for (int i = 5; i < 10002; i += 2)
    {
        int j;
        for (j = 3; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                break;
            }
        }
        if (j * j > i)
        {
            PrimePool[i] = true;
        }
    }
    int n;
    scanf("%d", &n);
    while (n != 0)
    {
        int count = 0;
        for (int i = 2; 2 * i < n; i++)
        {
            if (PrimePool[i] && PrimePool[n - i])
            {
                count++;
            }
        }
        printf("%d\n", count);
        scanf("%d", &n);
    }
    return 0;
}