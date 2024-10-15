#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int r,c,k;
int ci,di;
int result = 0;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int board[73][73];
int exit_dir[1005];
vector<tuple<int,int,int>> save_status(1005);
bool changed = 0;
bool vis[73][73];
int tmp_board[73][73];

void print_board(){
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cout<<tmp_board[i][j]<<"   ";

        }
        cout<<'\n';
    }
}
tuple<int,int,int,int> fin_loc;
void fall(int i, int ri, int ci, int di){
    fin_loc = make_tuple(i,ri,ci,di);
    changed = 0;
    if(ri+1<=r && board[ri][ci]==0 && board[ri+1][ci]==0 && board[ri][ci-1]==0 && board[ri][ci+1]==0){
        changed = 1;
        fall(i,ri+1,ci,di);
    }
    else if((ri+1)<=r && (ci-2)>= 1 && board[ri][ci-1]==0 && board[ri-1][ci-2]==0 && board[ri-2][ci-1]==0 && board[ri][ci-2]==0 && board[ri+1][ci-1] == 0){
        changed = 1;
        fall(i,ri+1,ci-1,(di+3)%4);
    }
    else if((ri+1)<=r && (ci+2)<=c && board[ri-2][ci+1]==0 && board[ri-1][ci+2]==0 && board[ri][ci+1]==0 && board[ri][ci+1]==0 && board[ri+1][ci+1]==0){
        changed = 1;
        fall(i,ri+1,ci+1,(di+1)%4);
    }

    
    // for(int dir=0;dir<4;dir++){
    //     int nx = ri-1 + dx[dir];
    //     int ny = ci + dy[dir];
    //     board[nx][ny] = i;
    // }
    // exit_dir[i] = di;
}
void initialize(){
    for(int i=0;i<=r;i++){
        for(int j=1;j<=c;j++){
            board[i][j] = 0;
        }
    }
    fill(exit_dir,exit_dir+k+1,0);
    for(int id=1;id<=k;id++) save_status[id] = {0,0,0};
}
void points(int i);
void update_loc(){
    int i,ri,ci,di;
    tie(i,ri,ci,di) = fin_loc;
    save_status[i] = make_tuple(ri-1,ci,di);
    // cout<<"ri is : "<<ri<<" "<<ci<<'\n';
    if(ri-1<){
        //cout<<"ri is : "<<ri<<" "<<ci<<'\n';
        // cout<<"here";
        initialize();
        return;
    }
    board[ri-1][ci] = i;
    for(int dir=0;dir<4;dir++){
        int nx = ri-1 + dx[dir];
        int ny = ci + dy[dir];
        // if(nx<1){
        //     initialize(i);
        //     return;
        // }
        board[nx][ny] = i;
    }
    exit_dir[i] = di;
   points(i);
}

void points(int i){
    for(int a=0;a<=r;a++) fill(vis[a],vis[a]+1+c,0);
    for(int i=0;i<=r;i++) fill(tmp_board[i],tmp_board[i]+c+1,0);

    for(int id=1;id<=i;id++){
        if(save_status[id]==make_tuple(0,0,0)) continue;
        int r,c,d;
        tie(r,c,d) = save_status[id];
        tmp_board[r][c] = id;
        for(int dir=0;dir<4;dir++){
            int nx = r + dx[dir];
            int ny = c + dy[dir];
            if(dir==d) tmp_board[nx][ny] = -1*id;
            else tmp_board[nx][ny] = id;
        }
    }
    int ri,ci,di;
    tie(ri,ci,di) = save_status[i];
    vis[ri][ci] = 1;
    int cur_id = i;
    // cout<<"ri is "<<ri;
    int max_row = ri+1;
    queue<pair<int,int>> q;
    for(int dir=0;dir<4;dir++){
        int nx = ri + dx[dir];
        int ny = ci + dy[dir];
        vis[nx][ny] = 1;
        
    }
    
    q.push({ri+dx[di],ci+dy[di]});
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        for(int dir=0;dir<4;dir++){
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if(nx<1||nx>r||ny<1||ny>c) continue;
            if(vis[nx][ny]==1 || tmp_board[nx][ny] == 0) continue;
            
            cur_id = abs(tmp_board[nx][ny]);
            int rr,cc,dd;
            tie(rr,cc,dd) = save_status[cur_id];
            vis[rr][cc] = 1;
            for(int ddir=0;ddir<4;ddir++){
                int nnx = rr+dx[ddir];
                int nny = cc+dy[ddir];
                vis[nnx][nny] = 1;
                if(nnx>max_row) max_row = nnx;
            }
            q.push({rr+dx[dd],cc+dy[dd]});
        }
    }

    result+=max_row;
    cout<<max_row<<'\n';
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>r>>c>>k;
    for(int i=1;i<=k;i++){
        cin>>ci>>di;
        exit_dir[i] = di;
        changed = 0;
        fin_loc = {0,0,0,0};
        fall(i,1,ci,di);
        update_loc();
        
       
        print_board();
    }
    cout<<result;
}