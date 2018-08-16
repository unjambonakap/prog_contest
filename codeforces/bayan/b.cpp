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

const int mod=1e9+7;
const int maxn=5e4+10;
int a[maxn];
int n,m;
int ta[2][4*maxn], tb[2][4*maxn];
int xx[2][4*maxn];
int res;
int MASK,B;
int tx[2][2];

int doit(int u, int v){
    int T=u, H=v;
    int best=H+1;
    while(T<=H){
        int M=T+H>>1;
        if ((a[M]&MASK)>=B) best=M, H=M-1;
        else T=M+1;
    }
    return best;
}

void sum(int aa, int ab, int ba, int bb){
    if (aa>ab || ba>bb) return;
    for (; aa<=ab; ++aa) for (int k=ba; k<=bb; ++k){
        res=res+((a[aa]^a[k])&MASK);
        if (res>=mod) res-=mod;
        if (res>=mod) res-=mod;
    }
}

void solve2(int px, int nt, int K){
    if (!K || !B) return;

    int *x=ta[px], *y=tb[px];
    int *nx=ta[px^1], *ny=tb[px^1];
    int nn=0;

    int have=0;
    REP(i,nt){
        if (xx[px][i]==1) continue;
        REP(k,2){
            int best=doit(x[i],y[i]);

            nx[nn]=x[i];
            ny[nn]=best-1;
            nx[nn+1]=best;
            ny[nn+1]=y[i];

            tx[k][0]=best-x[i];
            tx[k][1]=y[i]-best+1;


            nn+=2;
            ++i;
        }
        have+=tx[0][0]*tx[1][1]+tx[0][1]*tx[1][0];
        --i;
    }


    int nu=0;
    if (have>K){
        res=(res+1ll*B*K)%mod;
        for (int i=0; i<nn; i+=4){
            int aa=ny[i]-nx[i], bb=ny[i+1]-nx[i+1];
            int cc=ny[i+2]-nx[i+2], dd=ny[i+3]-nx[i+3];

            ++aa; ++bb; ++cc; ++dd;
            if (aa&&dd){
                xx[px][nu]=2;
                x[nu]=nx[i]; y[nu]=ny[i]; ++nu;
                x[nu]=nx[i+3]; y[nu]=ny[i+3]; ++nu;
            }

            if (bb&&cc){
                xx[px][nu]=2;
                x[nu]=nx[i+1]; y[nu]=ny[i+1]; ++nu;
                x[nu]=nx[i+2]; y[nu]=ny[i+2]; ++nu;
            }
        }
    }else{
        for (int i=0; i<nn; i+=4){
            int aa=ny[i]-nx[i], bb=ny[i+1]-nx[i+1];
            int cc=ny[i+2]-nx[i+2], dd=ny[i+3]-nx[i+3];

            ++aa; ++bb; ++cc; ++dd;
            sum(nx[i],ny[i],nx[i+3],ny[i+3]);
            sum(nx[i+1],ny[i+1],nx[i+2],ny[i+2]);
            if (aa&&cc){
                xx[px][nu]=2;
                x[nu]=nx[i]; y[nu]=ny[i]; ++nu;
                x[nu]=nx[i+2]; y[nu]=ny[i+2]; ++nu;
            }

            if (bb&&dd){
                xx[px][nu]=2;
                x[nu]=nx[i+1]; y[nu]=ny[i+1]; ++nu;
                x[nu]=nx[i+3]; y[nu]=ny[i+3]; ++nu;
            }
        }
        K-=have;
    }
    MASK^=B;
    B>>=1;
    solve2(px,nu,K);
}


void solve(int px, int nt, int K){

    if (!K||!B) return;

    int *x=ta[px], *y=tb[px];
    int *nx=ta[px^1], *ny=tb[px^1];
    int nn=0;

    int have=0;
    REP(i,nt) if (x[i]<y[i]){

        int best=doit(x[i],y[i]);

        int cnt=0;
        if (x[i]<=best-1){
            nx[nn]=x[i];
            ny[nn]=best-1;
            ++nn;
            ++cnt;
        }
        if (best<=y[i]){
            nx[nn]=best;
            ny[nn]=y[i];
            ++nn;
            ++cnt;
        }
        xx[px^1][nn-cnt]=cnt;
        have+=(y[i]-best+1)*(best-x[i]);
    }


    if (have>K){
        res=(res+1ll*B*K)%mod;
        MASK^=B;
        B>>=1;
        solve2(px^1,nn,K);
    }else{
        REP(i,nn){
            if (xx[px^1][i]==1) continue;
            sum(nx[i],ny[i],nx[i+1],ny[i+1]);
            ++i;
        }
        MASK^=B;
        B>>=1;
        solve(px^1,nn,K-have);
    }
}

int main(){
    while(cin>>n>>m, !cin.eof()){
        REP(i,n) scanf(" %d",a+i);
        sort(a,a+n);
        memset(xx,0,sizeof(xx));
        ta[0][0]=0; tb[0][0]=n-1;
        B=1<<29;
        MASK=(1<<30)-1;
        res=0;
        solve(0,1,m);

        cout<<res<<endl;
    }
    return 0;
}

