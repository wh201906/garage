#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    unsigned long long range;
    long long a, b, sum;
    while (scanf("%d", &n) != EOF)
    {
        range = 1;
        for (int i = 1; i < n; i++)
        {
            range *= 2;
        }
        scanf("%lld %lld", &a, &b);
        sum = a + b;
        if((a>0&&b>0&&sum<0)||(a<0&&b<0&&sum>0))
        {
            printf("Yes\n");
            continue;
        }
        if ((sum>0 && sum<range)||(sum<=0&&sum>=-range))
        {
            printf("WaHaHa\n");
        }
        else
        {
            printf("Yes\n");
        }
    }
}