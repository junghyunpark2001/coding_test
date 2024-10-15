#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
using namespace std;


int n,m;
int board[55][55];
vector<pair<int,int>> hospitals;
vector<pair<int,int>> people;
vector<int> v;
int result = INT_MAX;
int min_distance(vector<int>& v){
    int dist = 0;
    vector<pair<int,int>> selected_hospitals;
    for(int i=0;i<v.size();i++){
        if(v[i]==1) selected_hospitals.push_back(hospitals[i]);
    }
    for(int i=0;i<people.size();i++){
        int tmp = INT_MAX;
        for(int j=0;j<selected_hospitals.size();j++){
            int distance = abs(people[i].first-selected_hospitals[j].first)+abs(people[i].second-selected_hospitals[j].second);

            tmp = min(tmp,distance);
        }
        dist += tmp;
    }
    // cout<<dist<<'\n';
    // for(auto e: selected_hospitals){cout<<e.first<<" "<<e.second<<'\n';}

    return dist;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
            if(board[i][j]==2) hospitals.push_back({i,j});
            else if(board[i][j]==1) people.push_back({i,j});
        }
    }
  
    v.resize(hospitals.size());
    

    for(int i=0;i<m;i++) v[i] = 1;
    sort(v.begin(),v.end());
    
    do{
        result = min(result, min_distance(v));

    } while(next_permutation(v.begin(),v.end()));

    cout<<result;

}