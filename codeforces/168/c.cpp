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

const int maxn=111;
const double eps=1e-6;
const double pi=acos(-1);
int n;
int x[maxn], y[maxn];
int xl[4], yl[4];

double dot(double a, double b, double c, double d){return a*d-b*c;}
double dist(double a, double b){return a*a+b*b;}

int main(){
    cin>>n;
    REP(i,n) scanf(" %d%d",x+i,y+i);
    int fd=0;
    double best=0;

    REP(i,n) REP(j,i) REP(k,j){
        double xa=x[j]-x[i], xb=x[k]-x[i], ya=y[j]-y[i], yb=y[k]-y[i];
        if (fabs(dot(xa,ya,xb,yb))<eps) continue;
        xl[0]=x[i]; yl[0]=y[i];
        xl[1]=x[j]; yl[1]=y[j];
        xl[2]=x[k]; yl[2]=y[k];
        xl[3]=x[i]; yl[3]=y[i];

        double kk;
        if (ya){
            kk=(yb-ya)/2+xa*(xb-xa)/2/ya;
            kk=kk/(xb-xa*yb/ya);
        }else kk=(xa-xb)/2/yb;

        double xc=xb/2+kk*yb,yc=yb/2-kk*xb;
        double dd=dist(xc,yc);
        xc+=x[i]; yc+=y[i];
        if (best+eps>dd) continue;

        int sgn=0;
        vector<double> lst;
        REP(u,3){
            double dx=dot(xc-xl[u],yc-yl[u],xl[u+1]-xl[u],yl[u+1]-yl[u]);
            if (fabs(dx)<eps) continue;

            int nsgn=dx<0?-1:1;
            if (sgn!=0 && nsgn!=sgn) goto fail;
            sgn=nsgn;
        }
        REP(u,n){
            double dx=dist(xc-x[u],yc-y[u]);
            if (dx<dd-eps) goto fail;
            if (dx<dd+eps) lst.pb(atan2(yc-y[u],xc-x[u]));
        }
        sort(ALL(lst));
        assert(lst.size()>=3);
        lst.pb(lst[0]);
        REP(u,lst.size()-1) if (lst[u+1]-lst[u]>pi-eps) goto fail;
        best=dd, fd=1;
fail:;
    }

    best=sqrt(best);
    if (!fd) puts("-1");
    else printf("%.10lf\n",best);
    return 0;
}

