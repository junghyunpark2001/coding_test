#include <iostream>

using namespace std;

int dp[10005][4];
int t;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    dp[0][1] = 1;
    for(int i = 1; i <= 10000; i++){
        dp[i][1] = dp[i-1][1];
        if(i>=2) dp[i][2] = dp[i-2][1] + dp[i-2][2];
        if(i>=3) dp[i][3] = dp[i-3][1] + dp[i-3][2] + dp[i-3][3];
    }
    
    cin>>t;
    int n;
    for(int i = 0; i < t; i++){
        cin >> n;
        cout << dp[n][1] + dp[n][2] + dp[n][3] <<'\n';
    }
}