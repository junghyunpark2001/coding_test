#include <iostream>
#include <queue>
#define X first 
#define Y second

using namespace std;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int n,m;
string board[102];
int vis[102][102];
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;

    for(int j=0;j<n;j++)
        cin>>board[j];
    queue<pair<int,int>> q;
    q.push({0,0});
    vis[0][0] = 1;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(vis[nx][ny]>0||board[nx][ny]=='0') continue;
            vis[nx][ny] = vis[cur.X][cur.Y] + 1;
            q.push({nx,ny});
        }
    }
    cout<<vis[n-1][m-1];

}