#include <iostream>

#define MAX_N 499

using namespace std;

int n;
int cur_x, cur_y;
int move_dir, move_num;
int ans = 0;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int grid[MAX_N][MAX_N];

int dust_ratio[4][5][5] = {
    {
        {0, 0, 2, 0, 0},
        {0, 10, 7, 1, 0},
        {5, 0, 0, 0, 0},
        {0, 10, 7, 1, 0},
        {0, 0, 2, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {2, 7, 0, 7, 2},
        {0, 10, 0, 10, 0},
        {0, 0, 5, 0, 0},
    },
    {
        {0, 0, 2, 0, 0},
        {0, 1, 7, 10, 0},
        {0, 0, 0, 0, 5},
        {0, 1, 7, 10, 0},
        {0, 0, 2, 0, 0},
    },
    {
        {0, 0, 5, 0, 0},
        {0, 10, 0, 10, 0},
        {2, 7, 0, 7, 2},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
    }
};

bool inRange(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) return true;
    return false;
}

void addDust(int x, int y, int dust) {
    // (x, y)에 dust만큼의 먼지 추가
    // 격자 범위를 벗어난다면 ans에 더해줌
    if (!inRange(x, y))
        ans += dust;
    // 아니라면 해당 칸에 더해줌
    else
        grid[x][y] += dust;
}

void move() {
    cur_x += dx[move_dir];
    cur_y += dy[move_dir];

    int added_dust = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int dust = grid[cur_x][cur_y] * dust_ratio[move_dir][i][j] / 100;
            addDust(cur_x + i - 2, cur_y + j - 2, dust);
            added_dust += dust;
        }
    }
    // a% 자리 먼지 추가
    addDust(cur_x + dx[move_dir], cur_y + dy[move_dir], grid[cur_x][cur_y] - added_dust);
    // 현재 칸의 먼지를 0으로 설정
    grid[cur_x][cur_y] = 0;
}

bool End() {
    return !cur_x && !cur_y;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    cur_x = n / 2;
    cur_y = n / 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    move_dir = 0;
    move_num = 1;

    while (!End()) {
        for (int i = 0; i < move_num; i++) {
            move();
            if (End()) break;
        }

        move_dir = (move_dir + 1) % 4;
        if (move_dir == 0 || move_dir == 2)
            move_num++;
    }

    cout << ans;

    return 0;
}
