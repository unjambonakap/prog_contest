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

const int maxn=401;
const int maxv=1e5+10;

int n;
int np,nq;
int dp[maxn/2+1][maxn][maxn];//pos,pl,pr,tsp
int is[maxn][maxn];
int P=9705276;
int Q=12805858;

ll tb[maxv];
int nv;

set<ll> can;

int go(int a, int pl, int pr){
    if (a==(n+1)/2) return 0;

    int &r=dp[a][pl][pr];
    if (r!=-1) return r;
    r=-2;
    REP(x,2) REP(y,2){
        if (a==n/2 && x!=y) continue;
        int npl=pl+(x==0);
        int npr=pr+(y==0);

        int tp=npl+npr;
        int tq=2*(a+1)-tp;
        if (a==n/2) tp-=(x==0), tq=tq-1+(x==0);
        if (tp>np || tq>nq) continue;


        int c1=is[npl][a+1-npl];
        int c2=is[npr][a+1-npr];
        int c3=is[np-npl][nq-a-1+npl];
        int c4=is[np-npr][nq-a-1+npr];

        if (npl==npr) c1=c3=0;
        if (a==(n-1)/2) c3=c4=0;
        
        int nc=c1+c2+c3+c4;
        r=max((int)r,go(a+1,npl,npr)+nc);
    }

    return r;
}

void build(int a, int pl, int pr){
    if (a==(n+1)/2) return;

    int res=dp[a][pl][pr];

    REP(x,2) REP(y,2){
        if (a==n/2 && x!=y) continue;
        int npl=pl+(x==0);
        int npr=pr+(y==0);

        int tp=npl+npr;
        int tq=2*(a+1)-tp;
        if (a==n/2) tp-=(x==0), tq=tq-1+(x==0);
        if (tp>np || tq>nq) continue;

        int c1=is[npl][a+1-npl];
        int c2=is[npr][a+1-npr];
        int c3=is[np-npl][nq-a-1+npl];
        int c4=is[np-npr][nq-a-1+npr];

        if (npl==npr) c1=c3=0;
        if (a==(n-1)/2) c3=c4=0;
        int nc=c1+c2+c3+c4;

        if (res==go(a+1,npl,npr)+nc){
            if (a!=n/2) printf("%c",'P'+y);
            build(a+1,npl,npr);
            printf("%c",'P'+x);
            return;
        }
    }
    assert(0);
}

int main(){
    freopen("identification.in","r",stdin);
    freopen("identification.out","w",stdout);

    cin>>nv;
    REP(i,nv){
        double x; scanf(" %lf",&x);
        x*=1e5;
        tb[i]=x+0.7;
        can.insert(tb[i]);
    }

    ll best=0;
    REP(i,nv) best=max(best,tb[i]);

    np=nq=-1;
    REP(i,maxn) REP(j,maxn) if (best==1ll*i*P+1ll*j*Q) np=i, nq=j;


    n=np+nq;
    REP(i,np+1) REP(j,nq+1){
        ll v=1ll*i*P+1ll*j*Q;
        if (can.count(v)) is[i][j]=1;
    }


    memset(dp,-1,sizeof(dp));
    int res=go(0,0,0);
    build(0,0,0);
    puts("");

    return 0;
}

