#include <iostream>
#include <queue>

using namespace std;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    int x;
    int result = 0;
    priority_queue<int,vector<int>,greater<int>> pq;
    while(n--){
        cin>>x;
        pq.push(x);
    }
    int ans = 0;
    while(pq.size()>1){
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        ans+= a+b;
        pq.push(a+b);
    }
    cout<<ans;
    
}