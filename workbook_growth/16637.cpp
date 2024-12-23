#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

int n;
string expression;
int answer = INT_MIN;

int applyOperator(char op, int a, int b){
    if(op=='+')
        return a + b;
    if(op=='-')
        return a - b;
    if (op == '*')
        return a * b;
    if(op=='/')
        return a / b;
    return 0;
}

void dfs(int index, int currentValue){
    // 수식의 끝에 도달한 경우 최댓값 갱신
    if(index>=n){
        answer = max(answer, currentValue);
        return;
    }

    // 현재 연산자와 다음 숫자 가져오기
    char op = expression[index];
    int nextNum = expression[index + 1] - '0';
    
    // 1. 괄호 없이 현재 연산 수행
    int newValue = applyOperator(op, currentValue, nextNum);
    dfs(index + 2, newValue);

    // 2. 괄호 추가
    if(index+2<n){
        int bracketValue = applyOperator(expression[index + 2], nextNum, expression[index + 3]-'0');
        newValue = applyOperator(op, currentValue, bracketValue);
        dfs(index + 4, newValue);
    }
}

int main(){
    cin >> n >> expression;
    dfs(1, expression[0] - '0');
    cout << answer << '\n';
    return 0;
}