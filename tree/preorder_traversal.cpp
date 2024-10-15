#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int lc[9] = {0,2,4,6,0,0,0,0,0};
int rc[9] = {0,3,5,7,0,8,0,0,0};
void preorder(int cur){
    cout<<cur<<' ';
    if(lc[cur]!=0) preorder(lc[cur]);
    if(rc[cur]!=0) preorder(rc[cur]);
}
int main(void){

}