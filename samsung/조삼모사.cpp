#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

int p[22][22];
int n;
int result = INT_MAX;
int diff(vector<int>& v){
    int tmp = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(v[i]==1&&v[j]==1)tmp+=p[i][j];
            else if(v[i]==0&&v[j]==0) tmp-=p[i][j];
        }
    }
    return(abs(tmp));
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>p[i][j];
    vector<int> v(n);
    for (int i = 0; i < n / 2; ++i) v[i] = 1; // 초기화: n/2개의 1과 나머지 0

    sort(v.begin(),v.end());
    do{
        result = min(result, diff(v));
        
    }while(next_permutation(v.begin(),v.end()));
    cout<<result;
    

}