#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

#define X first
#define Y second

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,-1,1};
int maze[12][12];
int people[12][12];
int tmp_people[12][12];
int tmp_board[12][12];
int n,m,k;

int escaped = 0;
int tot_dist = 0;
pair<int,int> escape;

void print_people(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<people[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void print_maze(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<maze[i][j]<<" ";
        }
        cout<<'\n';
    }
}
int dist(int x, int y){
    return abs(escape.X-x)+abs(escape.Y-y);
}

void people_move(){

    for(int i=1;i<=n;i++)fill(tmp_people[i],tmp_people[i]+n+1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(people[i][j]>0){
                bool changed = 0;
                for(int dir=0;dir<4;dir++){
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];
                    if(make_pair(nx,ny) == escape){
                        cout<<"here\n";
                        escaped+=people[i][j];
                        changed = 1;
                        tot_dist++;
                        break;

                    }
                    if(dist(nx,ny)<dist(i,j) && maze[nx][ny]==0){
                        // cout<<people[i][j];
                        cout<<"e\n";
                        tmp_people[nx][ny] = people[i][j];
                        changed = 1;
                        tot_dist++;
                        cout<<"Ere\n";
                        break;
                    }
                }
                if(changed==0) tmp_people[i][j] = people[i][j];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            people[i][j] = tmp_people[i][j];
        }
    }

}

pair<int,int> start_point(int width){
    bool person_in = 0;
    bool exit_in = 0;
    for(int i=1;i<=n-width;i++){
        for(int j=1;j<=n-width;j++){
            for(int x=i;x<=i+width;x++){
                for(int y=j;y<=j+width;y++){

                    if(make_pair(x,y)==escape) exit_in = 1;
                    if(people[x][y]>=1) person_in = 1;

                }
            }
            if(exit_in&&person_in) return make_pair(i,j);
        }

    }
    return {0,0};
}

void maze_rotate(){
    pair<int,int> person;
    int min_dist = 500;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            

            if(people[i][j]>0&&dist(i,j)<min_dist){

                min_dist = dist(i,j);
                person = make_pair(i,j);

            }
        }
    }
    cout<<person.X<<" "<<person.Y;

    int width = max(abs(escape.X-person.X),abs(escape.Y-person.Y));
    pair<int,int> start = start_point(width);
    cout<<start.X<<" "<<start.Y<<"\n";
    
    // tmp boards initialize
    for(int i=1;i<=n;i++)fill(tmp_people[i],tmp_people[i]+n+1,0);
    for(int i=1;i<=n;i++)fill(tmp_board[i],tmp_board[i]+n+1,0);
    maze[escape.X][escape.Y] = -1;
    for(int i = start.X; i <= start.X + width; i++) {
        for(int j = start.Y; j <= start.Y + width; j++) {
            // 시계방향 90도 회전 공식 적용
            int new_i = j - start.Y + start.X;
            int new_j = start.X + width - (i - start.X);
            if(maze[i][j]>0) maze[i][j]--;

            tmp_board[new_i][new_j] = maze[i][j];
            tmp_people[new_i][new_j] = people[i][j];
        }
    }

    

    for(int i=start.X;i<=start.X+width;i++){
        for(int j=start.Y;j<=start.Y+width;j++){
            if(tmp_board[i][j]==-1){
                escape.X = i;
                escape.Y = j;
                tmp_board[i][j] = 0;
            }
            maze[i][j] = tmp_board[i][j];
            people[i][j] = tmp_people[i][j];
        }
    }

}

void simulate(){
    for(int i=0;i<k;i++){
        cout<<"turn"<<i<<'\n';
        people_move();
        maze_rotate();
        print_people();
        cout<<'\n';
        print_maze();
        cout<<escape.X<<" "<<escape.Y<<'\n';

        if(escaped==m) return;
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>maze[i][j];
        }
    }

    for(int i=0;i<m;i++){
        int r,c;
        cin>>r>>c;
        people[r][c]++;
    }

    cin>>escape.X>>escape.Y;

   simulate();

    cout<<tot_dist<<'\n'<<escape.Y<<" "<<escape.Y;
}