#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 이분 그래프 검사 함수
bool bipartite(vector<int> edges[], int v) {
    vector<int> vis(v + 1, 0); // 1-based indexing
    queue<int> q;
    
    for (int start = 1; start <= v; start++) {
        if (vis[start]) continue; // 이미 방문한 정점은 스킵
        q.push(start);
        vis[start] = 1; // 시작 노드는 색 1로 칠함
        
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            
            for (auto next : edges[cur]) {
                if (!vis[next]) { // 아직 방문하지 않은 노드
                    vis[next] = -vis[cur]; // 현재 노드와 다른 색으로 칠하기
                    q.push(next);
                } else if (vis[next] == vis[cur]) { 
                    return false; // 인접한 노드가 같은 색이면 이분 그래프가 아님
                }
            }
        }
    }
    return true; // 모든 노드가 이분 그래프 조건을 만족
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int k; // 테스트 케이스 수
    cin >> k;
    
    while (k--) {
        int v, e;
        cin >> v >> e; // 정점 수와 간선 수
        vector<int> edges[v + 1]; // 1-based indexing 사용
        
        for (int i = 0; i < e; i++) {
            int v1, v2;
            cin >> v1 >> v2;
            edges[v1].push_back(v2);
            edges[v2].push_back(v1);
        }
        
        if (bipartite(edges, v)) 
            cout << "YES\n";
        else 
            cout << "NO\n";
    }
    return 0;
}
