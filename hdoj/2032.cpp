#include <stdio.h>

#define SIZE 30

int main()
{
    //freopen("in.txt", "r", stdin);
    int n, table[SIZE][SIZE];
    table[0][0] = table[1][0] = table[1][1] = 1;
    for (int i = 2; i < SIZE; i++)
    {
        table[i][0] = table[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            table[i][j] = table[i - 1][j - 1] + table[i - 1][j];
        }
    }
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d", table[i][0]);
            for (int j = 1; j <= i; j++)
            {
                printf(" %d", table[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}