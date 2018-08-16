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


const int maxn=333;
const int maxe=2*1111+2*maxn;
const int inf=1e9;
int U[maxn];

struct mfmc{

    int to[maxe], from[maxe], prev[maxe], f[maxe], u[maxe], c[maxe], last[maxn];
    int dist[maxn];
    int par[maxn];
    int P[maxn];
    int ne,n,C;
    mfmc(int n):n(n){n=ne=C=0; memset(last,-1,sizeof(last)); memset(f,0,sizeof(f));}
    void init(){
        C=0;
        memset(dist,0x7f,sizeof(dist));
        dist[0]=0;
        while(1){
            int fd=0;
            REP(j,ne) if (f[j]<u[j] && dist[to[j]]>dist[from[j]]+c[j]) dist[to[j]]=dist[from[j]]+c[j], fd=1;
            if (!fd) break;
        }
        REP(i,n) P[i]=dist[i];
    }

    int adde(int a, int b, int _u, int _c){
        assert(ne<maxe);
        from[ne]=a; to[ne]=b; u[ne]=_u; c[ne]=_c; prev[ne]=last[a]; last[a]=ne; ++ne;
        swap(a,b);
        from[ne]=a; to[ne]=b; u[ne]=0; c[ne]=-_c; prev[ne]=last[a]; last[a]=ne; ++ne;
        return ne-2;
    }

    int augment(){
        memset(dist,0x7f,sizeof(dist));
        dist[0]=0; par[0]=-1;
        priority_queue<pii,vector<pii>,greater<pii> > q;
        q.push(MP(0,0));
        while(!q.empty()){
            int p=q.top().ND, d=q.top().ST; q.pop();
            if (dist[p]!=d) continue;
            for (int i=last[p]; i!=-1; i=prev[i]) if (f[i]<u[i]){
                int nc=c[i]+P[p]-P[to[i]];
                if (dist[to[i]]>nc+d) dist[to[i]]=nc+d, par[to[i]]=i, q.push(MP(dist[to[i]],to[i]));
            }
        }
        if (dist[1]>inf) return 0;
        REP(i,n) P[i]+=dist[i];
        int p=1;
        int nf=inf;
        while(par[p]!=-1){ checkmin(nf,u[par[p]]-f[par[p]]); p=from[par[p]]; }
        C+=(P[1]-P[0])*nf;
        p=1;
        while(par[p]!=-1){ f[par[p]]+=nf; f[par[p]^1]-=nf; p=from[par[p]]; }
        return nf;
    }
};


int main(){
    int n, m;
    freopen("gas.in", "r", stdin);
    freopen("gas.out", "w", stdout);
    cin>>n>>m;
    assert(n<maxn);
    vector<pii> tb;
    mfmc flow(n+2);

    int res=0;
    REP(i,m){ int a, b, v; scanf(" %d%d%d",&a,&b,&v); --a; --b; res+=v; U[a]-=v; U[b]+=v; tb.pb(MP(flow.adde(a+2,b+2,inf,1),v)); }
    int sa=0, sb=0;
    REP(i,n) if (U[i]>0) flow.adde(0,i+2,U[i],0), sa+=U[i]; else if (U[i]<0) flow.adde(i+2,1,-U[i],0), sb-=U[i];
    int cnt=0;
    if (sa!=sb) goto fail;
    flow.init();
    while(1){
        int x=flow.augment();
        cnt+=x;
        if (!x) break;
    }
    if (cnt!=sa) goto fail;
    printf("%d\n", res+flow.C);
    REP(i,m) printf("%d\n", flow.f[tb[i].ST]+tb[i].ND);
    return 0;
fail:;
     printf("-1\n");
     return 0;
}


