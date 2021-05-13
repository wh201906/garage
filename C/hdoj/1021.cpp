#include <stdio.h>

#include <stdio.h>

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        if ((n + 2) % 4 == 0)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}