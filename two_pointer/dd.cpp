#include<stdio.h>
    int f(int n){
 
    if (n <= 0) return 0;
    if (n <= 3) return n;
 
    return f(n - 2) + f(n - 3);
    }
 
    int main(){
 
    int ans = f(8);
    printf("%d\n", ans);
 
    return 0;
    }