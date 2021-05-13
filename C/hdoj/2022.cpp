#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main()
{
    int m, n;
    while (scanf("%d %d", &m, &n) != EOF)
    {
        int s = 0, x, y;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int mark;
                scanf("%d", &mark);
                if (abs(mark) > abs(s))
                {
                    s = mark;
                    x = i;
                    y = j;
                }
            }
        }
        x++;
        y++;
        printf("%d %d %d\n", x, y, s);
    }

}
