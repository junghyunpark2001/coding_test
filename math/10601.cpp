#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    
    // 자릿수를 저장할 벡터와 자릿수 합을 계산할 변수
    vector<int> digits;
    long long sum = 0;
    bool has_zero = false;
    
    for(char c : s){
        digits.push_back(c - '0');
        sum += (c - '0');
        if(c == '0') has_zero = true;
    }
    
    // 30의 배수를 만들기 위한 조건 확인
    if(!has_zero || sum % 3 != 0){
        cout << "-1";
        return 0;
    }
    
    // 자릿수를 내림차순으로 정렬
    sort(digits.begin(), digits.end(), [](int a, int b) -> bool {
        return a > b;
    });
    
    // 정렬된 자릿수를 출력
    for(int digit : digits){
        cout << digit;
    }
    
    return 0;
}
