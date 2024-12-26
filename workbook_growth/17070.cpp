#include <iostream>
#include <vector>

using namespace std;

int N;
int board[17][17];
int dp[17][17][3]; // 0: 가로, 1: 세로, 2: 대각선

int main() {
    cin >> N;

    // 입력받기
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> board[i][j];
        }
    }

    // 초기값 설정 (첫 파이프의 위치)
    dp[1][2][0] = 1;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (board[i][j] == 1) continue; // 벽이면 넘어감

            // 가로 -> 가로
            if (j - 1 > 0) dp[i][j][0] += dp[i][j - 1][0];

            // 대각선 -> 가로
            if (j - 1 > 0) dp[i][j][0] += dp[i][j - 1][2];

            // 세로 -> 세로
            if (i - 1 > 0) dp[i][j][1] += dp[i - 1][j][1];

            // 대각선 -> 세로
            if (i - 1 > 0) dp[i][j][1] += dp[i - 1][j][2];

            // 가로 -> 대각선
            if (i - 1 > 0 && j - 1 > 0 && board[i - 1][j] == 0 && board[i][j - 1] == 0)
                dp[i][j][2] += dp[i - 1][j - 1][0];

            // 세로 -> 대각선
            if (i - 1 > 0 && j - 1 > 0 && board[i - 1][j] == 0 && board[i][j - 1] == 0)
                dp[i][j][2] += dp[i - 1][j - 1][1];

            // 대각선 -> 대각선
            if (i - 1 > 0 && j - 1 > 0 && board[i - 1][j] == 0 && board[i][j - 1] == 0)
                dp[i][j][2] += dp[i - 1][j - 1][2];
        }
    }

    // 결과 출력 (세 방향의 합)
    cout << dp[N][N][0] + dp[N][N][1] + dp[N][N][2] << endl;

    return 0;
}
