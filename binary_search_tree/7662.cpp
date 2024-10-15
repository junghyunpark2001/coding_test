#include <iostream>
#include <set>

using namespace std;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int A;
    cin>>A;
    while(A--){
        int t;
        cin>>t;
        
        char n;
        int i;
        multiset<int> m;
        while(t--){
            cin>>n>>i;
            if(n=='I'){
                m.insert(i);
            }
            else if(n=='D'&&!m.empty()){
                if(i==1){
                    auto it = prev(m.end());
                    m.erase(it);
                }
                else{
                    
                    auto it = m.begin();
                    m.erase(it);
                }

            }
        }
        if(m.size()==0) cout<<"EMPTY\n";
        else{
            auto it1 = m.begin(), it2 = prev(m.end());
            cout<<*it2<<" "<<*it1<<"\n";
        }

    }

}