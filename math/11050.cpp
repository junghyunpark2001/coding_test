#include <iostream>
#include <cmath>
using namespace std;


int n,k;
int N=1;
int K=1;
int NK = 1;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)N*=i;

    for(int i=1;i<=k;i++)K*=i;

    for(int i=1;i<=(n-k);i++)NK*=i;

    cout<<N/(K*NK);
}