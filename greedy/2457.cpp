#include <iostream>
#include <tuple>
#include <vector>
using namespace std;


int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<pair<int,int>> flower;
    for(int i=0;i<n;i++){
        int sm,sd,em,ed;
        cin>>sm>>sd>>em>>ed;
        flower.push_back({sm*100+sd,em*100+ed});
    }

    int t = 301;
    int ans = 0;
    while(t<1201){
        int nxt_t = t;
        for(int i=0;i<n;i++){
            if(flower[i].first <= t && flower[i].second > nxt_t)
                nxt_t = flower[i].second;
        }
        if(nxt_t == t){
            cout<<0;
            return 0;
        }
        ans++;
        t = nxt_t;
    }
    cout<<ans;

}