#include <iostream>
#include <queue>
#include <tuple>

#define MAX_N 29
#define DIR_NUM 4

using namespace std;

int n;
int arr[29][29];
int next_arr[29][29];

int group_n;

int group[29][29];
int group_cnt[MAX_N*MAX_N+1];

bool visited[29][29];

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool inRange(int x, int y){
    return 0<=x && x<n && 0<=y && y<n;
}

void dfs(int x,int y){
    for(int i=0;i<4;i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(inRange(nx,ny) && !visited[nx][ny] && arr[nx][ny]==arr[x][y]){
            visited[nx][ny] = 1;
            group[nx][ny] = group_n;
            group_cnt[group_n]++;
            dfs(nx,ny);
        }
    }
}

void makeGroup(){
    group_n = 0;

    for(int i=0;i<n;i++) fill(visited[i],visited[i]+n,0);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(!visited[i][j]){
                group_n++;
                visited[i][j] = 1;
                group[i][j] = group_n;
                group_cnt[group_n] = 1;
                dfs(i,j);
            }
        }
}

int getArtScore(){
    int art_score = 0;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<4;k++){
                int nx = i +dx[k], ny = j + dy[k];
                if(inRange(nx,ny) && arr[i][j]!=arr[nx][ny]){
                    int g1 = group[i][j], g2 = group[nx][ny];
                    int num1 = arr[i][j], num2 = arr[nx][ny];
                    int cnt1 = group_cnt[g1], cnt2 = group_cnt[g2];
                    art_score += (cnt1 + cnt2) * num1 * num2;
                } 
            }
            
    return art_score / 2;
}

int getScore(){
    makeGroup();

    return getArtScore();
}

void RotateSquare(int sx, int sy, int square_n) {
    // 정사각형을 시계방향으로 90' 회전합니다.
    for(int x = sx; x < sx + square_n; x++)
        for(int y = sy; y < sy + square_n; y++) {
            int ox = x - sx, oy = y - sy;
            int rx = oy, ry = square_n - ox - 1;
            next_arr[rx + sx][ry + sy] = arr[x][y];
        }
}

void rotate() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            next_arr[i][j] = 0;
    

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            if(j == n / 2)
                next_arr[j][i] = arr[i][j];
            else if(i == n / 2)
                next_arr[n - j - 1][i] = arr[i][j];
        }

    int sqaure_n = n / 2;
    RotateSquare(0, 0, sqaure_n);
    RotateSquare(0, sqaure_n + 1, sqaure_n);
    RotateSquare(sqaure_n + 1, 0, sqaure_n);
    RotateSquare(sqaure_n + 1, sqaure_n + 1, sqaure_n);
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            arr[i][j] = next_arr[i][j];
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>arr[i][j];
    
    int ans = 0;
    for(int i=0;i<4;i++){
        ans+=getScore();
        rotate();
    }
    cout<<ans;
    return 0;
}