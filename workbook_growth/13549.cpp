#include <iostream>
#include <queue>
#include <vector>
#include <deque>

using namespace std;

int n, k;
int MAX = 100000;
vector<int> dist(MAX+1, -1);

int bfs(int n, int k){
    deque<int> dq;
    dq.push_front(n);
    dist[n] = 0;

    while(!dq.empty()){
        int cur = dq.front();
        dq.pop_front();

        if(cur == k) return dist[cur];

        if(cur * 2 <= MAX && dist[cur * 2] == -1){
            dist[cur * 2] = dist[cur];
            dq.push_back(cur * 2);
        }
        if(cur - 1 >= 0 && dist[cur - 1] == -1){
            dist[cur - 1] = dist[cur] + 1;
            dq.push_back(cur - 1);
        }
        if(cur + 1 <= MAX && dist[cur + 1] == -1){
            dist[cur + 1] = dist[cur] + 1;
            dq.push_back(cur + 1);
        }

    }
    return -1;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    cout << bfs(n,k) << '\n';
    return 0;

}