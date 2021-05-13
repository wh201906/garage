#include <stdio.h>

void test()
{
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i > -1000; i--)
        {
            printf("%d ", i);
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    //test();
    int t, list[100000], sum[100000];
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        if (i != 0)
            printf("\n");
        int n, tmp, max, l1, l2, label = 0;
        scanf("%d", &n);
        scanf("%d", &tmp);
        max = sum[0] = tmp;
        list[0] = -1;
        label++;
        if (tmp < 0)
        {
            list[label] = 0;
            label++;
        }
        for (int j = 1; j < n; j++)
        {
            scanf("%d", &tmp);
            sum[j] = sum[j - 1] + tmp;
            if (tmp < 0)
            {
                list[label] = j;
                label++;
            }
        }
        list[label] = n;
        label++;
        // if (label == 0)
        // {
        //     l1 = 0;
        //     l2 = n - 1;
        //     max = sum[n - 1];
        //     printf("Case %d:\n%d %d %d\n", i + 1, max, l1 + 1, l2 + 1);
        // }
        // else
        // {
        l1 = 0;
        int k, j;
        // for (k = 0; k < label-1; k++)
        // {
        //     if (sum[k] > max)
        //     {
        //         max = sum[k];
        //         l2 = k;
        //     }
        // }
        for (j = 0; j < label - 1; j++)
        {
            for (int k = j + 1; k < label; k++)
            {
                if (sum[list[k] - 1] - sum[list[j] + 1] > max)
                {
                    max = sum[list[k] - 1];
                    if (list[j] != -1)
                        max -= sum[list[j] + 1];
                    l1 = list[j] + 1;
                    l2 = list[k] - 1;
                }
            }
        }
        printf("Case %d:\n%d %d %d\n", i + 1, max, l1 + 1, l2 + 1);
        // }
    }
    return 0;
}