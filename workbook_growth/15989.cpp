#include <iostream>

using namespace std;
int t,n;
int dp[10005];

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>t;

    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 2;
    for(int i=4;i<=10000;i++) dp[i] = dp[i-1] + 1;

    for(int i=0;i<n;i++){
        cin>>n;

    }
    
}