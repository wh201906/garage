#include <stdio.h>

int main()
{
    // freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        // if (i != 0)
        // {
        //     printf("\n");
        // }
        int tmp, proc;
        scanf("%6d%5d", &tmp, &proc);
        printf("%d%d\n", 6, proc);
    }
    return 0;
}