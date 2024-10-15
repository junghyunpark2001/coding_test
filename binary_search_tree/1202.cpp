#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> jewels(n);
    multiset<int> bags;
    for (int i = 0; i < n; ++i) {
        cin >> jewels[i].second >> jewels[i].first; // store as (value, weight)
    }
    for (int i = 0; i < k; ++i) {
        int c;
        cin >> c;
        bags.insert(c);
    }

    // Sort jewels by value in descending order
    sort(jewels.begin(), jewels.end(), greater<pair<int, int>>());

    long long result = 0;

    for (auto& jewel : jewels) {
        int weight = jewel.second;
        int value = jewel.first;
        
        auto it = bags.lower_bound(weight);
        if (it != bags.end()) {
            result += value;
            bags.erase(it);
        }
    }

    cout << result << "\n";

    return 0;
}
