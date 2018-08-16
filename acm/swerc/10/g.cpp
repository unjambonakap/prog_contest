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

const int maxn=355;
const int maxm=maxn*maxn/2;

int n,m;
int ea[maxm], eb[maxm], ew[maxm];
int u[maxm], v[maxm];
int N;

int par[maxn];

int root(int a){return par[a]<0?a:par[a]=root(par[a]);}
int join(int a, int b){a=root(a); b=root(b); if (a!=b){par[a]=b; return 1;} return 0;}

int clean(){
    memset(par,-1,sizeof(par));
    int px=n-2;
    REPV(i,N){
        int a=root(ea[v[i]]),b=root(eb[v[i]]);
        if (a==b) continue;
        if (!px) return v[i];
        par[a]=b;
        u[--px]=v[i];
    }
    assert(0);
    return -1;
}

int main(){
    while(cin>>n>>m,n){
        vector<pair<int,pii> > tb;
        REP(i,m){ int a,b,c; scanf(" %d%d%d",&a,&b,&c); tb.pb(MP(c,MP(a,b)));}
        sort(ALL(tb));
        REP(i,m) ea[i]=tb[i].ND.ST, eb[i]=tb[i].ND.ND, ew[i]=tb[i].ST;
        assert(n<maxn);
        if (n==2){puts("0"); continue;}

        memset(par,-1,sizeof(par));
        int best=INT_MAX, j=0;
        int have=n;

        N=0;
        for (; j<m && have>1; ++j) have-=join(ea[j],eb[j]), v[N++]=j;

        while(1){
            int lx=clean();
            best=min(best,ew[u[n-3]]-ew[lx]);
            N=n-2;
            REP(i,N) v[i]=u[i];
            have=2;

            for (; j<m && have>1; ++j) have-=join(ea[j],eb[j]), v[N++]=j;
            if (have>1) break;
        }

        printf("%d\n",best);
    }
    return 0;
}

