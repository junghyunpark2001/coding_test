#include <iostream>
#include <queue>
#include <vector>


using namespace std;

vector<int> adj[100005];
int p[100005];

void dfs(int cur){
    for(int nxt : adj[cur]){
        if(p[cur]==nxt) continue;
        p[nxt] = cur;
        dfs(nxt);
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;
    
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        
    }
    dfs(1);
    for(int i=2;i<=n;i++) cout<<p[i] <<'\n';
}