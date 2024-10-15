#include <iostream>
#include <algorithm>

using namespace std;

int n,m;
int arr[10];
bool isused[10];
int num[10];

void func(int k){ // 현재 k개까지 수를 택함
    if(k==m){
        for(int i=0;i<m;i++)
            cout<<num[arr[i]] << ' ';
        cout<<'\n';
        return;
    }
    int st = 0;
    if(k!=0) st = arr[k-1] + 1;
    for(int i=st;i<n;i++){
        if(!isused[i]){
            arr[k] = i;
            isused[i] = 1;
            func(k+1);
            isused[i] = 0;
        }
    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>num[i];
    sort(num,num+n);
    func(0);

}