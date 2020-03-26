#include <stdio.h>

int main()
{
    int n, m, list[100][100], count = -1;
    double ave[100];
    //freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF)
    {
        // if (count != -1)
        // {
        //     printf("\n\n");
        // }
        count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int a = 0;
                scanf("%d", &a);
                list[i][j] = a;
            }
        }
        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < m; j++)
            {
                sum += list[i][j];
            }
            if (i == 0)
            {
                printf("%.2f", sum / m);
            }
            else
            {
                printf(" %.2f", sum / m);
            }
        }
        printf("\n");
        for (int i = 0; i < m; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < n; j++)
            {
                sum += list[j][i];
            }
            ave[i] = sum / n;
            if (i == 0)
            {
                printf("%.2f", ave[i]);
            }
            else
            {
                printf(" %.2f", ave[i]);
            }
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            int j;
            for (j = 0; j < m; j++)
            {
                if (list[i][j] < ave[j])
                {
                    break;
                }
            }
            if (j >= m)
            {
                count++;
            }
        }
        printf("%d\n\n", count);
    }

    return 0;
}