#include <iostream>
#include <cmath>
using namespace std;

int n,k;
int s[12];
int ans = 0;
int sum = 0;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>s[i];
    for(int i=n-1;i>=0;i--){
        if(s[i]<=k){
            int tmp = floor(k/s[i]);
   
            ans+=tmp;
            k = k%s[i];
        }
    }
    cout<<ans;

}