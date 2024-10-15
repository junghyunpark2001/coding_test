#include <iostream>

using namespace std;

int n, k;
int rail[205];
int person[205];
int st = 1;
int cnt = 0;
int firstPerson;
void move(){
    st--;
    if(st<=0) st = 2*n-st;
}

bool stability(){
    int tmp =0 ;
    for(int i=0;i<2*n;i++){
        if(rail[i]==0) tmp++;
    }
    if(tmp>=k) return false;
    return true;
}

void simulation(){
    cnt++;
    // 1. 무빙워크 한 칸 회전
    move();
    
    // 2. 가장 먼저 무빙워크에 올라탄 사람부터 이동
    if(st<=n){
        for(int i=st+n-1;i>st;i--){
            if(person[i]==0&&rail[i]>0) continue;
            else{
                person[i] = person[i-1];
                if(person[i])rail[i]--;
            }
        }
        person[st+n-1] = 0;
    }
    else{
        
        for(int i=st-n-1;i>1;i--) {
            if(person[i]==0&&rail[i]>0) continue;
            else{
                person[i] = person[i-1];
                if(person[i])rail[i]--;
            }
        }
        if(person[1]==0&&rail[1]>0&&person[2*n]){ person[1] = person[2*n];rail[1]--;}
        person[st-1-n] = 0;
        
        for(int i=2*n;i>st;i--) {
            if(person[i]==0&&rail[i]>0) continue;
            else{
                person[i] = person[i-1];
                if(person[i])rail[i]--;
            }
        }
    }

    // 3. 1번칸
    if(rail[st]>0&&person[st]==0){
        person[st] = 1;
        rail[st]--;
    }
    cout<<"\n";
    for(int i=1;i<=2*n;i++)cout<<person[i]<<" ";
    cout<<"\n";
    for(int i=1;i<=2*n;i++)cout<<rail[i]<<" ";


    // // 4. 안정성 테스트 종료


}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin>>n>>k;
    for(int i=1;i<=n*2;i++) cin>>rail[i];
    // while(stability()){
    //     simulation();
    //     if(!stability()) break;
    // }
    simulation();
    simulation();
    simulation();
    //cout<<cnt;



}