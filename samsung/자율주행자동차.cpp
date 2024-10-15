#include <iostream>

using namespace std;

int n, m;
int cur_x, cur_y, cur_dir;
int grid[52][52];
bool visited[52][52];

bool can_go(int x, int y) {
    return (!grid[x][y] && !visited[x][y]);
}

bool simulate(){
    visited[cur_x][cur_y] = true;

    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};

    for(int i=0;i<4;i++){
        int dir = (cur_dir -1 + 4) % 4;
        int nx = cur_x + dx[dir];
        int ny = cur_y + dy[dir];

        if(can_go(nx,ny)){
            cur_x = nx;
            cur_y = ny;
            cur_dir = dir;
            return true;
        }
        else cur_dir = dir;
    }

    int bx = cur_x - dx[cur_dir];
    int by = cur_y - dy[cur_dir];

    if(!grid[bx][by]){
        cur_x = bx;
        cur_y = by;
        return true;
    }
    else return false;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    cin>>cur_x>>cur_y>>cur_dir;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>grid[i][j];
    
    while(true){
        bool moved = simulate();
        if(!moved) break;
    }

    int ans = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(visited[i][j]) ans++;
    
    cout<<ans;
}