#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define X first 
#define Y second

using namespace std;

int n,k;
int board[14][14];
int dx[5] = {0,0,0,1,-1};
int dy[5] = {0,1,-1,0,0};
vector<int> chess[14][14];


bool check(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(chess[i][j].size()==k) return true;
        }
    }
    return false;
}



int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    // 체스판
    // 0 : 흰색, 1: 빨간색, 2: 파란색
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>board[i][j];
    vector<int> directions;
    vector<pair<int,int>> locations;
    for(int i=0;i<k;i++){
        int x,y,dir;
        cin>>x>>y>>dir;
        chess[x][y].push_back(i);
        locations.push_back({x,y});
        directions.push_back(dir);
    }

    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         for(auto a: chess[i][j]) cout<<a<<" ";
    //         cout<<"\n";
    //     }
    //     cout<<"\n";
    // }
    int result = 0;
    while(true){
        if (check()) break;
        for(int i=0;i<k;i++){
            // 혼자인 경우, 위에 뭐 있을 경우
            int index = 0;
            for(int in=0;in<chess[locations[i].X][locations[i].Y].size();in++){
                if(chess[locations[i].X][locations[i].Y][i]==in) index = in;
            }
            for(int in = index; in<chess[locations[i].X][locations[i].Y].size();in++){
                int nx = locations[i].X+dx[directions[i]];
                int ny = locations[i].Y+dy[directions[i]];
                // red blue boundary
                //boundary
                if(nx<0||nx>=n||ny<0||ny>=n){
                    if(directions[i]==1)directions[i]=2;
                    if(directions[i]==2)directions[i]=1;
                    if(directions[i]==3)directions[i]=4;
                    if(directions[i]==4)directions[i]=3;
                    
                }
                else if(board[nx][ny]==0){
                    
                }
            }

        }
    }
}