#include <stdio.h>
#include <math.h>
int main()
{
    int t;
    double x1, y1, x2, y2;
    double a, b, c, res;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        a = sqrt(x1 * x1 + y1 * y1);
        b = sqrt(x2 * x2 + y2 * y2);
        c = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        res = (a * a + b * b - c * c) / (2 * a * b);
        res = acos(res)/3.14159*180;
        printf("%.2f\n", res);
    }
    return 0;
}