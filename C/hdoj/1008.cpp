#include <stdio.h>

int main()
{
    int n,array[105];
    int sum,curr=0,tmp,delta;
    scanf("%d", &n);
    while(n!=0)
    {
        sum = 0;
        curr = 0;
        for (int i = 0; i < n;i++)
        {
            scanf("%d", &tmp);
            delta = tmp - curr;
            curr = tmp;
            if(delta>0)
            {
                sum += 6 * delta;
            }
            else if(delta<0)
            {
                sum += (-4) * delta;
            }
            sum += 5;
        }
        printf("%d\n", sum);
        scanf("%d", &n);
    }
    return 0;
}