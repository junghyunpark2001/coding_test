#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

int q,n,m;
bool belt_broken[12];
unordered_map<int,int> prv, nxt;
unordered_map<int,int> belt;
unordered_map<int,int> weight;
int head[12];

void print_belts(){
    for(int i=0;i<m;i++){
        int cur_id = head[i];
        cout<<"cur id is "<<cur_id<<'\n';
        while(cur_id!=0){
            cout<<cur_id<<" ";
            cur_id = nxt[cur_id];
        }
        cout<<'\n';
    }
}

void print_head(){
    for(int i=0;i<m;i++){
        cout<<prv[head[i]];
    }
}

void establish(){
    cin>>n>>m;
    vector<int> id;
    vector<int>w;
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        id.push_back(a);
    }
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        w.push_back(a);
    }
    int per_belt = n/m;

    for(int i=0;i<m;i++){
        vector<pair<int,int>> v;
        for(int j=0+(i*per_belt);j<per_belt+(i*per_belt);j++){
            v.push_back({id[j],w[j]});

        }
        for(int k=0;k<v.size();k++){
            if(k==0){
                head[i] = v[k].first;
                prv[v[k].first] = v[v.size()-1].first;
                cout<<v[v.size()-1].first;
                nxt[v[k].first] = v[k+1].first;
            }
            else if(k==v.size()-1){
                prv[v[k].first] = v[k-1].first;
                nxt[v[k].first] = 0;
            }
            else{
                prv[v[k].first] = v[k-1].first;
                nxt[v[k].first] = v[k+1].first;
            }
            weight[v[k].first] = v[k].second;
            belt[v[k].first] = i;
        }
    }

}

void unload(int w_max){
    int sum = 0;
    for(int i=0;i<m;i++){
        if(belt_broken[i]) continue;
        if(weight[head[i]]<=w_max){
            sum+=weight[head[i]];
            int cur = head[i];
            int next = nxt[cur];
            int prev = prv[cur];
            belt[cur] = -1;
            head[i] = next;
            prv[next] = prev;
            prv[cur] = 0;
        }
        else{
            int tail = prv[head[i]];
            int next = nxt[head[i]];
            nxt[tail] = head[i];
            nxt[head[i]] = 0;
            head[i] = next;
        
        }
        
    }
    cout<<sum<<'\n';
}

void remove(int r_id){
    if(weight.count(r_id)==0 || belt[r_id]==-1) cout<<-1;
    else{
        int belt_n = belt[r_id];
        cout<<r_id;
        if(r_id == head[r_id]){
            // head
            belt[r_id] = -1;
            head[belt_n] = nxt[r_id];
            prv[head[belt_n]] = prv[r_id];
            prv[r_id] = 0;
            nxt[r_id] = 0;
        }
        else if(r_id == prv[head[r_id]]){
            // tail
            belt[r_id] = -1;
            int prev = prv[r_id];
            nxt[prev] = 0;
        }
        else{
            // middle
            belt[r_id] = -1;
            int prev = prv[r_id];
            int next = nxt[r_id];
            nxt[prev] = next;
            prv[next] = prev;
        }
    }
    cout<<'\n';
}

void check(int f_id){
    if(belt[f_id]==-1) cout<<-1;
    else{
        cout<<belt[f_id];
        int cur_head = head[belt[f_id]];
        int cur_prv = prv[cur_head];
        head[belt[f_id]] = f_id;
        prv[f_id] = cur_prv;
        
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> q;
    for(int i=0;i<q;i++){
        int command;
        cin>>command;
        if(command==100){
            establish();
        }
        else if(command == 200){
            int w_max;
            cin>>w_max;
            unload(w_max);
        }
        else if(command == 300){
            int r_id;
            cin>>r_id;
            remove(r_id);
        }
        else if(command == 400){

        }
        else{

        }
    }
    print_belts();
    print_head();
}