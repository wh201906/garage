#include <stdio.h>
#include <math.h>

int main()
{
    // freopen("in.txt", "r", stdin);
    char str[100];
    double sum = 0, liang, val;
    while (scanf("%s", str) != EOF)
    {
        scanf("%s", str);
        sscanf(str, "%lf", &liang);
        scanf("%s", str);
        sscanf(str, "%lf", &val);
        sum += liang * val;
        // sum += floor(liang * val * 10 + 0.5) / 10;
    }
    printf("%.1f\n", floor(sum * 10 + 0.5) / 10);
    return 0;
}