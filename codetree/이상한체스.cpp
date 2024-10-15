#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n,m;
int board[10][10];
int vis[10][10];
vector<pair<int,int>> chess;
int result = 100;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

void print_board(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<vis[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void move(int x,int y,int dir){
    vis[x][y] = 1;
    int nx = x;
    int ny = y;
    while(true){

        nx += dx[dir];
        ny += dy[dir];
       
        if(board[nx][ny]==6) break;
        if(nx>=n||nx<0||ny>=m||ny<0) break;
        vis[nx][ny]=1;
    }
}


int count(vector<int>& v){
    for(int i=0;i<n;i++)fill(vis[i],vis[i]+m,0);
    int tmp = 0;
    for(int i=0;i<chess.size();i++){
        if(board[chess[i].first][chess[i].second]==1){
            move(chess[i].first,chess[i].second,(v[i]));
        }
        if(board[chess[i].first][chess[i].second]==2){
            move(chess[i].first,chess[i].second,(v[i]+1)%4);
            move(chess[i].first,chess[i].second,(v[i]+3)%4);
        }
        if(board[chess[i].first][chess[i].second]==3){
            move(chess[i].first,chess[i].second,v[i]);
            move(chess[i].first,chess[i].second,(v[i]+1)%4);
        }
        if(board[chess[i].first][chess[i].second]==4){
            move(chess[i].first,chess[i].second,v[i]);
            move(chess[i].first,chess[i].second,(v[i]+1)%4);
            move(chess[i].first,chess[i].second,(v[i]+2)%4);
        }
        if(board[chess[i].first][chess[i].second]==5){
            move(chess[i].first,chess[i].second,v[i]);
            move(chess[i].first,chess[i].second,(v[i]+1)%4);
            move(chess[i].first,chess[i].second,(v[i]+2)%4);
            move(chess[i].first,chess[i].second,(v[i]+3)%4);
        }

    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(vis[i][j]==0&&board[i][j]!=6) tmp++;
        }
    }
    return tmp;
}

void simulate(){
    
    for(int i=0;i<(1<<(2*chess.size()));i++){
        
        int brute = i;
        vector<int> v;
        for(int d=0;d<chess.size();d++){
            int tmp = brute%4;
            brute/=4;
            v.push_back(tmp);

           
        }
        //for(int a=0;a<v.size();a++) cout<<v[a]<<" ";
        //cout<<'\n';
        //print_board();
        //cout<<result<<'\n';
        result = min(result,count(v));
        
    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
            if(board[i][j]!=0&&board[i][j]!=6) chess.push_back({i,j});
        }
    }
    simulate();
    cout<<result;

}