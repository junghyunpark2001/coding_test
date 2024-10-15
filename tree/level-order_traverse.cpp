#include <iostream>
#include <queue>

using namespace std;

int lc[9]={0,2,4,6,0,0,0,0,0};
int rc[9]={0,3,5,7,0,8,0,0,0};
void bfs(){
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        cout<<cur<<' ';
        if(lc[cur]) q.push(lc[cur]);
         
    }

} 

