#include <iostream>
#include <vector>
#include <queue>

#define X first 
#define Y second 
using namespace std;

int n;
int result = 0;
int board[22][22];
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int students_seq[405]; 
vector<vector<int>> students;
bool friends[MAX_NUM + 1][MAX_NUM + 1];
int target_num[22];

void score(){
    int arr[5] = {0,0,0,0,0};
    for(int x=0;x<n;x++){
        for(int y=0;y<n;y++){
            // 각각 위치의 학생에 대하여
            int me = board[x][y];
            int close_students = 0;
            for(int dir=0;dir<4;dir++){
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if(nx<0||nx>=n||ny<0||ny>=n) continue;
                if(friend[me][board[nx][ny]] )close_students++;
                // for(int fn = 1;fn<=4;fn++){
                //     if(board[nx][ny]==students[students_seq[me]][fn]) close_students++;
                // }
                

            }
            if(close_students==1) {result+=1;}
            else if(close_students==2) {result+=10;}
            else if(close_students==3) {result+=100;}
            else if(close_students==4) {result+=1000;}
            cout<<"close friend of "<<me<<" is "<<close_students<<"\n";
        }
    }

}

void simulation(){

    for(int i=0;i<n;i++)fill(board[i],board[i]+n,0);
    for(int i=0;i<n*n;i++){
        int best_close_stduents = 0;
        int best_close_spaces = 0;

        int cur_student = students[i][0];
        pair<int,int> best_space = {-1,-1};

        // 결론에 필요한 값들 업데이트
        for(int x=0;x<n;x++){
            for(int y=0;y<n;y++){
                // 빈 공간 발견
                if (board[x][y]==0){
                    int close_students = 0;
                    int close_spaces = 0;
                    // 인접한 space, friends 찾기
                    for(int dir=0;dir<4;dir++){
                        int nx = x + dx[dir];
                        int ny = y + dy[dir];
                        if(nx<0||nx>=n||ny<0||ny>=n) continue;
                        if(board[nx][ny]==0) close_spaces++;
                        if(friends[board[x][y]][board[nx][ny]]) close_students++;
                    }
                    
                    // first case. many close friends
                    if(close_students>best_close_stduents) {
                        if(close_spaces>best_close_spaces) best_close_spaces = close_spaces;
                        best_close_stduents = close_students;
                        best_space = {x,y};

                    }
                    // second case. many spaces
                    else if(close_students==best_close_stduents){
                        if(close_spaces>best_close_spaces){

                            
                            best_space = {x,y};
                            best_close_spaces = close_spaces;

                        }
                    }
                    
                    if(close_students==4) break;
                    if(best_space.first==-1) best_space = {x,y};
                    // for third, forth case, no need update
                    
                }

                
            }
        }
        board[best_space.first][best_space.second] = students[i][0];


    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    
    for(int i=0;i<n*n;i++){
        cin >> target_num[i];

        for(int j = 1; j <= 4; j++) {
            int friend_num;
            cin >> friend_num;
            
            friends[target_num[i]][friend_num] = true;
        }
    }
    simulation();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<"  ";
        }
        cout<<"\n";
    }
    score();
    for(int i=1;i<=n*n;i++) cout<<students_seq[i]<<" ";
    cout<<"\n";
    cout<<result<<"\n";

}