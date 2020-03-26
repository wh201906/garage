#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        float max = -1.0, min = 101.0, sum = 0.0;
        int l;
        for (int i = 0; i < n; i++)
        {
            float tmp;
            scanf("%f", &tmp);
            sum += tmp;
            if (tmp > max)
            {
                max = tmp;
            }
            if (tmp < min)
            {
                min = tmp;
            }
        }
        sum -= max;
        sum -= min;
        printf("%.2f\n", sum / (n - 2));

    }
}