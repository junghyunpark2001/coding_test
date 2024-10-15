#include <iostream>
#include <string>
#include <deque>
#include <tuple>
#include <unordered_map>
#include <set>

using namespace std;

#define INF 1987654321
#define MAX_N 50000
#define MAX_D 300

int q, n;
set<int> is_in_readyq[MAX_D + 1];

priority_queue<int, vector<int>, greater<int> > rest_judger;


struct URL{
    int tme, id;
    int num;

    bool operator<(cont Url& b) const{
        if(id!=b.id) return id>b.id;
        return tme>b.tme;
    }
}
priority_queue<URL> url_pq[MAX_D + 1];