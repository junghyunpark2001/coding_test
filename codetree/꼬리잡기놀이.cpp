#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

#define X first
#define Y second

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int n,m,k;
int board[25][25]; // 1~n
int vis[25][25];

int result = 0;
vector<vector<pair<int,int>>> teams(6);
vector<int> scores(6,0);

void find_locs(){
    int team = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(board[i][j]==1 && !vis[i][j]){
                for(int a=1;a<=n;a++) fill(vis[a], vis[a]+n+1, 0);  // 초기화 위치 조정
                teams[team].push_back({i,j});
                stack<pair<int,int>> q;
                q.push({i,j}); 
                vis[i][j] = 1;
                pair<int,int> cur;
                while(!q.empty()){
                    cur = q.top();
                    q.pop();
                    for(int dir=0;dir<4;dir++){
                        int nx = cur.X + dx[dir];
                        int ny = cur.Y + dy[dir];
                        if(nx<1||nx>n||ny<1||ny>n) continue;
                        if(vis[nx][ny]||board[nx][ny]==0||board[nx][ny]==4||board[nx][ny]==3) continue;
                        
                        vis[nx][ny] = 1;    
                        teams[team].push_back({nx,ny});
                        q.push({nx,ny});
                    }
                }
                for(int dir=0;dir<4;dir++){
                    int nx = cur.X + dx[dir];
                    int ny = cur.Y + dy[dir];
                    if(nx<1||nx>n||ny<1||ny>n) continue;
                    if(board[nx][ny]==3) teams[team].push_back({nx,ny});
                }
                team++; 
            }
        }
    }
}

void move() {
    for (int i = 0; i < m; i++) {
        auto cur = teams[i][0];  // 현재 팀의 첫 번째 요소 (머리)
        auto last = teams[i][teams[i].size() - 1];  // 현재 팀의 마지막 요소 (꼬리)
        
        // 현재 팀의 각 요소들을 한 칸씩 이동 (마지막 요소를 첫 번째 위치로 이동)
        if ((abs(cur.X - last.X) == 1 && cur.Y == last.Y) || (cur.X == last.X && abs(cur.Y - last.Y) == 1)) {
            // 요소를 한 칸씩 이동
            for (int a = teams[i].size() - 1; a >= 1; a--) {
                teams[i][a] = teams[i][a - 1];
            }
            teams[i][0] = last;  // 마지막 요소가 첫 번째로 이동

            // 보드 상태 갱신
            board[last.X][last.Y] = 1;  // 새로운 머리 위치
            board[teams[i][1].X][teams[i][1].Y] = 2;  // 두 번째 위치는 몸통
            board[teams[i][teams[i].size() - 1].X][teams[i][teams[i].size() - 1].Y] = 3;  // 마지막 위치는 꼬리
        } else {
            // 트랙이 다 차지 않은 경우: 한 칸씩 밀고 새로운 위치로 이동
            for (int a = teams[i].size() - 1; a >= 1; a--) {
                teams[i][a] = teams[i][a - 1];
            }

            // 첫 번째 요소의 새로운 위치를 찾아 설정
            for (int dir = 0; dir < 4; dir++) {
                int nx = cur.X + dx[dir];
                int ny = cur.Y + dy[dir];

                // 보드 밖으로 나가지 않으며, 빈 공간(4)인 경우 이동
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && board[nx][ny] == 4) {
                    teams[i][0] = {nx, ny};
                    board[nx][ny] = 1;  // 첫 번째 위치 갱신
                    break;
                }
            }

            // 이전 첫 번째 좌표는 2로 설정 (머리 부분의 이전 위치)
            board[cur.X][cur.Y] = 2;    
            board[last.X][last.Y] = 4;  // 마지막 좌표는 빈 공간으로 설정

            // 마지막 위치는 꼬리로 갱신
            board[teams[i][teams[i].size() - 1].X][teams[i][teams[i].size() - 1].Y] = 3;
        }
    }
}



void print_board(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void add_score(int row, int column) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < teams[i].size(); j++) { 
            if (make_pair(row, column) == teams[i][j]) {
                scores[i] += (j + 1) * (j + 1);  // 점수 계산
                reverse(teams[i].begin(), teams[i].end());  // 팀 순서 역전
                
                // 보드 상태 갱신
                board[teams[i][0].X][teams[i][0].Y] = 1;  // 새로운 머리 위치
                int size = teams[i].size() - 1;
                board[teams[i][size].X][teams[i][size].Y] = 3;  // 새로운 꼬리 위치
                return;
            }
        }
    }
}


void hit(int turn){
    turn = (turn - 1) % (4 * n) + 1; // turn 값을 1부터 n까지의 범위로 변환
    if(turn <= n){
        int row = turn;
        for(int i=1;i<=n;i++){
            if(board[row][i]!=4&&board[row][i]!=0){
                add_score(row,i);
                return;
            }
        }
    }
    else if(turn <= 2 * n){
        int column = turn - n;
        for(int i=n;i>=1;i--){
            if(board[i][column]!=4&&board[i][column]!=0){
                add_score(i,column);
                return;
            }
        }
    }
    else if(turn <= 3 * n){
        int row = turn - 2 * n;
        for(int i=n;i>=1;i--){
            if(board[n+1-row][i]!=4&&board[n+1-row][i]!=0){
                add_score(n+1-row,i);
                return;
            }
        }
    }
    else {
        int column = turn - 3 * n;
        for(int i=1;i<=n;i++){
            if(board[i][n+1-column]!=4&&board[i][n+1-column]!=0){
                add_score(i,n+1-column);
                return;
            }
        }
    }
}


void simulate(){


    for(int i=1;i<=k;i++){
        move();
        hit(i);
        // print_board();

    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>board[i][j];
        }
    }

    find_locs();
    // move();

    
    // cout<<teams[0][0].first<<'\n';
    // for(int i=0;i<m;i++){
    //     for(auto e:teams[i]){
    //         cout<<e.first<<" "<<e.second<<'\n';
    //     }
    //     cout<<'\n';
    // }
    simulate();
    // print_board();
    // hit(1);
    // for(int i=0;i<m;i++)cout<<scores[i]<<" ";

    // simulate();
    for(auto e : scores) result+=e;
    cout<<result;
}