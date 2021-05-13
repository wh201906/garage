#include <stdio.h>
#include <queue>
#include <memory.h>

using namespace std;

struct state
{
    int x, y, time,total;
    bool operator<(const state s) const { return total > s.total; }
};

int main()
{
    int t, n, m;

    scanf("%d", &t);
    int vec[4][2] = { {0, -1},{0, 1}, {-1, 0}, {1, 0}};
    for (int i = 0; i < t; i++)
    {
        int map[15][15];
        int visited[15][15];
        memset(visited, -1, sizeof(visited));
        memset(map, -1, sizeof(map));
        priority_queue<state> que;
        state root,curr;
        scanf("%d %d", &n, &m);
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++)
            {
                scanf("%d", &map[j][k]);
                if (map[j][k] == 2)
                {
                    root.x = j;
                    root.y = k;
                }
            }
        root.time = 0;
        root.total = 0;
        que.push(root);
        while (!que.empty())
        {
            curr = que.top();
            que.pop();
            if (curr.x >= 0 && curr.x < n && curr.y >= 0 && curr.y < m && (visited[curr.x][curr.y] > curr.time || visited[curr.x][curr.y] == -1) && map[curr.x][curr.y] != 0 &&curr.time<6)
            {
                visited[curr.x][curr.y] = curr.time;
                // printf("----%d %d %d %d %d----\n",curr.x,curr.y,curr.time,curr.total,map[curr.x][curr.y]);
                if(map[curr.x][curr.y]==4)
                    curr.time = 0;
                else if(map[curr.x][curr.y]==3)
                    break;
                for (int j = 0; j < 4;j++)
                {
                    state next = curr;
                    next.x += vec[j][0];
                    next.y += vec[j][1];
                    next.time++;
                    next.total++;
                    que.push(next);
                }
            }
        }
        if(map[curr.x][curr.y]==3)
            printf("%d\n", curr.total);
        else
            printf("%d\n", -1); 
    }
    return 0;
}