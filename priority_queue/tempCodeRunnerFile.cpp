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
    int a = 0;
    while(!pq.empty()){
        if(a<2) result = result + pq.top();
        else result = 2*result + pq.top();
        pq.pop();
        a++;
    }
    cout<<result<<"\n";
}