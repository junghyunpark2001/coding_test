#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int arr[10] = {3,2,7,17,72,35,46,57,27,35};
    int n = 10;
    for(int i=n-1;i>0;i--){
        int mxidx = 0;
        for(int j=1;j<=i;j++){
            if(arr[mxidx]<arr[j]) mxidx = j;
        }
        swap(arr[mxidx],arr[i]);
    }
}