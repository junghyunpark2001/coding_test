#include <iostream>

using namespace std;

#define X first 
#define Y second 



int n;
int board[500][500];
int vis[500][500];
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
int cur_x, cur_y;
int dust_board1[5][5] = {{0,0,2,0,0},{0,10,7,1,0},{5,0,0,0,0},{0,10,7,1,0},{0,0,2,0,0}};
int dust_board2[5][5];
int dust_board3[5][5];
int dust_board4[5][5];

int update_board[5][5];
void rotation(){
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            dust_board2[i][j] = dust_board1[j][n-1-i];

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            dust_board3[i][j] = dust_board2[j][n-1-i];

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            dust_board4[i][j] = dust_board3[j][n-1-i];

                
}

bool inRange(int x, int y){
    if(x>=0&&x<n&&y>=0&&y<n) return true;
    return false;
}

void change(int dir){
    for(int i=0;i<n;i++) fill(update_board[i],update_board[i]+n,0);
    int sum = 0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            int nx = cur_x + i - 2;
            int ny = cur_y + j - 2;
            cout<<nx<<" "<<ny<<"\n";
            if(!inRange(nx,ny)) continue;
            else if(dir == 0){update_board[i][j] = board[cur_x][cur_y]*dust_board1[i][j]*0.01;}
            else if(dir == 1){update_board[i][j] = board[cur_x][cur_y]*dust_board2[i][j]*0.01;}
            else if(dir == 2){update_board[i][j] = board[cur_x][cur_y]*dust_board3[i][j]*0.01;}
            else if(dir == 3){update_board[i][j] = board[cur_x][cur_y]*dust_board4[i][j]*0.01;}
            sum += update_board[i][j];
        }
    }
    int a = board[cur_x][cur_y] - sum;
    if(dir==0) update_board[2][1] = a;
    if(dir==1) update_board[3][2] = a;
    if(dir==2) update_board[2][3] = a;
    if(dir==3) update_board[1][2] = a;
    cout<<cur_x<<" "<<cur_y<<"\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<update_board[i][j]<<"  ";
        }
        cout<<"\n";
    }

}

void move(){

    int dir = 0;
    int length = 1;
    int tmp = 0;
    while(cur_x>=0&&cur_y>=0){    
        for(int cnt=0;cnt<2;cnt++){
            for(int i=0;i<length;i++){
                dir%=4;
                cur_x = cur_x + dx[dir];
                cur_y = cur_y + dy[dir];
                if(cur_x<0||cur_y<0) break;
                change(dir);
                vis[cur_x][cur_y] = tmp;
                cout<<cur_x<<" "<<cur_y<<"\n";
                tmp++;
                
            }
            dir++;               
        }   
        length++; 
    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }
    rotation();
    cur_x = n/2;
    cur_y = n/2;
    cur_x--;
    change(0);
    
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<vis[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
}