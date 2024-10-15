#include <iostream>
#include <vector>
using namespace std;

int n,m,k;
int board[22][22];
int copy_board[22][22];
int monopoly[22][22];
int left_turns[22][22];
vector<vector<vector<int>>> players;
vector<pair<int,int>> players_location;
vector<int> players_dir; // 위치, 위치, 방향

// up, down, left, right
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

bool check(){
    int result = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            result += board[i][j];
            if(result>1) return false;
        }
    }
    if(result == 1) return true;
    return false;
}

void simulate(){
    for(int i=0;i<n;i++) fill(copy_board[i],copy_board[i]+n,0);
    // step 1. next 위치 찾기
    for(int i=0;i<m;i++){
        if(players_dir[i] == -1) continue;
        
        vector<int> dirs = players[i][players_dir[i]];
        bool changed = 0;
        for(int z=0;z<dirs.size();z++){
            int nx = players_location[m].first + dx[dirs[z]];
            int ny = players_location[m].second + dy[dirs[z]];
            if(nx>=n||nx<0||ny>=n||ny<0) continue;
            if(board[nx][ny]!=0 || monopoly[nx][ny]!=0) continue;
            changed = 1;
            copy_board[nx][ny] = i+1;
            break;
        }
        
        for(int dir = 0;dir<dirs.size();dir++) cout<<dirs[dir];
        cout<<'\n';
        // if copied -> players_dir = -1;
    }
    // copied_board != 0 -> continue
    // step 2. update monopoly
    // 2-1. if(monopoly > 0) monopoly--
    // 2-2. if(copy_board[i][j]) monopoly = k

    // step 3. copy board with copy_board
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m>>k;
    players_location.resize(m);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            cin>>board[i][j];
            if(board[i][j]!=0){
                players_location[board[i][j]] = {i,j};
            }
        }
    
    for(int i=0;i<m;i++){
        int dir;
        cin>>dir;
        players_dir.push_back(dir);
    }
    players.resize(m);
    for(int i=0;i<m;i++){
        for(int dirs=0;dirs<4;dirs++){
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            players[i].push_back({a,b,c,d});
        }
    }

    simulate();

}