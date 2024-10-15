#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

#define X first 
#define Y second 

int n,m,k,c; // size, turns, range, kill
int board[22][22];
int poison[22][22];
int tmp_board[22][22];

int killed = 0;

int dx1[4] = {1,0,-1,0};
int dy1[4] = {0,1,0,-1};
int dx2[4] = {1,1,-1,-1};
int dy2[4] = {-1,1,-1,1};

void print_board(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void tree_grow(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]<=0) continue;
            int grow=0;
            for(int dir=0;dir<4;dir++){
                int nx = i + dx1[dir];
                int ny = j + dy1[dir];
                if(nx<0||nx>=n||ny<0||ny>=n) continue;
                
                if(board[nx][ny]>0) grow++;
            }
            board[i][j]+=grow;
        }
    }
}

void reproduce(){
    for(int i=0;i<n;i++) fill(tmp_board[i],tmp_board[i]+n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]<=0) continue;
            int blank=0;
            vector<pair<int,int>> v;
            for(int dir=0;dir<4;dir++){
                int nx = i + dx1[dir];
                int ny = j + dy1[dir];
                if(nx<0||nx>=n||ny<0||ny>=n) continue;
                if(poison[nx][ny]>0||board[nx][ny]!=0) continue;
                v.push_back({nx,ny});
                blank++;
            }
            if(blank==0) continue;
            for (auto e : v){
                tmp_board[e.first][e.second]+=board[i][j]/blank;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            board[i][j]+=tmp_board[i][j];
        }
    }
}

void poison_tree(){

    pair<int,int> max_position = {0,0};
    int max_kill = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]<=0) continue;
            int kill_num = 0;
            kill_num+=board[i][j];
            for(int dir=0;dir<4;dir++){

                for(int range=1;range<=k;range++){
                    int nx = i + range*dx2[dir]; 
                    int ny = j + range*dy2[dir];
                    if(nx<0||nx>=n||ny<0||ny>=n) break;
                    if(board[nx][ny]<=0) break;
                    kill_num+=board[nx][ny];
                    // cout<<board[nx][ny]<<" ";

                }
                
            }
            // cout<<kill_num<<'\n';
            if(kill_num>max_kill){
                max_position = {i,j};
                max_kill = kill_num;
            }
        }
    }

    // cout<<max_kill;
    killed+=max_kill;
    board[max_position.X][max_position.Y] = 0;
    poison[max_position.X][max_position.Y] = 1;
    for(int dir=0;dir<4;dir++){
        for(int range=1;range<=k;range++){
            int nx = max_position.X + range*dx2[dir]; 
            int ny = max_position.Y + range*dy2[dir];
            if(nx<0||nx>=n||ny<0||ny>=n) break;
            if(board[nx][ny]<=0){ 
                poison[nx][ny]=1;
                break;
            }
            board[nx][ny] = 0;
            poison[nx][ny]=1;
        }
        
    } 
}

void simulate(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(poison[i][j]>0) poison[i][j]++;
        }
    }
    // step 1. tree grows
    tree_grow();

    // step 2. reproduce
    reproduce();

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(poison[i][j]==c+1) poison[i][j]=0;
        }
    }
    // step 3. poison
    poison_tree();
    // cout<<'\n';
    // print_board();cout<<'\n';
}


int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k>>c;
    for(int i=0;i<n;i++)   
        for(int j=0;j<n;j++)
            cin>>board[i][j];

    for(int i=0;i<m;i++){
        simulate();
    }
    // cout<<'\n';
    // print_board();

    cout<<killed<<'\n';
}