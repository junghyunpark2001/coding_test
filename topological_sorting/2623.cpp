#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> adj[1002];
vector<int> result;
int id[1002];

int n, m;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    
    int no, u, v;
    for (int i = 0; i < m; i++) {
        cin >> no;
        if (no == 0) continue;
        cin >> u;
        no--;
        while (no--) {
            cin >> v;
            adj[u].push_back(v);
            id[v]++;
            u = v;
        }
    }
    
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (id[i] == 0) q.push(i);
    }
    
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        result.push_back(cur);
        for (auto nxt: adj[cur]) {
            if (--id[nxt] == 0) q.push(nxt);
        }
    }
    
    if (result.size() != n) cout << 0;
    else for (auto a: result) cout << a << '\n';

    return 0;
}
