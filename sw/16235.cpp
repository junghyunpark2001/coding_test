#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n,m,k;
int field[12][12];
int S2D2[12][12];
int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1,-1,1,-1,0,1};
vector<int> tree[12][12];
int n,m,k;

void run1(int x,int y){
    auto& v = tree[x][y];
    //int idx = 
}

void run2(int x, int y){

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            field[i][j] = 5;
            cin>>S2D2[i][j];
        }
    while(m--){
        int x,y,z;
        cin>>x>>y>>z;
        tree[x][y].push_back(z);
    }
    while(k--){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                run1(i,j);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                run2(i,j);
    }
}
