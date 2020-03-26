#include <stdio.h>

int main()
{
    int n;
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        double a, b, c;
        scanf("%lf %lf %lf", &a, &b, &c);
        if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a)
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
        }
    }
    return 0;
}