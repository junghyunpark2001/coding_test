#include <iostream>

using namespace std;

#define MAX_N 10

int n,m,k;

int board[11][11];

int next_board[11][11];

pair<int,int> traveler[11];

pair<int,int> exits;

int ans;

int sx, sy, square_size;

void move_all_travler(){
    for(int i=1;i<=m;i++){
        if(traveler[i].first == exits.first && traveler[i].second == exits.second)
            continue;

        if(traveler[i].first != exits.first){
            int nx = traveler[i].first;
            int ny = traveler[i].second;

            if(exits.first>nx) nx++;
            else nx--;

            if(!board[nx][ny]){
                traveler[i].first = nx;
                traveler[i].second = ny;
                ans++;
                continue;
            }
        }
        if(traveler[i].second != exits.second){
            int nx = traveler[i].first;
            int ny = traveler[i].second;

            if(exits.second > ny) ny++;
            else ny--;

            if(!board[nx][ny]){
                traveler[i].first = nx;
                traveler[i].second = ny;
                ans++;
                continue;
            }
        }
    }
}

void find_min_square(){
    for(int sz = 2;sz<=n;sz++){
        for(int x1=1;x1<=n-sz+1;x1++){
            for(int y1=1;y1<=n-sz+1;y1++){
                int x2 = x1 + sz - 1;
                int y2 = y1 + sz - 1;

                if(!(x1 <= exits.first && exits.first <= x2 && y1 <= exits.second && exits.second <= y2)) {
                    continue;
                }
                bool is_traveler_in = false;
                for(int l = 1; l <= m; l++) {
                    if(x1 <= traveler[l].first && traveler[l].first <= x2 && y1 <= traveler[l].second && traveler[l].second <= y2) {
                        // 출구에 있는 참가자는 제외합니다.
                        if(!(traveler[l].first == exits.first && traveler[l].second == exits.second)) {
                            is_traveler_in = true;
                        }
                    }
                }
                if(is_traveler_in) {
                    sx = x1;
                    sy = y1;
                    square_size = sz;

                    return;
                }

            }
        }
    }
}

void rotate_square(){
    for(int x = sx;x<sx+square_size;x++){
        for(int y = sy; y < sy + square_size; y++){
            if(board[x][y]) board[x][y]--;
        }
    }
    for(int x = sx; x < sx + square_size; x++)
        for(int y = sy; y < sy + square_size; y++) {
            int ox = x - sx, oy = y - sy;
            int rx = oy, ry = square_size - ox - 1;
            next_board[rx + sx][ry + sy] = board[x][y];
        }

    for(int x = sx; x < sx + square_size; x++)
        for(int y = sy; y < sy + square_size; y++) {
            board[x][y] = next_board[x][y];
        }
}

void rotate_travler_exit(){
    for(int i=1;i<=m;i++){
        int x = traveler[i].first;
        int y = traveler[i].second;
        if(sx <= x && x < sx + square_size && sy <= y && y < sy + square_size) {
            int ox = x - sx, oy = y - sy;
            int rx = oy, ry = square_size - ox - 1;
            traveler[i] = make_pair(rx + sx, ry + sy);
        }
    }
    int x = exits.first;
    int y = exits.second;
    if(sx <= x && x < sx + square_size && sy <= y && y < sy + square_size) {
        int ox = x - sx, oy = y - sy;
        int rx = oy, ry = square_size - ox - 1;
        exits = make_pair(rx + sx, ry + sy);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>board[i][j];

    for(int i=1;i<=m;i++){
        cin>>traveler[i].first;
        cin>>traveler[i].second;
    }

    cin>>exits.first;
    cin>>exits.second;

    while(k--){
        move_all_travler();
        bool is_all_escaped = true;
        for(int i = 1; i <= m; i++) {
            if(!(traveler[i].first == exits.first && traveler[i].second == exits.second)) {
                is_all_escaped = false;
            }
        }

        if(is_all_escaped) break;

        find_min_square();
        rotate_square();
        rotate_travler_exit();

    }

    cout<<ans<<'\n';
    cout<<exits.first<<" "<<exits.second;
}