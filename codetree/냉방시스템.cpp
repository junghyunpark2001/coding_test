#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

#define X first
#define Y second

int n,m,k;
int grid[42][22];
int coolness[22][22];
int temp[22][22];

int dx[4] = {-1,0,0,1};
int dy[4] = {0,-1,1,0};

bool block[22][22][4];

bool visited[22][22];

int elapsed_time;

bool inRange(int x,int y){
    return 0<=x && x<n && 0<=y && y<n;
}

int revDir(int x_diff, int y_diff){
    for(int i=0;i<4;i++)
        if(dx[i]==x_diff && dy[i] == y_diff)
            return i;
    return -1;
}

void spread(int x, int y, int move_dir, int power){
    if(power == 0) return;

    visited[x][y] = 1;
    coolness[x][y] += power;

    // case 1. 직진
    int nx = x + dx[move_dir];
    int ny = y + dy[move_dir];
    if(inRange(nx,ny) && !visited[nx][ny] && !block[x][y][move_dir])
        spread(nx,ny,move_dir,power-1);
    
    if(dx[move_dir] == 0){
        int nxs[] = {x+1,x-1};
        for(int i=0;i<2;i++){
            int nx = nxs[i];
            int ny = y + dy[move_dir];
            if(inRange(nx,ny) && !visited[nx][ny] && !block[x][y][revDir(nx-x,0)] && !block[nx][y][move_dir])
                spread(nx,ny,move_dir,power-1);
        }
    }
    else{
        int nys[] = {y-1,y+1};
        for(int i=0;i<2;i++){
            int nx = x + dx[move_dir];
            int ny = nys[i];
            if(inRange(nx,ny) && !visited[nx][ny] && !block[x][y][revDir(0,ny-y)] && !block[x][ny][move_dir])
                spread(nx,ny,move_dir,power-1);
        }

    }

}

void clearVisited(){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            visited[i][j] = false;
}

void blow(){
    for(int x=0;x<n;x++)
        for(int y=0;y<n;y++)
            if(grid[x][y]>=2){
                int move_dir = (grid[x][y] <=3) ? (3-grid[x][y]) : (grid[x][y]-2);
                int nx = x + dx[move_dir];
                int ny = y + dy[move_dir];

                clearVisited();

                spread(nx,ny,move_dir,5);
            }
}

int getMixedCoolness(int x,int y){
    int remaining_c = coolness[x][y];
    for(int i=0;i<4;i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(inRange(nx,ny) && !block[x][y][i]){
            if(coolness[x][y] > coolness[nx][ny])
                remaining_c -= (coolness[x][y] - coolness[nx][ny]) / 4;
            else 
                remaining_c += (coolness[nx][ny] - coolness[nx][ny]) / 4;
        }
    }
    return remaining_c;
}

void mix(){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            temp[i][j] = 0;
    
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            temp[i][j] = getMixedCoolness(i,j);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            coolness[i][j] = temp[i][j];
}

bool isOuterWall(int x, int y){
    return x == 0 || x == n - 1 || y == 0 || y == n - 1;
}

void drop(){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(isOuterWall(i,j) && coolness[i][j]>0)
                coolness[i][j]--;
}

void simulate(){
    blow();
    mix();
    drop();
    elapsed_time++;
}
bool End() {
  
    if(elapsed_time > 100)
        return true;
    

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(grid[i][j] == 1 && 
               coolness[i][j] < k)
               return false;

    return true;
}

int main(){
    cin>>n>>m>>k;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>grid[i][j];
    for(int i=0;i<m;i++){
        int bx, by, bdir;
        cin>>bx>>by>>bdir;
        bx--; by--;
        block[bx][by][bdir] = 1;
        int nx = bx + dx[bdir];
        int ny = by + dy[bdir];

        if(inRange(nx, ny))
            block[nx][ny][3 - bdir] = true;
    }
    while(!End())
        simulate();


    if(elapsed_time <= 100)
        cout << elapsed_time;
    else
        cout << -1;
    return 0;
    
}