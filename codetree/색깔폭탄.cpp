#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define X first 
#define Y second 

int board[22][22];
int tmp[22][22];
int n,m;
int result;
bool vis[22][22];
vector<pair<int,int>> red;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

void print_board(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
}
vector<pair<int,int>> bfs(){
    int max_size = 0;
    int red_num = 0;
    int row = 0, column = 0;
    vector<pair<int,int>> bombs;
    for(int i=0;i<n;i++) fill(vis[i],vis[i]+n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // 빨간색에서 시작은 불가능
            int size = 0, rn = 0, r = 0, c = 0;
            if(vis[i][j]||board[i][j]<=0) continue;
            queue<pair<int,int>> q;
            vector<pair<int,int>> bomb;
            bomb.push_back({i,j});
            q.push({i,j});
            vis[i][j] = 1;
            size++;
            while(!q.empty()){
                for(auto e : red) vis[e.X][e.Y] = 0;
                auto cur = q.front();
                q.pop();
                for(int dir=0;dir<4;dir++){
                    int nx = cur.X + dx[dir];
                    int ny = cur.Y + dy[dir];
                    if(nx<0||nx>=n||ny<0||ny>=n) continue;
                    if(board[i][j]==-1 || vis[nx][ny] || (board[nx][ny]!=board[i][j] && board[nx][ny]!=0)) continue;
                    size++;
                    if(board[nx][ny]==0) rn++;
                    else if(nx>r){r=nx;c=ny;}
                    else if(nx==r && ny<c) c = ny;
                    vis[nx][ny] = 1;
                    q.push({nx,ny});
                    bomb.push_back({nx,ny});
                }
            }
            if(size>max_size){
                max_size = size; red_num = rn; row = r; column = c;
                bombs = bomb;
            }
            else if(size==max_size && rn < red_num){
                max_size = size; red_num = rn; row = r; column = c;
                bombs = bomb;
            }
            else if(size==max_size && rn==red_num && r>row){
                max_size = size; red_num = rn; row = r; column = c;
                bombs = bomb;
            }
            else if(size==max_size && rn==red_num && r==row && c<column){
                max_size = size; red_num = rn; row = r; column = c;
                bombs = bomb;
            }
        }
    }
    return bombs;
}

void fall(int element,int row, int column){
    if(row==n-1 || element==-1){
        tmp[row][column] = element;
        return;
    }
    else if(element==-2) return;
    if(tmp[row+1][column]==-2) fall(element,row+1,column);
    else tmp[row][column] = element;
}

void rotate(){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            tmp[i][j] = board[n-1-j][i];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            board[i][j] = tmp[i][j];
}

void simulate(){
    // step 1. 폭탄묶음 찾기
    vector<pair<int,int>> bombs = bfs();
     
    // step 2. 폭탄 제거
    // explode -> 빈칸 -2
    for(auto e : bombs) board[e.X][e.Y] = -2;
    for(int i=0;i<n;i++) fill(tmp[i],tmp[i]+n,-2);
    for(int j=0;j<n;j++){
        for(int i=n-1;i>=0;i--){
            fall(board[i][j],i,j);
        } 
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            board[i][j] = tmp[i][j];
    

    // step 3. 반시계 방향 회전
    cout<<'\n';
    print_board();
    rotate();
    cout<<'\n';
    print_board();
    for(int i=0;i<n;i++) fill(tmp[i],tmp[i]+n,-2);
    for(int j=0;j<n;j++){
        for(int i=n-1;i>=0;i--){
            fall(board[i][j],i,j);
        } 
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            board[i][j] = tmp[i][j];
    cout<<'\n';
    print_board();
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            cin >> board[i][j];   
            if(board[i][j]==0) red.push_back({i,j});  
        }
            
    
    simulate();

}