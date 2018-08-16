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
//#include <ext/hlsh_map>


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

const int maxn=111;
const int W=1e5, HA=100;
const double pi=acos(-1.);
const double eps=1e-9;

int hl, hr, n;
int xa[maxn], xb[maxn];
int c[maxn], f[maxn];
int wh[2][W+10];
int perm[maxn];

int cmp(int a, int b){return xa[a]<xa[b];}

int vis[maxn];

int which(double x, int f){
    int a=wh[f][int(x)];
    if (a==-1) return -1;
    if (xa[a]<=x+eps && x-eps<=xb[a]) return a;
    return -1;
}

int main(){
    cin>>hl>>hr>>n;
    REP(i,n){
        char cc;
        scanf(" %d %c %d %d",c+i,&cc,xa+i,xb+i);
        f[i]=cc=='T';
    }
    REP(i,n) perm[i]=i;
    sort(perm,perm+n,cmp);

    int xi[2]={0,0};
    memset(wh,-1,sizeof(wh));
    REP(j,n) for (int i=perm[j]; xi[f[i]]<=xb[i]; ++xi[f[i]]) wh[f[i]][xi[f[i]]]=i; 
    
    int best=0;
    FOR(i,1,n+1) REP(fx,2){

        int nf=fx^(i+1&1);

        memset(vis,0,sizeof(vis));
        double aa=1.*W/(HA*(i-1)+(fx?HA-hl:hl)+(nf?HA-hr:hr));

        double xo=aa*(fx?HA-hl:hl);
        int ff=fx;
        int sc=0;
        REP(j,i){
            int u=which(xo,ff);
            if (u==-1 || vis[u]) goto fail;
            vis[u]=1;
            sc+=c[u];

            xo+=aa*HA;
            ff^=1;
        }
        best=max(best,sc);
fail:;
    }

    printf("%d\n",best);
    return 0;
}

