#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define EMPTY make_tuple(0,0,0)
int n,m,k;

tuple<int,int,int> grid[103][103];
tuple<int,int,int> grid2[103][103];

int dx[5] = {0,-1,1,0,0};
int dy[5] = {0,0,0,1,-1};
int result = 0;
void move() {
    for(int i = 1; i <= n; i++) fill(grid2[i], grid2[i] + m + 1, EMPTY);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(grid[i][j] != EMPTY) {
                int s, d, b;
                tie(s, d, b) = grid[i][j];

                int nx = i + dx[d] * s;
                int ny = j + dy[d] * s;

                while(nx < 1 || nx > n || ny < 1 || ny > m) {
                    if(nx < 1) {
                        nx = 2 - nx;
                        d = 2;
                    } else if(nx > n) {
                        nx = 2 * n - nx;
                        d = 1;
                    } else if(ny < 1) {
                        ny = 2 - ny;
                        d = 3;
                    } else if(ny > m) {
                        ny = 2 * m - ny;
                        d = 4;
                    }
                }


                if(grid2[nx][ny] == EMPTY) {
                    grid2[nx][ny] = make_tuple(s, d, b);
                } else { 
                    int s2, d2, b2;    
                    tie(s2, d2, b2) = grid2[nx][ny];
                    if(b > b2) {
                        grid2[nx][ny] = make_tuple(s, d, b);
                    }     
                }
            }
        }              
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            grid[i][j] = grid2[i][j];
        }
    }
}

void simulate(){
    
    for(int i=1;i<=m;i++){
        // step 1. 채취

        for(int j=1;j<=n;j++){
            if(grid[j][i]!=EMPTY) {
                int s,d,b;
                tie(s,d,b) = grid[j][i];
                result+=b;
                grid[j][i] = EMPTY;

                break;
            }
            
        }
        
        // step 2. 곰팡이 이동
        move();
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=0;i<=n;i++) fill(grid[i],grid[i]+m+1,EMPTY);

    for(int i=0;i<k;i++){
        int x,y,s,d,b;
        cin>>x>>y>>s>>d>>b;
        grid[x][y] = make_tuple(s,d,b);

    }

    simulate();
    cout<<result;

}