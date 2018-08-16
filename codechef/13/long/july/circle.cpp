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

const int maxn=33;
const double eps=1e-7;
int x[maxn], y[maxn];
int n;

double det(double xa, double ya, double xb, double yb){return xa*yb-ya*xb;}
double dist(double a, double b){return a*a+b*b;}


int checkit(int a, int b, int c, int e){
    double xa,ya,xb,yb,xc,yc;
    xa=x[b]-x[a];
    ya=y[b]-y[a];
    xb=x[c]-x[a];
    yb=y[c]-y[a];
    xc=x[e]-x[a];
    yc=y[e]-y[a];

    double d=det(xa,ya,xb,yb);
    if (fabs(d)<eps) return 0;

    double k=det((xa-xb)/2.,(ya-yb)/2.,yb,-xb)/-d;
    double xo=xa/2.+k*ya;
    double yo=ya/2.-k*xa;

    return dist(xo,yo)+eps>dist(xc-xo,yc-yo);
}

int main(){
    int tn; cin>>tn;

    REP(ti,tn){
        int tot=0;
        int res=0;
        cin>>n;
        REP(i,n) scanf(" %d%d",x+i,y+i);
        REP(i,n) REP(j,i) REP(k,j) REP(l,n){
            if (l==i||l==j||l==k) continue;
            ++tot;
            if (checkit(i,j,k,l)) ++res;
        }
        printf("%.10lf\n",1.*res/tot);
    }
    return 0;
}

