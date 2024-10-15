#include <iostream>
#include <vector>
using namespace std;

vector<int> v;
int k,n;
int main() {
    // 여기에 코드를 작성해주세요.
    cin>>n>>k;
    for(int i=0;i<n;i++) {int r;cin>>r;v.push_back(r);}
    int result = 0;

    int diff= n-k;
    for(int i=0;i<=diff;i++){

        int sum = 0;
        for(int j = i;j<i+k;j++){ sum+=v[j];}
        if(sum>result) result = sum;
    }
    cout<<result;
    return 0;
}