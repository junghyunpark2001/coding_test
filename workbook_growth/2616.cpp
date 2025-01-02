#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> population(50005,0);



int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> population[i];
    cin >> m;

    vector<int> prefixSum(n + 1, 0);
    for (int i = 1; i <= n; i++){
        prefixSum[i] = prefixSum[i - 1] + population[i];
    }

    // dp[i][j]는 i번째 소형 기관차까지 사용하고 j번째 객차까지 고려했을 때 최대 승객 수
    vector<vector<int>> dp(4, vector<int>(n + 1, 0));

    for (int i = 1; i <= 3; i++){
        for (int j = 1 * m; j <= n; j++){
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - m] + (prefixSum[j] - prefixSum[j - m]));
        }
    }

    cout << dp[3][n] << '\n';

    return 0;
}