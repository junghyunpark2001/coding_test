#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
using namespace std;
#define info tuple<int,int,int>

int n,m,h,k;
int turn = 0;
int tree[101][101];
int board[101][10];

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

vector<info> runners;
vector<info> it_sequence;
info it;
int it_turn = 0;
int it_dir = 1;
void dist(){

}


void it_initialize(){
    int cur_x = n/2; int cur_y = n/2;
    int dir = 0;
    int length = 1;
    int repeat = 0;
    int move = 0;
    it_sequence.push_back({cur_x,cur_y,dir});
    while(cur_x>=0&&cur_y>=0){
        cur_x = cur_x + dx[dir];
        cur_y = cur_y + dy[dir];
        if(cur_x<0||cur_y<0)break;
        it_sequence.push_back({cur_x,cur_y,dir});
        move++;
        if(move==length){
            move = 0;
            repeat++;
            dir = (dir+1)%4;
        }
        if(repeat==2){
            repeat = 0;
            length++;
        }
    }
    // for(int i=0;i<it_sequence.size();i++){
    //     cout<<it_sequence[i].first<<" "<<it_sequence[i].second<<'\n';
    // }
}

info it_move(){
    int nx,ny,dir;
    int cur_x,cur_y;
    tie(cur_x,cur_y,ignore) = it_sequence[it_turn];
    if(it_turn>=it_sequence.size()-1) it_dir = -1;
    if(it_turn<=0) it_dir = 1;
    
    it_turn += it_dir;
    tie(nx,ny,dir) = it_sequence[it_turn];
    board[cur_x][cur_y] = 0;
    board[nx][ny] = 1;

    return make_tuple(cur_x,cur_y,dir);
    
}



void simulate(){
    for(int t=0;t<3;t++){
        int it_x, it_y, it_dir;
        tie(it_x,it_y,it_dir) = it_move();
        for(int i=0;i<runners.size();i++){
            int ru_x, ru_y,ru_dir;
            tie(ru_x, ru_y,ru_dir) = runners[i];
            if(abs(ru_x-it_x)+abs(ru_y-it_y)<=3){
                int nx = ru_x + dx[ru_dir];
                int ny = ru_y + dy[ru_dir];

                if(nx<0||nx>=n||ny<0||ny>=n){
                    ru_dir = (ru_dir+2)%4;
                    cout<<ru_dir<<'\n';
                    nx = ru_x + dx[ru_dir];
                    ny = ru_y + dy[ru_dir];    
                }

                runners[i] = make_tuple(nx,ny,ru_dir);
                board[ru_x][ru_y] = 0;
            }
        }
        for(int i=0;i<runners.size();i++){
            int ru_x,ru_y;
            cout<<ru_x<<" "<<ru_y<<'\n';
            tie(ru_x,ru_y,ignore) = runners[i];
            board[ru_x][ru_y] = 2;
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<board[i][j]<<" ";
            }
            cout<<'\n';
        }
        cout<<'\n';
    }
    
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>h>>k;
    board[n/2][n/2] = 1;
    for(int i=0;i<m;i++){
        int x,y,d;
        cin>>x>>y>>d;
        runners.push_back(make_tuple(x,y,d));
        board[x][y] = 2;
    }
    for(int i=0;i<h;i++){
        int x,y;
        cin>>x>>y;
        tree[x][y] = 1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
    cout<<'\n';

    it = make_tuple(n/2,n/2,1);
    it_initialize();

    simulate();

    
}