#include <iostream>
using namespace std;

const int mx = 1000005;
int dat[mx];
int pos = 0;

void push(int x){
    dat[pos++] = x;
}

void pop(){
    pos--;
}

int top(){
    return dat[pos-1];
}

void test(){

}

int main(void){
    test();
}