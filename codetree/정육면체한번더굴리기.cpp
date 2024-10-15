#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

int n,m;
int board[22][22];
// dice[1][2] = floor
int dice[3][4] = {{0,4,0,0},{5,6,2,1},{0,3,0,0}};
int tmp[3][4];
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int result = 0;

int cur_x = 0;
int cur_y = 0;
int cur_dir = 1;

void print_dice(){
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            cout<<dice[i][j];
        }
        cout<<'\n';
    } 
}

void roll(int dir){
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            tmp[i][j] = dice[i][j];
        }
    }
    if(dir==0){
        dice[1][0] = tmp[1][1];
        dice[1][1] = tmp[1][2];
        dice[1][2] = tmp[1][3];
        dice[1][3] = tmp[1][0];
    }
    else if(dir==3){
        dice[0][1] = tmp[1][3];
        dice[1][1] = tmp[0][1];
        dice[2][1] = tmp[1][1];
        dice[1][3] = tmp[2][1];
    }
    else if(dir==2){
        dice[1][0] = tmp[1][3];
        dice[1][1] = tmp[1][0];
        dice[1][2] = tmp[1][1];
        dice[1][3] = tmp[1][2];
    }
    else if(dir==1){
        dice[0][1] = tmp[1][1];
        dice[1][1] = tmp[2][1];
        dice[2][1] = tmp[1][3];
        dice[1][3] = tmp[0][1];
    }
    // cout<<'\n';
    // print_dice();

}
int vis[22][22];
void bfs(int x, int y){
    int dice_floor = board[x][y];
    for(int i=0;i<n;i++) fill(vis[i],vis[i]+n,0);
    vis[x][y] = 1;
    result+=dice_floor;
    queue<pair<int,int>> q;
    q.push({x,y});
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if(nx<0||nx>=n||ny<0||ny>=n) continue;
            if(vis[nx][ny]||board[nx][ny]!=dice_floor) continue;
            q.push({nx,ny});
            vis[nx][ny] = 1;
            result+=dice_floor;
        }
    }
}

void simulate(){
    for(int i=0;i<m;i++){
        cur_x+=dx[cur_dir];
        cur_y+=dy[cur_dir];
        bool oob = 0;
        if(cur_x<0||cur_x>=n||cur_y<0||cur_y>=n){
            cur_dir = (cur_dir+2)%4;
            cur_x += 2*dx[cur_dir];
            cur_y += 2*dy[cur_dir];
            oob=1;
        }
        roll(cur_dir);
        // cout<<cur_dir;
        // cout<<"\ncur floor "<<dice[1][1]<<'\n';
        // cout<<"cur x, y"<<cur_x<<" "<<cur_y<<'\n';
        bfs(cur_x, cur_y);
        if(dice[1][1]==board[cur_x][cur_y]){
            continue;
        }
        else if(dice[1][1]>board[cur_x][cur_y]) cur_dir=(cur_dir+3)%4;
        else if(dice[1][1]<board[cur_x][cur_y]) cur_dir = (cur_dir+1)%4;
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>board[i][j];
    simulate();
    //roll(2);

    cout<<result;
}