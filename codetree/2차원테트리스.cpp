#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
int k;
int blue[4][4];
int red [4][6];
int yellow[6][4];
vector<tuple<int,int,int>> blocks;

void print_red(){
    for(int i=0;i<4;i++){
        for(int j=0;j<6;j++){
            cout<<red[i][j]<<" ";
        }
        cout<<'\n';
    }
}
void print_yellow(){
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            cout<<yellow[i][j]<<" ";
        }
        cout<<'\n';
    }
}
void slide_red(int t, int x,int y){
    // step 1. slide blocks
    if(t==1){
        int index = 5;
        for(int i=5;i>=0;i--){
            if(red[x][i]==1) index = i-1;
        }
        cout<<index<<'\n';
        red[x][index] = 1;
    }
    else if(t==2){
        int index = 5;
        for(int i=5;i>=0;i--){
            if(red[x][i]==1) index = i-1;
        }
    
        red[x][index] = 1;
        red[x][index-1] = 1;
    }
    else{
        int index = 5;
        for(int i=5;i>=0;i--){
            if(red[x][i]==1 || red[x+1][i]) index = i-1;
        }
        red[x][index] = 1;
        red[x+1][index] = 1;
    }
    // step 2. filled column, row
    int slide_row = 0;
    for(int i=5;i>=0;i--){
        bool filled = 1;
        for(int j=0;j<4;j++){
            if(red[j][i]==0) filled = 0;
        }
        if(filled){
            slide_row++;
            for(int j=0;j<4;j++){
                red[j][i] = 0;
            }
        }
    }
    if(slide_row>=1){
        for(int i=5-slide_row;i>=0;i--){
            for(int j=0;j<4;j++){
                red[j][i+slide_row] = yellow[j][i];
                
            }
        }
    }
    // step 3. flooded area
    int flooded = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            if(red[i][j]==1)flooded = 2-j;
            
        }
    }

    
    if(flooded>=1){
        cout<<"here\n";
        for(int i=5;i>=2;i--){
            for(int j=0;j<4;j++){
                red[j][i] = red[j][i-flooded];
            }
        }
        for(int i=0;i<4;i++)
            for(int j=0;j<2;j++)
                red[i][j] = 0;
    }

}
void slide_yellow(int t,int x,int y){
    // step 1. slide blocks
    if(t==1){
        int index = 5;
        for(int i=5;i>=0;i--){
            if(yellow[i][y]==1) index = i-1;
        }
        yellow[index][y]=1;
    }
    else if(t==2){
        int index = 5;
        for(int i=5;i>=0;i--){
            if(yellow[i][y]==1||yellow[i][y+1]) index = i-1;
        }
    
        yellow[index][y] = 1;
        yellow[index][y+1] = 1;
    }
    else{
        int index = 5;
        for(int i=5;i>=0;i--){
            if(yellow[i][y]==1) index = i-1;
        }
        yellow[index][y] = 1;
        yellow[index-1][y] = 1;
    }
    // step 2. filled column, row
    int slide_columns = 0;
    for(int i=5;i>=0;i--){
        bool filled = 1;
        for(int j=0;j<4;j++){
            if(yellow[i][j]==0) filled = 0;
        }
        if(filled){
            slide_columns++;
            for(int j=0;j<4;j++){
                yellow[i][j] = 0;
            }
        }
    }
    if(slide_columns>=1){
        for(int i=5-slide_columns;i>=0;i--){
            for(int j=0;j<4;j++){
                yellow[i+slide_columns][j] = yellow[i][j];
                
            }
        }
    }

    // step 3. flooded area 
    int flooded = 0;
    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            if(yellow[i][j]==1) {
                flooded = 2-i;
                break;
            }
        }
    }
    if(flooded>=1){
        for(int i=5-flooded;i>=0;i--){
            for(int j=0;j<4;j++){
                yellow[i+flooded][j] = yellow[i][j];
                
            }
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<4;j++){
                yellow[i][j] = 0;
            }
        }
    }
}

void slide(int t,int x,int y){
    // step 1. slide
    
    // step 2. filled column, row

    // step 3. flowed area
}

void simulate(){
    for(int i=0;i<blocks.size();i++){
        int t,x,y;
        tie(t,x,y) = blocks[i];
        slide_red(t,x,y);
        slide_yellow(t,x,y);
        
        // slide(t,x,y);
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>k;
    while(k--){
        int t,x,y;
        cin>>t>>x>>y;
        blocks.push_back(make_tuple(t,x,y));
    }
    simulate();
    // slide_red(1,1,1);
    // slide_red(2,1,2);
    // slide_red(3,0,1);
    // slide_red(1,3,0);
    // slide_red(3,1,3);
    // slide_yellow(1,1,1);
    // slide_yellow(2,1,2);
    // slide_yellow(3,0,1);
    // slide_yellow(1,3,0);
    // slide_yellow(3,1,3);
    print_red();
    cout<<'\n';
    print_yellow();

}