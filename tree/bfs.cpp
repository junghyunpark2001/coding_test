#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<int> adj[10];
int p[10];
void bfs(int root){
    queue<int> q;
    q.push(root);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        cout<<cur<<' ';
        for(int nxt:adj[cur]){
            if(p[cur]==nxt) continue;;
            q.push(nxt);
            p[nxt] = cur;
        }
    }
}

vector<int> adj2[10];
int p2[10];
int depth2[10];
void dfs(int cur){
    cout<<cur<<' ';
    for(int nxt: adj2[cur]){
        if(p2[cur]==nxt) continue;
        depth2[nxt] = depth2[cur] + 1;
        dfs(nxt);
    }
} 

vector<int> adj3[10];
void dfs2(int cur, int par){
    cout<<cur<<' ';
    for(int nxt:adj3[cur]){
        if(par==nxt) continue;
        dfs2(nxt,cur);
    }
}