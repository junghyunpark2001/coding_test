#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int board[22][22];
int tmp[22][22];
int result = 0;
int n;
int maximum(){
    int max_block = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            max_block = max(max_block,board[i][j]);
        }
    }
    return max_block;
}

vector<int> slide(vector<int>& v){
    vector<int> tmp;
    tmp.push_back(v[0]);
    int it = 1;
    for(int i=1;i<v.size();i++){
        if(tmp.back()==0) tmp[tmp.size()-1] += v[i];
        else if(it==1 && tmp.back()==v[i]) {
            tmp[tmp.size()-1] *=2;
            it++;
        }
        else{
            tmp.push_back(v[i]);
            it=1;
        }

    }
    return tmp;
}

void tilt(){

    for(int i=0;i<n;i++){
        vector<int> v;
        for(int j=0;j<n;j++){
            if(board[i][j]!=0)v.push_back(board[i][j]);
        }
        vector<int> tmp = slide(v);
        for(int a=0;a<tmp.size();a++) board[i][a] = tmp[a];
        for(int a=tmp.size();a<n;a++) board[i][a] = 0;
    }
    
}

void rotate(){
    for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			tmp[i][j] = board[n - j - 1][i];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            board[i][j] = tmp[i][j];
    
}

void find_max(int round){
    if(round==6) return;
    for(int dir=0;dir<4;dir++){
        
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                tmp[i][j] = board[n - j - 1][i];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                board[i][j] = tmp[i][j];
        
        // for(int a=0;a<=dir;a++) rotate();
        tilt();
        // for(int a=4-dir;a<=dir;a++) rotate();
        find_max(round+1);
        
        result = max(result,maximum());
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>board[i][j];

    find_max(1);

    cout<<result<<'\n';
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }

}