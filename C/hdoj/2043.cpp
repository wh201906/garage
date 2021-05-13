#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    freopen("in.txt", "r", stdin);
    int m;
    scanf("%d", &m);
    getchar();
    for (int i = 0; i < m; i++)
    {
        int typ[4] = {0, 0, 0, 0}, len, count = 0;
        char str[52];
        fgets(str, 51, stdin);
        len = strlen(str);
        if(str[len-1]='\n')
            len--;
        if (len < 8 || len > 16)
        {
            printf("NO\n");
            continue;
        }
        for (int j = 0; j < len; j++)
        {
            if (isupper(str[j]))
                typ[0]++;
            else if (islower(str[j]))
                typ[1]++;
            else if (isdigit(str[j]))
                typ[2]++;
            else //if (str[j] == '~' || str[j] == '!' || str[j] == '@' || str[j] == '#' || str[j] == '$' || str[j] == '%' || str[j] == '^')
                typ[3]++;
        }
        for (int j = 0; j < 4; j++)
        {
            if (typ[j] != 0)
            {
                count++;
            }
        }
        if (count < 3)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}