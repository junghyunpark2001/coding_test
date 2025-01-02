#include <iostream>
#include <queue>
#include <vector>


using namespace std;

int n, m;
int cheese[105][105];
int boundary[105][105];

bool vis[105][105];

int dx[4] = {1,0,-1,0};
int dy[4] = {0, 1, 0, -1};

int bfs()
{
    int melt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++){
            vis[i][j] = 0;
        }
    }

    queue<pair<int, int>> q;
    vis[0][0] = 1;
    q.push({0, 0});
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        for (int dir = 0; dir < 4; dir++){
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if(nx<0 || nx>=n || ny<0 || ny>=m)
                continue;
            if(vis[nx][ny])
                continue;
            if(cheese[nx][ny]==1){
                melt++;
                cheese[nx][ny] = 0;
                vis[nx][ny] = 1;
            } else{
                vis[nx][ny] = 1;
                q.push({nx, ny});
            }

        }
    }

    return melt;
}

bool check(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if(cheese[i][j])
                return false;
        }
    }
    return true;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++){
            cin >> cheese[i][j];
        }
    }

    int cnt = 0;
    int num = 0;

    while (!check())
    {
        cnt++;
        num = bfs();
    }
    cout << cnt<<'\n'<<num<<'\n';
    return 0;
}