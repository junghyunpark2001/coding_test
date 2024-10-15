#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> v;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        v.push_back(a);
    }
    sort(v.begin(),v.end());

    int result = 0;
    int add_result = 0;
    for(int i=0;i<v.size();i++){

        result += v[i];
        add_result += result;
        
    }
    cout<<add_result<<'\n';
}