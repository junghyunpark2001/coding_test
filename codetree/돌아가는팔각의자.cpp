#include <iostream>
#include <queue>
using namespace std;

string chair[5];
int chairs[5][8];
int k;


int dx[2] = {-1,1};
int dir[5];
int vis[5];

void rotate(int n, int d){
    int tmp[8] = {0,0,0,0,0,0,0,0};
    if(d==-1){
        for(int i=0;i<7;i++) tmp[i] = chairs[n][i+1];
        tmp[7] = chairs[n][0];
    }
    else if(d==1){
        for(int i=1;i<8;i++) tmp[i] = chairs[n][i-1];
        tmp[0] = chairs[n][7];
    }

    for(int i=0;i<8;i++) chairs[n][i] = tmp[i];
}
void simulate(int n,int d){
    fill(dir,dir+5,0);
    fill(vis,vis+5,0);
    queue<int> q;
    q.push(n);
    dir[n] = d;
    vis[n] = 1;

    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int d=0;d<2;d++){
            int nx = cur + dx[d];
            if(nx>4||nx<1) continue;
            if(vis[nx]) continue;
            if(d==0){
                if(chairs[cur][6]!=chairs[nx][2]){
                    q.push(nx);
                    dir[nx] = dir[cur] * -1;
                    vis[nx] = 1;
                }
            }
            else if(d==1){
                if(chairs[cur][2]!=chairs[nx][6]){
                    q.push(nx);
                    dir[nx] = dir[cur] * -1;
                    vis[nx] = 1;
                }
            }
        }
    }

    for(int i=1;i<5;i++){
        if(dir[i]!=0) rotate(i,dir[i]);
        
    }

}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    for(int i=1;i<=4;i++){
        cin>>chair[i];
    }
    for(int i=1;i<=4;i++){
        for(int j=0;j<8;j++){
            chairs[i][j] = int(chair[i][j])-48;
        }
    }
    cin>>k;
    for(int i=0;i<k;i++){
        int n, d;
        cin>>n>>d;
        simulate(n,d);
    }
    int result = 0;
    result = chairs[1][0] + 2*chairs[2][0] + 4*chairs[3][0] + 8*chairs[4][0];

    cout<<result;

    // for(int i=1;i<5;i++){
    //     for(int j=0;j<8;j++){
    //         cout<<chairs[i][j];
    //     }
    //     cout<<'\n';
    // }
}