#include <stdio.h>
#include <math.h>

int lis[1000005];

int main()
{
    int t, n, tmp, j;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        long long sum = 0;
        scanf("%d", &n);
        for (j = 0; j < n; j++)
        {
            scanf("%d", &tmp);
            sum += tmp;
            lis[j] = tmp;
        }
        for (j = 0; j < n; j++)
        {
            if (lis[j] > sum - lis[j] + 1)
                break;
        }
        if (j < n)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}