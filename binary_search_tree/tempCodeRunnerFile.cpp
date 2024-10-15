#include <iostream>
#include <set>
#include <map>

using namespace std;

multiset<int> ms;
map<int,int> mp;
int n,k;
int result = 0;
int main(void){
    cin>>n>>k;
    while(n--){
        int m,v;
        cin>>m>>v;
        mp[v] = m;
    }
    while(k--){
        int c;
        cin>>c;
        ms.insert(c);
    }

    auto it = prev(mp.end());

    while(true){
        int M = it->second;

        auto it2 = ms.lower_bound(M);
        if(it2!=ms.end()){
            result += it->first;
            ms.erase(it2);
        }
        if(it==mp.begin()) break;
        it--;
    }

    cout<<result<<"\n";
}