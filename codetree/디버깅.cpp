#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <tuple>

#define MAX_H 30
#define MAX_N 10

using namespace std;

int n,m,h;
int line[MAX_H+1][MAX_N+1];

int num[MAX_N+1];

vector<pair<int,int>> candidates;

int ans = INT_MAX;

bool possible(){
    // 유실 선끼리 이어져 있으면 불가능
    for(int a=1;a<=h;a++)
        for(int b=2;b<n;b++)
            if(line[a][b]&&line[a][b-1])
                return false;
    for(int i=1;i<=n;i++)  
        num[i] = i;
    
    for(int a=1;a<=h;a++)
        for(int b=1;b<n;b++)
            if(line[a][b])
                swap(num[b],num[b+1]);
    for(int i=1;i<=n;i++)
        if(num[i]!=i)
            return false;
    
    return true;

}

void find_min(int cur_idx, int cnt){
    if(cnt>=ans)
        return;
    
    if(possible())
        ans = min(ans,cnt);
    
    if(cnt==3 || cur_idx == (int)candidates.size())
        return;
    
    find_min(cur_idx+1,cnt);
    
    int a,b;
    tie(a,b) = candidates[cur_idx];
    line[a][b] = true;
    find_min(cur_idx+1,cnt+1);
    line[a][b] = false;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>h;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        line[a][b] = true;
    }

    for(int i=1;i<=h;i++)
        for(int j=1;j<n;j++)
            if(!line[i][j])
                candidates.push_back(make_pair(i,j));

    find_min(0,0);

    if(ans==INT_MAX) ans=-1;

    cout<<ans;

    return 0;

}