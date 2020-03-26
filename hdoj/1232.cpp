#include <stdio.h>

const int NUM = 10000;

int prev[NUM];

int find(int node)
{
    int root = node;
    while (prev[root] != root)
    {
        root = prev[root];
    }
    int curr = node,tmp;
    while(curr!=root)
    {
        tmp = prev[curr];
        prev[tmp] = root;
        curr = tmp;
    }
    return curr;
}

bool add(int node1, int node2)
{
    int root1 = find(node1), root2 = find(node2);
    if (root1 != root2)
    {
        prev[node2] = root1;
        return true;
    }
    else
    {
        return false;
    }
}

void init(int num)
{
    for (int i = 0; i < num; i++)
    {
        prev[i] = i;
    }
}

int main()
{
    int n, m, rlist[NUM],rnum, tmp1, tmp2;
    scanf("%d %d", &n, &m);
    while (n != 0)
    {
        init(n);
        rnum = 0;
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d", &tmp1, &tmp2);
            add(tmp1, tmp2);
        }
        for (int i = 0; i < n;i++)
        {
            tmp1 = find(i);
            int j;
            for (j = 0; j < rnum;j++)
            {
                if(tmp1==rlist[j])
                {
                    break;
                }
            }
            if(j>=rnum)
            {
                rlist[j]=
            }
        }
            scanf("%d %d", &n, &m);
    }
}