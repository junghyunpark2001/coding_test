#include <iostream>

using namespace std;

int n,m;
int board[202][202];
int result = 0;
int blocks[5][4][4] = 
    {{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
    {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
    {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
    {{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}},
    {{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}
    };


void rotate(int number){
    int tmp[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tmp[i][j] = 0;
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tmp[i][j] = blocks[number][3-j][i];
            
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            blocks[number][i][j] = tmp[i][j];
            
        }
    }

}
void flip(int number){
    int tmp[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tmp[i][j] = 0;
        }
    } 
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tmp[i][j] = blocks[number][i][3-j];
        }
    } 
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            blocks[number][i][j] = tmp[i][j];
           
        }
    }
}

int score(int i,int j,int i_start,int j_start, int number){
    int tmp = 0;

    for(int a=0;a<4-i_start;a++){
        for(int b=0;b<4-j_start;b++){
            int nx = i + a;
            int ny = j + b;
            
            if(nx>=n||nx<0||ny>=m||ny<0) continue;
            else if(blocks[number][i_start + a][j_start + b]==1){
                tmp+=board[nx][ny];

            }
        }
    }
    return tmp;
}

bool can_attach(int x, int y, int number){
    // int cnt = 0;
    // for(int a=0;a<4;a++){
    //     for(int b=0;b<4;b++){
    //         int nx = a + x;
    //         int ny = b + y;
    //         if(nx>=n||nx<0||ny>=m||ny<0) continue;
    //         if(blocks[number][a][b]==1) {cout<<"here";cnt++;}
    //     }
    // }
    // if(cnt==4) {cout<<"here";return true;}
    // return false;
    return true;
}


int attach(int number){
    int i_start=3;int j_start=3;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(blocks[number][i][j]==1){
                i_start = min(i,i_start);
                j_start = min(j,j_start);
            }
        }
    }
    int tmp=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(can_attach(i,j,number)){
                int tmp_score = score(i,j,i_start,j_start,number);
                tmp = max(tmp_score,tmp);
            }
        }
    }
    return tmp;
    
}

void simulate(){
    for(int i=0;i<5;i++){
        for(int t=0;t<4;t++){
            rotate(i);
            int tmp = attach(i);
            result = max(tmp,result);
        }
        flip(i);
        for(int t=0;t<4;t++){
            rotate(i);
            int tmp = attach(i);
            result = max(tmp,result);
        }  

    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
            
        }

    }


    simulate();
    cout<<result;

}
