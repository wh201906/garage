#include <stdio.h>

int main()
{
    int a, b,res;
    scanf("%d %d", &a, &b);
    while(a!=0 && b!=0)
    {
        res = 1;
        for (int i = 0; i < b;i++)
        {
            res *= a;
            res %= 1000;
        }
        printf("%d\n", res);
        scanf("%d %d", &a, &b);
    }
    return 0;
}