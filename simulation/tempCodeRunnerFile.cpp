#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define X first
#define Y second
int board[202][202];
int vis[202][202];
int k,w,h;
int dx1[8] = {2,2,1,1,-1,-1,-2-2};
int dy1[8] = {-1,1,2,-2,2,-2,1,-1};
int dx2[4] = {1,0,-1,0};
int dy2[4] = {0,1,0,-1};
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>k;
    cin>>w>>h;
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            cin>>board[i][j];
    
    int result = 0;
    queue<pair<int,int>> q;
    vis[0][0] = 1;
    q.push({0,0});
    while(!q.empty()){
    
        pair<int,int> cur = q.front(); q.pop();
        if(k>0){
            for(int dir=0;dir<8;dir++){
                int nx = cur.X + dx1[dir];
                int ny = cur.Y + dy1[dir];
                if(nx<0||nx>=h||ny<0||ny>=w) continue;
                if(vis[nx][ny]==1||board[nx][ny]==1) continue;
                vis[nx][ny] = 1;
                q.push({nx,ny});
            }
        }
        else{
            for(int dir=0;dir<4;dir++){
                int nx = cur.X + dx2[dir];
                int ny = cur.Y + dy2[dir];
                if(nx<0||nx>=h||ny<0||ny>=w) continue;
                if(vis[nx][ny]!=0||board[nx][ny]==1) continue;
                vis[nx][ny] = vis[cur.X][cur.Y]+1;
                q.push({nx,ny});
            }
        }
        k--;

    }
    if(vis[h-1][w-1]==0)cout<<-1;
    else cout<<vis[h-1][w-1];

}