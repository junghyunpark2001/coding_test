#include <iostream>
#include <algorithm>
using namespace std;

const int mx = 10000005;
int dat[mx], pre[mx], nxt[mx];
void traverse(){
    int cur = nxt[0];
    while(cur!=-1){
        cout<<dat[cur] <<' ';
        cur = nxt[cur];
    }
}

int main(void){
    fill(pre,pre+mx,-1);
    fill(nxt,nxt+mx,-1);
    
}  