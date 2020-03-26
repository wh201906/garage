#include <stdio.h>
#include <memory.h>
#include <string.h>

char list[1001][17];
int len = 0, count[1001];

int find(char *str);

int main()
{
    int n, label = -1, count[1001];
    char *maxp;
    int maxv = 0;
    scanf("%d", &n);
    while (n != 0)
    {
        len = 0;
        maxv = 0;
        char proc[17];
        memset(list, '\0', sizeof(list));
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; i++)
        {
            scanf("%s", proc);
            label = find(proc);
            if (label == -1)
            {
                strcpy(list[len], proc);
                label = len;
                len++;
            }
            count[label]++;
            if (count[label] > maxv)
            {
                maxv = count[label];
                maxp = list[label];
            }
        }
        printf("%s\n", maxp);
        scanf("%d", &n);
    }
}

int find(char *str)
{
    for (int i = 0; i < len; i++)
    {
        if (strcmp(str, list[i]) == 0)
            return i;
    }
    return -1;
}