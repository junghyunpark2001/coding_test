#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int paper[10][10];
int used[6] = {0};
int answer = INT_MAX;


bool canPlace(int x,int y,int size){
    if(x+size>10||y+size>10)
        return false;
    for (int i = x; i < x + size;i++){
        for (int j = y; j < y + size;j++){
            if(paper[i][j]==0)
                return false;
        }
    }
    return true;
}

void place(int x, int y, int size, int val){
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++){
            paper[i][j] = val;
        }
}

void dfs(int cnt){
    bool done = true;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(paper[i][j] == 1){
                done = false;
                break;
            }
        }
        if(!done)
            break;
    }

    if(done){
        answer = min(answer, cnt);
        return;
    }

    int x = -1, y = -1;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(paper[i][j]==1){
                x = i;
                y = j;
                break;
            }
        }
        if(x!=-1)
            break;
    }
    // 크기 5부터 1까지 색종이를 시도
    for (int size = 5; size >= 1; size--) {
        if (used[size] < 5 && canPlace(x, y, size)) {
            // 색종이를 덮을 수 있으면 덮고
            used[size]++;
            place(x, y, size, 0); // 덮은 곳은 0으로 바꿈

            // 재귀 호출
            dfs(cnt + 1);

            // 백트래킹
            used[size]--;
            place(x, y, size, 1); // 덮은 곳을 다시 1로 되돌림
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 보드 입력
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> paper[i][j];
        }
    }

    // DFS로 최소 색종이 수를 찾음
    dfs(0);

    // 결과 출력
    if (answer == INT_MAX) cout << -1; // 덮을 수 없으면 -1 출력
    else cout << answer; // 최소 색종이 수 출력

    return 0;
}