#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<pair<int,int>> times;
vector<int> profits;

int max_profit;
vector<int> selected_jobs;

int get_profit(){
    int profit = 0;
    for(int i=0;i<(int)selected_jobs.size();i++)
        profit += profits[selected_jobs[i]];
    return profit;
}

bool is_available(){
    for(int i=0;i<(int)selected_jobs.size()-1;i++)
        if(times[selected_jobs[i]].second>=times[selected_jobs[i+1]].first)
            return false;
    
    for(int i=0;i<(int)selected_jobs.size();i++)
        if(times[selected_jobs[i]].second>n)
            return false;
    
    return true;
}

void find_max_profit(int cur_idx){
    if(cur_idx == n){
        if(is_available())
            max_profit = max(max_profit, get_profit());
    }
    find_max_profit(cur_idx + 1);
    selected_jobs.push_back(cur_idx);
    find_max_profit(cur_idx+1);
    selected_jobs.pop_back();
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t,p;
    for(int i=1;i<=n;i++){
        cin>>t>>p;
        // 외주 작업 시작일, 종료일
        times.push_back(make_pair(i,i+t-1));
        profits.push_back(p);
    }
    
    find_max_profit(0);
    cout<<max_profit;

    return 0;
}