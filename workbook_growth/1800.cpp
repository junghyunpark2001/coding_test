#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N,P,K;
vector<pair<int,int>> graph[10005];
int dist[10005];

bool dijkstra(int x){
    priority_queue<pair<int,int>> pq;
    pq.push(make_pair(0,1));

    while(!pq.empty()){
        int cnode = pq.top().second;
        int cweight = -1 * pq.top().first;

        pq.pop();

        if(dist[cnode] < cweight) continue;

        for(int i=0;i<graph[cnode].size();i++){
			int nnode = graph[cnode].at(i).first;
			int nweight = graph[cnode].at(i).second;

            int w = cweight + (nweight>x);

            if(dist[nnode] > w){
                dist[nnode] = w;
                pq.push(make_pair(-1*w, nnode));
            }
        }
    }
    return dist[N] <= K;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>N>>P>>K;

    for(int i=0;i<P;i++){
        int n1,n2,price;
        cin>>n1>>n2>>price;
        graph[n1].push_back(make_pair(n2,price));
        graph[n2].push_back(make_pair(n1,price));   
    }

    int l=0, r=1e7, ans=-1;

    while(l<=r){
        int mid = (l + r) >> 1;
        memset(dist, 0x3f, sizeof dist);
        dist[1] = 0;

        if(dijkstra(mid)){
            r = mid - 1;
            ans = mid;
        }
        else{
            l = mid + 1;
        }

    }
    cout<<ans;


}