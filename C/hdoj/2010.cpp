#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int min = 100, max = 999;
    
    while (scanf("%d %d",&min,&max) != EOF)
    {
        int n=0;
        bool a[4] = { false };
        int b[4] = { 0 };
        if ((153 >= min) && (153 <= max))
        {
            a[0] = true;
            n++;
        }   
        if ((370 >= min) && (370 <= max))
        {
            a[1] = true;
            n++;
        }
        if ((371 >= min) && (371 <= max))
        {
            a[2] = true;
            n++;
        }
        if ((407 >= min) && (407 <= max))
        {
            a[3] = true;
            n++;
        }
        if (n == 0)
        {
            printf("no");
        }
        else
        {
            int j = 0;
            if (a[0] == true)
            {
                b[j] = 153;
                j++;
            }
            if (a[1] == true)
            {
                b[j] = 370;
                j++;
            }
            if (a[2] == true)
            {
                b[j] = 371;
                j++;
            }
            if (a[3] == true)
            {
                b[j] = 407;
                j++;
            }
            printf("%d", b[0]);
            for (int i = 1; i < n; i++)
            {
                printf(" %d", b[i]);
            }
        }  
        printf("\n");
    }
}

// #include <iostream>
// using namespace std;

//int main()
//{
//    for (int i = 1; i < 10; i++)
//    {
//        for (int j = 0; j < 10; j++)
//        {
//            for (int k = 0; k < 10; k++)
//            {
//
//                if ((i * i * i + j * j * j + k * k * k) == i * 100 + j * 10 + k)
//                {
//                    cout << i * 100 + j * 10 + k<<endl;
//                }
//            }
//        }
//    }
//}
