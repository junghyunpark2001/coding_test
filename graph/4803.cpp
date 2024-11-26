#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool is_tree(vector<int> edges[], int start, vector<int>& vis) {
    queue<int> q;
    q.push(start);
    vis[start] = 1; // 방문 처리
    int node_count = 0; // 노드 개수
    int edge_count = 0; // 간선 개수

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        node_count++; // 방문한 노드 개수 증가

        for (auto next : edges[cur]) {
            edge_count++; // 간선 개수 증가
            if (!vis[next]) {
                vis[next] = 1; // 방문 처리
                q.push(next);
            }
        }
    }

    edge_count /= 2; // 무방향 그래프이므로 간선이 양방향으로 기록됨

    // 트리 조건: 간선 개수 = 노드 개수 - 1
    return (edge_count == node_count - 1);
}

void tree_num(vector<int> edges[], int n) {
    int result = 0;
    vector<int> vis(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            // 연결 컴포넌트가 트리인지 확인
            if (is_tree(edges, i, vis)) {
                result++;
            }
        }
    }
    if(result == 0) cout <<"No trees.\n";
    else if(result == 1) cout<<"There is one tree.\n";
    else cout<<"A forest of "<<result<<" trees.\n";
}



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int test_case = 1;
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        vector<int> edges[n + 1];

        for (int i = 0; i < m; i++) {
            int n1, n2;
            cin >> n1 >> n2;
            edges[n1].push_back(n2);
            edges[n2].push_back(n1);
        }

        cout << "Case " << test_case++ << ": ";
        tree_num(edges, n);
    }

    return 0;
}