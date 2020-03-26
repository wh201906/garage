#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n;i++)
    {
        char ch;
        int count=0;
        while((ch=getchar())!='\n' && ch!=EOF)
        {
            if(ch<0)
            {
                count++;
            }
        }
        count /= 2;
        printf("%d\n", count);
    }
    return 0;
}