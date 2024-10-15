#include <iostream>
#include <queue>

using namespace std;

int main(void){
    priority_queue<int> pq;
    pq.push(10); pq.push(2); pq.push(5); pq.push(9);
    cout<<pq.top()<<'\n';
    pq.pop();
    cout<<pq.size()<<'\n';
    if(pq.empty()) cout<<"PQ is empty\n";
    else cout<<"PQ is not empty\n";
    pq.pop();
    cout<<pq.top()<<'\n';
    pq.push(5); pq.push(15);
    cout<<pq.top()<<'\n';
}
