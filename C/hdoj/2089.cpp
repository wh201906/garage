#include <stdio.h>

int main()
{
    int a[6], n, m, sum;
    scanf("%d %d", &n, &m);
    while (n != 0 && m != 0)
    {
        sum = m - n + 1;
        if (n == 1000000)
            n = 999999;
        if (m == 1000000)
            m = 999999;
        for (int i = n; i <= m; i++)
        {
            int tmp = i, j;
            for (j = 5; j >= 0; j--)
            {
                a[j] = tmp % 10;
                if (a[j] == 4)
                {
                    break;
                }
                tmp /= 10;
            }
            if (a[j] == 4)
            {
                sum--;
                continue;
            }
            for (j = 0; j < 5; j++)
            {
                if (a[j] == 6 && a[j + 1] == 2)
                {
                    break;
                }
            }
            if (a[j] == 6 && a[j + 1] == 2)
            {
                sum--;
                continue;
            }
        }
        printf("%d\n", sum);
        scanf("%d %d", &n, &m);
    }

    return 0;
}