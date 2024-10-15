#include <iostream>
#include <tuple>

#define MAX_N 100

using namespace std;

int n, k;

pair<int,bool> u[MAX_N];
pair<int,bool> d[MAX_N];

void shift(){
    pair<int,bool> tmp = u[n-1];
    for(int i=n-1;i>=1;i--)
        u[i] = u[i-1];
    u[0] = d[n-1];

    for(int i=n-1;i>=n;i--)
        d[i] = d[i-1];
    d[0] = tmp;
}

bool can_move(int idx){
    if(idx==n) return 1;

    // 안정성이 0보다 크고 사람이 없는 경우에만 이동 가능
    int stability; bool occupied;
    tie(stability, occupied) = u[idx];
    return stability>0 && !occupied;
}

void move(int idx){
    int cur_stability;
    tie(cur_stability, ignore) = u[idx];
    u[idx] = make_pair(cur_stability,false);

    // 밖으로 나가는 것이 아니면 안정성 1 감소, 사람 추가
    if(idx+1<n){
        int next_stability;
        tie(next_stability,ignore) = u[idx+1];
        u[idx+1] = make_pair(next_stability-1,1);

    }
}

void move_all(){
    // 현재 위치에 사람이 있고, 다음 위치로 이동이 가능한 경우에만 이동
    for(int i=n-1;i>=0;i--){
        bool occupied;
        tie(ignore,occupied) = u[i];
        if(occupied && can_move(i+1)) move(i);
    }
}

void add(){
    // 안정성이 0 이상이고 사람이 없는 경우에만 첫 번째 위치에 사람 추가
    int stability; bool occupied;
    tie(stability, occupied) = u[0];
    if(stability>0&&!occupied) u[0] = make_pair(stability-1, 1);
}

void simulate(){
    // step 1. 무빙워크 한 칸 회전
    shift();

    // step 2. 사람들 한 칸씩 앞으로 이동
    move_all();

    // step 3. 사람들 새로 추가
    add();

    // step 4. n번 칸 위치에 사람이 있다면, 즉시 하차
    bool occupied;
    tie(ignore, occupied) = u[n-1];
    if(occupied) move(n-1);
    cout<<"here\n";
}

bool finish(){
    int unstable_cnt = 0;
    for(int i=0;i<n;i++){
        int stability;
        tie(stability, ignore) = u[i];
        if(!stability) unstable_cnt++;
    }
    for(int i=0;i<n;i++){
        int stability;
        tie(stability, ignore) = d[i];
        if(!stability) unstable_cnt++;
    }
    cout<<unstable_cnt;
    return unstable_cnt >=k;
}

int main(){
    cin>>n>>k;
    for(int i=0;i<n;i++){
        int stability;
        cin>>stability;
        u[i] = make_pair(stability, false);
    }
    for(int i=0;i<n;i++){
        int stability;
        cin>>stability;
        d[i] = make_pair(stability, false);
    }

    int trial = 0;

    while(!finish()){
        simulate();
        trial++;
    }

    cout<<trial;
    return 0;
}