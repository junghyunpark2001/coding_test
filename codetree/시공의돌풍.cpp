#include <iostream>
#include <algorithm>
using namespace std;

int n,m,t;
vector<int>locations;
int board[52][52];
int add_dust[52][52];
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

bool in_range(int x,int y){
    if(board[x][y]!=-1 && x>=0&& x<n && y>=0 && y<m) return true;
    return false;
}

void diffuse(){
    for(int i=0;i<n;i++) fill(add_dust[i],add_dust[i]+m,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j]==-1) continue;
            int tmp_dust = 0;
            for(int dir=0;dir<4;dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(in_range(nx,ny)){ 
                    add_dust[nx][ny] += board[i][j]/5;
                    tmp_dust += board[i][j]/5;
                }
            }
            add_dust[i][j] -= tmp_dust;
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            board[i][j] += add_dust[i][j];
        }
    }
}

void clean(){
    // upper part
    for(int i=locations[0];i>0;i--) board[i][0] = board[i-1][0];
    for(int i=0;i<m-1;i++) board[0][i] = board[0][i+1];
    for(int i=0;i<locations[0];i++) board[i][m-1] = board[i+1][m-1];
    for(int i=m-1;i>0;i--) board[locations[0]][i] = board[locations[0]][i-1];
    board[locations[0]][0] = -1; board[locations[0]][1] = 0;

    // down part
    for(int i=locations[1];i<n-1;i++) board[i][0] = board[i+1][0];
    for(int i=0;i<m-1;i++) board[n-1][i] = board[n-1][i+1];
    for(int i=n-1;i>locations[1];i--)board[i][m-1] = board[i-1][m-1];
    for(int i=m-1;i>0;i--)board[locations[1]][i] = board[locations[1]][i-1];
    board[locations[1]][0] = -1; board[locations[1]][1] = 0;

}

void simulate(){
    for(int i=0;i<t;i++){
        diffuse();
        clean();
    }
 

}

int result(){
    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j]==-1) continue;
            ans+=board[i][j];
        }
    }
    return ans;
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>t;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
            if(board[i][j]==-1){
                locations.push_back(i);
            }
        }
    }
    simulate();
    cout<<result()<<'\n';
    // cout<<'\n';
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout<<board[i][j]<<" ";
    //     }
    //     cout<<'\n';
    // }
}