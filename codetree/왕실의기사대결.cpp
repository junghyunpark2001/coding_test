#include <iostream>
#include <tuple>
#include <vector>
using namespace std;



int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

int l,n,q; 
// 0:empty, 1:trap, 2:wall
int board[43][43];
int knight_board[43][43];
int tmp_board[43][43];
bool dead[33];
vector<tuple<int,int,int,int,int>> knights;
int damage[33];

void print_board(){
    for(int i=1;i<=l;i++){
        for(int j=1;j<=l;j++){
            cout<<knight_board[i][j]<<" ";

        }
        cout<<'\n';
    }
}
void knight_initialize(){
    for(int i=1;i<=n;i++){
        int r,c,h,w,k;
        tie(r,c,h,w,k) = knights[i];
        for(int x=r;x<r+h;x++){
            for(int y=c;y<c+w;y++){
                knight_board[x][y] = i;
            }
        }
    }
}
bool check = 1;
bool knight_move[33];

void check_push(int i,int d){
    knight_move[i] = 1;
    if(check==0) return;
    int r,c,h,w,k;
    tie(r,c,h,w,k) = knights[i];
    for(int x=r;x<r+h;x++){
        for(int y=c;y<c+w;y++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx>l||nx<1||ny>l||ny<1){check = 0; return;}
            if(board[nx][ny]==2){check=0;return;}
            if(knight_board[nx][ny]!=i) check_push(knight_board[nx][ny],d);
        }
    }
}

void push(int i,int d){
    for(int a=1;a<=l;a++) fill(knight_board[a],knight_board[a]+1+l,0);
    
    for(int a=1;a<=n;a++) if(knight_move[a]){
        int r,c,h,w,k;
        tie(r,c,h,w,k) = knights[a];
        int nx = r + dx[d];
        int ny = c + dy[d];
        r = nx;
        c = ny;
        knights[a] = {r,c,h,w,k};

    }
    for(int a=1;a<=n;a++){
        if(dead[a]) {continue;}
        int r,c,h,w,k;
        tie(r,c,h,w,k) = knights[a];

        for(int x=r;x<r+h;x++)
            for(int y=c;y<c+w;y++){
                knight_board[x][y] = a;
                if(a!=i && knight_move[a] && board[x][y]==1){
                    k--;
                    damage[a]++;
                }
            } 
        knights[a] = {r,c,h,w,k};   
    }
}

void die(){
    for(int i=1;i<=n;i++){
        int r,c,h,w,k;
        tie(r,c,h,w,k) = knights[i];
        if(k<=0){
            dead[i] = 1;

        }
    }
}

void attack(int i,int d){
    int k;
    fill(knight_move,knight_move+n+1,0);
    tie(ignore,ignore,ignore,ignore,k) = knights[i];
    if(k<=0) return;
    check = 1;
    check_push(i,d);
    
    if(check) push(i,d);
    die();

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>l>>n>>q;
    for(int i=1;i<=l;i++){
        for(int j=1;j<=l;j++){
            cin>>board[i][j];
        }
    }
    knights.push_back({0,0,0,0,0});
    for(int i=1;i<=n;i++){
        // (r,c) 높이, 너비, 체력
        int r,c,h,w,k;
        cin>>r>>c>>h>>w>>k;
        knights.push_back(make_tuple(r,c,h,w,k));
    }
    knight_initialize();
    for(int a=0;a<q;a++){
        int i,d;
        cin>>i>>d;
        attack(i,d);

    }
    int result = 0;
    for(int i=1;i<=n;i++){
        if(!dead[i]){
            result+=damage[i];
        }
    }
    cout<<result<<'\n';
}