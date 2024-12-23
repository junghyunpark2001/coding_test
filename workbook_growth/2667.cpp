#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n;
int board[26][26];
bool vis[26][26];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int bfs(int x, int y) {
    queue<pair<int, int>> q;
    vis[x][y] = 1;
    q.push({x, y});
    int count = 0; // 단지 내 집의 수

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        count++;

        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];

            // 유효 범위를 벗어나거나 이미 방문했거나, 집이 없는 곳은 무시
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (vis[nx][ny] || board[nx][ny] == 0) continue;

            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            board[i][j] = row[j] - '0';
        }
    }

    vector<int> complex_sizes; // 각 단지의 크기 저장

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!vis[i][j] && board[i][j] == 1) {
                int size = bfs(i, j);
                complex_sizes.push_back(size);
            }
        }
    }

    // 각 단지의 크기를 오름차순으로 정렬
    sort(complex_sizes.begin(), complex_sizes.end());

    // 총 단지 수 출력
    cout << complex_sizes.size() << "\n";

    // 각 단지의 크기 출력
    for (int size : complex_sizes) {
        cout << size << "\n";
    }

    return 0;
}
