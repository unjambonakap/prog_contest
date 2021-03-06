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

const int maxn=222;
const int oo=1e9;
const int maxe=maxn*maxn;

int to[maxe], from[maxe], f[maxe], u[maxe], prev[maxe], last[maxn];
int a[maxn];
int n,N,ne;
int g[maxn][maxn];
char buf[maxn];
int is[maxn];
int na;

int rmpa[maxn], rmpb[maxn];
int vis[maxn];
int STEP;


void adde(int a, int b, int F){
    to[ne]=b; from[ne]=a; f[ne]=F; u[ne]=0; prev[ne]=last[a]; last[a]=ne++;
    swap(a,b); F=0;
    to[ne]=b; from[ne]=a; f[ne]=F; u[ne]=0; prev[ne]=last[a]; last[a]=ne++;
}

int dfs(int a){
    if (a==1) return 1;
    if (vis[a]==STEP) return 0;
    vis[a]=STEP;
    for (int i=last[a]; i>=0; i=prev[i]) if (u[i]<f[i] && dfs(to[i])){
        ++u[i]; --u[i^1];
        return 1;
    }
    return 0;
}

int augment(){
    if (!dfs(0)){
        ++STEP;
        if (!dfs(0)) return 0;
    }
    return 1;
}



int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        REP(i,n) scanf(" %d",a+i);
        REP(i,n){
            scanf(" %s",buf);
            REP(j,n) g[i][j]=buf[j]=='Y';
            g[i][i]=1;
        }

        memset(is,0,sizeof(is));
        REP(i,n) if (a[i]==0) REP(j,n) if (g[i][j]&&a[j]) is[j]=1;

        ne=0; memset(last,-1,sizeof(last));
        na=0;
        vi lst;

        N=2;
        REP(i,n) if (a[i]){
            adde(0,N+na,a[i]);
            rmpa[i]=na++;
        }
        REP(i,n) if (a[i]){
            int uu=1;
            if (is[i]) uu=0, lst.pb(ne);
            adde(2+na+rmpa[i],1,uu);
        }

        N+=2*na;
        REP(i,n) REP(j,n) if (a[i] && g[i][j] && a[j]) adde(2+rmpa[i],2+na+rmpa[j],oo);

        memset(vis,0,sizeof(vis));
        STEP=0;
        int res=0;
        int fd=1;

        ++STEP;
        REP(i,na-lst.size()) if (!augment()){fd=0; break;}
        for (; fd; ++res){
            ++STEP;
            REP(i,lst.size()) ++f[lst[i]];
            REP(i,lst.size()) if (!augment()){fd=0; break;}
            if (!fd) break;
        }
        printf("%d\n",res);
    }
    return 0;
}

