#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define vertex tuple<int,int> 

int dx[4] = {-1,-1,1,1};
int dy[4] = {1,-1,-1,1};
int n;
int ground[22][22];
int whose[22][22];
int dif = INT_MAX;

bool inside_index(const vector<pair<int, int>>& v,int x,int y){
    int flag = 0;
    if(x<=v[0].first&&x>=v[2].first&&y<=v[1].second&&y>=v[3].second) return true;
    return false;
}

void map_score(){
    vector<int> pops = {0,0,0,0,0};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            pops[whose[i][j]-1] += ground[i][j];
        }
    }


    sort(pops.begin(),pops.end());
    int tmp = pops[4]-pops[0];
    // cout<<"tmp is "<<tmp<<'\n';
    if(tmp<dif){dif = tmp;}

    
}

void population(const vector<pair<int, int>>& v,int a, int b){
    for(int i=0;i<n;i++) fill(whose[i],whose[i]+n,0);
    for(int i=0;i<v[3].first;i++){
        for(int j=0;j<=v[2].second;j++){
            if(whose[i][j]==1) break;
            whose[i][j]=2;
        }
    }
    for(int i=0;i<=v[1].first;i++){
        for(int j=v[2].second+1;j<n;j++){

            whose[i][j] = 3;
        }
    }

    for(int i=v[1].first+1;i<n;i++){
        for(int j=v[0].second;j<n;j++){
            whose[i][j] = 5;
        }
    }

    for(int i=0;i<4;i++){
        whose[v[i].first][v[i].second] = 1;
    }
    
    for(int i=1;i<=a;i++){
        whose[v[0].first+i*dx[0]][v[0].second+i*dy[0]] = 1;
    }
    for(int i=0;i<=b;i++){
        whose[v[1].first+i*dx[1]][v[1].second+i*dy[1]] = 1;

    }
    for(int i=1;i<=a;i++){
        whose[v[2].first+i*dx[2]][v[2].second+i*dy[2]] = 1;
    }
    for(int i=1;i<=b;i++){
        whose[v[3].first+i*dx[3]][v[3].second+i*dy[3]] = 1;
    }

    for(int i=0;i<n;i++){
        bool flag = 0;
        for(int j=0;j<n;j++){
            if((i==v[0].first&&j==v[0].second)||(i==v[2].first&&j==v[2].second))
            continue;
            if(whose[i][j]==1){
                flag = !flag;
            }
            if(flag==1) whose[i][j] = 1;
            
        }
    }
    for(int i=0;i<v[3].first;i++){
        for(int j=0;j<=v[2].second;j++){
            if(whose[i][j]==1) break;
            whose[i][j]=2;
        }
    }
    for(int i=v[3].first;i<n;i++){
        for(int j=0;j<v[0].second;j++){
            if(whose[i][j]==1) break;
            whose[i][j] = 4;
        }
    }
    map_score();
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<whose[i][j]<<" ";
    //     }
    //     cout<<'\n';
    // }
    // cout<<'\n';


}



void in_range(int i,int j,int a,int b){
    vector<pair<int,int>> v(4);

    int x0,y0,x1,y1,x2,y2,x3,y3;
    v[0].first = i; v[0].second = j;
    v[1].first = v[0].first + a*dx[0];v[1].second = v[0].second + a*dy[0];
    v[2].first = v[1].first + b*dx[1];v[2].second = v[1].second + b*dy[1];
    v[3].first = v[2].first + a*dx[2];v[3].second = v[2].second + a*dy[2];
    int flag = 0;
    for(int i=0;i<4;i++){
        if(v[i].first>=0&&v[i].first<n&&v[i].second>=0&&v[i].second<n) flag++;
    }
    if(flag==4){
        population(v,a,b);
    }

    // if(flag==4) return true;
    // return false;


}

void divide(){
    // 각 좌표에 대해
    for(int i=2;i<n;i++){
        for(int j=1;j<(n-1);j++){
            // 다양한 사각형
            for(int a=1;a<n;a++){
                for(int b=1;b<n;b++){
                    in_range(i,j,a,b);
                        
                    
                }
            }
        }
    }
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>ground[i][j];
        }
    }
    divide();

    cout<<dif;

}