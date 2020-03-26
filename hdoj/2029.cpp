#include <stdio.h>

int main()
{
    int n, c = 0;
    char list[100][100];
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++)
    {
        c = 0;
        char ch;
        ch = getchar();
        int j;
        while (ch != '\n' && ch != EOF)
        {
            list[i][c] = ch;
            c++;
            ch = getchar();
        }
        c--;
        for (j = 0; j < (c / 2); j++)
        {
            if (list[i][j] != list[i][c - j])
            {
                printf("no\n");
                break;
            }
        }
        if (j >= (c / 2))
        {
            printf("yes\n");
        }
    }
    return 0;
}