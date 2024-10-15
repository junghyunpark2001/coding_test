#include <iostream>
#include <tuple>
#include <queue>
#include <climits>

#define MAX_N 15
#define MAX_M 30
#define DIR_NUM 4
#define EMPTY make_pair(-1,-1)

using namespace std;

int n,m;

// 0이면 빈칸, 1이면 베이스 캠프, 2라면 아무도 갈 수 없는 곳
int grid[MAX_N][MAX_N];

// 편의점 목록 관리
pair<int,int> cvs_list[MAX_M];

// 현재 사람들의 위치 관리
pair<int,int> people[MAX_M];

// 현재 시간을 기록
int curr_t;

// dx,dy값을 문제에서의 우선수위 순으로 표기
int dx[DIR_NUM] = {-1,0,0,1};
int dy[DIR_NUM] = {0,-1,1,0};

// bfs에 사용되는 변수
int step[MAX_N][MAX_N]; // 최단거리 결과 기록
bool visited[MAX_N][MAX_N]; // 방문 여부 표시

// (x,y) 가 격자 내에 있는 좌표인지 판단
bool InRange(int x, int y){
    return x >=0 && x<n && y>=0 && y<n;
}

// (x,y)로 이동이 가능한지 판단
bool CanGo(int x, int y){
    // 범위를 벗어나지 않으면서, 방문했던 적이 없으면서, 이동 가능한 곳
    return InRange(x,y) && !visited[x][y] && grid[x][y]!=2;
}

// start_pos를 시작으로 하는 BFS 진행
// 시작점으로부터의 최단거리 결과는 step 배열에 기록
void BFS(pair<int,int> start_pos){
    // visited, step 값 전부 초기와
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            visited[i][j] = false;
            step[i][j] = 0;
        }
    queue<pair<int,int>> q;
    int sx = start_pos.first, sy = start_pos.second;
    q.push(start_pos);
    visited[sx][sy] = true;
    step[sx][sy] = 0;

    // BFS 진행
    while(!q.empty()){
        pair<int,int> curr_pos = q.front();
        q.pop();

        // 인접한 칸을 보며 아직 방문하지 않은 칸을 큐에 삽입
        int x = curr_pos.first, y = curr_pos.second;
        for(int i=0;i<DIR_NUM;i++){
            int nx = x + dx[i], ny = y + dy[i];
            //갈 수 있는 경우에만 진행
            if(CanGo(nx,ny)){
                visited[nx][ny] = true;
                step[nx][ny] = step[x][y] + 1;
                q.push(make_pair(nx,ny));
            }
        }
    }
}

// 시뮬레이션 진행
void Simulate(){
    // step 1. 격자에 있는 사람들에 한하여 편의점 방향을 향해 1칸 이동
    for(int i=0;i<m;i++){
        // 아직 격자 밖에 있는 사람이거나 편의점에 도착한 사람이라면 패스
        if(people[i]==EMPTY || people[i]==cvs_list[i]) continue;
        BFS(cvs_list[i]);

        int px, py;
        tie(px,py) = people[i];

        int min_dist = INT_MAX;
        int min_x = -1, min_y = -1;
        for(int j=0;j<DIR_NUM;j++){
            int nx = px+dx[j], ny = py+dy[j];
            if(InRange(nx,ny)&&visited[nx][ny]&&min_dist>step[nx][ny]){
                min_dist = step[nx][ny];
                min_x = nx; min_y = ny;
            }
        }

        // 우선순위가 가장 높은 위치로 한 칸 이동
        people[i] = make_pair(min_x,min_y);
    }

    // step 2. 편의점에 도착했다면 이동 불가능한 표시로 grid 값 2로 변경
    for(int i=0;i<m;i++){
        if(people[i]==cvs_list[i]){
            int px, py;
            tie(px,py) = people[i];
            grid[px][py] = 2;
        }
    }

    // step 3. 현재 시간 curr_t에 대해 curr_t<=m이라면 t번 사람이 베이스 캠프로 이동

    // curr_t가 m보다 크다면 패스
    if(curr_t>m) return;

    // step 3-1. 편의점으로부터 가장 가까운 베이스 캠프 고르기 위해 편의점을 시작으로 하는 BFS 진행
    BFS(cvs_list[curr_t-1]);

    // step 3-2. 편의점으로부터 가장 가까운 베이스 캠프 선택
    int min_dist = INT_MAX;
    int min_x = -1, min_y = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(visited[i][j]&&grid[i][j]==1&&min_dist>step[i][j]){
                min_dist = step[i][j];
                min_x = i; min_y = j;
            }
        }
    }
    // 우선순위가 가장 높은 베이스 캠프로 이동
    people[curr_t-1] = make_pair(min_x,min_y);
    grid[min_x][min_y] = 2;
}

// 전부 편의점에 도착했는지 확인
bool End(){
    for(int i=0;i<m;i++){
        if(people[i]!=cvs_list[i])
            return false;
    }
    return true;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>grid[i][j];
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        cvs_list[i] = make_pair(x-1,y-1);
    }

    for(int i=0;i<m;i++) people[i] = EMPTY;

    while(true){
        curr_t++;
        Simulate();
        if(End()) break;
    }
    cout<<curr_t;
    return 0;
}