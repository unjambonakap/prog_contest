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

const int maxn=502;
const int maxq=6e5+10;
const int nb=32;
const int maxc=(maxn+nb-1)/nb;

int n,m;
int a[maxn][maxn];
char buf[maxn];
int dp[maxn][maxn][maxc];
int dp2[maxn][maxn][maxc];


int xa[maxq],xb[maxq],ya[maxq],yb[maxq];
int tb[maxq];
int res[maxq];
int nc;

void go(int *x, int na, int xl, int xh){
    if (!na) return;

    int xm=xl+xh>>1;
    int nx=0;

    REP(i,na) if (ya[x[i]]<=xm && yb[x[i]]>=xm) swap(x[nx++],x[i]);

    REP(i,n) if (!a[i][xm]){
        REP(k,nc) dp[i][xm][k]=0;
        dp[i][xm][i/nb]=1<<(i&0x1f);
        if (i&&!a[i-1][xm]) REP(j,nc) dp[i][xm][j]|=dp[i-1][xm][j];
    }

    FOR(i,xm+1,xh) REP(j,n) if (!a[j][i]){
        REP(k,nc) dp[j][i][k]=0;
        if (j && !a[j-1][i]) REP(k,nc) dp[j][i][k]|=dp[j-1][i][k];
        if (!a[j][i-1]) REP(k,nc) dp[j][i][k]|=dp[j][i-1][k];
    }


    for (int i=n-1; i>=0; --i) if (!a[i][xm]){
        REP(k,nc) dp2[i][xm][k]=0;
        dp2[i][xm][i/nb]=1<<(i&0x1f);
        if (i!=n-1&&!a[i+1][xm]) REP(j,nc) dp2[i][xm][j]|=dp2[i+1][xm][j];
    }
    for (int i=xm-1; i>=xl; --i) for (int j=n-1; j>=0; --j) if (!a[j][i]){
        REP(k,nc) dp2[j][i][k]=0;
        if (j<n-1 && !a[j+1][i]) REP(k,nc) dp2[j][i][k]|=dp2[j+1][i][k];
        if (!a[j][i+1]) REP(k,nc) dp2[j][i][k]|=dp2[j][i+1][k];
    }

    REP(i,nx){
        int fd=0;
        int u=x[i];
        REP(k,nc) fd|=dp2[xa[u]][ya[u]][k]&dp[xb[u]][yb[u]][k];
        res[u]=fd;
    }
    


    if (xl+1==xh) return;
    na-=nx;
    x+=nx; nx=0;
    REP(i,na) if (yb[x[i]]<xm) swap(x[i],x[nx++]);
    go(x,nx,xl,xm);
    go(x+nx,na-nx,xm+1,xh);
}

int main(){
    cin>>n>>m;
    REP(i,n){
        scanf(" %s",buf);
        REP(j,m) a[i][j]=buf[j]=='#';
    }
    nc=(n+nb-1)/nb;
    int nq;
    cin>>nq;
    REP(i,nq){
        scanf(" %d%d%d%d",xa+i,ya+i,xb+i,yb+i);
        --xa[i]; --xb[i];
        --ya[i]; --yb[i];
        tb[i]=i;
    }

    go(tb,nq,0,m);
    REP(i,nq) puts(res[i]?"Yes":"No");
    return 0;
}

