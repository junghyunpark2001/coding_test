#include <iostream>
#include <stack>

using namespace std;
int n;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;

    stack<pair<int,int> > s;
    for(int i = 1; i <= n; i++){
        int height;
        cin >> height;

        while (!s.empty() && s.top().first < height) {
            s.pop();
        }
        if(s.empty()){
            cout << "0 ";
        } else {
            cout << s.top().second << " ";
        }
        s.push({height, i});
    }
    cout<<'\n';
}