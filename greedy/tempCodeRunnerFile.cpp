#include <iostream>
#include<algorithm>
using namespace std;

int n;
int ans = 0;
int weight;
int s[100002];
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0;i<n;i++)cin>>s[i];
    sort(s,s+n);
    for(int i=0;i<n;i++){
        weight = s[i] * (n-i);
        ans = max(ans,weight);
    }
    cout<<ans;
}