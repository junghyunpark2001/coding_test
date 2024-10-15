#include <iostream>
#include <algorithm>

using namespace std;

int n;
int board[105][105];
int dp[105][105][2];
pair<int,int> path[105][105];

int main(){
    cin>> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>board[i][j];

    int diff = 0;
    int upper = 0;
    dp[0][0][0] = board[0][0];
    dp[0][0][1] = board[0][0];
    for(int i=1;i<n;i++){
        dp[i][0][0] = min(board[i][0], dp[i-1][0][0]);
        dp[i][0][1] = max(board[i][0], dp[i-1][0][1]);
        path[i][0] = {i-1,0};
    }
    for(int i=1;i<n;i++){
        dp[0][i][0] = min(board[0][i], dp[0][i-1][0]);
        dp[0][i][1] =max(board[0][i], dp[0][i-1][1]);
        path[i][0] = {0,i-1};
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            int diff1 = abs(min(board[i][j],dp[i][j-1][0]) - max(board[i][j],dp[i][j-1][1]));
            int diff2 = abs(min(board[i][j],dp[i-1][j][0]) - max(board[i][j],dp[i-1][j][1]));
            if(diff1<diff2){
                dp[i][j][0] = min(board[i][j],dp[i][j-1][0]);
                dp[i][j][1] = max(board[i][j],dp[i][j-1][1]);
            }
            else{
                dp[i][j][0] = min(board[i][j],dp[i-1][j][0]);
                dp[i][j][1] = max(board[i][j],dp[i-1][j][1]);
            }
            
        }
    }
    cout<<dp[n-1][n-1][1]-dp[n-1][n-1][0];
}