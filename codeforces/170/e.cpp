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
typedef unsigned int uint;
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

const int maxn=888;
const int maxe=maxn*maxn;
const double oo=1e9;
const double eps=1e-9;

int to[maxe], from[maxe], f[maxe], u[maxe], prev[maxe], last[maxn];
double cost[maxe];
int ne,n;
int x[maxn], y[maxn];
double P[maxn];
double res;
int S,T;
double dist[maxn];
int vis[maxn];
int par[maxn];

void adde(int a, int b, int _u, double c){
    from[ne]=a; to[ne]=b; u[ne]=_u; cost[ne]=c; prev[ne]=last[a]; last[a]=ne++;
    swap(a,b); _u=0; c=-c;
    from[ne]=a; to[ne]=b; u[ne]=_u; cost[ne]=c; prev[ne]=last[a]; last[a]=ne++;
}

double sqr(int x, int y){return sqrt(x*x+y*y);}

void init(){
    priority_queue<pair<double,int> > q;
    REP(i,T) P[i]=oo;

    q.push(MP(0,S));
    P[S]=0;
    while(q.size()){
        double c=-q.top().ST;
        int a=q.top().ND;
        q.pop();
        if (c+eps>P[a]) continue;

        for (int i=last[a]; i>=0; i=prev[i]) if (f[i]<u[i]){
            double nc=c+cost[i];
            int b=to[i];
            if (nc+eps<P[b]) P[b]=nc, q.push(MP(-nc,b));
        }
    }
}

int go(){
    priority_queue<pair<double,int> > q;

    memset(vis,0,sizeof(vis));
    REP(i,T+1) dist[i]=oo;
    q.push(MP(0,S));
    dist[S]=0;

    while(q.size()){
        double c=-q.top().ST;
        int a=q.top().ND;
        q.pop();

        if (vis[a]) continue;
        vis[a]=1;

        for (int i=last[a]; i>=0; i=prev[i]) if (f[i]<u[i]){
            int b=to[i];
            double nc=c+cost[i]+P[a]-P[b];
            if (nc+eps<dist[b]) dist[b]=nc, q.push(MP(-nc,b)), par[b]=i;
        }
    }
    if (!vis[T]) return 0;
    REP(i,T+1) P[i]+=dist[i];

    int p=T;
    while(p!=S) ++f[par[p]], --f[par[p]^1], p=from[par[p]];
    res+=P[T]-P[S];
    return 1;
}

int main(){
    cin>>n;
    memset(last,-1,sizeof(last));
    REP(i,n) scanf(" %d%d",x+i,y+i);
    REP(i,n) adde(2*n,i,2,0), adde(n+i,2*n+1,1,0);
    REP(i,n) REP(j,n) if (y[i]>y[j]) adde(i,n+j,1,sqr(x[i]-x[j],y[i]-y[j]));

    S=2*n; T=2*n+1;
    int fd=1;
    init();
    REP(i,n-1) if (!go()){fd=0; break;}
    if (!fd) puts("-1");
    else printf("%.10lf\n",res);
    return 0;
}

