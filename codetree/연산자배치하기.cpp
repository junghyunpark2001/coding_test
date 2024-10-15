#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int n;
int arr[13];
int n1,n2,n3,n4;

int calculate(vector<int>& v){
    int result = arr[0];
    for(int i=1;i<n;i++){
        if(v[i-1]==0) result+=arr[i];
        else if(v[i-1]==1) result-=arr[i];
        else if(v[i-1]==2) result *= arr[i];
        else if(v[i-1]==3) result /= arr[i];
    }
    return result;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0;i<n;i++) cin>>arr[i];
    cin>>n1>>n2>>n3>>n4;

    vector<int> v;
    for(int i=0;i<n1;i++) v.push_back(0);
    for(int i=0;i<n2;i++) v.push_back(1);
    for(int i=0;i<n3;i++) v.push_back(2);
    for(int i=0;i<n4;i++) v.push_back(3);
    int min_sum = INT_MAX;
    int max_sum = -INT_MAX;
    do{
        min_sum = min(min_sum, calculate(v));
        max_sum = max(max_sum, calculate(v));

    }while(next_permutation(v.begin(),v.end()));

    cout<<min_sum<<" "<<max_sum;
}