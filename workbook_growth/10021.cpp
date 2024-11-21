
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 2000 + 1;

typedef struct{
    int y, x;
}Coord;

typedef struct{
    int idx, idx2;
    int distance;
}Edge;

bool cmp(Edge a, Edge b){
    return a.distance < b.distance;
}

int parent[MAX];

int findParent(int idx){
    if(parent[idx]<0){
        return idx;
    }
    return parent[idx] = findParent(parent[idx]);
}

bool merge(int idx, int idx2){
    int idxParent = findParent(idx);
    int idx2Parent = findParent(idx2);

    if(idxParent == idx2Parent){
        return false;
    }

    parent[idx2Parent] = idxParent;

    return true;

}

int distance(Coord a, Coord b){
    return (b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x);
}



int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, C;
    cin>>N>>C;

    vector<Coord> v;
    vector<Edge> edges;
    
    for(int i=0;i<N;i++){
        int y,x;
        cin>>y>>x;

        v.push_back({y,x});

        for(int j=0;j<i;j++){
            int dist = distance(v[j], v[i]);
            if(dist >= C) edges.push_back({i,j,dist});
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    fill(parent,parent+N,-1);

    int result = 0, pipeCnt = 0;

    for(int i=0;i<edges.size();i++){
        if(merge(edges[i].idx, edges[i].idx2)){
            result += edges[i].distance;

            if(++pipeCnt == N-1) break;
        }
    }

    if(pipeCnt != N-1) cout<<-1<<'\n';

    else cout<<result<<'\n';

    return 0;
}