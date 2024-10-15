#include <iostream>
#include <queue>

using namespace std;

vector <int> adj1[10];
bool vis1[10];
void bfs1(){
    queue<int> q;
    q.push(1);
    vis1[1] = true;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        cout<<cur<<' ';
        for(auto nxt: adj1[cur]){
            if(vis1[nxt]) continue;
            q.push(nxt);
            vis1[nxt] = true;
        }
    }
}

vector<int> adj2[10];
int dist[10];
void bfs2(){
    queue<int> q;
    fill(dist,dist+10,-1);
    q.push(1);
    dist[1] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(auto nxt:adj2[cur]){
            if(dist[nxt]!=-1)continue;
            q.push(nxt);
            dist[nxt] = dist[cur]+1;
        }
    }
}

vector<int> adj3[10];
int vis3[10];
int v = 9;
void bfs3(){
    queue<int> q;
    for(int i=0;i<=v;i++){
        
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
}