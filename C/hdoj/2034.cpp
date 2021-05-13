#include <stdio.h>
#include <algorithm>

int cmp(const void * p1, const void * p2) 
{
    return (*(int*)p1) - (*(int*)p2);
}

void test()
{
    for (int i = 0; i < 200;i++)
        printf("%d ", i);

}

int main()
{
    //test();
    int lis1[100], lis2[100], com[100], l1, l2, c;
    int n, m, tmp;
    scanf("%d %d", &n, &m);
    while (n != 0 || m != 0)
    {
        c = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &tmp);
            lis1[i] = tmp;
        }
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &tmp);
            lis2[i] = tmp;
        }
        for (int i = 0; i < n; i++)
        {
            int j;
            for (j = 0; j < m; j++)
            {
                if (lis1[i] == lis2[j])
                    break;
            }
            if (j >= m)
            {
                int k;
                for (k = 0; k < c; k++)
                {
                    if (lis1[i] == com[k])
                        break;
                }
                if (k >= c)
                {
                    com[k] = lis1[i];
                    c++;
                }
            }
        }
        if (c == 0)
        {
            printf("NULL");
        }
        else
        {
            qsort(com, c, sizeof(int),cmp);
            for (int i = 0; i < c; i++)
            {
                printf("%d ", com[i]);
            }
        }
        printf("\n");
        scanf("%d %d", &n, &m);
    }
    return 0;
}