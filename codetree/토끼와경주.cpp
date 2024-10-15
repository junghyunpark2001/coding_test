#include <iostream>
#include <unordered_map>
#include <tuple>
#include <limits.h>
using namespace std;

// dist, jump, i+j, i, j
unordered_map<int,tuple<int,int,int,int,int>> rabbits;
unordered_map<int,int> rabbits_score;
int q,n,m,p;
int dx[4] = {1,0,0,-1};
int dy[4] = {0,1,-1,0};

void compete(int k,int s){
    unordered_map<int,bool> changed;

    for(int i=0;i<k;i++){
        int best_rabbit = -1;
        tuple<int,int,int,int,int> state = {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};

        // 우선순위 토끼 결정
        for(const auto& pair: rabbits){
            int dist, jump, i_j, ii, jj;
            tie(dist, jump, i_j, ii, jj) = pair.second;
            tuple<int,int,int,int,int> compare_state = {jump, i_j, ii, jj, pair.first};

            if(compare_state < state){
                state = compare_state;
                best_rabbit = pair.first;
            }
        }

        // best_rabbit 이동
        int dist, jump, i_j, ii, jj;
        tie(dist, jump, i_j, ii, jj) = rabbits[best_rabbit];
        tuple<int,int,int,int> best_move = {-1, -1, -1, -1};

        // 4방향 중 우선순위 높은 곳 선택
        for(int dir = 0; dir < 4; dir++){
            int nx = ii + dist * dx[dir];
            int ny = jj + dist * dy[dir];

            if(nx < 1 || nx > n || ny < 1 || ny > m) continue;

            tuple<int,int,int,int> move = {nx + ny, nx, ny, dir};
            if(move > best_move){
                best_move = move;
            }
        }

        // best_move에 따라 위치 변경
        int nx = get<1>(best_move);
        int ny = get<2>(best_move);
        rabbits[best_rabbit] = make_tuple(dist, jump + 1, nx + ny, nx, ny);

        // 나머지 토끼 점수 추가
        for(auto& pair: rabbits_score){
            if(pair.first == best_rabbit) continue;
            pair.second += (nx + ny);
        }

        changed[best_rabbit] = true;
    }

    // K번 이동 후 점수 추가할 토끼 결정
    int max_rabbit = -1;
    tuple<int,int,int,int> state = {-1, -1, -1, -1};
    for(const auto& pair: rabbits){
        if(changed.find(pair.first) == changed.end()) continue;

        int dist, jump, i_j, ii, jj;
        tie(dist, jump, i_j, ii, jj) = pair.second;
        tuple<int,int,int,int> compare_state = {i_j, ii, jj, pair.first};

        if(compare_state > state){
            state = compare_state;
            max_rabbit = pair.first;
        }
    }

    rabbits_score[max_rabbit] += s;
}

void change_dist(int t, int l){
    int dist, jump, i_j, ii, jj;
    tie(dist, jump, i_j, ii, jj) = rabbits[t];
    dist *= l;
    rabbits[t] = {dist, jump, i_j, ii, jj};
}

void choose_rabbit(){
    int id = -1;
    int score = 0;
    for(const auto& pair: rabbits_score){
        if(pair.second > score || (pair.second == score && pair.first < id)){
            score = pair.second;
            id = pair.first;
        }
    }
    cout << score << '\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> q;
    for(int i=0; i<q; i++){
        int command;
        cin >> command;
        if(command == 100){
            cin >> n >> m >> p;
            for(int j=0; j<p; j++){
                int pid, d;
                cin >> pid >> d;
                rabbits[pid] = make_tuple(d, 0, 2, 1, 1);
                rabbits_score[pid] = 0;
            } 
        }
        else if(command == 200){
            int k, s;
            cin >> k >> s;
            compete(k, s);
        }
        else if(command == 300){
            int t, l;
            cin >> t >> l;
            change_dist(t, l);
        }
        else if(command == 400){
            choose_rabbit();
        }
    }
}
