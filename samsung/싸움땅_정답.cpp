#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4
#define Player tuple<int,int,int,int,int,int>
#define EMPTY make_tuple(-1,-1,-1,-1,-1,-1)

using namespace std;

int n,m,k;

// 각 칸에 총 목록 관리
vector<int> gun[MAX_N][MAX_N];

// 각 칸에 플레이어 정보 관리
// (num, x, y, d, s, a) 
// 공격력 a인 총
Player players[MAX_M];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

// 플레이어들의 포인트 정보 기록
int points[MAX_M];

bool in_range(int x, int y){
    return x>=0 && x<n && 0<=y && y<n;
}

tuple<int,int,int> get_next(int x,int y,int d){
    int nx = x + dx[d];
    int ny = y + dy[d];

    if(!in_range(nx,ny)){
        d = (d+2)%4;
        nx = x + dx[d];
        ny = y + dy[d];
    }
    return make_tuple(nx,ny,d);
}

// 해당 칸의 플레이어 반환
Player find_player(pair<int,int> pos){
    for(int i=0;i<m;i++){
        int x,y;
        tie(ignore,x,y,ignore,ignore,ignore) = players[i];
        if(pos==make_pair(x,y))
            return players[i];
    }
    return EMPTY;
}

void update(Player p){
    int num;

    for(int i=0;i<m;i++){
        int num_i;
        tie(num_i,ignore,ignore,ignore,ignore,ignore) = p;
        if(num_i==num){
            players[i] = p;
            break;
        }
    }
}

// 플레이어 p를 pos 위치로 이동
void move(Player p, pair<int,int> pos){
    int num,x,y,d,s,a;
    tie(num,x,y,d,s,a) = p;

    int nx,ny;
    tie(nx,ny) = pos;

    // 가장 좋은 총으로 갱신
    gun[nx][ny].push_back(a);
    sort(gun[nx][ny].begin(),gun[nx][ny].end(),greater<int>());
    a = gun[nx][ny][0];
    gun[nx][ny].erase(gun[nx][ny].begin());

    p = make_tuple(num,nx,ny,d,s,a);
    update(p);
}

// 진 사람 움직임 진행
void loser_move(Player p){
    int num,x,y,d,s,a;
    tie(num,x,y,d,s,a) = p;

    // 현재 위치에 총 내려놓음
    gun[x][y].push_back(a);

    // 빈 공간 찾아 이동
    for(int i = 0; i < 4; i++) {
        int ndir = (d + i) % 4;
        int nx = x + dx[ndir], ny = y + dy[ndir];
        if(in_range(nx, ny) && find_player(make_pair(nx, ny)) == EMPTY) {
            p = make_tuple(num, x, y, ndir, s, 0);
            move(p, make_pair(nx, ny));
            break;
        }
    }
}

// 결투 진행
void duel(Player p1, Player p2, pair<int,int> pos){
    int num1, d1, s1, a1;
    tie(num1, ignore, ignore, d1, s1, a1) = p1;

    int num2, d2, s2, a2;
    tie(num2, ignore, ignore, d2, s2, a2) = p2;
    // p1이 이긴 경우
    if(make_pair(s1 + a1, s1) > make_pair(s2 + a2, s2)) {
        points[num1] += (s1 + a1) - (s2 + a2);
        loser_move(p2);
        move(p1, pos);
    }
    // p2가 이긴 경우
    else {
        points[num2] += (s2 + a2) - (s1 + a1);
        loser_move(p1);
        move(p2, pos);
    }
}

void simulate(){
    for(int i=0;i<m;i++){
        int num, x, y, d, s, a;
        tie(num, x, y, d, s, a) = players[i];
    

        // step 1-1. 현재 플레이어 움직일 위치, 다음 위치, 방향 구하기
        int nx,ny,ndir;
        tie(nx,ny,ndir) = get_next(x,y,d);

        // 해당 위치 전 플레이어 정보
        Player next_player = find_player(make_pair(nx,ny));

        // 현재 플레이어의 위치, 방향 보정
        Player cur_player = make_tuple(num,nx,ny,ndir,s,a);
        update(cur_player);

        // step 2. 해당 위치오 이동
        // step 2-1. 플레이어 없다면 그대로 이동
        if(next_player==EMPTY) 
            move(cur_player,make_pair(nx,ny));
        // step 2-2. 결투
        else    
            duel(cur_player, next_player, make_pair(nx,ny));
    }
}

int main() {
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            int num;
            cin >> num;

            // 총이 놓여 있는 .
            if(num != 0)
                gun[i][j].push_back(num);
        }

    for(int i = 0; i < m; i++) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        players[i] = make_tuple(i, x - 1, y - 1, d, s, 0);
    }

    while(k--)
        simulate();
    
    for(int i = 0; i < m; i++)
        cout << points[i] << " ";
    return 0;
}