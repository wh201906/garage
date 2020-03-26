#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    for (int k = 0; k < n; k++)
    {
        char ch;
        int a = 0, e = 0, i = 0, o = 0, u = 0;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            if (ch == 'A' || ch == 'a')
            {
                a++;
            }
            else if (ch == 'E' || ch == 'e')
            {
                e++;
            }
            else if (ch == 'I' || ch == 'i')
            {
                i++;
            }
            else if (ch == 'O' || ch == 'o')
            {
                o++;
            }
            else if (ch == 'U' || ch == 'u')
            {
                u++;
            }
        }
        if(k==0)
        {
            printf("a:%d\ne:%d\ni:%d\no:%d\nu:%d\n", a, e, i, o, u);
        }
        else
        {
            printf("\na:%d\ne:%d\ni:%d\no:%d\nu:%d\n", a, e, i, o, u);
        }
    }
    return 0;
}