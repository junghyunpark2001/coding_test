#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define X first
#define Y second
#define z third
int board[202][202];
int vis[32][202][202];
int bx,by,kn;
int dx1[8] = {2,2,1,1,-1,-1,-2-2};
int dy1[8] = {-1,1,2,-2,2,-2,1,-1};
int dx2[4] = {1,0,-1,0};
int dy2[4] = {0,1,0,-1};
queue<tuple<int,int,int>> Q;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>kn>>by>>bx;
    for(int i=0;i<bx;i++)
        for(int j=0;j<by;j++)
            cin>>board[i][j];
    Q.push({0,0,0});
    vis[0][0][0] = 1;
    
    while(!Q.empty()){
        int vk,vx,vy;
        tuple<int,int,int> cur = Q.front(); Q.pop();
        if(vk<kn){
            for(int dir=0;dir<8;dir++){
                int nx = vx + dx2[dir];
                int ny = vy + dy2[dir];
                if(nx<0||nx>=bx||ny<0||ny>=by) continue;
                if(vis[vk+1][nx][ny]||board[nx][ny]) continue;
                vis[vk+1][nx][ny] = vis[vk][vx][vy]+1;
                Q.push({vk+1,nx,ny});
            }
        }
        for (int i = 0; i < 4; i++) {
            int nx = vx + dx1[i], ny = vy + dy1[i];
            if (nx < 0 || ny < 0 || bx <= nx || by <= ny) continue;
            if (board[nx][ny]) continue;
            if (vis[vk][nx][ny]) continue;
            vis[vk][nx][ny] = vis[vk][vx][vy] + 1;
            Q.push({ vk, nx, ny });
        }
    }
    int ans = 0x7f7f7f7f;
    for (int i = 0; i < kn + 1; i++)
        if(vis[i][bx - 1][by - 1]) ans = min(ans, vis[i][bx - 1][by - 1]);
    if (ans != 0x7f7f7f7f) cout << ans - 1;
    else cout << -1;
}