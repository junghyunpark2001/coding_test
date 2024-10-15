#include <iostream>
#include <vector>
using namespace std;

int n,l;
int board[105][105];
int result = 0;



bool available(vector<int> v){

    vector<int> s(n,0);
    for(int i=1;i<n;i++){
        if(v[i]==v[i-1]) continue;
        if(v[i]-v[i-1]==1){
            if((i-l)<0) return false;
            if(s[i-1]==1) return false;
            s[i-1] = 1;
            for(int a=2;a<=l;a++){
                if(s[i-a]==1) return false;
                s[i-a] = 1;
                if(v[i-a]!=v[i-1]) return false;
            }
        }
        if(v[i-1]-v[i]==1){
            if(i+l-1>=n) return false;
            for(int a=0;a<l;a++){
                if(s[i+a]==1) return false;
                s[i+a] = 1;
                if(v[i+a]!=v[i]) return false;
            }
        }
        if(abs(v[i]-v[i-1])>1) return false;
    }
    return true;
}

void simulate(){
    for(int i=0;i<n;i++){
        vector<int> v;
        for(int j=0;j<n;j++){
            v.push_back(board[i][j]);
        }
        // cout<<available(v);
        if(available(v)) result++;
    }
    for(int i=0;i<n;i++){
        vector<int> v;
        for(int j=0;j<n;j++){
            v.push_back(board[j][i]);
        }
        // cout<<available(v);
        if(available(v)) result++;
    }
}


int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>l;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>board[i][j];
    simulate();
    cout<<result;
}