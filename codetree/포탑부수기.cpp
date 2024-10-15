#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

#define X first
#define Y second

int n,m,k;
int board[12][12];

// bfs에 사용
int vis[12][12];
int dist[12][12];
int path_board[12][12];
int recent_attack[12][12];
int dx[8] = {0,1,0,-1,1,1,-1,-1};
int dy[8] = {1,0,-1,0,1,-1,1,-1};

// 정비에 사용
bool attack_related[12][12];

pair<int,int> attack;
pair<int,int> attacked;

pair<int,int> choose_attacker(){
    int min_at = 5001;
    pair<int,int> result = {-1,-1};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(board[i][j]==0) continue;
            if(board[i][j]<min_at){
                min_at = board[i][j];
                result = {i,j};
            }
        
            else if(board[i][j]==min_at){
                if(recent_attack[i][j]>recent_attack[result.X][result.Y]){
                    result = {i,j};
                }
                else if((recent_attack[i][j]==recent_attack[result.X][result.Y]) && (i+j)>(result.X+result.Y)){
                    result = {i,j};
                }
                else if((recent_attack[i][j]==recent_attack[result.X][result.Y]) && (i+j)==(result.X+result.Y) && i>result.X){
                    result = {i,j};
                }
            }
        }
    }
    return result;
}

pair<int,int> choose_attacked(){
    int max_at = -1;
    pair<int,int> result = {-1,-1};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(attack.X==i && attack.Y==j) continue;
            if(board[i][j]==0) continue;
            if(board[i][j]>max_at){
                max_at = board[i][j];
                result = {i,j};
            }
            else if(board[i][j]==max_at){
                cout<<i<<j<<" "<<result.X<<result.Y<<'\n';

                if(recent_attack[i][j]<recent_attack[result.X][result.Y]){
                    result = {i,j};
                }
                else if((recent_attack[i][j]==recent_attack[result.X][result.Y]) && (i+j)<(result.X+result.Y)){
                    
                    result = {i,j};
                }
                else if((recent_attack[i][j]==recent_attack[result.X][result.Y]) && (i+j)==(result.X+result.Y) && i<result.X){
                    result = {i,j};
                } 
            }
        }
    }
    return result;
}

void bfs(){
    dist[attack.X][attack.Y] = 0;
    vis[attack.X][attack.Y] = 1;
    queue<pair<int,int>> q;
    q.push({attack.X,attack.Y});
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            // if(nx<1||nx>n||ny<1||ny>m) continue;
            if(nx<1) nx=n;
            if(ny<1) ny=m;
            if(nx>n) nx=1;
            if(ny>m) ny=1;
            if(vis[nx][ny]||board[nx][ny]==0) continue;
            vis[nx][ny] = 1;
            dist[nx][ny] = dist[cur.X][cur.Y] + 1;
            q.push({nx,ny});
        }
    }
}

void print_board(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void find_path(){
    for(int i=1;i<=n;i++) fill(vis[i],vis[i]+1+m,0);
    queue<pair<int,int>> q;
    q.push({attacked.X,attacked.Y});
    vis[attacked.X][attacked.Y] = 1;
    path_board[attacked.X][attacked.Y] = dist[attacked.X][attacked.Y];
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx<1) nx=n;
            if(ny<1) ny=m;
            if(nx>n) nx=1;
            if(ny>m) ny=1;
            if(vis[nx][ny] || dist[nx][ny]==-1) continue;
            if(dist[nx][ny] != dist[cur.X][cur.Y]-1) continue;
            vis[nx][ny] = 1;
            path_board[nx][ny] = dist[nx][ny];
            q.push({nx,ny});
        }
    }

}

void laser_attack(){
    pair<int,int> cur = attack;
    while(true){
        for(int dir=0;dir<4;dir++){
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx<1) nx=n;
            if(ny<1) ny=m;
            if(nx>n) nx=1;
            if(ny>m) ny=1;    

            if(path_board[nx][ny] && dist[nx][ny] == dist[cur.X][cur.Y] + 1){
                cur = {nx,ny};

                break;
            }        
        }
        if(cur == attacked){
            board[cur.X][cur.Y] -= board[attack.X][attack.Y];
            attack_related[cur.X][cur.Y] = 1;
            break;
        }
        else{
            attack_related[cur.X][cur.Y] = 1;
            board[cur.X][cur.Y] -= (board[attack.X][attack.Y]/2);
        }
    }
}

void laser_and_bomb(){
    // 레이저
    for(int i=1;i<=n;i++){ 
        fill(vis[i],vis[i]+1+m,0);
        fill(path_board[i],path_board[i]+1+m,0);
        fill(dist[i],dist[i]+1+m,-1);

    }
    bfs();
    if(dist[attacked.X][attacked.Y]!=-1){
        cout<<"laers\n";

        find_path();
        laser_attack();
    }
    // 포탄
    else if(dist[attacked.X][attacked.Y]){
        cout<<"bomb\n";
        board[attacked.X][attacked.Y] -= board[attack.X][attack.Y];
        for(int dir=0;dir<8;dir++){
            int nx = attacked.X + dx[dir];
            int ny = attacked.Y + dy[dir];
            if(nx<1) nx=n;
            if(ny<1) ny=m;
            if(nx>n) nx=1;
            if(ny>m) ny=1; 
            if(board[nx][ny]==0 || (attack.X==nx && attack.Y==ny)) continue;
            attack_related[nx][ny] = 1;
            board[nx][ny] -= (board[attack.X][attack.Y]/2);
        }
    }

    
}

void simulate(int turn){
    
    for(int i=1;i<=n;i++) fill(attack_related[i],attack_related[i]+1+m,0);
    // step 1. 공격자 선정
    attack = choose_attacker();

    

    recent_attack[attack.X][attack.Y] = turn;
    // step 2. 공격자의 공격
    attacked = choose_attacked();
    board[attack.X][attack.Y] += (n+m);
    attack_related[attack.X][attack.Y] = 1;
    attack_related[attacked.X][attacked.Y] = 1;
    if(attacked.X == -1 && attacked.Y == -1) return;
    // 공격
    laser_and_bomb();



    // step 3. 포탑 부서짐
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(board[i][j]<0) board[i][j] = 0;
        }
    }
    
    // step 4. 포탑 정비

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(board[i][j]>0 && !attack_related[i][j]) board[i][j]++;
        }
    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>board[i][j];
    
    for(int i=1;i<=k;i++){
        
        simulate(i);
        cout<<'\n';
        cout<<attack.X<<" "<<attack.Y<<'\n';
        cout<<attacked.X<<" "<<attacked.Y<<'\n';
        print_board();
        int left = 0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                if(board[i][j]) left++;
            }
        }
        if(left==1) break;
        
    }
        
    int max_score = -1;
    int left = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            
            if(board[i][j]>max_score) max_score = board[i][j];
        }
    }
    cout<<max_score<<'\n';
}