#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    char op = '+';
    int result = 0;
    string tmp;
    for(int i=0;i<s.size();i++){
        if(s[i]!='-'&&s[i]!='+') tmp+=s[i];

        if(s[i]=='-'||s[i]=='+'||i==s.size()-1){
            if(op=='+') result += stoi(tmp);
            else if(op=='-') result -=stoi(tmp);
            
            tmp = "";
        }
        if(s[i]=='-'){
         
            op = '-';
        }  
 
    }
    cout<<result;
}