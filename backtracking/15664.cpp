#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int arr[10];
int num[10];


void func(int k, int st){
    if(k==m){
        for(int i=0;i<m;++i)
            cout<<arr[i] <<' ';
        cout<<'\n';
        return;
    }
    int tmp = 0;
    for(int i=st;i<n;++i){
        if(tmp!=num[i]){
            arr[k] = num[i];
            tmp = arr[k];
            func(k+1,i+1);
        }
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=0;i<n;++i){
        cin>>num[i];
    }
    sort(num,num+n);
}