#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int n,c;
vector<int> network[101];
bool vis[100];

int bfs(){
    int result = 0;
    vis[1] = 1;
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(auto v : network[cur]){
            if(vis[v]) continue;
            q.push(v); vis[v]=1; result++;
        }

    }
    return result;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n>> c;
    for(int i=0;i<c;i++){
        int n1,n2;
        cin>>n1>>n2;
        network[n1].push_back(n2);
        network[n2].push_back(n1);

    }

    cout<<bfs()<<'\n';


}