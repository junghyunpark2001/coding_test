#include <iostream>
#include <stack>

using namespace std;

vector<int> adj1[10];
bool vis1[10];
void dfs1(){
    stack<int> s;
    s.push(1);
    vis1[1] = true;
    while(!s.empty()){
        int cur = s.top();
        s.pop();
        cout<<cur<<' ';
        for(auto nxt : adj1[cur]){
            if(vis1[nxt]) continue;
            s.push(nxt);
            vis1[nxt] = true;
        }
    }
}

vector<int> adj2[10];
bool vis2[10];
void dfs2(int cur){
    vis2[cur] = true;
    cout<<cur<<' ';
    for(auto nxt:adj2[cur]){
        if(vis2[nxt]) continue;
        dfs2(nxt);
    }
}

vector<int> adj3[10];
bool vis3[10];
void dfs3(){
    stack<int> s;
    s.push(1);
    while(!s.empty()){
        int cur = s.top();
        s.pop();
        if(vis3[cur]) continue;
        vis3[cur] = true;
        cout<<cur<<' ';
        for(auto nxt : adj3[cur]){
            if(vis3[nxt]) continue;
            s.push(nxt);
        }
    }
}


int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
}