#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cmath>

int main()
{
    double x1, y1, x2, y2;
    while (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != EOF)
    {
        printf("%.2f\n", sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
    }
}