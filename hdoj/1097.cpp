#include <stdio.h>

int main()
{
    int a, b;
    int lis[5];
    while (scanf("%d %d", &a, &b) != EOF)
    {
        if (b == 0)
        {
            printf("1\n");
        }
        else if (a == 0)
        {
            printf("0\n");
        }
        else
        {
            a = a % 10;//先使得a的值变小，否则后面会爆int
            lis[1] = a;
            for (int i = 2; i < 5; i++)
            {
                lis[i] = (lis[i - 1] * a)%10;
            }
            lis[0] = lis[4];
            int res = b % 4;
            printf("%d\n", lis[res]);
        }
    }
    return 0;
}