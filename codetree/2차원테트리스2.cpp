#include <iostream>

using namespace std;

int k,t,x,y;
int result = 0;

int board_blue[4][4];
int board_red[6][4];
int board_yellow[6][4];

void print_yellow(){
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            cout<<board_yellow[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void print_red(){
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            cout<<board_red[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void yellow_type1(int layer, int x){
    if(layer==5){ 
        board_yellow[layer][x] = 1;
        return;
    }
    if(!board_yellow[layer+1][x]) yellow_type1(layer+1,x);
    else{
        board_yellow[layer][x] = 1;
        return;
    }
}

void red_type1(int layer, int x){
    if(layer==5){
        board_red[layer][x] = 1;
        return;
    }
    if(!board_red[layer+1][x]) red_type1(layer+1,x);
    else{
        board_red[layer][x] = 1;
        return;
    }
}

void yellow_type2(int layer, int x){
    if(layer==5){
        board_yellow[layer][x] = 1;
        board_yellow[layer][x+1] = 1;
        return;
    }
    if(!board_yellow[layer+1][x] && !board_yellow[layer+1][x+1]) yellow_type2(layer+1,x);
    else{
        board_yellow[layer][x] = 1;
        board_yellow[layer][x+1] = 1;
        return;
    }

}

void red_type2(int layer, int x){
    if(layer==5){
        board_red[layer][x] = 1;
        board_red[layer-1][x] = 1;
        return;
    }
    if(!board_red[layer+1][x]) red_type2(layer+1,x);
    else{
        board_red[layer][x] = 1;
        board_red[layer-1][x] = 1;
        return;
    }
}

void yellow_type3(int layer, int x){
    if(layer==5){
        board_yellow[layer][x] = 1;
        board_yellow[layer-1][x] = 1;
        return;
    }
    if(!board_yellow[layer+1][x]) yellow_type3(layer+1,x);
    else{
        board_yellow[layer][x] = 1;
        board_yellow[layer-1][x] = 1;
        return;
    }

}

void red_type3(int layer, int x){
    if(layer==5){
        board_red[layer][x] = 1;
        board_red[layer][x+1] = 1;
        return;
    }
    if(!board_red[layer+1][x] && !board_red[layer+1][x+1]) red_type3(layer+1,x);
    else{
        board_red[layer][x] = 1;
        board_red[layer][x+1] = 1;
        return;
    }

}



void slide_red(int t, int x){
    // slide
    if(t==1) red_type1(0,x);
    else if(t==2) red_type2(0,x);
    else red_type3(0,x);

    // remove last row
    for(int i=5;i>=0;i--){
        bool remove_row = 1;
        for(int j=0;j<4;j++){
            if(!board_red[i][j]){
                remove_row = 0;
                break;
            }
        }
        if(remove_row){
            result++;
            
            for(int x=i;x>0;x--){
                for(int y=0;y<4;y++){
                    board_red[x][y] = board_red[x-1][y];
                }
            }
            for(int y=0;y<4;y++) board_red[0][y] = 0;
            i++;
        }
    }

    // flooded
    int flooded = 0;
    for(int i=0;i<2;i++){
        bool remove_row = 0;
        for(int j=0;j<4;j++){
            if(board_red[i][j]){
                remove_row = 1;
                break;
            }
        }
        if(remove_row == 1) flooded++;
    }
    if(flooded>0){
        for(int i=5;i>=flooded;i--){
            for(int j=0;j<4;j++){
                board_red[i][j] = board_red[i-flooded][j];
            }
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<4;j++){
                board_red[i][j] = 0;
            }
        }
    }
}



void slide_yellow(int t,int x){
    // slide
    if(t==1) yellow_type1(0,x);
    else if(t==2) yellow_type2(0,x);
    else yellow_type3(0,x);

    // remove last row
    for(int i=5;i>=0;i--){
        bool remove_row = 1;
        for(int j=0;j<4;j++){
            if(!board_yellow[i][j]){
                remove_row = 0;
                break;
            }
        }
        if(remove_row){
            result++;
            
            for(int x=i;x>0;x--){
                for(int y=0;y<4;y++){
                    board_yellow[x][y] = board_yellow[x-1][y];
                }
            }
            for(int y=0;y<4;y++) board_yellow[0][y] = 0;
            i++;
        }
    }


    // int rows = 0;
    
    // for(int i=5;i>=0;i--){
    //     bool remove_row = 1;
    //     for(int j=0;j<4;j++){
    //         if(board_yellow[i][j]==0){
    //             remove_row = 0;
    //             break;
    //         }
    //     }
    //     if(remove_row == 1) rows++;
    //     else break;

    // }
    // if(rows>0){
    //     result += rows;
    //     for(int i=5;i>=rows;i--){
    //         for(int j=0;j<4;j++){
    //             board_yellow[i][j] = board_yellow[i-rows][j];
    //         }
    //     }
    // }

    // flooded
    int flooded = 0;
    for(int i=0;i<2;i++){
        bool remove_row = 0;
        for(int j=0;j<4;j++){
            if(board_yellow[i][j]){
                remove_row = 1;
                break;
            }
        }
        if(remove_row == 1) flooded++;
    }
    if(flooded>0){
        for(int i=5;i>=flooded;i--){
            for(int j=0;j<4;j++){
                board_yellow[i][j] = board_yellow[i-flooded][j];
            }
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<4;j++){
                board_yellow[i][j] = 0;
            }
        }
    }
}

void simulate(int t,int x,int y){
    slide_yellow(t,y);
    slide_red(t,x);
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>k;
    for(int i=0;i<k;i++){
        cin>>t>>x>>y;
        simulate(t,x,y);

    }

    


    // slide_red(2,1);
    // slide_red(3,1);

    // print_red();
    cout<<result;
    int num = 0;
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            if(board_red[i][j]==1) num++;
            if(board_yellow[i][j]==1) num++;
        }
    }
    cout<<'\n'<<num;

    

}