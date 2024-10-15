#include <iostream>
#include <utility>

using namespace std;

int n;

bool dragon_point[101][101];

bool new_dragon_point[101][101];

bool paper[101][101];

pair<int,int> rotate(int x,int y,int center_x, int center_y){
    return make_pair(y-center_y+center_x, center_x-x+center_y);
}

void simulate(int center_x, int center_y){
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
            new_dragon_point[i][j] = false;
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
            if(dragon_point[i][j]){
                int next_x,next_y;
                tie(next_x,next_y) = rotate(i,j,center_x,center_y);

                new_dragon_point[next_x][next_y] = true;
            }
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
            if(new_dragon_point[i][j])
                dragon_point[i][j] = true;

}

void draw_dragon_curve(int x,int y,int d,int g){
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
            dragon_point[i][j] = false;
    
    int dx[4] = {0,-1,0,1};
    int dy[4] = {1,0,-1,0};

    int start_x = x, start_y = y;
    int end_x = x + dx[d], end_y = y + dy[d];
    dragon_point[start_x][start_y] = true;
    dragon_point[end_x][end_y] = true;

    while(g--){
        simulate(end_x,end_y);
        tie(end_x,end_y) = rotate(start_x, start_y,end_x,end_y);
    }
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
            if(dragon_point[i][j])
                paper[i][j] = true;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0;i<n;i++){
        int x,y,d,g;
        cin>>x>>y>>d>>g;
        draw_dragon_curve(x,y,d,g);
    }

    int ans = 0;

    for(int i=0;i<100;i++) 
        for(int j=0;j<100;j++)
            if(paper[i][j]&&paper[i][j+1]&&paper[i+1][j]&&paper[i+1][j+1])
                ans++;
    
    cout<<ans;

    return 0;
}