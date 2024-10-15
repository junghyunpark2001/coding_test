#include <iostream>
#include <cmath>
#include <utility>
#include <algorithm>

#define MAX_N 10
#define MAX_M 10

using namespace std;

int n,m;
char a[MAX_N][MAX_M];

pair<int,int> red_pos;
pair<int,int> blue_pos;

const pair<int,int> OUT_OF_MAP = make_pair(MAX_N,MAX_M);

int ans = 11;

bool blue_exist(){
    return blue_pos != OUT_OF_MAP;
}

bool red_exist(){
    return red_pos != OUT_OF_MAP;
}

bool red_must_first(int dir){
    int rx = red_pos.first, ry = red_pos.second;
    int bx = blue_pos.first, by = blue_pos.second;

    if(dir==0) return (ry==by&&rx<bx);
    else if(dir==1) return (ry==by&&rx>bx);
    else if(dir==2) return (rx==bx&&ry<by);
    else return (rx==bx&&ry>by);
}

bool can_go(int x, int y){
    return a[x][y]!='#' && make_pair(x,y)!=red_pos && make_pair(x,y)!=blue_pos;
}

pair<int,int> get_destination(pair<int,int> pos, int dir){
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    int nx = pos.first + dx[dir], ny = pos.second + dy[dir];
    if(!can_go(nx,ny)) return pos;
    if(a[nx][ny]=='O') return OUT_OF_MAP;
    return get_destination(make_pair(nx,ny),dir);
}

void tilt(int dir){
    if(red_must_first(dir)){
        red_pos = get_destination(red_pos,dir);
        blue_pos = get_destination(blue_pos, dir);
    }
    else{
        blue_pos = get_destination(blue_pos, dir);
        red_pos = get_destination(red_pos,dir);
    }
}

void find_min(int cnt){
    if(!blue_exist()) return;
    if(!red_exist()){
        ans = min(ans,cnt);
        return;
    }
    if(cnt>=10) return;
    for(int dir=0;dir<4;dir++){
        pair<int,int> tmp_red = red_pos;
        pair<int,int> tmp_blue = blue_pos;

        tilt(dir);
        find_min(cnt+1);

        red_pos = tmp_red;
        blue_pos = tmp_blue;
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];

            if(a[i][j]=='R'){
                a[i][j] = '.';
                red_pos = make_pair(i,j);
            }
            if(a[i][j]=='B'){
                a[i][j] = '.';
                blue_pos = make_pair(i,j);
            }
        }
    }
    find_min(0);
    if(ans==11)
        ans=-1;
    cout<<ans;
    return 0;
}