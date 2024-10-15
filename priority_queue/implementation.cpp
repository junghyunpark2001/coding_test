#include <iostream>
#include <algorithm>
using namespace std;

int heap[1000005];
int sz = 0;

void push(int x){
    heap[++sz] = x;
    int idx = sz;
    while(idx!=1){
        int par = idx/2;
        if(heap[par]<=heap[idx]) break;
        swap(heap[par],heap[idx]);
        idx = par;
    }
}

int top(){
    return heap[1];
}

void pop(){
    heap[1] = heap[sz--];
    int idx = 1;
    while(2*idx<=sz){
        int lc = 2*idx, rc = 2*idx+1;
        int min_child = lc;
        if(rc<=sz&&heap[rc]<heap[lc]) min_child = rc;
        if(heap[idx]<=heap[min_child]) break;
        swap(heap[idx],heap[min_child]);
        idx = min_child; 
    }
}

void test(){

}

int main(void){

}