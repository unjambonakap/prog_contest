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

const int maxn=44;
const int maxe=2*(maxn*maxn+maxn)+1e5;
const int inf=maxn*maxn;
int g[maxn][maxn];
int cost[maxe], f[maxe], u[maxe], from[maxe], to[maxe], last[maxe], prev[maxe];
int m;
int ce[maxn];
int d[2*maxn];
int fc;
int par[2*maxn];
int vis[2*maxn];
int step;


int n, A, B;
int getc(char c){if (c=='/') return 0; return 1+(c=='C');}

int adde(int a, int b, int cx, int ux){
    cost[m]=cx; f[m]=0; u[m]=ux; from[m]=a; to[m]=b; prev[m]=last[a]; last[a]=m; ++m;
    cost[m]=-cx; f[m]=0; u[m]=0; from[m]=b; to[m]=a; prev[m]=last[b]; last[b]=m; ++m;
    return m-2;
}

void go(){
    while(1){
        memset(d,0,sizeof(d));
        memset(par,-1,sizeof(par));

        REP(_step,n-1){
            int fd=0;
            REP(i,m) if (f[i]<u[i] && d[to[i]]>d[from[i]]+cost[i]){
                par[to[i]]=i;
                fd=1;
                d[to[i]]=d[from[i]]+cost[i];
            }
            if (!fd) return;
        }
        int fd=0;
        REP(i,m) if (f[i]<u[i] && d[to[i]]>d[from[i]]+cost[i]){//negative cycle
            int p=i;
            par[to[i]]=p;
            ++step;
            vis[to[i]]=step;
            vi tb;
            tb.pb(p); p=par[from[p]];
            while(vis[to[p]]!=step){int y=par[from[p]]; tb.pb(p); vis[to[p]]=step;  p=y; }
            int x=from[p];
            REPV(i,tb.size()){
                int y=tb[i];
                fc+=cost[y];
                ++f[y]; --f[y^1];
                if (from[y]==x) break;
            }
            fd=1;
            break;
        }
        if (!fd) return;
    }

}


int main(){
    int tn=0;
    while(cin>>n>>A>>B, n){
        ++tn;
        REP(i,n){
            string s; cin>>s;
            REP(j,n) g[i][j]=getc(s[j]);
        }
        m=0;
        //if (tn!=7)continue;

        memset(last,-1,sizeof(last));
        memset(prev,0,sizeof(prev));
        REP(i,n) ce[i]=adde(i,n+i,0,0);
        int cntx=0;
        REP(i,n) REP(j,n){
            if (g[i][j]==1) adde(n+i,j,-1,1);
            else if (g[i][j]==2) adde(n+i,j,-inf,1), ++cntx;
        }
        fc=cntx*inf;
        n*=2;

        int res=-1;
        REP(i,n+1){
            REP(j,n/2) u[ce[j]]=u[ce[j]^1]=i;
            go();
            if (fc>0) continue;
            int tmp=-fc+cntx;
            if (i*B>tmp*A) continue;
            checkmax(res,tmp-cntx);
        }

        printf("Case %d: ", tn);
        if (res==-1) puts("impossible");
        else printf("%d\n", res);
    }
    return 0;
}



