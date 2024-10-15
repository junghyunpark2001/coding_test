#include <iostream>
#include <queue>
#include <climits>

using namespace std;
#define MAX 22



int n;
int board[MAX][MAX];
int vis[MAX][MAX];
int cur_x, cur_y, cur_level, cur_time;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int killed_num = 0;
bool updated;

void initialize(){
    cur_level = 2;
    cur_time = 0;
}



bool in_range(int x,int y){
    if(x>=0 && y>=0 && x<n && y<n && board[x][y]<=cur_level) return true;
    return false;
}
void bfs(){
    for(int i=0;i<n;i++) fill(vis[i],vis[i]+n,-1);
    queue<pair<int, int>> q;
    q.push({cur_x, cur_y});
    vis[cur_x][cur_y] = 0;
    while(!q.empty()){
        pair<int, int> cur = q.front();
        q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if(!in_range(nx,ny)) continue;
            if(vis[nx][ny]!=-1) continue;
            q.push({nx,ny});
            vis[nx][ny] = vis[cur.first][cur.second] + 1;
        }
    }
    return;
}
pair<int, int> kill() {
    int result = INT_MAX;
    pair<int, int> location = {-1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] > 0 && board[i][j] < cur_level) {
                if (vis[i][j] != -1 && vis[i][j] < result) {
                    result = vis[i][j];
                    location = {i, j};
                }
                else if (vis[i][j] != -1 && vis[i][j] == result) {
                    if (location.first == -1 || i < location.first || (i == location.first && j < location.second)) {
                        location = {i, j};
                    }
                }
            }
        }
    }
    return location;
}


void update(int x,int y){
    cur_x = x;
    cur_y = y;
    cur_time += vis[x][y];
    killed_num++;
    if(killed_num==cur_level){
        cur_level++;
        killed_num = 0;
    }

    board[x][y]=0;
}

void simulate(){
    while (true) {
        bfs();
        pair<int, int> location = kill();
        if (location.first == -1) break; 
        update(location.first, location.second);
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    initialize();

    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
            if(board[i][j]==9){board[i][j]=0;cur_x=i;cur_y=j;}
        }
    }

    simulate();
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<vis[i][j]<<" ";
    //     }
    //     cout<<'\n';
    // }
    // cout<<kill().first<<" "<<kill().second<<'\n';
    cout<<cur_time<<'\n';
}