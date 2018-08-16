#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)

#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}
const int maxn=1e5+10;

int parent[maxn];
int root(int a){return parent[a]==-1?a:parent[a]=root(parent[a]);}

struct cmpA{
    bool operator()(const vi &a, const vi &b)const{
        if (a.size()!=b.size()) return a.size()<b.size();
        return a<b;
    }
};


void doit(ostringstream &os, vi &a, const vi &b){
    if (a.size()+b.size()>5){
        vi tmp;
        int na=5-b.size();
        REP(i, na) tmp.pb(a[a.size()-na+i]);

        REP(i, na-1) a.pop_back();

        doit(os, tmp, b);
    }else{
        int na=a.size(), nb=b.size();
        os<<na+nb<<endl;
        REP(i, na) os<<a[i]+1<<" ";
        REP(i, nb) os<<b[i]+1<<" ";
        os<<endl;
        REP(i, na) os<<a[(i+1)%na]+1<<" ";
        REP(i, nb) os<<b[(i+1)%nb]+1<<" ";
        os<<endl;
    }


}
int main(){
    int tb[maxn];
    int n;
    cin>>n;
    REP(i, n){ cin>>tb[i]; --tb[i]; }
    memset(parent, -1, sizeof(parent));
    REP(i, n) if (root(tb[i])!=root(i)) parent[root(tb[i])]=root(i);
    ostringstream os;
    int cnt=0;
    vector<vi> b[6];

    REP(i, n) if (parent[i]==-1){
        vi x;
        x.pb(i);
        int j=tb[i];
        while(j!=i) x.pb(j), j=tb[j];

        while(x.size()>5){
            doit(os, x, vi());
            ++cnt;
        }
        if (x.size()>=2) b[x.size()].pb(x);
    }
    while(b[2].size() && b[3].size()){
        doit(os, b[3].back(), b[2].back());
        ++cnt;
        b[2].pop_back(); b[3].pop_back();
    }
    while(b[2].size()>=2){
        doit(os, b[2][b[2].size()-2], b[2].back());
        b[2].pop_back(); b[2].pop_back();
        ++cnt;
    }
    while(b[3].size()>=3){
        doit(os, b[3][b[3].size()-2], b[3].back());
        b[3].pop_back();
        ++cnt;
        doit(os, b[3][b[3].size()-2], b[3].back());
        ++cnt;
        b[3].pop_back();
        b[3].pop_back();
    }
    REP(i, 6) while(b[i].size()){
        doit(os, b[i].back(), vi());
        b[i].pop_back();
        ++cnt;
    }





    printf("%d\n", cnt);
    cout<<os.str();



}
