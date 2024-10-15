#include <iostream>
#include <queue>

using namespace std;

#define MAX_N 31
#define MAX_L 41

int l, n, q;
int info[MAX_L][MAX_L];
int bef_k[MAX_N];
int r[MAX_N], c[MAX_N], h[MAX_N], w[MAX_N], k[MAX_N];
int nr[MAX_N], nc[MAX_N];
int dmg[MAX_N];
bool is_moved[MAX_N];

int dx[4] = {-1,0,1,0,};
int dy[4] = {0,1,0,-1};