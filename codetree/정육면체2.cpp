#include <iostream>
#include <utility>
#include <tuple>
#include <queue>

#define MAX_N 20
#define FACE_NUM 6
#define DIR_NUM 4
#define OUT_OF_GRID make_pair(-1,-1)

using namespace std;

int n,m;
int x,y;
int move_dir;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int grid[MAX_N+2][MAX_N+2];

queue<pair<int,int>> bfs_q;
bool visited[MAX_N+2][MAX_N+2];

int u=1,f=2,r=3;

int ans = 0;

bool in_range(int x,int y){
    return 0<=x && x<n && 0<=y && y<n;
}

bool can_go(int x,int y,int target_num){
    return in_range(x,y) && !visited[x][y] && grid[x][y] == target_num;
}

int BFS(int x,int y,int target_num){
    
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
}