#include <stdio.h>

int main()
{
    int t, n;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        double max = -1, tmp;
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &tmp);
            if (tmp > max)
            {
                max = tmp;
            }
        }
        printf("%.2f\n", max);
    }
    return 0;
}