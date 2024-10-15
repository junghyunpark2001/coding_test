#include <iostream>
#include <algorithm>
#include <tuple>

#define MAX_N 20
#define MAX_M 400
#define DIR_NUM 4
#define EMPTY make_pair(401,401)
#define EMPTY_NUM 401

using namespace std;

int n,m,k;
int given_map[MAX_N][MAX_N];
int next_dir[MAX_M+1][DIR_NUM][DIR_NUM];

pair<int,int> player[MAX_N][MAX_N];
pair<int,int> next_player[MAX_N][MAX_N];

pair<int,int> contract[MAX_N][MAX_N];

int elapsed_time;

bool in_range(int x, int y){
    return 0<=x&&x<n&&0<=y&&y<n;
}

bool can_go(int x,int y,int target_num){
    if(!in_range(x,y)) return false;

    int contract_num;
    tie(contract_num, ignore) = contract[x][y];

    return contract_num == target_num;
}

tuple<int,int,int> next_pos(int x, int y, int cur_dir){
    int dx[DIR_NUM] = {-1,1,0,0};
    int dy[DIR_NUM] = {0,0,-1,1};

    int num;
    tie(num,ignore) = player[x][y];

    // case 1.
    // 독점 계약을 맺지 않은 공간이 있다면 이동
    for(int i=0;i<4;i++){
        int move_dir = next_dir[num][cur_dir][i];
        int nx = x + dx[move_dir], ny = y + dy[move_dir];

        if(can_go(nx,ny,EMPTY_NUM)) return make_tuple(nx,ny,move_dir);
    }

    // case 2.
    // 인접한 곳이 모두 독점계약이라면 본인 땅으로 이동
    for(int i=0;i<4;i++){
        int move_dir = next_dir[num][cur_dir][i];
        int nx = x + dx[move_dir], ny = y + dy[move_dir];
        
        if(can_go(nx, ny, num))
            return make_tuple(nx, ny, move_dir);
    }
}

void update(int x, int y, pair<int,int> new_player){
    if(next_player[x][y]>new_player) next_player[x][y]=new_player;
}

void move(int x,int y){
    int num, cur_dir;
    tie(num,cur_dir) = player[x][y];

    // step 1. 현재 플레이어의 다음 위치와 방향 구하기
    int nx, ny, move_dir;
    tie(nx,ny,move_dir) = next_pos(x,y,cur_dir);
    
    // step 2. 플레이어 옮기기
    update(nx,ny,make_pair(num,move_dir));

}

void dec_contract(int x,int y){
    int num, remaining_period;
    tie(num,remaining_period) = contract[x][y];

    if(remaining_period==1) contract[x][y] = EMPTY;
    else contract[x][y] = make_pair(num,remaining_period-1);

}

void add_contract(int x,int y){
    int num;
    tie(num,ignore) = player[x][y];
    contract[x][y] = make_pair(num,k);
}

void simulate(){
    // step 1. next_player 초기화
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            next_player[i][j] = EMPTY;
    
    // step 2. 각 플레이어들 한 칸씩 옮겨줌
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(player[i][j]!=EMPTY) 
                move(i,j);
    
    // step 3. next_grid 값을 grid로 옮겨줌
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            player[i][j] = next_player[i][j];
    
    // step 4. 남은 contract 기간 1씩 감소
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(contract[i][j]!= EMPTY) dec_contract(i,j);

    // step 5. 새로운 contract 갱신
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(player[i][j]!= EMPTY) add_contract(i,j);
}

bool end(){
    if(elapsed_time>=1000) return true;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(player[i][j]==EMPTY) continue;

            int num;
            tie(num,ignore)=player[i][j];
            if(num!=1) return false;
        }
        return true;
    }
}