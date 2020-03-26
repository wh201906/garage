#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

bool isPrime[3000];

int main()
{
    int x, y;
    isPrime[2] = true;
    isPrime[3] = true;
    for (int i = 4; i < 3000; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            isPrime[i] = true;
            if (i % j == 0)
            {
                isPrime[i] = false;
                break;
            }
        }
    }
    scanf("%d %d", &x, &y);
    while (x != 0 || y != 0)
    {
        int tmp;
        if (x > y)
        {
            tmp = x;
            x = y;
            y = tmp;
        }
        bool is=true;
        for (int i = x; i <= y; i++)
        {
            if (isPrime[i*i+i+41] != true)
            {
                is = false;
                break;
            }
        }
        if (is)
        {
            printf("OK\n");
        }
        else
        {
            printf("Sorry\n");
        }
        scanf("%d %d", &x, &y);
    }
}