#include <iostream>
using namespace std;

const int mx = 1000005;
int dat[mx];
int head = 0, tail = 0;

void push(int x){
    dat[tail++] = x;
}

void pop(){
    head++;
}

int front(){
    return dat[head];
}

int back(){
    return dat[tail-1];
}

void test(){

}

int main(void){
    test();
}