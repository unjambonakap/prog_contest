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

const int maxn=2222;
const int maxe=maxn*maxn;
const int oo=1e9;
const double eps=1e-9;

int to[maxe],from[maxe],f[maxe],u[maxe],prev[maxe],last[maxn],ne;
int vis[maxn];
int x[maxn], y[maxn], nx[maxn], mx[maxn];
int N;
int n,STEP;


double dist(int x, int y){return sqrt(x*x+y*y);}

void adde(int a, int b, int x){
    to[ne]=b; from[ne]=a; f[ne]=0; u[ne]=x; prev[ne]=last[a]; last[a]=ne; ++ne;
    swap(a,b); x=0;
    to[ne]=b; from[ne]=a; f[ne]=0; u[ne]=x; prev[ne]=last[a]; last[a]=ne; ++ne;
}

int dfs(int a){
    if (a==1) return 1;
    if (vis[a]==STEP) return 0;
    vis[a]=STEP;
    for (int i=last[a]; i!=-1; i=prev[i]) if (f[i]<u[i] && dfs(to[i])){ ++f[i]; --f[i^1]; return 1;}
    return 0;
}

int mf(){
    memset(f,0,sizeof(int)*ne);
    ++STEP;
    int res=0;
    while(1){
        if (!dfs(0)){++STEP; if (!dfs(0)) break;}
        ++res;
    }
    return res;
}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        double D;
        cin>>N>>D;
        int na=0;
        REP(i,N) scanf(" %d%d%d%d",x+i,y+i,nx+i,mx+i), na+=nx[i];

        ne=0;
        memset(last,-1,sizeof(last));
        REP(i,N) adde(2+i,1,0);
        REP(i,N) adde(0,2+i,nx[i]);
        REP(i,N) adde(2+i,2+N+i,mx[i]);
        REP(i,N) REP(j,N) if (i!=j && dist(x[i]-x[j],y[i]-y[j])<D+eps) adde(2+N+i,2+j,oo);


        vi tb;
        REP(i,N){
            if (i) u[2*i-2]=0;
            u[2*i]=na;
            if (mf()==na) tb.pb(i);
        }
        if (tb.size()==0) tb.pb(-1);
        REP(i,tb.size()-1) printf("%d ",tb[i]);
        printf("%d\n",tb.back());
    }
    return 0;
}

