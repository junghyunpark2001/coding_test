#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

int n,m;
int board[10][10];
int board2[10][10];
int vis[10][10];
int result = 0;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
void bfs(vector<pair<int,int>> walls){
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            board2[i][j] = board[i][j];
    for(int i=0;i<n;i++) fill(vis[i],vis[i]+m,0);
    for(int i=0;i<3;i++){
        int x,y;
        x = walls[i].first; 
        y = walls[i].second;
        if(board2[x][y]==2 || board2[x][y]==1) return;
        board2[x][y] = 1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board2[i][j]==2){
                queue<pair<int,int>> q;
                q.push({i,j});
                vis[i][j] = 1;
                while(!q.empty()){
                    auto cur = q.front();
                    q.pop();
                    for(int dir=0;dir<4;dir++){
                        int nx = cur.first + dx[dir];
                        int ny = cur.second + dy[dir];
                        if(nx<0||nx>=n||ny<0||ny>=m) continue;
                        if(board2[nx][ny]==1||vis[nx][ny]) continue;
                        board2[nx][ny] = 2;
                        q.push({nx,ny});
                        vis[nx][ny] = 1;
                    }
                }
            }
        }
    }
    int tmp = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(board2[i][j]==0) tmp++;
    result = max(tmp,result);
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout<<board2[i][j]<<" ";
    //     }
    //     cout<<'\n';
    // }
    // cout<<'\n';
}

void simulate() {
    vector<bool> v(n * m, 0); // 모든 값을 0으로 초기화
    fill(v.end()-3, v.end(), 1); // 처음 3개 값을 1로 설정
    
    do {
        vector<pair<int,int>> walls;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == 1) walls.push_back({i/m,i%m});
            
        }
        
        bfs(walls);
    } while (next_permutation(v.begin(), v.end()));

}



int main(void){
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>board[i][j];
    
    simulate();

    cout<<result;
}