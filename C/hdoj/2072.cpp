#include <stdio.h>
#include <string.h>

char list[100000][1000], list_nodump[10000][1000];

int main()
{
    //char list[1000][50], list_nodump[1000][50];
    //freopen("in.txt", "r", stdin);
    char ch;
    int label = 0, word = 0, word_nodump = 0;
    ch = getchar();
    while (ch != '#')
    {
        memset(list, '\0', sizeof(list));
        memset(list_nodump, '\0', sizeof(list_nodump));
        word = 0, word_nodump = 0;
        while (ch != '#' && ch != '\n')
        {
            label = 0;
            while (ch != '#' && ch != '\n' && ch != ' ')
            {
                list[word][label] = ch;
                label++;
                ch = getchar();
            }
            if (label != 0)
            {
                list[word][label] = '\0';
                word++;
            }
            if (ch == '\n' || ch == '#')
            {
                break;
            }
            else if (ch == ' ')
            {
                ch = getchar();
            }
        }
        strcpy(list_nodump[0], list[0]);
        word_nodump = 1;
        int i, j;
        for (i = 0; i < word; i++)
        {
            for (j = 0; j < word_nodump; j++)
            {
                if (strcmp(list[i], list_nodump[j]) == 0)
                {
                    break;
                }
            }
            if (strcmp(list[i], list_nodump[j]) != 0)
            {
                strcpy(list_nodump[word_nodump], list[i]);
                word_nodump++;
            }
        }
        printf("%d\n", word);
        if (ch == '#')
        {
            break;
        }
        else if (ch == '\n')
        {
            ch = getchar();
        }
    }
    return 0;
}