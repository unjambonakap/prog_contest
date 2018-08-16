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


const int maxn=55;

int g[maxn][maxn];
int f[maxn][maxn];
int vis[maxn];
int can[maxn];
int val[maxn];
int step;
int n;
int T;

int dfs(int a, int fx=10000){
    if (a==T) return fx;
    if (vis[a]==step) return 0;
    vis[a]=step;
    REP(i,n) if (can[i] && f[a][i]<g[a][i]){
        int u=dfs(i,min(fx,g[a][i]-f[a][i]));
        if (u){f[a][i]+=u;  f[i][a]-=u; return u;}
    }
    return 0;
}

int mf(int s){
    memset(f,0,sizeof(f));
    int res=0;
    ++step;
    while(1){
        int x=dfs(s); res+=x;
        if (!x){
            ++step;
            x=dfs(s);
            res+=x;
            if (!x) break;
        }
    }
    return res;

}

int main(){
    //freopen("tunnels.in", "r", stdin);
    //freopen("tunnels.out", "w", stdout);
    int m;
    int tn=0;
    T=0;

    while(cin>>n>>m,n){
        ++n;
        ++tn;
        memset(g,0,sizeof(g));
        REP(i,m){int a, b; scanf(" %d%d", &a,&b); ++g[a][b]; ++g[b][a];}
        memset(can,1,sizeof(can));
        REP(i,n) val[i]=1e8;

        int best=0;
        while(1){

            FOR(i,1,n) if (can[i]) val[i]=min(val[i],mf(i)+best);


            vi tb;
            best=1e8;
            FOR(i,1,n) if (can[i]){
                if (val[i]<best) best=val[i], tb.clear();
                if (val[i]==best) tb.pb(i);
            }
            REP(i,tb.size()) can[tb[i]]=0;

            if (!can[1]){
                printf("Case %d: %d\n", tn,best);
                puts("");
                break;
            }
        }
    }

    return 0;
}

