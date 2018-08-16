#include <vector>
#include<complex>
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

typedef complex<double> point;
typedef vector<point> vc;
const double pi=acos(-1.);

const int maxv=2e7+10;
const int maxn=4e5+10;
int n;
ll a[maxn];
ll F[maxn];
int f[maxn];
char has[maxv];


void fft(vc &a, vc &wl){
    int n=a.size();
    for (int i=2, l=1; i<=n; i<<=1, ++l){
        point w=wl[l];
        for (int j=0; j<n; j+=i){
            point pw=1;
            REP(k,i/2){
                point u=a[j+k], v=pw*a[j+k+i/2];
                a[j+k]=u+v;
                a[j+k+i/2]=u-v;
                pw*=w;
            }
        }
    }

}


vi go(vc a, vc b){

    int n=a.size();
    int bx=1;
    while(bx<n) bx<<=1;
    n=bx<<1;
    vi rev(n);
    int nb=0;
    while(1<<nb<n) ++nb;
    REP(i,n){
        int ni=0;
        REP(j,nb) if (i&two(j)) ni|=1<<nb-j-1;
        rev[i]=ni;
    }
    a.resize(n,0);
    b.resize(n,0);


    point w(cos(2*pi/n),sin(2*pi/n));
    vc wl(nb+1);
    wl[0]=w;
    REP(i,nb) wl[i+1]=wl[i]*wl[i];
    reverse(ALL(wl));

    vc x(n), y(n);
    REP(i,n) x[rev[i]]=a[i];
    REP(i,n) y[rev[i]]=b[i];
    fft(x,wl); fft(y,wl);



    REP(i,n) x[i]=x[i]*y[i];

    REP(i,nb+1) wl[i]=conj(wl[i]);

    vc res(n);
    REP(i,n) res[rev[i]]=x[i];
    fft(res,wl);

    vi ans(n);
    REP(i,n) ans[i]=res[i].real()/n+0.5;
    return ans;
}


int main(){
    cin>>n;
    REP(i,n) scanf(" %Ld",a+i);
    int lim1=2e3;
    int lim2=2e4;

    //n=lim2;
    //n=5e4;
    //REP(i,n) a[i]=4e10/n/n;
    REP(i,n) F[i+1]=F[i]+a[i];

    int res=0;
    if (n<lim1){
        set<ll> tb;
        REP(i,n) REP(j,i+1) tb.insert(F[i+1]-F[j]);
        
        res=tb.size();
    }else if (n<lim2){
        REP(i,n+1) f[i]=F[i];
        REP(i,n) REP(j,i+1) has[f[i+1]-f[j]]=1;
        
        REP(i,F[n]+1) res+=has[i];
    }else{
        int mx=F[n];
        vc a(mx+1),b(mx+1);
        REP(i,n) a[F[i+1]]=1, b[mx-F[i]]=1;
        vi x=go(a,b);
        FOR(i,mx+1,x.size()) res+=x[i]>0;

    }
    printf("%d\n",res-1);
    return 0;
}

