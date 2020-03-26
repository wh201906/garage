#include <stdio.h>

int main()
{
    int n, a[1000], b[1000], res[1000], a_l = 0, b_l = 0, tmp;
    int *big, *small, big_l, small_l;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
        {
            printf("\n");
        }
        a_l = 0;
        b_l = 0;
        char ch;
        ch = getchar();
        while (ch != ' ')
        {
            a[a_l] = ch - '0';
            a_l++;
            ch = getchar();
        }
        ch = getchar();
        while (ch != '\n' && ch != EOF)
        {
            b[b_l] = ch - '0';
            b_l++;
            ch = getchar();
        }
        for (int i = 0; i * 2 < a_l; i++)
        {
            tmp = a[i];
            a[i] = a[a_l - 1 - i];
            a[a_l - 1 - i] = tmp;
        }
        for (int i = 0; i * 2 < b_l; i++)
        {
            tmp = b[i];
            b[i] = b[b_l - 1 - i];
            b[b_l - 1 - i] = tmp;
        }

        if (a_l < b_l)
        {
            big = b;
            small = a;
            big_l = b_l;
            small_l = a_l;
        }
        else
        {
            big = a;
            small = b;
            big_l = a_l;
            small_l = b_l;
        }

        *(big + big_l) = 0;
        for (int i = small_l; i <= big_l; i++)
        {
            *(small + i) = 0;
        }
        for (int i = 0; i <= big_l; i++)
        {
            res[i] = *(big + i);
        }

        for (int i = 0; i < big_l; i++)
        {
            res[i] += *(small + i);
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
        printf("Case %d:\n", i + 1);
        for (int i = a_l - 1; i >= 0; i--)
        {
            printf("%d", a[i]);
        }
        printf(" + ");
        for (int i = b_l - 1; i >= 0; i--)
        {
            printf("%d", b[i]);
        }
        printf(" = ");
        if (res[big_l] == 0)
        {
            big_l--;
        }
        for (int i = big_l; i >= 0; i--)
        {
            printf("%d", res[i]);
        }
        printf("\n");
    }
    return 0;
}