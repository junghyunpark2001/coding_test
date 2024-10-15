#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 100001
#define MAX_D 22


int q,n;
int a[MAX_N], p[MAX_N], val[MAX_N];
bool noti[MAX_N];
int nx[MAX_N][MAX_D];

void init(){
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]>20) a[i] = 20;
    }

    for(int i=1;i<=n;i++){
        int cur = i;
        int x = a[i];
        nx[cur][x]++;
        while(p[cur] && x){
            cur = p[cur];
            x--;
            if(x) nx[cur][x]++;
            val[cur]++;
        }
    }
}

void toggle_noti(int chat){
    if(noti[chat]){
        int cur = p[chat];
        int num = 1;
        while(cur){
            for(int i=num;i<=21;i++){
                val[cur] += nx[chat][i];
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>q>>n;

}