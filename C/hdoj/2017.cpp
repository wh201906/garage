#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    freopen("in.txt", "r", stdin);
    int n,count;
    char a;
    scanf("%d", &n);
    getchar();//跳过第一行的\n
    for (int i = 0; i < n; i++)
    {

        count = 0;
        a = getchar();
        while (a != '\n')
        {
            if (a > 47 && a < 58)
            {
                count++;
            }
            a = getchar();
        }
        printf("%d\n", count);
    }
}