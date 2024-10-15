#include <iostream>
#include <queue>

using namespace std;

#define X first 
#define Y second

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int n,l,r;
int board[55][55];
int vis[55][55];
int open[55][55];
bool changed = 0;
bool check(){
    int cur = board[0][0];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]!=cur) return false;
        }
    }
    return true;
}

void print_open(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
}
void simulate(){
    for(int i=0;i<n;i++)fill(vis[i],vis[i]+n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!vis[i][j]){
                int sum = 0;
                queue<pair<int,int>> q;
                vector<pair<int,int>> v;
                q.push({i,j});
                v.push_back({i,j});
                sum+=board[i][j];
                vis[i][j] = 1;
                while(!q.empty()){
                    auto cur = q.front();
                    q.pop();
                    for(int dir=0;dir<4;dir++){
                        int nx = cur.X + dx[dir];
                        int ny = cur.Y + dy[dir];
                        if(nx<0||nx>=n||ny<0||ny>=n)continue;
                        if(vis[nx][ny]) continue;
                        int diff = abs(board[cur.X][cur.Y]-board[nx][ny]);
                        if(diff<l||diff>r) continue;
                        sum += board[nx][ny];
                        vis[nx][ny] = 1;
                        q.push({nx,ny});
                        v.push_back({nx,ny});

                    }
                }
                if(v.size()>1){
                    changed = 1;
                    int avg = sum / v.size();
                    for(auto e:v) board[e.first][e.second] = avg;
                }
            }
        }
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>l>>r;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>board[i][j];
    int cnt = 0;
    
    while(true){
        changed = 0;
        simulate();
        if(changed) cnt++;
        else break;
    }
    cout<<cnt;

}