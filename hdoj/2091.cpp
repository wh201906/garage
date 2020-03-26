#include <stdio.h>

int main()
{
    char a;
    int n;
    bool isfirst = true;
    scanf("%c", &a);
    while (a != '@')
    {
        if (isfirst)
            isfirst = false;
        else
            printf("\n");
        scanf("%d", &n);
        getchar();
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n - i; j++)
            {
                printf(" ");
            }
            printf("%c", a);
            if (i != 1)
            {
                for (int j = 3; j < 2 * i; j++)
                {
                    printf(" ");
                }
                printf("%c", a);
            }
            printf("\n");
        }
        for (int i = 1; i < 2 * n; i++)
        {
            printf("%c", a);
        }
        printf("\n");
        scanf("%c", &a);
    }
    return 0;
}