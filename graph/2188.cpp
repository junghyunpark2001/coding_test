#include <iostream>
#include <vector>
#define MAX 201

using namespace std;

int n,m;
vector<int> cow[MAX];
int assign_cow[MAX]; // 배정된 소와 축사의 정보 저장
bool check[MAX];

bool dfs(int x){
    for(int i=0;i<cow[x].size();i++){
        int t = cow[x][i];
        if(check[t]) continue;
        check[t] = 1;
        if(assign_cow[t]
         == 0 || dfs(assign_cow[t])){
            assign_cow[t] = x;
            return true;
        }
    }
    return false;
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
   
    for(int i=1;i<=n;i++){
        int house_num;
        cin>>house_num;
        for(int j=0;j<house_num;j++){
            int house_num;
            cin>>house_num;
            cow[i].push_back(house_num);
        }
    }
    int count = 0;
    for(int i=1;i<=n;i++){
        fill(check,check+MAX,false);
        if(dfs(i)) count++;
    }
    cout<<count<<'\n';
    

}