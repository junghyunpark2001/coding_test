#include <iostream>
#include <tuple>
#include <climits>
#include <vector>

using namespace std;

#define X first 
#define Y second 


int santa_state[33]; // 0 : alive, 1 : pass, 2 : pass_last, -1 : oob
int board[53][53];
int santa_score[33];


// size, turns, santas, rudolf_power, santa_power
int n,m,p,c,d; 
vector<pair<int,int>> santas(33);
pair<int,int> rudolf;

int dx[8] = {-1,0,1,0,1,1,-1,-1};
int dy[8] = {0,1,0,-1,-1,1,-1,1};

int dist(int rx,int ry, int santa_num){
    int distance = (santas[santa_num].X-rx)*(santas[santa_num].X-rx) + 
                    (santas[santa_num].Y-ry)*(santas[santa_num].Y-ry);
    return distance;
}

void move(int santa_num,int dir){
    for(int i=1;i<=p;i++){
        if(santa_num==i) continue;
        if(santas[santa_num] == santas[i]){
           
            santas[i].X += dx[dir];
            santas[i].Y += dy[dir];
            if(santas[i].X<1||santas[i].X>n||santas[i].Y<1||santas[i].Y>n){ 
                santa_state[i] = -1;
                return;
            }
            move(i,dir);
        }
    }
}

void collision(int santa_num, int dir){
    int new_dir = dir;
    // if(dir<4){
    //     new_dir = (dir+2)%4;
    // } else{
    //     dir-=3;
    //     new_dir = 3+(dir+2)%4;
    // }
    int nx = santas[santa_num].X + c*dx[new_dir];
    int ny = santas[santa_num].Y + c*dy[new_dir];

    santas[santa_num].X = nx;
    santas[santa_num].Y = ny;
    if(nx<1||nx>n||ny<1||ny>n) santa_state[santa_num] = -1;
    else{
        move(santa_num,new_dir);
    }

}

void rudolf_collision(int santa_num, int dir){
    if(santas[santa_num]==rudolf){
        // cout<<"rudolf collided\n";
        santa_score[santa_num]+=c;
        santa_state[santa_num] = 1;
        collision(santa_num,dir);

    }
   
}


void rudolf_move(){
    int min_dist = INT_MAX;
    int close_santa;

    // find closest santa
    for(int i=1;i<=p;i++){
        if(santa_state[i]==-1) continue;
        if(dist(rudolf.X,rudolf.Y,i)<min_dist){
            min_dist = dist(rudolf.X,rudolf.Y,i);
            close_santa = i;
        } 
        else if(dist(rudolf.X,rudolf.Y,i)==min_dist){
            if(santas[i].first>santas[close_santa].first) close_santa = i;
            else if((santas[i].first == santas[close_santa].first) && 
                    (santas[i].second>santas[close_santa].second)) close_santa = i;
        }
    }

    // move closer to santa
    int closer_dist = INT_MAX;
    int nnx,nny;
    int ddir;
    for(int dir=0;dir<8;dir++){
        int nx = rudolf.X + dx[dir];
        int ny = rudolf.Y + dy[dir];
        if(nx<1||nx>n||ny<1||ny>n) continue;
        if(dist(nx,ny,close_santa)<closer_dist){
            closer_dist = dist(nx,ny,close_santa);
            nnx = nx;
            nny = ny;
            ddir = dir;
        }
    }

    // update rudolf coor
    rudolf.X = nnx;
    rudolf.Y = nny;

    rudolf_collision(close_santa,ddir);


}


int dist2(int nx,int ny){
    int distance = (rudolf.X-nx)*(rudolf.X-nx) + 
                    (rudolf.Y-ny)*(rudolf.Y-ny);
    return distance;
}

void santa_collision(int dir, int santa_num){
    santa_score[santa_num]+=d;
    santa_state[santa_num] = 1;

    int new_dir = (dir+2)%4;

    int nx = santas[santa_num].X + d*dx[new_dir];
    int ny = santas[santa_num].Y + d*dy[new_dir];

    santas[santa_num].X = nx;
    santas[santa_num].Y = ny;
    if(nx<1||nx>n||ny<1||ny>n) santa_state[santa_num] = -1;
    else{
        move(santa_num,new_dir);
    }
    
}
void santa_move(){
    for(int i=1;i<=p;i++){
        // santa #n
        if(santa_state[i]!=0) continue;
        int min_dist = dist2(santas[i].X,santas[i].Y);
        int nnx = santas[i].X, nny = santas[i].Y;
        int ddir;
        // cout<<i<<"th santa\n";
        for(int dir=0;dir<4;dir++){
            int nx = santas[i].X + dx[dir];
            int ny = santas[i].Y + dy[dir];
            if(nx<1||nx>n||ny<1||ny>n) continue;
            bool empty = 0;
            // cout<<nx<<" "<<ny<<'\n';
            for(int a=1;a<=p;a++){
                if(a==i) continue;
                
                if(make_pair(nx,ny)==santas[a]){empty = 1;}
            }
            if(empty==1) continue;
            // cout<<dist2(nx,ny)<<" ";
            
            if(dist2(nx,ny)<min_dist){
                min_dist = dist2(nx,ny);
                nnx = nx;
                nny = ny;
                ddir = dir;
            }
        }
        
        if(santas[i]!=make_pair(nnx,nny)) santas[i] = make_pair(nnx,nny);
        // cout<<'\n';
        if(santas[i]==rudolf){
            // cout<<i<<" collided\n";
            santa_collision(ddir, i);
        }
        
    }
    
}




void simulate(){
    // rudolf moves
    rudolf_move();
    santa_move();
    // cout<< "rudolf :\n";
    // cout<<rudolf.X<<" "<<rudolf.Y<<'\n';
    // cout<<"santas: \n";
    // for(int i=1;i<=p;i++){
    //     cout<<santas[i].X<<" "<<santas[i].Y<<'\n';
    // }
    // cout<<"satnas state: \n";
    // for(int i=1;i<=p;i++){
    //     cout<<santa_state[i]<<" ";
    // }
    // cout<<'\n';

    
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>p>>c>>d;

    cin>>rudolf.X>>rudolf.Y;
    board[rudolf.X][rudolf.Y] = -1;

    for(int i=1;i<=p;i++){
        int index;
        cin>>index;
        cin>>santas[index].first>>santas[index].second;
        board[santas[index].first][santas[index].second] = index;
    }

    for(int i=0;i<m;i++){
        // cout<<i<<"th turn\n";
        for(int j=1;j<=p;j++){
            if(santa_state[j]==1) santa_state[j] = 2;
            else if(santa_state[j]==2) santa_state[j] = 0;
        }
        simulate();
        bool end = 1;
        for(int i=1;i<=p;i++){
            if(santa_state[i]!=-1){ 
                santa_score[i]++;
                end = 0;
            }
            
        }
        // for(int i=1;i<=p;i++) cout<<santa_score[i]<<" ";
        if(end) break;
        
        
    }
    
    for(int i=1;i<=p;i++) cout<<santa_score[i]<<" ";
    
}