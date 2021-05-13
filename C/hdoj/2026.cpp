#include <stdio.h>

int main()
{
    //freopen("in.txt", "r", stdin);
    char ch;
    bool willHandle = false;
    ch = getchar();
    putchar(ch - 'a' + 'A');
    ch = getchar();
    while (ch != EOF)
    {

        if (ch == ' ' || ch == '\n')
        {
            willHandle = true;
            putchar(ch);
        }
        else if (willHandle == true)
        {
            willHandle = false;
            putchar(ch - 'a' + 'A');
        }
        else
        {
            putchar(ch);
        }
        ch = getchar();
    }
    return 0;
}