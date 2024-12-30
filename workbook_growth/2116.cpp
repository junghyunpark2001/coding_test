#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int oppositeFace(int face) {
    if (face == 0) return 5;
    if (face == 1) return 3;
    if (face == 2) return 4;
    if (face == 3) return 1;
    if (face == 4) return 2;
    if (face == 5) return 0;
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> dice(n, vector<int>(6));

    // 주사위 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> dice[i][j];
        }
    }

    int maxSum = 0;

    // 첫 번째 주사위의 아랫면을 0~5로 설정
    for (int bottom = 0; bottom < 6; bottom++) {
        int sum = 0;
        int topValue = -1;

        // 각 주사위를 순차적으로 쌓음
        for (int i = 0; i < n; i++) {
            // 아랫면 값 계산
            int bottomValue = (i == 0) ? dice[0][bottom] : topValue;

            // 윗면 인덱스 찾기
            auto it = find(dice[i].begin(), dice[i].end(), bottomValue);
            if (it == dice[i].end()) {
                cerr << "Error: Value not found in dice[i]." << endl;
                return -1;
            }
            int topIndex = oppositeFace(it - dice[i].begin());
            topValue = dice[i][topIndex];

            // 옆면 중 최대값 계산
            int sideMax = 0;
            for (int j = 0; j < 6; j++) {
                if (j != (it - dice[i].begin()) && j != topIndex) {
                    sideMax = max(sideMax, dice[i][j]);
                }
            }
            sum += sideMax;
        }

        maxSum = max(maxSum, sum);
    }

    cout << maxSum << '\n';
    return 0;
}
