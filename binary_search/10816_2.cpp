#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
int a[500002];

int lower_idx(int target, int len){
    int st = 0;
    int en = len-1;
    while(st<en){
        int mid = (st+en)/2;
        if(a[mid]>=target)en = mid;
        else st = mid+1;
    }
    return st;
    
}

int upper_idx(int target,int len){
    int st = 0;
    int en = len;
    while(st<en){
        int mid = (st+en)/2;
        if(a[mid]>target) en = mid;
        else st = mid+1;
    }
    return st;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    int m;
    cin>>m;
    while(m--){
        int t;
        cin>>t;
        cout<<upper_idx(t,n)-lower_idx(t,n)<<" ";
    }
    
}