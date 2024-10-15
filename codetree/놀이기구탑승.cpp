#include <iostream>

using namespace std;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int n,n0,n1,n2,n3,n4;
int board[22][22];
int friends[405][5];
int friends_map[405]; // studnet -> loc
void print_board(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
}
int empty(int x,int y){
    int result = 0;
    for(int dir=0;dir<4;dir++){
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx<1||nx>n||ny<1||ny>n) continue;
        if(board[nx][ny]) continue;
        result++;
    }
    return result;
}

int like(int num, int x,int y){
    int result = 0;
    for(int dir=0;dir<4;dir++){
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx<1||nx>n||ny<1||ny>n) continue;
        for(int n=1;n<=4;n++) if(board[nx][ny]==friends[num][n]) result++;
    }
    return result;
}

void simulate(){
    for(int a=1;a<=n*n;a++){
        int r=-1,c=-1;
        int max_empty = 0;
        int max_friends = 0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(board[i][j]!=0) continue;
                if(like(a,i,j)>max_friends){
                    max_friends = like(a,i,j);
                    max_empty = empty(i,j);
                    r=i; c=j;
                }
                else if(like(a,i,j)==max_friends && max_empty<empty(i,j)){
                    max_empty = empty(i,j);
                    r=i; c=j;
                }
                else if(!max_empty && !max_friends && r==-1 && c==-1){
                    r=i; c=j;
                }
            }
        }
        board[r][c] = friends[a][0];
        // print_board();cout<<'\n';
    }
    
}

int score(){
    int result = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int close = 0;
            int me = board[i][j];
            for(int dir=0;dir<4;dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx<1||nx>n||ny<1||ny>n) continue;
                for(int a=1;a<=4;a++){
                    if(board[nx][ny]==friends[friends_map[me]][a]) close++;
                }
            }
            if(close==1) result+=1;
            else if(close==2) result+=10;
            else if(close==3) result+=100;
            else if(close==4) result+=1000;
        }
    }
    return result;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n*n;i++){
        cin>>n0>>n1>>n2>>n3>>n4;
        friends[i][0] = n0;friends[i][1] = n1;
        friends[i][2] = n2;friends[i][3] = n3; 
        friends[i][4] = n4;
        friends_map[n0] = i;
    }
    simulate();
    cout<<score();
}