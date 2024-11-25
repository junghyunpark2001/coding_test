#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

#define MAX_NODE 52
#define INF 1e9

// 용량 배열
int capacity[MAX_NODE][MAX_NODE];

// 유량 배열
int flow[MAX_NODE][MAX_NODE];

// BFS 탐색 시, 인접한 노드 확인을 위한 배열
vector<int> neighbor_node[MAX_NODE];

// BFS 탐색 시, 방문했던 노드 기록을 위한 배열
int visited[MAX_NODE];

// 최대 유량 결과
int result_max_flow;

int ctoi(char c){
    if(c<='Z'){
        return c - 'A';
    }
    return c - 'a' + 26;
}

int maximum_flow(int source_node, int sink_node){
    // source에서 sink까지의 증가경로가 없을 때까지 반복
    while(1){
        // 방문 노드를 배열 -1로 초기화
        memset(visited, -1, sizeof(visited));
        //BFS 탐색시 사용되는 queue
        queue<int> q;
        // source를 queue에 삽입
        q.push(source_node);

        // source에서 sink까지 BFS 탐색이 끝날 때까지 반복
        while(!q.empty()){
            int current_node = q.front();
            q.pop();
            for(int i=0;i<neighbor_node[current_node].size();++i){
                int next_node = neighbor_node[current_node][i];
                if((capacity[current_node][next_node] - flow[current_node][next_node] > 0 && (visited[next_node] == -1))){
                    q.push(next_node);
                    // 인접 노드가 현재 노드로부터 방문됐음을 기록
                    visited[next_node] = current_node;
                    if(next_node==sink_node) break;
                }
            }
            if(visited[sink_node]!=-1)break;
        }
        // BFS 탐색이 끝났음에도 불구하고, sink_node가 방문되지 않았다는 건
        // 더 이상 source->sink path가 없다는 의미이므로, 탐색 종료
        if(visited[sink_node] == -1) break;

        // source->sink path가 있는 경우
        int temp_max_flow = INF;
        int residual_capacity;
        // 방문 노드 배열을 역순으로 확인하며, 최대 유량 확인
        for(int i=sink_node; i!=source_node; i=visited[i]){
            // 이전 노드에서 다음 노드로 가는 유량 증가
            residual_capacity = capacity[visited[i]][i] - flow[visited[i]][i];
            // 최대 유량과 최소 비교 후 변환
            temp_max_flow = min(temp_max_flow, residual_capacity);
        }

        // 방문 노드 배열을 역순으로 탐색하며, 유량 증가
        for(int i=sink_node; i!=source_node; i=visited[i]){
            // 이전 노드에서 다음 노드로 가는 유량 증가
            flow[visited[i]][i] += temp_max_flow;
            flow[i][visited[i]] -= temp_max_flow;
        }
        result_max_flow += temp_max_flow;
    }
    return result_max_flow;


}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    // 간선 개수 입력
    int edge_count;
    cin >> edge_count;

    // 간선 및 용량 입력
    char start_node, end_node;
    int input_capacity;
    for(int i = 0; i < edge_count; i++){
        int n1,n2,c;
        cin>>start_node>>end_node>>input_capacity;
        start_node = ctoi(start_node);
        end_node = ctoi(end_node);

        neighbor_node[start_node].push_back(end_node);
        neighbor_node[end_node].push_back(start_node);

        capacity[start_node][end_node] += input_capacity;
        capacity[end_node][start_node] += input_capacity;
    }

    cout << maximum_flow(ctoi('A'),ctoi('Z'))<<'\n';

}