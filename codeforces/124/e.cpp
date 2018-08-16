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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=111111;
vector<pii> e[maxn];
int lst[maxn];
int n, m;
int par[maxn];
int with[maxn];
int is[maxn];
ll dist[maxn];

int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
int join(int a, int b){a=root(a); b=root(b); if (a==b) return 0; par[a]=b; return 1;}

struct event{
    int a,p;
    ll d;
    event(ll d ,int a, int p):d(d),a(a),p(p){}
    bool operator<(const event &e)const{
        if (d!=e.d) return d>e.d;
        return a<e.a;
    }
};

int main(){
    cin>>n>>m;
    REP(i,m){ int a, b, c; scanf(" %d%d%d",&a,&b,&c); --a; --b; e[a].pb(MP(b,c)); e[b].pb(MP(a,c));}
    int K; cin>>K;
    REP(i,K) scanf(" %d", lst+i), --lst[i];
    memset(par,-1,sizeof(par));
    priority_queue<event> q;

    memset(dist,-1,sizeof(dist));
    memset(with,-1,sizeof(with));
    REP(i,K) q.push(event(0,lst[i],lst[i])), is[lst[i]]=1;
    ll res=0;
    vector<pair<ll,pii> > A;
    while(q.size()){
        assert(q.size());
        event ex=q.top(); q.pop();
        int a=ex.a, p=ex.p; ll d=ex.d;

        if (with[a]==-1){
            if (!a) res+=d;
            with[a]=p, dist[a]=d;
            REP(i,e[a].size()) q.push(event(d+e[a][i].ND,e[a][i].ST,p));
        }else A.pb(MP(dist[a]+d,MP(with[a],p)));
    }
    sort(ALL(A));
    REP(i,A.size()){
        int a=A[i].ND.ST, b=A[i].ND.ND;
        if (join(a,b)) res+=A[i].ST;
    }
    cout<<res<<endl;
    return 0;
}
     


