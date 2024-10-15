#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


int t;
int max_weight(int n, vector<int>& v){
    int result = 0;

    for(int i=0;i<n/4;++i){
        cout<<n<<'\n';
        int a = v[4*i];
        int b = v[4*i+1];
        int c = v[4*i+2];
        int d = v[4*i+3];
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<'\n';
        result += 2*(d-a);
    }
    return result;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> v;
        for(int i=0;i<n;i++){

            int rr;
            cin>>rr;
            v.push_back(rr);
        }
        sort(v.begin(),v.end());
        cout<< max_weight(n,v)<<'\n';
    
    }

    

}