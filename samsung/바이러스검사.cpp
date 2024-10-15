#include <iostream>

using namespace std;

int n;
int people[1000005];
int m1,m2;
int result = 0;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++) cin>>people[i];
    cin>>m1>>m2;
    result += n;
    for(int i=0;i<n;++i){
        people[i] -= m1;
        if(people[i]<0) people[i]=0;
        if(people[i]%m2==0) result+=(people[i]/m2);
        else result += (people[i]/m2+1);
        
    }
    cout<<result;
}