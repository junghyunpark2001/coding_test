#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int board[16][16];
int copy_board[16][16];
int n, m, d;

// 적을 공격하는 함수
int kill(vector<int>& pos) {
    // copy_board에 board 복사
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            copy_board[i][j] = board[i][j];
        }
    }

    int kill_num = 0;

    // 적군이 이동하는 과정
    for (int t = 0; t < n; t++) {
        vector<pair<int, int>> kill_pos;

        // 각 궁수의 공격 대상 찾기
        for (int p : pos) {
            int min_dist = d + 1; // 최대 공격 거리 + 1
            int target_x = -1, target_y = -1;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (copy_board[i][j]) { // 적이 있는 경우
                        int dist = abs(n - i) + abs(p - j);
                        if (dist <= d) { // 공격 거리 안에 있는 경우
                            if (dist < min_dist || (dist == min_dist && j < target_y)) {
                                min_dist = dist;
                                target_x = i;
                                target_y = j;
                            }
                        }
                    }
                }
            }

            if (target_x != -1 && target_y != -1) {
                kill_pos.push_back({target_x, target_y});
            }
        }

        // 중복 제거 후 적 제거
        for (auto& p : kill_pos) {
            if (copy_board[p.first][p.second]) {
                copy_board[p.first][p.second] = 0;
                kill_num++;
            }
        }

        // 적 이동
        for (int i = n - 1; i > 0; i--) {
            for (int j = 0; j < m; j++) {
                copy_board[i][j] = copy_board[i - 1][j];
            }
        }
        for (int j = 0; j < m; j++) {
            copy_board[0][j] = 0;
        }
    }

    return kill_num;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> d;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    vector<int> v(m, 0);
    v[m - 3] = 1;
    v[m - 2] = 1;
    v[m - 1] = 1;

    int result = 0;

    // 모든 궁수 배치 조합 탐색
    do {
        vector<int> pos;
        for (int i = 0; i < m; i++) {
            if (v[i]) pos.push_back(i);
        }
        result = max(result, kill(pos));
    } while (next_permutation(v.begin(), v.end()));

    cout << result << '\n';
    return 0;
}
