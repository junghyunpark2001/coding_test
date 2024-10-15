#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define X first
#define Y second

using namespace std;

int n,m,d;
int board[18][17];
vector<int> v;
vector<int,int> enemy;

int simulation(){
    int result;
    for(int i=0;i<m;i++){
        if(board[n][i]){
            int min_dis = 1000;
            pair<int,int> loc;
            for(int x=n-1;x>=0;x--){
                for(int y=0;y<m;y++){
                    if((abs(n-x)+abs(i-y))<min_dis&&(abs(n-x)+abs(i-y))>d){
                        min_dis = board[x][y];
                        loc.X = x;
                        loc.Y = y;
                    }
                }
            }
            if(board[loc.X][loc.Y]==1) board[loc.X][loc.Y] = 0;
             
        }
        
    }
}

int main(void){
    cin>>n>>m>>d;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
            v.push_back(0);

        }
    }
    v[0] = 1; v[1] = 1; v[2] = 1;
    do{
        for(int i=0;i<m;i++){
            board[n][i] = v[i];
        }
        
    } while (next_permutation(v.begin(),v.end()));
}