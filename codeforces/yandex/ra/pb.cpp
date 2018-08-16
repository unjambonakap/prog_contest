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
const int m=3;
int n;
int k[m];
ll tk[m];
ll to[maxn];

list<ll> q[m];

struct event{
    ll t;
    int id;
    int p;
    bool operator<(const event &e)const{
        if (t!=e.t) return t>e.t;
        return id<e.id;
    }
    event(ll t, int id, int p):t(t), id(id), p(p){}
};

int main(){
    REP(i, m) cin>>k[i];
    REP(i, m) cin>>tk[i];
    cin>>n;
    REP(i, n) cin>>to[i];
    REP(i, m) checkmin(k[i], n);
    REP(i, m) REP(j, k[i]) q[i].pb(0);

    priority_queue<event> ql;
    REP(i, n) ql.push(event(to[i], i, 0));
    ll res=0;
    while(!ql.empty()){
        event e=ql.top(); ql.pop();
        if (e.p==m){
            checkmax(res, e.t-to[e.id]);
            continue;
        }
        e.t=max(q[e.p].front(), e.t)+tk[e.p];
        q[e.p].pop_front();
        q[e.p].pb(e.t);
        ++e.p;
        ql.push(e);
    }

    cout<<res<<endl;

    return 0;
}



