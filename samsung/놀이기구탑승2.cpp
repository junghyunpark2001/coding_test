#include <iostream>
#include <cmath>
#include <tuple>


#define EMPTY 0

using namespace std;

typedef tuple<int,int,int,int> Cell; // 친구, 빈공간, -x, -y

int n;

int target_num[22];
bool friends[402][402];

int rides[22][22];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

bool InRange(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

bool IsFriend(int n1, int n2){
    return friends[n1][n2];
}

Cell curcell(int num, int x, int y){
    int friend_cnt = 0, space_cnt = 0;
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(!InRange(nx,ny)) continue;
        if(rides[nx][ny]==0) space_cnt++;
        else if(IsFriend(num,rides[nx][ny])) friend_cnt++;
    }
    return make_tuple(friend_cnt,space_cnt,-x,-y);
}

void move(int num){
    Cell best_cell = make_tuple(0,0,-(n+1),-(n+1));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(rides[i][j]==EMPTY){
                Cell curr = curcell(num,i,j);
                if(best_cell<curr) best_cell = curr;
            }
    int x,y;
    tie(ignore, ignore, x, y) = best_cell;
    rides[-x][-y] = num;
}

int score(int x,int y){
    int cnt = 0;
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(InRange(nx,ny) && IsFriend(rides[x][y],rides[nx][ny])) cnt++;
    }
    return (int)pow(10, cnt - 1);
}

int totalscore(){
    int result = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            result+=score(i,j);
    return result;
}

int main(void){
    cin>>n;
    for(int i=1;i<=n*n;i++){
        cin>>target_num[i];
        for(int j=1;j<=4;j++){
            int friend_num;
            cin>>friend_num;

            friends[target_num[i]][friend_num] = true;
        }
    }

    for(int i=1;i<=n*n;i++)
        move(target_num[i]);

    int ans = totalscore();
    cout<<ans;

    
}