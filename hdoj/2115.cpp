#include <stdio.h>
#include <algorithm>

typedef struct
{
    char name[100];
    int t;
    int rank;
} man;

bool cmp(man m1, man m2)
{
    if (m1.t < m2.t)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int n, tmp,count=1;
    man mans[15];
    scanf("%d", &n);
    while (n != 0)
    {
        getchar();
        for (int i = 0; i < n; i++)
        {
            scanf("%s %d:%d", mans[i].name, &tmp, &mans[i].t);
            mans[i].t += 60 * tmp;
        }
        std::sort(mans, mans + n, cmp);
        if(count>1)
        {
            printf("\n");
        }
        printf("Case #%d\n", count);
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && mans[i].t == mans[i - 1].t)
            {
                mans[i].rank = mans[i - 1].rank;
            }
            else
            {
                mans[i].rank = i + 1;
            }
            printf("%s %d\n", mans[i].name, mans[i].rank);
        }
        count++;
        scanf("%d", &n);
    }
}