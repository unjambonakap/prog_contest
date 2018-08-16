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

const int maxn=1555;
const double pi=acos(-1.);


vi e[maxn];
int n;
int x[maxn], y[maxn];
int res[maxn];
int has[maxn];
ll dist(ll a, ll b){return a*a+b*b;}

int dfs(int a, int p=-1){
    has[a]=1;
    REP(i,e[a].size()){int b=e[a][i]; if (b!=p) has[a]+=dfs(b,a);}
    return has[a];
}

void go(int a, int b, vi &lst, int p=-1){
    res[b]=a+1;
    //printf("PUT %d on %d xaxa %d\n", a+1, b+1, has[a]);
    assert(has[a]==lst.size()+1);
    if (!lst.size()) return;
    vector<pair<double,int> > A;
    REP(i,lst.size()) A.pb(MP(atan2(y[lst[i]]-y[b],x[lst[i]]-x[b]),lst[i]));
    sort(ALL(A));
    REP(i,lst.size()) A.pb(A[i]);

    int m=0;
    REP(i,lst.size()-1) if (A[i+1].ST-A[i].ST>pi) m=i+1;
    //printf("HAVE %d %d >> \n", a, b);
    //REP(i,lst.size()) printf("%d >> %lf\n", A[m+i].ND, A[m+i].ST);
    REP(i,e[a].size()){
        int u=e[a][i];
        if (u==p) continue;
        vi tmp;
        int best=0;
        REP(j,has[u]-1) tmp.pb(A[m++].ND);
        go(u,A[m++].ND,tmp,a);
    }
}

int main(){
    cin>>n;
    REP(i,n-1){int a, b; scanf(" %d%d", &a,&b); --a; --b; e[a].pb(b); e[b].pb(a);}
    REP(i,n) scanf(" %d%d", x+i,y+i);

    dfs(0);
    int u=0;
    REP(i,n) if (x[i]<x[u]) u=i;
    vi lst; REP(i,n) if (i!=u) lst.pb(i);
    go(0,u,lst);


    REP(i,n-1) printf("%d ", res[i]); printf("%d\n", res[n-1]);
    return 0;
}


