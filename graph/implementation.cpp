#include <iostream>
using namespace std;


// 인접행렬
void directed_graph1(){
    int adj_matrix[10][10] = {};
    int v,e;
    cin>>v>>e;
    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj_matrix[u][v] = 1;
    }
}

void undirected_graph1(){
    int adj_matrix[10][10] = {};
    int v,e;
    cin>>v>>e;  
    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj_matrix[u][v] = 1;
        adj_matrix[v][u] = 1;
    }
}

// 인접리스트
void directed_graph2(){
    vector<int> adj[10];
    int v,e;
    cin>>v>>e;
    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }

}

void undirected_graph2(){
    vector<int> adj[10];
    int v,e;
    cin>>v>>e;
    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

}
