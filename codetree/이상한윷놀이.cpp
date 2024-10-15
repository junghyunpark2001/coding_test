#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

#define X first 
#define Y second 


int dx[5] = {0,0,0,-1,1};
int dy[5] = {0,1,-1,0,0};

int n,k;
int board[14][14]; // 0:white, 1:red, 2:blue
vector<int> horse_board[14][14];
vector<tuple<int,int,int>> horses(13);

bool end_check(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(horse_board[i][j].size()==k) return true;
    return false;
}

void simulate(){
    for(int i=1;i<=k;i++){
        int x,y,d;
        tie(x,y,d) = horses[i];
        int nx = x + dx[d];
        int ny = y + dy[d];
        vector<int> tmp_origin;
        vector<int> tmp_move;
        bool meet = 0;
        for(int e:horse_board[x][y]){
            if(e==i) meet = 1;
            if(!meet) tmp_origin.push_back(e);
            else tmp_move.push_back(e);
        }
        horse_board[x][y] = tmp_origin;
        if(nx<1||nx>n||ny<1||ny>n){
            if(d==1) d=2;
            if(d==2) d=1;
            if(d==3) d=4;
            if(d==4) d=3;
            nx = x + dx[d];
            ny = y + dy[d];
            for(int e: tmp_move){
                horse_board[nx][ny].push_back(e);
                int xx,yy,dd;
                dd = d;
                tie(xx,yy,dd) = horses[e];
                horses[e] = make_tuple(nx,ny,dd);
            }
        }
        else if(board[nx][ny]==2){
            if(d==1) d=2;
            if(d==2) d=1;
            if(d==3) d=4;
            if(d==4) d=3;
            nx = x + dx[d];
            ny = y + dy[d];
            for(int e: tmp_move){
                horse_board[nx][ny].push_back(e);
                int xx,yy,dd;
                tie(xx,yy,dd) = horses[e];
                horses[e] = make_tuple(nx,ny,dd);
            }
        }

        else if(board[nx][ny]==0){
            for(int e: tmp_move){
                horse_board[nx][ny].push_back(e);
                int xx,yy,dd;
                tie(xx,yy,dd) = horses[e];
                horses[e] = make_tuple(nx,ny,dd);
            }
        }

        else if(board[nx][ny]==1){
            for(int a = tmp_move.size()-1;a>=0;a--){
                horse_board[nx][ny].push_back(tmp_move[a]);
                int xx,yy,dd;
                tie(xx,yy,dd) = horses[tmp_move[a]];
                horses[tmp_move[a]] = make_tuple(nx,ny,dd);
            }
        }

    }
}

void print_horses(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(horse_board[i][j].size()==0) cout<<0;
            for(auto e:horse_board[i][j]) cout<<e;
            cout<<" ";
        }
        cout<<'\n';
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>board[i][j];
        }
    }

    for(int i=1;i<=k;i++){
        int x,y,d;
        cin>>x>>y>>d;
        horse_board[x][y].push_back(i);
        horses[i] = {x,y,d};
    }
    int result = 0;
    for(int i=0;i<5;i++){
        simulate();
        result++;
        if(end_check()) break;
        
        print_horses();
        cout<<'\n';
    }
    // for(int i=0;i<1000;i++){
    //     simulate();
    //     result++;
    //     if(end_check()) break;
        
    // }
    // if(result==1000) cout<<-1;
    // else cout<<result;

    // simulate();

    // print_horses();

}