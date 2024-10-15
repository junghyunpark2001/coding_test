#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define X first
#define Y second

using namespace std;
int r,c,t;
int board[52][52];
int change[52][52];
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
vector<pair<int,int>> location;
void simulate(){
    for(int i=0;i<r;i++)fill(change[i],change[i]+c,0);

    // 미세먼지 확산
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(board[i][j]==-1||board[i][j]==0) continue;
            for(int dir=0;dir<4;dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx<0||nx>=r||ny<0||ny>=c) continue;
                if(board[nx][ny]==-1) continue;
                int tmp = board[i][j]/5;
                change[nx][ny]+=tmp;

                change[i][j] -= tmp;

            }
        }
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            board[i][j]+=change[i][j];
        }
    }

}
// 공기청정기 순환
void air_purifier(){

    for(int i=location[0].X-1;i>0;i--){
        if(board[i][0]==-1) continue;
        board[i][0] = board[i-1][0];
    }
    for(int i=location[1].X;i<r-1;i++){
        if(board[i][0]==-1) continue;
        board[i][0] = board[i+1][0];
    }
    for(int i=0;i<c-1;i++) {
        board[0][i] = board[0][i+1];
        board[r-1][i] = board[r-1][i+1];
    }
    for(int i=0;i<location[0].X;i++) board[i][c-1] = board[i+1][c-1];
    for(int i=r-1;i>location[1].X;i--) board[i][c-1] = board[i-1][c-1];
    for(int i=c-1;i>1;i--){
        board[location[0].X][i] = board[location[0].X][i-1];
        board[location[1].X][i] = board[location[1].X][i-1];

    }
    board[location[0].X][1] = 0;
    board[location[1].X][1] = 0;
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>r>>c>>t;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>board[i][j];
            if(board[i][j]==-1)location.push_back({i,j});
        }
    }
    for(int q=0;q<t;q++){
        simulate();
        air_purifier();

    }
    int result = 0;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            result+=board[i][j];
        }
    }
    cout<<result+2<<"\n";


}