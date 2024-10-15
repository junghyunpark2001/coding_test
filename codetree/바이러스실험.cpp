#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

int dx[8] = {1,1,1,-1,-1,-1,0,0};
int dy[8] = {0,1,-1,0,1,-1,1,-1};

int n,m,k;
int nutrition[12][12];
int now_nutrition[12][12];
int dead[12][12];
vector<int> viruses[12][12];

void initialize(){

    cin>>n>>m>>k;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>nutrition[i][j];
        }
    }
    
    for(int i=0;i<m;i++){
        int r,c,age;
        cin>>r>>c>>age;
        viruses[r][c].push_back(age);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            now_nutrition[i][j] = 5;
        }
    }
}

void eat(){
    for(int i=1;i<=n;i++) fill(dead[i],dead[i]+n+1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sort(viruses[i][j].begin(),viruses[i][j].end());

            
            vector<int> survivors;
            for(int it=0;it<viruses[i][j].size();it++){
                if(viruses[i][j][it]<=now_nutrition[i][j]){
    
                    now_nutrition[i][j]-=viruses[i][j][it];
          
                    survivors.push_back(viruses[i][j][it]+1);
                }
                else{
                    
                    dead[i][j]+=viruses[i][j][it]/2;
                }
            }
            viruses[i][j] = survivors;
        }
    }
    
}

void add_nut1(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            now_nutrition[i][j] += dead[i][j];
        }
    }
}

void breed(){
    vector<pair<int,int>> vir_tmp;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int it=0;it<viruses[i][j].size();it++){
                if(viruses[i][j][it]%5==0)vir_tmp.push_back({i,j});
            }
        }
    }
    for(int i=0;i<vir_tmp.size();i++){
        for(int dir = 0;dir<8;dir++){
            int nx = vir_tmp[i].first + dx[dir];
            int ny = vir_tmp[i].second + dy[dir];
            if(nx<1||nx>n||ny<1||ny>n) continue;
            viruses[nx][ny].push_back(1);
        }
    }
}

void add_nut2(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            now_nutrition[i][j] += nutrition[i][j];
        }
    }
}

void simulate(){
    for(int a=0;a<k;a++){
        eat();



        add_nut1();

        breed();


        add_nut2();

    }

}

int result(){
    int result = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            result += viruses[i][j].size();
        }
    }
    return result;
}



int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    initialize();

    simulate();
    

    cout<<result()<<'\n';
   

}