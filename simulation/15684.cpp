#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define X first
#define Y second

bool ladder[32][32];
int idxs[3];
vector<pair<int,int>> coords;
int n,m,h;

bool check(){
    for(int j=1;j<=n;j++){
        int cur = j;
        for(int i=1;i<=h;i++){
            if(ladder[i][cur-1])cur--;
            else if(ladder[i][cur])cur++;
        }
        if(cur!=j)return false;
    }
    return true;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>h;
    while(m--){
        int a,b;
        cin>>a>>b;
        ladder[a][b] = true;
    }

    for(int i=1;i<=h;i++)
        for(int j=1;j<n;j++){
            if(ladder[i][j-1]||ladder[i][j]||ladder[i][j+1]) continue;
            coords.push_back({i,j});
        }
    if(check()){
        cout<<0;
        return 0;
    }

    
    int ans = 0x7f7f7f7f;
    int sz = coords.size();
    for(int i=0;i<sz;i++){
        ladder[coords[i].X][coords[i].Y] = true;
        if(check()) ans =min(ans,1);
        
    }


}