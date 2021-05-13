// #include <stdio.h>

// int list[1000002];

// int main()
// {
//     int a, b, n;
//     scanf("%d %d %d", &a, &b, &n);
//     list[1] = 1;
//     list[2] = 1;
//     while (a != 0 || b != 0 || n != 0)
//     {
//         for (int i = 3; i <= n;i++)
//         {
//             list[i] = (a * list[i - 1] + b * list[i - 2]) % 7;
//         }
//         printf("%d\n",list[n]);
//         scanf("%d %d %d", &a, &b, &n);
//     }
// }

#include <stdio.h>

int main()
{
    int array[130] = {-1, 1, 1};
    int a, b, n;
    int label, i, j;
    bool brk;
    scanf("%d %d %d", &a, &b, &n);
    while (a != 0 || b != 0 || n != 0)
    {
        brk = false;
        label = 0;
        for (i = 3; i < 130; i++)
        {
            array[i] = (a * array[i - 1] + b * array[i - 2]) % 7;
            for (j = 2; j < i; j++)
            {
                if (array[i] == array[j] && array[i - 1] == array[j - 1])
                {
                    brk = true;
                    break;
                }
            }
            if (brk)
                break;
        }
        int t = i - j;
        printf("%d\n", array[((n - j) % t) + j]);
        scanf("%d %d %d", &a, &b, &n);
    }
    return 0;
}