#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    while(a!=0 && b!=0)
    {
        a %= b;
        a *= 100;
        bool isfirst = true;
        for (int c = 0; c < 100;c++)
        {
            if((a+c)%b==0)
            {
                if(isfirst)
                {
                    printf("%02d", c);
                    isfirst = false;
                }
                else
                {
                    printf(" %02d", c);
                }
                
            }
        }
        printf("\n");
        scanf("%d %d", &a, &b);
    }
}