#include <stdio.h>

void rev(char *start, char *end)
{
    int n = end - start;
    char tmp;
    for (int i = 0; i <= n / 2; i++)
    {
        tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int n, j;
    char str[200], ch;
    scanf("%d", &n);
    getchar();
    while (1)
    {
        scanf("%s", str);
        for (j = 0; str[j] != '\n' && str[j] != '\0'; j++)
            ;
        rev(str, str + j - 1);
        printf("%s", str);
        ch = getchar();
        if (ch != EOF)
        {
            putchar(ch);
        }
        else
        {
            break;
        }
    }
    return 0;
}