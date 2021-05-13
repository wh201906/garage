#include <stdio.h>

long long list[10000000];

long long gcd(long long a, long long b)
{
    long long tmp;
    if (a < b)
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
    freopen("in.txt", "r", stdin);
    int n;
    long long tmp;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &list[i]);
        }
        for (int i = 1; i < n; i++)
        {
            tmp = list[i - 1] * list[i];
            list[i] = tmp / gcd(list[i - 1], list[i]);
        }
        printf("%lld\n", list[n - 1]);
    }
    return 0;
}