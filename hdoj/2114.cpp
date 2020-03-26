#include <stdio.h>

int main()
{
    long long n, sum,fac,start;
    while (scanf("%lld", &n) != EOF)
    {
        if(n<=200)
        {
            start = 1;
        }
        else
        {
            start = n-(n % 200)+1;
        }
        sum = 0;
        for (int i = start; i <= n; i++)
        {
            fac = i % 10000;
            sum += (fac * fac * fac);
            sum %= 10000;
        }
        printf("%04lld\n", sum);
    }
    return 0;
}