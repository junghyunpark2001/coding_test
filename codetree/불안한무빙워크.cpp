#include <iostream>
#include <deque>
using namespace std;

int n,k;
deque<int> up;
deque<int> down;
int person[105];

void simulate(){
    // step 1. rotate

    up.push_front(down[0]);

    down.push_back(up[n]);
    up.pop_back();
    down.pop_front();

    for (int i = n - 2; i >= 0; i--) {
        person[i + 1] = person[i];
    }
    person[0] = 0; // 첫 번째 위치에서 사람 없음
    person[n - 1] = 0;


    // step 2. people move
    for (int i = n - 2; i >= 0; i--) {
        if (person[i] == 1 && person[i + 1] == 0 && up[i + 1] > 0) {
            person[i + 1] = 1;
            person[i] = 0;
            up[i + 1]--;
        }
    }
    person[n - 1] = 0;

    if(up[0]>0){ 
        person[0] = 1;
        up[0]--;
    }
    // cout<<"t\n";
    // cout<<down[n-1]<<'\n';
    // for(int i=0;i<n;i++) cout<<person[i]<<" ";
    // cout<<'\n';
    // for(int i=0;i<up.size();i++) cout<<up[i]<<" ";
    // cout<<'\n';
    // for(int i=0;i<down.size();i++) cout<<down[i]<<" ";
    // cout<<'\n';


}
bool check(){
    int num = 0;
    for(int i=0;i<up.size();i++) if(up[i]==0) num++;
    for(int i=0;i<down.size();i++) if(down[i]==0) num++;
    if(num>=k)return false;
    return true;
}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;


    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        up.push_back(a);
    }
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        down.push_front(a);
    }
    int result = 0;
    while(true){
        result++;
        simulate();
        if(!check()) break; 
    }   
    cout<<result;
}