#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int n,m,h,k;
int board[105][105];
vector<int> runner[105][105];
int tree[105][105];

int dx[5] = {0,0,1,0,-1};
int dy[5] = {0,1,0,-1,0};

int dx2[4] = {-1,0,1,0};
int dy2[4] = {0,1,0,-1};
vector<tuple<int,int,int>> tagger_locs;
vector<tuple<int,int,int>> runner_locs;

int cur_x; 
int cur_y; 
int cur_dir;

int result = 0;

void tagger_initialize(){
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};
    int nx = cur_x, ny = cur_y;

    int cur_dir = 0;
    tagger_locs.push_back(make_tuple(nx,ny,cur_dir));
    for(int length=1;length<n;length++){
        for(int repeat=0;repeat<2;repeat++){
            
            for(int move=0;move<length;move++){
                nx += dx[cur_dir];
                ny += dy[cur_dir];
                if(move==length-1)cur_dir=(cur_dir+1)%4;
                tagger_locs.push_back(make_tuple(nx,ny,cur_dir));

            }
        }

    }

    for(int move=0;move<n-2;move++){
        nx+=dx[cur_dir];
        ny+=dy[cur_dir];

        tagger_locs.push_back(make_tuple(nx,ny,cur_dir));
    }
    tagger_locs.push_back(make_tuple(1,1,2));
    cur_dir = 2;
    nx = 1;
    ny = 1;
    for(int move=0;move<n-1;move++){
        nx+=dx[cur_dir];
        ny+=dy[cur_dir];
        if(move==n-2) cur_dir = 1;
        tagger_locs.push_back(make_tuple(nx,ny,cur_dir));
    }
    for(int length=n-1;length>=1;length--){
        for(int repeat=0;repeat<2;repeat++){
            
            for(int move=0;move<length;move++){
                nx += dx[cur_dir];
                ny += dy[cur_dir];
                if(move==length-1)cur_dir=(cur_dir+3)%4;
                tagger_locs.push_back(make_tuple(nx,ny,cur_dir));

            }
        }

    }
    tagger_locs.pop_back();
    // for(int i=tagger_locs.size()-2;i>0;i--){
    //     int x,y,d;
    //     tie(x,y,d) = tagger_locs[i];
    //     d=(d+2)%4;
    //     tagger_locs.push_back(make_tuple(x,y,d));
    // }

    // for(auto e: tagger_locs){
    //     int x,y,d;
    //     tie(x,y,d) = e;
    //     cout<<x<<y<<d<<'\n';
    // }
}

bool move(int x,int y){
    int dist = abs(x-cur_x)+abs(y-cur_y);
    if(dist<=3)return true;
    return false;
}
void move_runner(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            runner[i][j].clear();
        }
    }
    for(int i=0;i<runner_locs.size();i++){
        int x,y,d;
        tie(x,y,d) = runner_locs[i];
        if(move(x,y)){
            int nx = x + dx[d], ny = y + dy[d];
            // 격자 벗어날 경우
            if(nx<1||nx>n||ny<1||ny>n){
                if(d==1)d=3;
                else if(d==2) d=4;
                else if(d==3) d=1;
                else if(d==4) d=2;
                nx = x + dx[d], ny = y + dy[d];
                if(nx!=cur_x||ny!=cur_y){ 
                    runner_locs[i] = make_tuple(nx,ny,d);
                    runner[nx][ny].push_back(d);
                }
                else{
                    runner_locs[i] = make_tuple(x,y,d);
                    runner[x][y].push_back(d);
                }
            }
            // 격자 안 벗어날 경우
            else{
                if(nx!=cur_x||ny!=cur_y){ 
                    runner_locs[i] = make_tuple(nx,ny,d);
                    runner[nx][ny].push_back(d);
                }
                else{
                    runner_locs[i] = make_tuple(x,y,d);
                    runner[x][y].push_back(d);
                }
            }
        }
        else{
            runner[x][y].push_back(d);
        }
    }
}

void print_runners(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(auto e:runner[i][j]){
                cout<<e;
            }
            if(i==cur_x && j==cur_y) cout<<cur_dir<<'*';
            else if(runner[i][j].size()==0) cout<<0;
            cout<<" ";
        }
        cout<<'\n';
    }
}

void simulate(){
    for(int num=1;num<=k;num++){
        move_runner();
        int catch_nums = 0;
        tie(cur_x,cur_y,cur_dir) = tagger_locs[num%tagger_locs.size()];
        int nx = cur_x, ny = cur_y;

        for(int sight=0;sight<=2;sight++){

            nx=cur_x+sight*dx2[cur_dir];
            ny=cur_y+sight*dy2[cur_dir];
            if(nx<1||nx>n||ny<1||ny>n) continue;
            if(tree[nx][ny]) continue;

            // cout<<nx<<" "<<ny<<'\n';
            // cout<<runner[nx][ny].size()<<'\n';
            if(runner[nx][ny].size()>0){
                

                catch_nums+=runner[nx][ny].size();
                vector<tuple<int,int,int>> tmp;
                for(auto e: runner_locs){
                    int xx,yy;
                    tie(xx,yy,ignore) = e;
                    if(xx==nx && yy==ny) continue;
                    tmp.push_back(e);
                }
                runner_locs = tmp;
            }
            
        }
        // cout<<'\n';
        // print_runners();
        result += catch_nums * num;
    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>h>>k;
    for(int i=0;i<m;i++){
        int x,y,d;
        cin>>x>>y>>d;
        runner_locs.push_back(make_tuple(x,y,d));
        
    }
    cur_x = n/2+1;
    cur_y = n/2+1;
    cur_dir = 0;
    for(int i=0;i<h;i++){
        int x,y;
        cin>>x>>y;
        tree[x][y] = 1;
    }

    
    tagger_initialize();
    simulate();

   

    cout<<result<<'\n';
}