#include <iostream>

using namespace std;

int n;
int people[10];
int result[10];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    fill(result, result+10, -1);
    cin >> n;
    for(int i = 0; i < n; i++){
        int p;
        cin >> p;
        people[i] = p;
    }

    for(int i = 0; i < n; i++){
        int cnt = 0;
        for(int j = 0; j < n; j++){
            if(result[j] != -1)
                continue;
            if(cnt == people[i]){
                result[j] = i;
                break;
            }
            cnt++;
            
        }
        
    }

    for(int i = 0; i < n; i++)
        cout << result[i]+1 << " ";


}