#include <iostream>
#include <queue>
#include <queue>
#include <algorithm>
#include <vector>


using namespace std;

#define X first
#define Y second

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int board[7][7];
int k, m;
int wall_relics[305];
int tmp_board[7][7];
int tmp[3][3];
int tmp2[3][3];
int vis[7][7];
queue<int> walls;
bool changed = 0;
int results[13];


void rotate(int x, int y, int rot){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            tmp_board[i][j] = board[i][j];
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            // tmp_board[j][4-i] = board[i][j];
            tmp[j][2-i] = board[i+x][j+y];
        }
    }
    // rot=0 -> 90, 1 -> 180, 2 -> 270
    for(int a=0;a<rot;a++){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                tmp2[j][2-i] = tmp[i][j];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                tmp[i][j] = tmp2[i][j];
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tmp_board[i+x][j+y] = tmp[i][j];
        }
    }
    
    // for(int i=0;i<5;i++){
    //     for(int j=0;j<5;j++){
    //         cout<<tmp_board[i][j]<<" ";
    //     }
    //     cout<<'\n';
    // }
}

int bfs(){
    for(int i=0;i<5;i++) fill(vis[i],vis[i]+5,0);
    int result = 0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(vis[i][j]) continue;
            queue<pair<int,int>> q;
            int piece_num = 1;
            vis[i][j] = 1;
            q.push({i,j});
            while(!q.empty()){
                auto cur = q.front();
                q.pop();
                for(int dir=0;dir<4;dir++){
                    int nx = cur.X + dx[dir];
                    int ny = cur.Y + dy[dir];
                    if(nx<0||nx>4||ny<0||ny>4) continue;
                    if(vis[nx][ny]||tmp_board[nx][ny]!=tmp_board[i][j]) continue;
                    piece_num++;
                    q.push({nx,ny});
                    vis[nx][ny] = 1;
                }
            }
            if(piece_num>=3) result+=piece_num;

        }
    }
    return result;
}

void bfs2(int kk){
    for(int i=0;i<5;i++) fill(vis[i],vis[i]+5,0);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(vis[i][j]) continue;
            queue<pair<int,int>> q;
            vector<pair<int,int>> v;
            int piece_num = 1;
            vis[i][j] = 1;
            q.push({i,j});
            v.push_back({i,j});
            while(!q.empty()){
                auto cur = q.front();
                q.pop();
                for(int dir=0;dir<4;dir++){
                    int nx = cur.X + dx[dir];
                    int ny = cur.Y + dy[dir];
                    if(nx<0||nx>4||ny<0||ny>4) continue;
                    if(vis[nx][ny]||tmp_board[nx][ny]!=tmp_board[i][j]) continue;
                    piece_num++;
                    q.push({nx,ny});
                    v.push_back({nx,ny});

                    vis[nx][ny] = 1;
                }
            }
            if(piece_num>=3){
                results[kk]+=piece_num;

                changed = 1;
                for(auto e: v) tmp_board[e.X][e.Y] = 0;
            }

        }
    } 
}

void print_board(){
    for(int i=0;i<5;i++){   
        for(int j=0;j<5;j++){
            cout<<tmp_board[i][j]<<" ";
        }
        cout<<'\n';
    }
}

void fill_empty(){
    for(int j=0;j<5;j++){
        for(int i=4;i>=0;i--){
            if(tmp_board[i][j]==0){
                tmp_board[i][j] = walls.front();
                walls.pop();
            }
        }
    }
}

void simulate(int kk){
    int score = 2;
    
    int max_i, max_j, max_rot;
    for(int rot=0;rot<3;rot++){
        for(int j=0;j<3;j++){
            for(int i=0;i<3;i++){
                rotate(i,j,rot);
                if(bfs()>score){
                    score = bfs();
                    max_i = i;
                    max_j = j;
                    max_rot = rot;
                }

            }
        }
    }
    if(score==2) return;
    // cout<<max_i<<" "<<max_j<<" "<<max_rot<<'\n';
    rotate(max_i,max_j,max_rot);

    
    // print_board();
    // cout<<'\n';
    changed  = 0;
    while(true){
        changed = 0;
        bfs2(kk);
        // print_board();
        // cout<<'\n';
        fill_empty();
        if(!changed) break;

    }
    // print_board();
    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            board[x][y] = tmp_board[x][y];
        }
    }

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>k>>m;

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cin>>board[i][j];
        }
    }


    for(int i=0;i<m;i++){
        cin>>wall_relics[i];
        walls.push(wall_relics[i]);
    }

    for(int i=1;i<=k;i++){
        simulate(i);
        if(results[i]>=3) cout<<results[i]<<" ";
        else break;
    }

    // simulate();

    // simulate(1);
    // cout<<results[1];
  
}
