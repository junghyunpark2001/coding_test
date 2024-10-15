#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
bool vis[1005];
vector<int> adj[1005];

int n,m;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    while(m--){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int num = 0;
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        num++;
        queue<int> q;
        q.push(i);
        vis[i] = 1;
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(auto nxt: adj[cur]){
                if(vis[nxt]) continue;
                q.push(nxt);
                vis[nxt] = 1;
            }
        }  
    }
    cout<<num;
}