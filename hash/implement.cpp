#include <iostream>
using namespace std;

const int M = 1000003;
const int a = 1000;
const int MX = 500005;
int head[M];
int pre[MX];
int nxt[MX];
string key[MX];
int val[MX];
int unused = 0;

int my_hash(string& s){
    int h = 0;
    for(auto x : s)
        h = (h * a + x) % M;
    return h;
}

int find(string k){
    int h = my_hash(k);
    int idx = head[h];
    while(idx!=-1){
        if(key[idx] == k) return idx;
        idx = nxt[idx];
    }
    return -1;
}

void insert(string k, int v){
    int idx = find(k);
    if(idx!=-1){
        val[idx] = v;
        return;
    }
    int h = my_hash(k);
    key[unused] = k;
    val[unused] = v;
    if(head[h] != -1){
        nxt[unused] = head[h];
        pre[head[h]] = unused;
    }
    head[h] = unused;
    unused++;
}
 void test(){

 }

 int main(){
    fill(head,head+M,-1);
    fill(pre, pre+MX, -1);
    fill(nxt, nxt+MX, -1);
    test();
 }