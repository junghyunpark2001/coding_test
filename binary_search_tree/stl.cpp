#include <iostream>
#include <set>
#include <map>

using namespace std;

void set_example(){
    set<int> s;
    s.insert(-10); s.insert(100); s.insert(15);
    s.insert(-10);
    cout<<s.erase(100)<<'\n';
    cout<<s.erase(20)<<'\n';
    if(s.find(15)!=s.end()) cout<<"15 is in s\n";
    else cout<<"15 is not in s\n";
    cout<<s.size()<<'\n';
    cout<<s.count(50)<<'\n';
    for(auto e:s)cout<<e<<' ';
    cout<<'\n';
    s.insert(-40);

    set<int>::iterator it1 = s.begin();
    it1++;
    auto it2 = prev(it1);
    it2 = next(it1);
    advance(it2,-2);
    auto it3 = s.lower_bound(-20);

    cout<<*it1<<'\n';
    cout<<*it2<<'\n';
    cout<<*it3<<'\n';
}

void multiset_example(){
    multiset<int> ms;
    ms.insert(-10); ms.insert(100); ms.insert(15);
    ms.insert(-10); ms.insert(15);
    cout<<ms.size()<<'\n';
    for(auto e: ms)cout<<e<<' ';
    cout<<"\n";
    cout<<ms.erase(15)<<'\n';
    ms.erase(ms.find(-10));
    ms.insert(100);
    cout<<ms.count(100)<<'\n';
    auto it1 = ms.begin();
    auto it2 = ms.upper_bound(100);
    auto it3 = ms.find(100);
}

void map_example(){
    map<string,int> m;
    m["hi"] = 123;
    m["bkd"] = 1000;
    m["gogo"] = 165;
    cout<<m.size()<<'\n';
    m["hi"] = -7;
    if(m.find("hi")!=m.end())cout<<"hi in m\n";
    else cout<<"hi not in m\n";
    m.erase("bkd");
    for(auto e: m) cout<<e.first<<' '<<e.second<<'\n';
    auto it1 = m.find("gogo");
    cout<<it1->first << ' '<< it1->second <<'\n';
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
}