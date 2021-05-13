#include <stdio.h>

int main()
{
    long long a,b;
    while(scanf("%lld %lld",&a,&b)!=EOF)
    {
        if((a+b)!=0 && (a+b)%86==0)
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
    return 0;
}