#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

#define X first
#define Y second

int n,m,q;
int board[55][55];
int vis[55][55];
tuple<int,int,int> t[52];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int final_change = 0;
void shift(int board_x, int dir){
    // 시계 방향
    if(dir==0){
        int tmp = board[board_x][m];
        for(int i=m;i>1;i--) board[board_x][i] = board[board_x][i-1];
        board[board_x][1] = tmp;
    }
    // 반시계 방향
    else if(dir==1){
        int tmp = board[board_x][1];
        for(int i=1;i<m;i++) board[board_x][i] = board[board_x][i+1];
        board[board_x][m] = tmp;
    }
}

void move(tuple<int,int,int> update){
    int x, d, k; // 원판 종류, 방향, 회전 칸 수
    tie(x,d,k) = update;
    int i = 1;
    int xx = x;

    while(xx<=n){

        xx=x*i;
        for(int j=0;j<k;j++){
            shift(xx,d);
        }
        //x/=i;
        i++;
    }
}

void check_delete(){
    final_change = 0;
    //for(int i=0;i<=n;i++) fill(vis[i],vis[i]+m+1,-1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //fill(&vis[0][0], &vis[0][0] + sizeof(vis) / sizeof(int), -1);
            for(int i=0;i<=n;i++) fill(vis[i],vis[i]+m+1,-1);
            bool flag = 0;
            
            queue<pair<int,int>> q;
            if(board[i][j]!=0){
                q.push({i,j});
                vis[i][j] = 1;                
            }
            // q.push({i,j});
            // vis[i][j]=1;
            while(!q.empty()){
                auto cur = q.front();
                q.pop();

                for(int dir=0;dir<4;dir++){
                    int nx = cur.X + dx[dir];
                    int ny = cur.Y + dy[dir];
                    if(ny<1) ny = m;
                    if(ny>=m+1) ny = 1;
       
                    if(nx<1 || nx>=n+1) continue;
                    if(vis[nx][ny]==1||board[nx][ny]!=board[cur.X][cur.Y]) continue;
                    flag = 1;
                    final_change = 1;
                    q.push({nx,ny});
                    vis[nx][ny] = 1;
                }
            }

            if(flag==1){
                for(int x=1;x<=n;x++){
                    for(int y=1;y<=m;y++){
                        if(vis[x][y]==1) board[x][y] = 0;
                    }
                }
            }
        }
    }
    
}

void normalize(){
    int tot = 0;
    int cnt = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            tot += board[i][j];
            if(board[i][j]!=0)cnt++;
        }
    }
    int avg;
    if(cnt==0) avg = 0;
    else{
        avg = tot / cnt;
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(board[i][j]!=0){
                    if(board[i][j]>avg) board[i][j]--;
                    else if(board[i][j]<avg) board[i][j]++;
                }
            
            }
        }
    }

}

int final_score(){
    int score = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            score+=board[i][j];
    return score;
}

void simulate(){
    
    for(int i=0;i<q;i++){
        move(t[i]);

        check_delete();
        if(final_change==0) normalize();


    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>board[i][j];
        }
    }
    for(int i=0;i<q;i++){
        int x,d,k;
        cin>>x>>d>>k;
        t[i] = make_tuple(x,d,k);

    }

    simulate();

    cout<<final_score()<<'\n';



}