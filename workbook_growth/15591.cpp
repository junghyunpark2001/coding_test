#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

int N,Q;


vector<pair<int, int>> v[5000+1]; 

void dijkstra(int start, vector<vector<pair<int,int>>>& graph){
    vector<int> distance(N,INT_MAX);
    
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>N>>Q;
    for(int i=0;i<N-1;i++){
        int p,q,r;
        cin>>p>>q>>r;
        v[p].push_back({q,r});
        v[q].push_back({p,r});

    }

    for(int i=0;i<Q;i++){
        vector<bool> visit(5005,0);
        int ans = 0;
        int k,video;
        cin>>k>>video;
        queue<int> q;
        q.push(video);
        visit[video] = 1;
        while(!q.empty()){
            int now = q.front(); 
            q.pop();
            for(int j=0;j<v[now].size();j++){
                int next = v[now][j].first;
                if(visit[next]) continue;
                if(v[now][j].second>=k){
                    visit[next] = 1;
                    ans++;
                    q.push(next);
                }
            }
        }
        cout<<ans<<'\n';
        
    }

}