#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int q,n,m;
int weight[2005][2005];
vector<int> id_available(30005,-1);

vector<pair<int, int>> adjList[2005]; // 인접 리스트 (정점, 가중치)

void addEdge(int u, int v, int weight) {
    adjList[u].emplace_back(v, weight); // u에서 v로 가는 가중치 엣지 추가
    adjList[v].emplace_back(u, weight); // v에서 u로 가는 가중치 엣지 추가 (무방향 그래프)
}
vector<int> dijkstra(int start);
void printt(int startVertex){
    vector<int> distances = dijkstra(startVertex);
        cout << "정점 " << startVertex << "에서의 최단 거리:\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << "정점 " << i << ": " << distances[i] << endl;
    }
}

vector<int> dijkstra2(int start){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> distance(n,INT_MAX);

    distance[start] = 0;
    pq.push({0,start});

    while(!pq.empty()){
        int cur_dist = pq.top().first;
        int cur_vertex = pq.top().second;
        pq.pop();
        if(cur_dist > distance[cur_vertex]) continue;

        for(const auto &edge: adjList[cur_vertex]){
            int next_vertex = edge.first;
            int next_dist = edge.second;

            int new_dist = cur_dist + next_dist;
            if(distance[next_vertex]>new_dist) {
                distance[next_vertex] = new_dist;
                pq.push({new_dist, next_vertex});
            }


        }
    }
    return distance;
}

vector<int> dijkstra(int start){
    vector<int> distance(n,INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 최소 힙

    distance[start] = 0;
    pq.push({0,start});

    while(!pq.empty()){
        int current_dist = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        if(current_dist > distance[current_vertex]) continue;

        for(const auto &edge : adjList[current_vertex]){
            int next_vertex = edge.first;
            int weight = edge.second;

            int new_dist = current_dist + weight;

            if(new_dist < distance[next_vertex]){
                distance[next_vertex] = new_dist;
                pq.push({new_dist, next_vertex}); // 새로운 거리를 힙에 추가

            }
        }
    }
    return distance;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> distances;
    cin>>q;
    for(int i=0;i<q;i++){
        int command;
        cin>>command;
        if(command == 100){
            cin>>n>>m;
            for(int j=0;j<m;j++){
                int v,u,w;
                cin>>v>>u>>w;
                addEdge(v,u,w);
            }
            distances = dijkstra(0);
        }
        else if(command == 200){
            int id, revenue, dest;
            cin >> id >> revenue >> dest;
            pq.push({distances[dest]-revenue,id});
            id_available[id] = dest;
        }
        else if(command == 300){
            int id;
            cin>>id;
            id_available[id] = -1;
        }
        else if(command == 400){
            while(!pq.empty()){
                int revenue = pq.top().first;
                int cur_id = pq.top().second;
                if(id_available[cur_id]==-1 || revenue > 0){pq.pop();continue;}
                id_available[cur_id] = -1;
                // cout<<revenue;
                cout<<"cur id is "<<cur_id<<'\n';
                pq.pop();
                break;
            }
            if(pq.empty()) cout<<-1;
        }
        else if(command == 500){
            int new_start;
            cin >> new_start;
            vector<pair<int,int>> tmp;
            while(!pq.empty()){
                tmp.push_back({abs(pq.top().first)+distances[id_available[pq.top().second]],pq.top().second});
                pq.pop();
            }
            distances = dijkstra(new_start);
            printt(new_start);
            for(auto e: tmp){
                pq.push({distances[id_available[e.second]]-e.first,e.second});
            }
            cout<<"pq size is "<<pq.size()<<'\n';
        }
    }

}
