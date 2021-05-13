#include <stdio.h>

int main()
{
    int n, tmp, a[25] = {0,1,4,7,6,5,6,3,6,9,0,1,6,3,6,5,6,7,4,9,0};
    int i, j, k;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        printf("%d\n", a[tmp % 20]);
    }
    return 0;
}