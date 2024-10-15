#include <iostream>
#include <stack>
using namespace std;

int main(void){
    int n;
    cin>>n;
    stack<int> s;

    for(int i=0;i<n;i++){
        string st;
        cin>>st;
        if(st=="push"){
            int a;
            cin>>a;
            s.push(a);
        }
        else if(st=="top"&&s.size()!=0) cout<<s.top()<<"\n";
        else if(st=="top"&&s.size()==0) cout<<-1<<"\n";
        else if(st=="size")cout<<s.size()<<"\n";
        else if(st=="pop"&&s.size()!=0){cout<<s.top()<<"\n";s.pop();}
        else if(st=="pop"&&s.size()==0) cout<<-1<<"\n";
        else if(st=="empty") cout<<(s.size()==0)<<"\n";

    }
}