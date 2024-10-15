#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m, k; // 격자크기, 플레이어수, 라운드수
vector<int> grid[22][22]; // 격자에 놓여진 총
int vis[22][22]; // 격자에 있는 플레이어 표시
tuple<int, int, int, int, int> players[32]; // 플레이어 정보
int extra_points[32]; // 추가 점수

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool in_range(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <=n;
}

bool collision(int x, int y) {
    return vis[x][y] >= 1;
}

void choose_gun(vector<int>& guns, int& my_gun) {
    for (int& gun : guns) {
        if (gun > my_gun) {
            swap(gun, my_gun);
        }
    }
}

void add_points(int winner, int diff) {
    extra_points[winner] += diff;
}

int who_is_winner(int p1, int p2) {
    int x1, y1, dir1, s1, g1;
    int x2, y2, dir2, s2, g2;
    tie(x1, y1, dir1, s1, g1) = players[p1];
    tie(x2, y2, dir2, s2, g2) = players[p2];
    
    int winner;
    if (s1 + g1 > s2 + g2) {
        winner = p1;
    } else if (s1 + g1 < s2 + g2) {
        winner = p2;
    } else {
        if (s1 > s2) {
            winner = p1;
        } else {
            winner = p2;
        }
    }
    int diff = abs((s1 + g1) - (s2 + g2));
    add_points(winner, diff);
    return winner;
}

void move(tuple<int, int, int, int, int>& p) {
    int x, y, dir, s, g;
    tie(x, y, dir, s, g) = p;
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    // 격자 벗어나면 반대로 한 칸 이동
    if (!in_range(nx, ny)) {
        dir = (dir + 2) % 4;
        nx = x + dx[dir];
        ny = y + dy[dir];
    }

    // 이동한 칸에 플레이어가 있는 경우
    if (collision(nx, ny)) {
        int origin_player = vis[nx][ny];
        int new_player = vis[x][y];
        int winner = who_is_winner(new_player, origin_player);

        if (winner == new_player) {
            vis[nx][ny] = new_player;
            vis[x][y] = 0;
        } else {
            vis[x][y] = 0;
        }

        choose_gun(grid[nx][ny], get<4>(players[winner]));

        int loser = (winner == new_player) ? origin_player : new_player;
        for (int dd = 0; dd < 4; dd++) {
            int nx2 = nx + dx[dir];
            int ny2 = ny + dy[dir];
            if (in_range(nx2, ny2) && !collision(nx2, ny2)) {
                vis[nx2][ny2] = loser;
                players[loser] = make_tuple(nx2, ny2, dir, get<3>(players[loser]), 0);
                break;
            }
            else{
                dir = (dir + 1) % 4;
                int nnx = nx + dx[dir];
                int nny = ny + dy[dir];
                if (in_range(nnx, nny) && !collision(nnx, nny)) {
                    vis[nnx][nny] = loser;
                    players[loser] = make_tuple(nnx, nny, dir, get<3>(players[loser]), 0);
                    break;
                }
            }

        }
    } else {
        vis[nx][ny] = vis[x][y];
        vis[x][y] = 0;
        choose_gun(grid[nx][ny], g);
        get<0>(p) = nx;
        get<1>(p) = ny;
        get<2>(p) = dir;
        get<4>(p) = g;
    }
}

int main() {
    cin >> n >> m >> k;
    for (int i = 1 ;i <=n; i++) {
        for (int j = 1; j <= n; j++) {
            int num;
            cin >> num;
            if (num > 0) {
                grid[i][j].push_back(num);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y, d, s; // 플레이어 위치, 방향, 초기 능력치
        cin >> x >> y >> d >> s;
        players[i] = make_tuple(x, y, d, s, 0);
        vis[x][y] = i;
    }
    cout<<'\n';
    for(int x=1;x<=n;x++){
        for(int y=1;y<=n;y++){
            cout<<vis[x][y]<<" ";
        }
        cout<<'\n';
    }
    cout<<'\n';
    

    for (int round = 0; round < k; round++) {
        for (int i = 1; i <= m; i++) {
            move(players[i]);
            for(int x=1;x<=n;x++){
                for(int y=1;y<=n;y++){
                    cout<<vis[x][y]<<" ";
                }
                cout<<'\n';
            }
            cout<<'\n';
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << extra_points[i] << " ";
    }
    cout << endl;

    return 0;
}
