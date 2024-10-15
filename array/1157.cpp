#include <iostream>
#include <string>
#include <cctype> // std::toupper

int main() {
    std::string input;
    std::getline(std::cin, input); // 입력 문자열 받기

    int count[26] = {0}; // 알파벳 빈도수를 저장할 배열

    // 입력 문자열의 모든 문자를 대문자로 변환하고 빈도수 계산
    for (char& ch : input) {
        ch = std::toupper(static_cast<unsigned char>(ch)); // 대문자로 변환
        if (std::isalpha(ch)) { // 알파벳인 경우만 처리
            count[ch - 'A']++; // 빈도수 증가
        }
    }

    // 가장 빈도가 높은 알파벳 찾기
    int maxCount = 0;
    char maxChar = '?'; // 결과 초기값
    bool duplicate = false;

    for (int i = 0; i < 26; ++i) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            maxChar = 'A' + i;
            duplicate = false; // 새로운 최대 빈도 발견 시 중복 없음
        } else if (count[i] == maxCount) {
            duplicate = true; // 동일 최대 빈도 발견 시 중복 존재
        }
    }

    // 결과 출력
    if (duplicate) {
        std::cout << '?' << std::endl; // 중복일 경우 '?'
    } else {
        std::cout << maxChar << std::endl; // 가장 많이 등장한 알파벳 출력
    }

    return 0;
}
