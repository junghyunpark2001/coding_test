#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#define X first
#define Y second

using namespace std;

int n,m;
int board1[52][52];
int board2[52][52];
int vis[52][52];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
vector<pair<int,int>> virus;
int check(vector<pair<int,int>>& selected_virus){
    for(int i=0;i<n;i++) fill(vis[i],vis[i]+n,-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // 활성 바이러스 -1
            // 비활성 바이러스 -2
            // 벽 -5
            if(board1[i][j]==1) board2[i][j] = -5;
            if(board1[i][j]==2) board2[i][j] = -2;
            if(board1[i][j]==0) board2[i][j] = 0;
        }
    }
    queue<pair<int,int>> q;
    for(int i=0;i<selected_virus.size();i++) {
        board2[selected_virus[i].X][selected_virus[i].Y] = -1;
        q.push({selected_virus[i].X,selected_virus[i].Y});
        vis[selected_virus[i].X][selected_virus[i].Y] = 0;
    }
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.X+dx[dir];
            int ny = cur.Y+dy[dir];
            if(nx<0||nx>=n||ny<0||ny>=n) continue;
            if(board2[nx][ny]==-5||vis[nx][ny]!=-1) continue;
            // if(board1[nx][ny]==-2){
            //     q.push({nx,ny}); 
            // }
            q.push({nx,ny}); 
            
            vis[nx][ny] = vis[cur.X][cur.Y] + 1;
        }
    }

    int result = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board2[i][j]==0&&vis[i][j]==-1) return -1;
            if(board2[i][j]!=-2) result = max(result,vis[i][j]);
        }
    }
    return result;
}



int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board1[i][j];
            if(board1[i][j]==2) virus.push_back({i,j});
        }
    }
    int n = virus.size();
    int r = m;
    vector<bool> select(n);
    int result = 0x7fffffff;
    fill(select.end() - r, select.end(), true);
    do {
        // Print the current combination
        vector<pair<int,int>> selected_virus;
        for (int i = 0; i < n; ++i) {
            if (select[i]) {
                selected_virus.push_back({virus[i].X,virus[i].Y});
            }
        }
        if(check(selected_virus)!=-1) result = min(check(selected_virus),result);

    } while (next_permutation(select.begin(), select.end()));
    // vector<pair<int,int>> selected;
    // selected.push_back({0,0});
    // selected.push_back({1,5});
    // selected.push_back({4,3});
    // cout<<check(selected);
    if(result==0x7fffffff) cout<<-1;
    else cout<<result;
}   