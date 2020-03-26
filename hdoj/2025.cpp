#include <stdio.h>

int main()
{
    //freopen("in.txt", "r", stdin);
    char ch = 1, list[100][100], max[100];
    int row = 0, label = 0;
    for (int i = 0; i < 100; i++)
    {
        max[i] = -1;
    }
    ch = getchar();
    while (ch != EOF)
    {
        label = 0;
        while (ch != '\n' && ch != EOF)
        {
            list[row][label] = ch;
            label++;
            if (ch > max[row])
            {
                max[row] = ch;
            }
            ch = getchar();
        }
        list[row][label] = '\0';
        row++;
        ch = getchar();
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; list[i][j] != '\0'; j++)
        {
            putchar(list[i][j]);
            if (list[i][j] == max[i])
            {
                printf("(max)");
            }
        }
        printf("\n");
    }
    return 0;
}
