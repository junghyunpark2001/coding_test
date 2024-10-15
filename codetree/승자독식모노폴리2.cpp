#include <iostream>

using namespace std;

#define X first 
#define Y second 

int n,m,k;
int dx[5] = {0,-1,1,0,0};
int dy[5] = {0,0,0,-1,1};

int cur_dir[205];
int board[22][22];
int copy_board[22][22];
pair<int,int> monopoly_board[22][22];
pair<int,int> copy_monopoly_board[22][22];
int players_direction[405][5][4];

void print_board(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<copy_board[i][j]<<" ";
        }
        cout<<'\n';
    }
}

bool check_end(){
    int result = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            result+=board[i][j];
    if(result==1) return true;
    else return false;
}

void print_monopoly_board(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<monopoly_board[i][j].X<<monopoly_board[i][j].Y<<" ";
        }
        cout<<'\n';
    }
}

void move(){
    for(int i=0;i<n;i++) fill(copy_board[i],copy_board[i]+n,0);
    for(int i=0;i<n;i++) fill(copy_monopoly_board[i],copy_monopoly_board[i]+n,make_pair(0,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]!=0){
                int ndir = -1;
                // cout<<board[i][j]<<" here\n";
                int player_num = board[i][j];
                // find not monopoly space
                for(int dir=0;dir<4;dir++){
                    int nx = i + dx[players_direction[player_num][cur_dir[player_num]][dir]];
                    int ny = j + dy[players_direction[player_num][cur_dir[player_num]][dir]];
                    // cout<<nx<<" "<<ny<<'\n';
                    if(nx>=n||nx<0||ny>=n||ny<0) continue;
                    if(monopoly_board[nx][ny].first==0) {
                        ndir=players_direction[player_num][cur_dir[player_num]][dir];
                        break;
                    }
                }
                // back to my space
                if(ndir==-1){
                    // cout<<"no\n";
                    for(int dir=0;dir<4;dir++){
                        int nx = i + dx[players_direction[player_num][cur_dir[player_num]][dir]];
                        int ny = j + dy[players_direction[player_num][cur_dir[player_num]][dir]];
                        if(nx>=n||nx<0||ny>=n||ny<0) continue;
                        if(monopoly_board[nx][ny].first==player_num) {
                            ndir=players_direction[player_num][cur_dir[player_num]][dir];
                            break;
                        }
                    }
                }
                int nx = i + dx[ndir];
                int ny = j + dy[ndir];
                if(copy_board[nx][ny]>0 && copy_board[nx][ny]<player_num) continue;
                else{ 
                    copy_board[nx][ny] = player_num;
                    copy_monopoly_board[nx][ny] = {player_num,k};
                }
                cur_dir[player_num] = ndir;



            }

        }
    }
    
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            board[i][j] = copy_board[i][j];
}

void simulate(){
    move();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(monopoly_board[i][j]!=make_pair(0,0)){
                monopoly_board[i][j].second--;
                if(monopoly_board[i][j].second==0) monopoly_board[i][j] = {0,0};
            }
            if(copy_monopoly_board[i][j]!=make_pair(0,0)) monopoly_board[i][j] = copy_monopoly_board[i][j];
        }
    }
    
    // print_board();
    // cout<<'\n';
    // print_monopoly_board();
    // cout<<'\n';

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
            if(board[i][j]>0) monopoly_board[i][j] = {board[i][j],k};
            else monopoly_board[i][j]={0,0};
        }
    }
    
    for(int i=1;i<=m;i++) cin>>cur_dir[i];

    for(int i=1;i<=m;i++){
        for(int j=1;j<5;j++){
            for(int dir=0;dir<4;dir++){
                cin>>players_direction[i][j][dir];
            }
        }
    }

    for(int i=1;i<=1000;i++){
        simulate();
        if(check_end()){
            cout<<i;
            return 0;
        }
    }
    cout<<-1;
}