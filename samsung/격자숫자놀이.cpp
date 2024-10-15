#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int r,c,k;
int board[100][100];
vector<pair<int,int>> numbers;
int number[100];
int row = 3, column = 3;

vector<int> change(vector<int>& v){
    fill(number,number+100,0);
    for(int i=0;i<v.size();i++){
        number[v[i]]++;
    }
    vector<int> tmp;
    // for(int i=0;i<v.size();i++){
    //     tmp.push_back(v[i]);
    //     tmp.push_back(number[v[i]]);
    //     cout<<v[i]<<" "<<number[v[i]]<<'\n';
    // }
    for(int i=1;i<99;i++){
        if(number[i]!=0){
            tmp.push_back(i);
            tmp.push_back(number[i]);
        }
    }
    return tmp;

}

void change_row() {
    for (int i = 0; i < row; i++) {
        vector<int> tmp;
        for (int j = 0; j < column; j++) {
            tmp.push_back(board[i][j]);
        }
        vector<int> v = change(tmp);
        int size = v.size();
        column = max(column, size);
        for (int j = 0; j < size; j++) board[i][j] = v[j];
        for (int j = size; j < column; j++) board[i][j] = 0; // 남은 공간 0으로 채움
    }
}

void change_column() {
    for (int j = 0; j < column; j++) {
        vector<int> tmp;
        for (int i = 0; i < row; i++) {
            tmp.push_back(board[i][j]);
        }
        vector<int> v = change(tmp);
        int size = v.size();
        row = max(row, size);
        for (int i = 0; i < size; i++) board[i][j] = v[i];
        for (int i = size; i < row; i++) board[i][j] = 0; // 남은 공간 0으로 채움
    }
}


int simulate(){
    for(int i=0;i<1;i++){
        if(row>=column) change_row();
        else change_column();
        if(board[r][c]==k) return i;
    }
    return -1;

}




int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>r>>c>>k;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            cin>>board[i][j];
    
    cout<<simulate()<<'\n';
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
    
}