#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

int n;
string expression;

int applyOperator(char op, int a, int b){
    if(op=='+')
        return a + b;
    if(op=='-')
        return a - b;
    if(op=='*')
        return a * b;
    return 0;
}

int calculateMaxValue(){
    vector<int> numbers;
    vector<char> operators;

    // 숫자와 연산자 분리
    for (size_t i = 0; i < expression.length(); ++i) {
        if (isdigit(expression[i])) {
            // 한 자리 숫자를 바로 추가
            numbers.push_back(expression[i] - '0');
        } else {
            // 연산자는 operators에 추가
            operators.push_back(expression[i]);
        }
    }


    int n = numbers.size();
    vector<vector<int>> dpMax(n, vector<int>(n, INT_MIN));
    vector<vector<int>> dpMin(n, vector<int>(n, INT_MAX));

    // 초기화 (i==j일 때 숫자 자체가 최댓값/최소값)
    for (int i = 0; i < n;i++){
        dpMax[i][i] = numbers[i];
        dpMin[i][i] = numbers[i];
    }

    // DP를 사용하여 부분 수식 계산
    for (int len = 1; len < n; ++len){ // 부분 수식 길이
        for (int i = 0; i < n - len; ++i){
            int j = i + len;
            for (int k = i; k < j; ++k){
                int maxLeft = dpMax[i][k];
                int maxRight = dpMax[k + 1][j];
                int minLeft = dpMin[i][k];
                int minRight = dpMin[k + 1][j];

                // 최댓값 계산
                dpMax[i][j] = max(dpMax[i][j], applyOperator(operators[k], maxLeft, maxRight));
                dpMax[i][j] = max(dpMax[i][j], applyOperator(operators[k], minLeft, minRight));
                dpMax[i][j] = max(dpMax[i][j], applyOperator(operators[k], maxLeft, minRight));
                dpMax[i][j] = max(dpMax[i][j], applyOperator(operators[k], minLeft, maxRight));

                // 최솟값 계산
                dpMin[i][j] = min(dpMin[i][j], applyOperator(operators[k], maxLeft, maxRight));
                dpMin[i][j] = min(dpMin[i][j], applyOperator(operators[k], minLeft, minRight));
                dpMin[i][j] = min(dpMin[i][j], applyOperator(operators[k], maxLeft, minRight));
                dpMin[i][j] = min(dpMin[i][j], applyOperator(operators[k], minLeft, maxRight));

            }
        }
    }
    return dpMax[0][n - 1];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    cin >> expression;

    int result = calculateMaxValue();
    cout << result << '\n';
}