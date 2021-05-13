#include <stdio.h>
#include <algorithm>

struct stu
{
    int num;
    double s;
};

bool cmp(stu *p1, stu *p2)
{
    if (p1->s > p2->s)
    {
        return true;
    }
    else
    {
        return false;
    }
}

stu list[1001];
stu *ptr[1001];
int lab;

int main()
{
    freopen("in.txt", "r", stdin);
    int tar;
    while (scanf("%d", &tar) != EOF)
    {
        lab = 0;
        int num, s,tmp=0;
        scanf("%d %d", &num, &s);
        while (num != 0)
        {
            list[lab].num = num;
            list[lab].s = s;
            ptr[lab] = &list[lab];
            lab++;
            scanf("%d %d", &num, &s);
        }
        std::sort(ptr, ptr + lab, cmp);
        for (int i = 0; i < lab; i++)
        {
            if (i > 0 && ptr[i]->s < ptr[i - 1]->s)
            {
                tmp = i;
            }
            if(ptr[i]->num==tar)
            {
                printf("%d\n", tmp+1);
                break;
            }
        }
    }
    return 0;
}