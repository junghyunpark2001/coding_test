#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int r, c, k;
int board[105][105];
int board2[105][105];

int max_i = 3, max_j = 3;
int time_cnt = 0;

bool check_end() {
    return board[r - 1][c - 1] == k;
}

void copy_board() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            board[i][j] = board2[i][j];
        }
    }
}

void new_sort() {
    for (int i = 0; i < 100; i++) fill(board2[i], board2[i] + 100, 0);

    for (int i = 0; i < max_i; i++) {
        vector<pair<int, int>> count_vec;
        int cnt[101] = {0};

        for (int j = 0; j < max_j; j++) {
            if (board[i][j] != 0) cnt[board[i][j]]++;
        }

        for (int j = 1; j <= 100; j++) {
            if (cnt[j] > 0) count_vec.push_back({cnt[j], j});
        }

        sort(count_vec.begin(), count_vec.end());

        int idx = 0;
        for (auto& p : count_vec) {
            board2[i][idx++] = p.second;
            board2[i][idx++] = p.first;
            if (idx >= 100) break;
        }
        max_j = max(max_j, idx);
    }
}

void new_sort2() {
    for (int i = 0; i < 100; i++) fill(board2[i], board2[i] + 100, 0);

    for (int j = 0; j < max_j; j++) {
        vector<pair<int, int>> count_vec;
        int cnt[101] = {0};

        for (int i = 0; i < max_i; i++) {
            if (board[i][j] != 0) cnt[board[i][j]]++;
        }

        for (int i = 1; i <= 100; i++) {
            if (cnt[i] > 0) count_vec.push_back({cnt[i], i});
        }

        sort(count_vec.begin(), count_vec.end());

        int idx = 0;
        for (auto& p : count_vec) {
            board2[idx++][j] = p.second;
            board2[idx++][j] = p.first;
            if (idx >= 100) break;
        }
        max_i = max(max_i, idx);
    }
}

void simulate() {
    if (max_i >= max_j) {
        new_sort();
    } else {
        new_sort2();
    }
    copy_board();
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c >> k;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> board[i][j];

    if (check_end()) {
        cout << 0;
        return 0;
    }

    for (int i = 0; i < 100; i++) {
        simulate();
        time_cnt++;
        if (check_end()) break;
    }

    if (time_cnt == 100) cout << -1;
    else cout << time_cnt;
}
