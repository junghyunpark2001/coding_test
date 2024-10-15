#include<iostream>
#include<algorithm>
using namespace std;

int n;
int a[102];
int b[102];
int ans;

bool inverse_sort(int a,int b){
    return a>b;
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];
    //0 1 1 1 6
    //8 7 3 2 1
    sort(a,a+n);
    sort(b,b+n,inverse_sort);
    for(int i=0;i<n;i++){
        ans+=a[i]*b[i];
    }
    cout<<ans<<"\n";
}
