#include <stdio.h>
#include <algorithm>

int main()
{
    int n,lis[105];
    scanf("%d", &n);
    while(n!=0)
    {
        for (int i = 0; i < n;i++)
        {
            scanf("%d", &lis[i]);
        }
        std::sort(lis, lis + n);
        printf("%d\n", lis[n - 1]);
        scanf("%d", &n);
    }
    return 0;
}