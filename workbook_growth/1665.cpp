#include <iostream>
#include <queue>

using namespace std;

int n;
priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for(int i = 0; i < n; i++){
        int t;
        cin >> t;

        // 입력 값 분배
        if(maxHeap.size() > minHeap.size()) minHeap.push(t);
        else maxHeap.push(t);

        // 두 힙의 값 필요 시 교환
        if(!maxHeap.empty() && !minHeap.empty()){
            if(minHeap.top() < maxHeap.top()){
                int max_val = maxHeap.top();
                int min_val = minHeap.top();

                maxHeap.pop();
                minHeap.pop();

                maxHeap.push(min_val);
                minHeap.push(max_val);
            }
        }

        cout << maxHeap.top() << '\n';

    }


}