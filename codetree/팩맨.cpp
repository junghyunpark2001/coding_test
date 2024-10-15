#include <iostream>
#include <vector>

using namespace std;

int m,t; // 몬스터 마리 수 턴
int r,c; // 팩맨 초기 위치

int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
int dx2[8] = {-1,-1,0,1,1,1,0,-1};
int dy2[8] = {0,-1,-1,-1,0,1,1,1};

// 팩맨(필요할까?)
int pboard[5][5];
// 몬스터 방향
vector<int> mboard[6][6];
vector<int> tmp[5][5];
// 알 방향
vector<int> eboard[5][5];
// 시체 턴(처음에 1,턴 시작시 ++, 3에 사라짐)
vector<int> dboard[5][5];

int dirs[64][3];

void print_board(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(mboard[i][j].size()==0) cout<<-1;
            else for(auto e:mboard[i][j])cout<<e;
            cout<<"    ";
        }
        cout<<'\n';
    }
}

void move_monster(){
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
            tmp[i][j] = {};
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(mboard[i][j].size()==0) continue;
            bool moved = 0;
            for(auto e:mboard[i][j]){
                int nx=i,ny=j;
                for(int dir=0;dir<8;dir++){
                    nx = i + dx2[(e+dir)%8];
                    ny = j + dy2[(e+dir)%8];
                    if(nx<1||nx>4||ny<1||ny>4) continue;
                    if(dboard[nx][ny].size()>0 || (r==nx && c==ny)) continue;
                    moved = 1;
                    tmp[nx][ny].push_back((e+dir)%8);
                    break;
                }
                if(!moved) tmp[i][j].push_back(e);
            }
        }
    }
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
            mboard[i][j] = tmp[i][j];
}

void make_dirs(){
   
    for(int i=0;i<64;i++){
        int tmp = i;
        
        for(int brute=2;brute>=0;brute--){
            dirs[i][brute] = tmp%4;
            tmp/=4;
        }
    }
    // for(int i=0;i<64;i++){
    //     for(int dir=0;dir<3;dir++){
    //         cout<<dirs[i][dir];
    //     }
    //     cout<<'\n';
    // }
}

void move_packman(){
    int max_eat = 0;
    int d[3] = {0,0,0};
    bool vis[6][6];
    for(int i=0;i<64;i++){
        for(int ii=1;ii<=4;ii++)
            for(int jj=1;jj<=4;jj++)
                vis[ii][jj] = 0;
        int eat = 0;
        int nx = r, ny = c;
        int passed = 1;
        for(int j=0;j<3;j++){
            nx+=dx[dirs[i][j]];
            ny+=dy[dirs[i][j]];
            if(nx<1||nx>4||ny<1||ny>4){passed=0; break;}
            if(vis[nx][ny]==1) continue;

            vis[nx][ny] = 1;
            
            eat+=mboard[nx][ny].size();
        }
        if(passed && eat>max_eat){
            d[0] = dirs[i][0];
            d[1] = dirs[i][1];
            d[2] = dirs[i][2];
            max_eat = eat;
        }
    }

    for(int dir=0;dir<3;dir++){
        r+=dx[d[dir]];
        c+=dy[d[dir]];
        if(mboard[r][c].size()>0)
            for(int i=0;i<mboard[r][c].size();i++) dboard[r][c].push_back(1);
        mboard[r][c] = {};
    }
}

void remove_dead(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(dboard[i][j].size()==0) continue;
            vector<int> tmp_v = {};
            for(auto e:dboard[i][j]) if(e<3) tmp_v.push_back(e);
            dboard[i][j] = tmp_v;
        }
    }
}

void egg_copied(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(eboard[i][j].size()==0) continue;
            for(auto e:eboard[i][j]) mboard[i][j].push_back(e);
            eboard[i][j] = {};
        }
    }
}

void simulation(){
    // 시체 턴 수 추가
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(dboard[i][j].size()==0) continue;
            for(int k=0;k<dboard[i][j].size();k++){ dboard[i][j][k]++;}
        }
    }

    // step1. 몬스터 복제 시도
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(mboard[i][j].size()==0) continue;
            for(int e:mboard[i][j]) eboard[i][j].push_back(e);
        }
    }
    // step2. 몬스터 이동
    move_monster();

    // // step3. 팩맨 이동
    move_packman();
    // // step4. 몬스터 시체 소멸
    remove_dead();

    // // step5. 몬스터 복제 완성
    egg_copied();




}

int get_result(){
    int result = 0;
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
            result+=mboard[i][j].size();
    return result;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>m>>t;
    cin>>r>>c;
    int rr,cc,dd;
    for(int i=0;i<m;i++){
        
        cin>>rr>>cc>>dd;
        mboard[rr][cc].push_back(dd-1);
    }



    make_dirs(); 

    for(int i=0;i<t;i++){
        simulation();
        
    }
    cout<<get_result();

}