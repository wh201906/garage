#include <stdio.h>

int main()
{
    //freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    while (n != -1)
    {
        long long tmp1 = 1, tmp2 = 1, tmp;
        if (n == 0)
        {
            tmp2 = 0;
        }
        else if (n >= 3)
        {
            for (int i = 3; i <= n; i++)
            {
                tmp = tmp1;
                tmp1 = tmp2;
                tmp2 = tmp + tmp1;
            }
        }

        printf("%lld\n", tmp2);
        scanf("%d", &n);
    }
    return 0;
}