#include <iostream>

using namespace std;

int board[10][10];
int main(void){
    int max = 0;
    int x,y;
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            cin>>board[i][j];
            if(board[i][j]>max){
                x = i;
                y = j;
                max = board[i][j];
            }
        }
    }

    cout<<max<<'\n';
    cout<<x<<" "<<y;
}