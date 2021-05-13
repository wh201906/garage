#include <stdio.h>

int main()
{
    int n;
    bool f = true;
    while (scanf("%d", &n) != EOF)
    {
        if(f)
        {
            f = false;
        }
        else
        {
            printf("\n");
        }
        
        int sum = 0, a;
        while (n != 0)
        {
            a = n % 10;
            n = n / 10;
            if (a % 2 == 0)
            {
                sum += a;
            }
        }
        printf("%d\n", sum);
    }
}