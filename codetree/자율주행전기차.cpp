#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

#define X first 
#define Y second 

int n,m,c;
int cur_x, cur_y;
vector<pair<int,int>> goals(405);

int board[22][22];
int people[22][22];
int copy_people[22][22];
bool vis[22][22];
int dist[22][22];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

bool check(){
    bool left = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(people[i][j]) left = 1;
    return left;

}

int bfs(int x1,int x2,int y1,int y2){
    for(int i=1;i<=n;i++) fill(vis[i],vis[i]+n+1,0);
    for(int i=1;i<=n;i++) fill(dist[i],dist[i]+n+1,0);
    queue<pair<int,int>> q;
    q.push({x1,x2});
    vis[x1][x2] = 1;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx<1||nx>n||ny<1||ny>n) continue;
            if(vis[nx][ny]||board[nx][ny]) continue;
            q.push({nx,ny});
            vis[nx][ny] = 1;
            dist[nx][ny] = dist[cur.X][cur.Y] + 1;
        }
    }
    return dist[y1][y2];
}

void move(){
    // 승객 고르기
    int guest_num,guest_x,guest_y;
    int min_dist = INT_MAX;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){

            if(people[i][j] && bfs(cur_x,cur_y,i,j)<min_dist){
                // cout<<"cur is "<<vis[i][j]<<'\n';
                if(vis[i][j]==0){
                    c = -1;
                    return;
                }
                guest_num = people[i][j];
                guest_x = i; guest_y = j;
                min_dist = bfs(cur_x,cur_y,i,j);

            }
        }
    }
    // cout<<"to the guest: ";
    // cout<<guest_num<<" "<<guest_x<<" "<<guest_y<<'\n';
    
    c-=min_dist;

    cur_x = guest_x; cur_y = guest_y;
    // cout<<cur_x<<" "<<cur_y<<'\n';
    people[cur_x][cur_y] = 0;
    int distance = bfs(cur_x,cur_y,goals[guest_num].X,goals[guest_num].Y);
    if(vis[goals[guest_num].X][goals[guest_num].Y]==0){
        c=-1;
        return;
    }
    c-=distance;

    cur_x = goals[guest_num].X; cur_y = goals[guest_num].Y;
    if(c>=0) c += 2*distance;
    // cout<<"to the goal\n";
    // cout<<cur_x<<" "<<cur_y<<" "<<c<<'\n';

    

}

void simulate(){
    while(true){
        if(c<0){
            cout<<-1;
            return;
        }
        if(check()) move();
        else break;

    }
    cout<<c;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>c;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>board[i][j];
    
    cin>>cur_x>>cur_y;
    for(int i=1;i<=m;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        people[x1][y1] = i;
        goals[i] = make_pair(x2,y2);
    }
    simulate();
    

}