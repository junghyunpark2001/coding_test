#include <iostream>

using namespace std;

int n,m,x,y,k;
int board[22][22];
int dice[6];
int copied[6];

int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
void update_dice(int dir);

void move(int dir){
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if(nx<0||nx>=n||ny<0||ny>=m) return;
    x = nx; y = ny;
    update_dice(dir);
    if(board[x][y]==0) board[x][y] = dice[0];
    else {dice[0] = board[x][y]; board[x][y] = 0;}
    cout<<dice[3]<<'\n';

}

void update_dice(int dir){
    if(dir==0){
        copied[0] = dice[5];
        copied[3] = dice[4];
        copied[4] = dice[0];
        copied[5] = dice[3];
        copied[2] = dice[2];
        copied[1] = dice[1];
    }
    else if(dir==1){
        copied[0] = dice[4];
        copied[3] = dice[5];
        copied[4] = dice[3];
        copied[5] = dice[0];
        copied[2] = dice[2];
        copied[1] = dice[1];
    }
    else if(dir==3){
        copied[0] = dice[2];
        copied[1] = dice[0];
        copied[2] = dice[3];
        copied[3] = dice[1];
        copied[4] = dice[4];
        copied[5] = dice[5];
    }
    else if(dir==2){
        copied[0] = dice[1];
        copied[1] = dice[3];
        copied[2] = dice[0];
        copied[3] = dice[2];
        copied[4] = dice[4];
        copied[5] = dice[5];
    }
    for(int i=0;i<6;i++) dice[i] = copied[i];
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>x>>y>>k;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>board[i][j];

    for(int i=0;i<k;i++){
        int dir;
        cin>>dir;

        move(dir-1);
    }
    return 0;
}