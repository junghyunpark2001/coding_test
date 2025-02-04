#include <iostream>
#include <vector>
using namespace std;

int n;
vector<pair<int,int>> v;
vector<int> result;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    
    for(int i = 0; i < n; i++){
        int x, y; // 몸무게, 키
        cin >> x >> y;
        v.push_back({x, y});
        
    }

    for(int i = 0; i < n; i++){
        int place = 1;
        for(int j = 0; j < n; j++){
            if(i == j){
                continue;
            }
            if(v[i].first < v[j].first && v[i].second < v[j].second){
                place++;
            }
        }
        result.push_back(place);
    }
    for(auto e : result)
        cout << e << " ";
}
