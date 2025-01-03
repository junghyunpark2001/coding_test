#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n,m;
int board[305][305];
int tmp[305][305];
int vis[305][305];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void melt()
{
    for (int i = 0; i < n; i++)
        fill(tmp[i], tmp[i] + m, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] > 0)
            {
                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                        continue;
                    if(board[nx][ny]==0)
                        tmp[i][j]++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            board[i][j] -= tmp[i][j];
            if(board[i][j]<0)
                board[i][j] = 0;
        }
    }
}

int check(){
    for (int i = 0; i < n; i++)
        fill(vis[i], vis[i] + m, 0);

    int num = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++){
            if(!board[i][j] || vis[i][j])
                continue;
            num++;
            queue<pair<int, int>> q;
            q.push({i, j});
            vis[i][j] = 1;
            while(!q.empty()){
                auto cur = q.front();
                q.pop();
                for (int dir = 0; dir < 4; dir++){
                    int nx = cur.first + dx[dir];
                    int ny = cur.second + dy[dir];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                        continue;
                    if(!board[nx][ny]||vis[nx][ny])
                        continue;
                    q.push({nx, ny});
                    vis[nx][ny] = 1;

                }
            }
        }
    }
    return num;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> board[i][j];
        }
    }

    int result = 0;
    while (true)
    {
        melt();
        result++;
        int num = check();
        if(num==1)
            continue;
        else if (num == 0)
        {
            cout << 0 << '\n';
            return 0;
        }
        else{
            cout << result << '\n';
            return 0;
        }
    }
}