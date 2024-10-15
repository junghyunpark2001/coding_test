#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

long long n;
string s;
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    
    vector<int> v;
    for(int i = 0; i < s.size(); i++) 
        v.push_back(s[i] - '0');
    
    sort(v.begin(), v.end(), greater<int>()); // 가장 큰 수부터 시작하도록 내림차순 정렬
    long long result = -1;

    do {
        long long tmp = 0;
        for(int i = 0; i < v.size(); i++) {
            tmp = tmp * 10 + v[i];  // tmp는 현재 순열의 수
        }
        if (tmp % 30 == 0) {  // 30으로 나눌 수 있는지 확인
            result = tmp;
            break;  // 첫 번째로 찾은 30의 배수가 가장 큽니다.
        }
    } while (prev_permutation(v.begin(), v.end())); // 큰 순열부터 시작

    cout << result;
}
