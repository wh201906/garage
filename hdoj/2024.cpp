#include <stdio.h>
#include <string.h>

bool isvalid(char ch);
bool iskey(char *ch);
char keylist[37][25] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "inline", "restrict", "_Bool", "_Complex", "_Imaginary"};

int main()
{
    char tmp;
    //freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    tmp = getchar();
    for (int i = 0; i < n; i++)
    {
        char ch, list[52];
        int l = 0;
        ch = getchar();
        list[l] = ch;
        l++;
        if ((!isvalid(ch)) || (ch >= '0' && ch <= '9'))
        {
            printf("no\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            if (!isvalid(ch))
            {
                break;
            }
            list[l] = ch;
            l++;
        }
        if (isvalid(ch) || ch == '\n' || ch == EOF)
        {
            list[l] = '\0';
            if (!iskey(list))
            {
                printf("yes\n");
            }
            else
            {
                printf("no\n");
            }
        }
        else
        {
            printf("no\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
        }
    }
    return 0;
}

bool isvalid(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool iskey(char *ch)
{
    for (int i = 0; i < 37; i++)
    {
        if (strcmp(keylist[i], ch) == 0)
        {
            return true;
        }
    }
    return false;
}