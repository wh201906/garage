#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int n, sig[3];
    scanf("%d", &n);
    while (n != 0)
    {
        sig[0] = sig[1] = sig[2] = 0;
        for (int i = 0; i < n; i++)
        {
            double a;
            scanf("%lf", &a);
            if (a < 0)
            {
                sig[0]++;
            }
            else if (a > 0)
            {
                sig[2]++;
            }
            else
            {
                sig[1]++;
            }
        }
        printf("%d %d %d\n", sig[0], sig[1], sig[2]);
        scanf("%d", &n);
    }
}