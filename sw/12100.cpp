#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define X first
#define Y second 


int n;
int board[22][22];
int copy_board[22][22];
void rotate(){
    int tmp[22][22];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            tmp[i][j] = copy_board[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            copy_board[i][j] = tmp[n-j-1][i];
}

void slide(int n, int dir){
    if(dir==1) rotate();
    if(dir==2){
        for(int i=0;i<2;i++) rotate();
    } 
    if(dir==3){
        for(int i=0;i<dir;i++) rotate();
    } 
    for(int i=0;i<n;i++){
        vector<pair<int,int>> v;
        for(int j=0;j<n;j++){
            if(copy_board[i][j]!=0){
                if(v.empty() || copy_board[i][j] != v.back().first || v.back().second == 1) {
                    v.push_back({copy_board[i][j], 0});
                } else {
                    v.back().first *= 2;
                    v.back().second = 1;
                }
            }
        }

        for(int j=0;j<n;j++){
            if(j<v.size()) copy_board[i][j] = v[j].X;
            else copy_board[i][j] = 0;
        }

        // for(int j=0;j<v.size();j++) board[i][j] = v[j].X;
        // for(int j=i-v.size();j<n;j++) board[i][j] = 0;
    }
    
}


int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>board[i][j];


    int result = 0;

    for(int tmp=0;tmp<1<<(10);tmp++){
        int brute = tmp;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                copy_board[i][j] = board[i][j];
        for(int i=0;i<5;i++){
            int dir = brute%4;
            brute /= 4;
            slide(n,dir);
        }
        int tmp_result = 0; 
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                result = max(result,copy_board[i][j]);
            }

        }

    
    } 

    cout<<result<<"\n";
}