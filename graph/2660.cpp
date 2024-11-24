#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>


using namespace std;

int n;
vector<int> edges[51];
int scores[51];

int bfs(int n){
    vector<int> vis(51,0);
    vector<int> dist(51,0);
    vis[n] = 1;
    queue<int> q;
    q.push(n);
    
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(auto v : edges[cur]){
            if(vis[v]) continue;
            vis[v] = 1;
            dist[v] = dist[cur] + 1;
            q.push(v);
        }
    }

   return *(max_element(dist.begin(), dist.end()));
}



int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    while(true){
        int n1,n2;
        cin>>n1>>n2;
        if(n1==-1 && n2==-1) break;
        edges[n1].push_back(n2);
        edges[n2].push_back(n1);
        
    }


    for(int i=1;i<=n;i++){
        scores[i] = bfs(i);
    }

    int min_score = 10000;
    int min_num = 0;
    vector<int> min_people;
    for(int i=1;i<=n;i++) {min_score = min(min_score,scores[i]);}
    for(int i=1;i<=n;i++){
        if(scores[i]==min_score){
            min_num++;
            min_people.push_back(i);
        }
    }
    cout<<min_score<<" "<<min_num<<'\n';
    for(auto v:min_people) cout<<v<<" ";
    cout<<'\n';

}