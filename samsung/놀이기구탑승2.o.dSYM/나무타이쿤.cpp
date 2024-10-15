#include <iostream>
#include <queue>
using namespace std;

int n,m,d,p;
int board[17][17];
int nutrition[17][17];

int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {1,1,0,-1,-1,-1,0,1};

int ddx[4] = {-1,-1,1,1};
int ddy[4] = {-1,1,-1,1};

bool inRange(int x, int y){
    if(x>=0&&x<n&&y>=0&&y<n) return true;
    return false;
}

void move(int p, int d){
    vector<pair<int,int>> tmp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nutrition[i][j]==1){
                
                int nx = i + (p)*dx[d-1];
                int ny = j + (p)*dy[d-1];

                if(nx>=n) nx = (nx-n);
                if(ny>=n) ny = (ny-n);
                if(nx<0) nx = n+nx;
                if(ny<0) ny = n+ny;

                nutrition[i][j] = 0;
                tmp.push_back({nx,ny});
            }
        }
    }
    for(int i=0;i<tmp.size();i++){
        nutrition[tmp[i].first][tmp[i].second] = 1;
    }


}

int height(){
    int tot = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            tot+=board[i][j];
    return tot;
}

void grow(){

    // step 2
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nutrition[i][j]==1) board[i][j]++;
        }
    }
    // step 3
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nutrition[i][j]==1){
                for(int dir=0;dir<4;dir++){
                    int nx = i + ddx[dir];
                    int ny = j + ddy[dir];
                    if(nx<0||nx>=n||ny<0||ny>=n) continue;

                    if (board[nx][ny]>=1) board[i][j]++;
                }


            }
        }
    }

    queue<pair<int,int>> q;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(board[i][j]>=2&&nutrition[i][j]!=1) {
                board[i][j]-=2;
                q.push({i,j});
                
            }
    
    for(int i=0;i<n;i++) fill(nutrition[i],nutrition[i]+n,0);
    while(!q.empty()){
        auto cur = q.front();
        nutrition[cur.first][cur.second] = 1;
        q.pop();
    }

    
}

int main(void){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }
    nutrition[n-1][0] = 1; nutrition[n-1][1]=1; nutrition[n-2][1]=1; nutrition[n-2][0]=1;
    
    while(m--) {
        cin>>d>>p;
        move(p,d);
        grow();

    }

    cout<<height();

}