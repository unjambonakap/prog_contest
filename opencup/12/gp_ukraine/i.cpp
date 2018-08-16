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

typedef complex<double> Complex;

const double pi=acos(-1);

const int maxn=888;
char A[maxn][maxn];
char B[maxn][maxn];

void fft(vector<Complex> &a, Complex w){
    int n=a.size();
    if (n==1) return;

    vector<Complex> na[2];
    na[0].resize(n/2);
    na[1].resize(n/2);
    
    REP(i,n) na[i&1][i>>1]=a[i];
    fft(na[0],w*w);
    fft(na[1],w*w);
    Complex v=1;
    REP(i,(n>>1)){
        Complex u=v*na[1][i];
        a[i]=na[0][i]+u;
        a[i+(n>>1)]=na[0][i]-u;
        v*=w;
    }
}

vi doit(vector<Complex> &a, vector<Complex> &b){
    int n=a.size();
    int bx=1;
    while(bx<n) bx<<=1;
    n=bx<<1;
    a.resize(n,0);
    b.resize(n,0);
    Complex w=Complex(cos(2*pi/n), sin(2*pi/n));

    fft(a,w);
    fft(b,w);
    REP(i,n) a[i]*=b[i];
    fft(a,conj(w));
    vi res;
    REP(i,n) res.pb(int(a[i].real()/n+0.1));
    return res;
}

int main(){
    freopen("i.in", "r", stdin);
    freopen("i.out", "w", stdout);

    int R, C, H, W;
    cin>>R>>C;
    REP(i,R) scanf(" %s", A[i]);
    REP(i,R) REP(j,C) A[i][j]-='0';
    cin>>H>>W;
    REP(i,H) scanf(" %s", B[i]);
    REP(i,R) REP(j,C) B[i][j]=B[i][j]=='#';

    int res=0;
    vector<Complex> a, b;
    REP(i,R) REP(j,C) a.pb(A[i][j]), b.pb(B[i][j]);

    reverse(ALL(a));
    vi tb=doit(a,b);
    REP(i,R-H+1) REP(j,C-W+1) checkmax(res,tb[R*C-1-(C*i+j)]); 
    cout<<res<<endl;
    return 0;
}



