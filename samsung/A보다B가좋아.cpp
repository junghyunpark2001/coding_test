
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int min_insertion(int n, const string &str) {

    int minBCount = 0;
    vector<int> prefixA(n + 1, 0);
    vector<int> prefixB(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        prefixA[i + 1] = prefixA[i] + (str[i] == 'A');
        prefixB[i + 1] = prefixB[i] + (str[i] == 'B');
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int countA = prefixA[j + 1] - prefixA[i];
            int countB = prefixB[j + 1] - prefixB[i];
            if (countA > countB) {
                minBCount += countA - countB;
                prefixB[j + 1] += countA - countB;
            }
        }
    }

    return minBCount;
}

int main() {
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; ++caseNum) {
        int len;
        string str;
        cin >> len >> str;
        int result = min_insertion(len, str);
        cout << "Case #" << caseNum << endl;
        cout << result << endl;
    }
    return 0;
}
