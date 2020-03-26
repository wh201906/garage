#include <stdio.h>
#include <math.h>

int main()
{
    freopen("in.txt", "r", stdin);
    char ch = 1, list[1000];
    int i, n;
    while (ch != EOF)
    {
        bool isEqual = true;
        for (i = 0; (ch = getchar()) != ' '; i++)
        {
            list[i] = ch;
        }
        list[i] = '\0';
        n = i;
        for (i = 0; i <= n && (ch = getchar()) != '\n' && ch != EOF; i++)
        {
            if (ch != list[i])
            {
                while(ch!='\n'&&ch!=EOF)
                {
                    ch = getchar();
                }
                printf("NO\n");
                isEqual = false;
                break;
            }
        }
        if(isEqual)
        {
            printf("YES\n");
        }
    }
    return 0;
}