#include <stdio.h>

long long gcd(long long a, long long b)
{
    long long tmp;
    if (b > a)
    {
        tmp = a;
        a = b;
        b = tmp;
    }
    while (b > 0)
    {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int main()
{
    int t, n;
    long long tmp;

    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        long long res = 1;
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
        {
            scanf("%lld", &tmp);
            res *= tmp / gcd(res, tmp);
        }
        printf("%lld\n", res);
    }
    return 0;
}