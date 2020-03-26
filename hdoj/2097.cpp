#include <stdio.h>

int dev(int n,int d)
{
    int sum = 0;
    while(n>0)
    {
        sum += n % d;
        n /= d;
    }
    return sum;
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n!=0)
    {
        if(dev(n,10)==dev(n,16) && dev(n,10)==dev(n,12))
        {
            printf("%04d is a Sky Number.\n",n);
        }
        else
        {
            printf("%04d is not a Sky Number.\n",n);
        }
        scanf("%d", &n);
    }
    return 0;
}