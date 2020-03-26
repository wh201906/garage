#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{

    int n;
    scanf("%d", &n);
    while (n != 0)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            int salary;
            scanf("%d", &salary);
            count += salary / 100;
            salary %= 100;
            count += salary / 50;
            salary %= 50;
            count += salary / 10;
            salary %= 10;
            count += salary / 5;
            salary %= 5;
            count += salary / 2;
            salary %= 2;
            count += salary;
        }
        printf("%d\n", count);
        scanf("%d", &n);
    }
    
}
 