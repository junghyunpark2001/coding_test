#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, q;
int dart[52][52];
bool vis[52][52];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void print_dart() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << dart[i][j] << " ";
        }
        cout << '\n';
    }
}

void rotate(int x, int d, int k) {
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        if (i % x == 0) v.push_back(i);
    }
    if (d == 0) {
        // 시계방향
        for (auto e : v) {
            vector<int> tmp(m + 1);
            for (int j = 1; j <= m; j++) tmp[j] = dart[e][j];
            for (int j = 1; j <= m; j++) dart[e][(j + k - 1) % m + 1] = tmp[j];
        }
    } else if (d == 1) {
        // 반시계방향
        for (auto e : v) {
            vector<int> tmp(m + 1);
            for (int j = 1; j <= m; j++) tmp[j] = dart[e][j];
            for (int j = 1; j <= m; j++) dart[e][(j - k - 1 + m) % m + 1] = tmp[j];
        }
    }
}

bool changed() {
    bool result = false;
    for (int i = 1; i <= n; i++) fill(vis[i], vis[i] + m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dart[i][j] == -1) continue;
            queue<pair<int, int>> qu;
            vector<pair<int, int>> v;
            qu.push({i, j});
            v.push_back({i, j});
            vis[i][j] = 1;
            while (!qu.empty()) {
                auto cur = qu.front(); qu.pop();
                for (int dir = 0; dir < 4; dir++) {
                    int nx = cur.first + dx[dir];
                    int ny = cur.second + dy[dir];
                    if (nx < 1 || nx > n) continue;
                    if (ny < 1) ny = m;
                    if (ny > m) ny = 1;
                    if (vis[nx][ny] || dart[nx][ny] != dart[cur.first][cur.second] || dart[nx][ny] == -1) continue;

                    qu.push({nx, ny});
                    vis[nx][ny] = 1;
                    v.push_back({nx, ny});
                }
            }
            if (v.size() > 1) {
                result = true;
                for (auto e : v) {
                    dart[e.first][e.second] = -1;
                }
            }
        }
    }
    return result;
}

void normalize() {
    int sum = 0, num = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dart[i][j] != -1) {
                sum += dart[i][j];
                num++;
            }
        }
    }
    if (num == 0) return;
    int avg = sum / num;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dart[i][j] != -1) {
                if (dart[i][j] > avg) dart[i][j]--;
                else if (dart[i][j] < avg) dart[i][j]++;
            }
        }
    }
}

void simulate() {
    while (q--) {
        int x, d, k;
        cin >> x >> d >> k;
        rotate(x, d, k);
        if (!changed()) normalize();
    }
}

int score() {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dart[i][j] != -1) result += dart[i][j];
        }
    }
    return result;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> dart[i][j];
        }
    }

    simulate();
    cout << score();
}
