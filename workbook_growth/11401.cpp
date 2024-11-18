#include <iostream>

using namespace std;

#define MOD 1000000007  // 모듈러 연산의 기준이 되는 값 (10^9 + 7)

// (n^k) % MOD를 효율적으로 계산하는 함수 (빠른 거듭제곱 알고리즘)
long long pow(long long n, long long k) {
    long long ret = 1;
    
    // 빠른 거듭제곱 (Exponentiation by Squaring)
    while (k) {
        if (k % 2) ret = (ret * n) % MOD;  // k가 홀수일 경우 n을 곱함
        n = (n * n) % MOD;  // n을 제곱하여 거듭제곱 수를 줄임
        k /= 2;  // k를 반으로 나눔
    }
    
    return ret;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    long long A = 1, B = 1;
    
    // A = n * (n-1) * ... * (n-k+1)
    for (int i = n; i >= n - k + 1; --i) A = (A * i) % MOD;
    // B = k!
    for (int i = 2; i <= k; ++i) B = (B * i) % MOD;
    
    // 올바른 pow 함수 사용
    cout << (A * pow(B, MOD - 2)) % MOD;
    
    return 0;
}
