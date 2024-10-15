#include <iostream>
using namespace std;

const int mx = 1000005;
int dat[2*mx+1];
int head  = mx, tail = mx;

void push_front(int x){
    dat[--head] = x;
}

void push_back(int x){
    dat[tail++] = x;
}

void pop_front(){   
    head++;
}

void pop_back(){
    tail--;
}

int front(){
    return dat[head];
}

int back(){
    return dat[tail-1];
}