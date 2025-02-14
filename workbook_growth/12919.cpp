#include <iostream>
#include <algorithm>

using namespace std;
string S,T;
bool possible = false;

void dfs(string current){
    if(current == S){
        possible = true;
        return;
    }
    if(current.size() <= S.size() || possible) return;
    
    if(current.back() == 'A'){
        dfs(current.substr(0, current.size() - 1)); // 끝에 'A' 제거
    }

    if(current.front() == 'B'){
        string reversed = current.substr(1);
        reverse(reversed.begin(), reversed.end());
        dfs(reversed);
    }



}
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> T;
    dfs(T);
    cout << (possible ? 1 : 0) <<'\n';
    return 0;
}