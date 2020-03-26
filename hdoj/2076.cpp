#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        double h, m, s, pin1, pin2, tmp;
        scanf("%lf %lf %lf", &h, &m, &s);
        if (h > 12)
            h -= 12;
        m += s / 60;
        h += m / 60;
        pin1 = h / 12 * 360;
        pin2 = m / 60 * 360;
        if (pin1 > pin2)
        {
            tmp = pin1;
            pin1 = pin2;
            pin2 = tmp;
        }
        pin2 -= pin1;
        if (pin2 > 180)
            pin2 = 360 - pin2;
        printf("%.0f\n", pin2 - 0.5);
    }
    return 0;
}