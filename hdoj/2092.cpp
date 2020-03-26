#include <stdio.h>
#include <math.h>

int main()
{
    int n, m;
    double x, y;
    scanf("%d %d", &n, &m);
    while (n != 0 || m != 0)
    {
        if (n * n - 4 * m < 0)
        {
            printf("No\n");
        }
        else
        {
            x = sqrt(n * n - 4 * m);
            y = ((-n) + x) / -2;
            if (fabs(y - (int)y) > 0.0000001)
            {
                printf("No\n");
            }
            else
            {
                y = ((-n) - x) / -2;
                if (fabs(y - (int)y) > 0.0000001)
                {
                    printf("No\n");
                }
                else
                {
                    printf("Yes\n");
                }
            }
        }

        scanf("%d %d", &n, &m);
    }
}