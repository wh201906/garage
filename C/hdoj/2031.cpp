#include <stdio.h>

int main()
{
    freopen("in.txt", "r", stdin);
    int n, r, label, tmp;
    int list[35];
    bool below0;
    while (scanf("%d %d", &n, &r) != EOF)
    {
        below0 = false;
        label = 0;
        if (n == 0)
        {
            printf("0");
        }
        else if (n < 0)
        {
            below0 = true;
            n = -n;
        }
        while (n > 0)
        {
            tmp = n % r;
            list[label] = tmp;
            label++;
            n /= r;
        }
        if (below0)
        {
            printf("-");
        }
        for (int i = label - 1; i >= 0; i--)
        {
            if (list[i] >= 0 && list[i] <= 9)
            {
                printf("%d", list[i]);
            }
            else
            {
                printf("%c", list[i] - 10 + 'A');
            }
        }
        printf("\n");
    }

    return 0;
}