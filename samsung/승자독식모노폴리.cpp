#include <iostream>

using namespace std;

int board[22][22][3]; // player, left turn, 독점 player
int n,m,k; // n : 격자 크기, m : 플레이어 수, k : 독점계약 턴 수
int priority[22][4][4];
int dx[22][4][4]; // player, dir -> dir
int dy[22][4][4];


int dir[22]; // index number(player) direction
int turn = 0;

bool in_range(int x, int y){
    if(x>=0&&x<n&&y>=0&&y<n) return true;
    return false;
}

// 1번 플레이어만 남은 경우
bool check(){
    if(dir[1]!=0){
        for(int i=2;i<n;i++){
            if(dir[i]!=0) return false;;
        }
    }
    return true;
}

// 불가능한 경우
bool impossible(){
    if(turn>=1000) return true;
    if(dir[1]==0) return true;
    return false;
}

void simulation(){
    turn++;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j][1]>0){
                board[i][j][1]--;
                if(board[i][j][1]==0)board[i][j][2]=0; // turn 0 되면 독점 player 공백으로 변경
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j][0]!=0) {
                // 플레이어 발견
                int player = board[i][j][0];
                // 빈 칸 확인
                bool flag = 1; // 끝일때도 1이면 독점칸 search
                for(int d = 0;d<4;d++){
                    int nx = i + dx[player][dir[player]][d];
                    int ny = j + dy[player][dir[player]][d];
                    if(board[nx][ny][2]==0){
                        flag = 0;
                        board[nx][ny][0] = player;
                        board[nx][ny][1] = k;
                        board[nx][ny][2] = player;
                        board[i][j][0] = 0;
                        
                    }
                }
                if(flag==1){
                    for(int d=0;d<4;d++){
                        int nx = i + dx[player][dir[player]][d];
                        int ny = j + dy[player][dir[player]][d];
                        if(board[nx][ny][2]==player){
                            board[nx][ny][0]=player;
                            board[nx][ny][1]=k;
                            board[i][j][0]=0;
                        }
                    }
                }


            }
        }
    }
}



int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j][0];
            board[i][j][2] = board[i][j][0];
            if(board[i][j]!=0) board[i][j][1]++;
        }
    }
    for(int i=1;i<n;i++) cin>>dir[i];

    for(int i=1;i<=m;i++){
        for(int now=0;now<4;now++){
            for(int next=0;next<4;next++){
                int dir;
                cin>>dir;
                if(dir==1){
                    dx[i][now][next] = -1;
                    dy[i][now][next] = 0;
                }
                else if(dir==2){
                    dx[i][now][next] = 1;
                    dy[i][now][next] = 0;
                }
                else if(dir==3){
                    dx[i][now][next] = 0;
                    dy[i][now][next] =-1;
                }
                else if(dir==4){
                    dx[i][now][next] = 0;
                    dy[i][now][next] = 1;
                }
            }
        }
    }
    // cout<<"board: \n";
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<board[i][j][0]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"dx\n";
    // for(int i=0;i<n;i++){
    //     for(int x=0;x<4;x++){
    //         for(int y=0;y<4;y++){
    //             cout<<dx[i][x][y]<<" ";
    //         }
    //         cout<<"\n";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"dy\n";
    // for(int i=0;i<n;i++){
    //     for(int x=0;x<4;x++){
    //         for(int y=0;y<4;y++){
    //             cout<<dy[i][x][y]<<" ";
    //         }
    //         cout<<"\n";
    //     }
    //     cout<<"\n";
    // }
}