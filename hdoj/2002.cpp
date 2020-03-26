#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415927
#include <stdio.h>

int main() 
{
    double r;
    while (scanf("%lf", &r) != EOF)
    {
        printf("%.3f\n", PI * r * r * r * 1.333333333333);
    }
}

//无论是double还是float输出都用%f