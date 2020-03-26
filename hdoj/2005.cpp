#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

bool isRunNian(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}
int main()
{
    int y, m, d, res;
    while (scanf("%d/%d/%d", &y, &m, &d) != EOF)
    {
        if (m < 3)
        {
            res = 31 * (m - 1) + d;
        }
        else
        {
            if (isRunNian(y))
            {
                res = 60;
            }
            else
            {
                res = 59;
            }
            if (m == 3 || m == 5 || m == 7)
            {
                res += (m - 3) / 2 * 61 + d;
            }
            else if (m == 4 || m == 6)
            {
                res += 31 + (m - 4) / 2 * 61 + d;
            }
            else if (m == 8 || m == 10 || m == 12)
            {
                res += 153 + (m - 8) / 2 * 61 + d;
            }
            else if (m == 9 || m == 11)
            {
                res += 184 + (m - 9) / 2 * 61 + d;
            }
        }
        printf("%d\n", res);

    }
}