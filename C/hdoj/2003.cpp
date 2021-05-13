#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <stdio.h>

int main()
{
    double a;
    while (scanf("%lf", &a) != EOF)
    {
        printf("%.2f\n",fabs(a));
        //printf("%.2f\n", abs(a));
    }
}

//G++下只有fabs编译可以通过，C++(MSVC)下两者皆可通过
//因G++下会先取绝对值后取整