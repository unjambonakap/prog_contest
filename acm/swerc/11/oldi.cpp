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

const int maxn=1001;
const double eps=1e-5;
const double pi=acos(-1.);

double dist[maxn][maxn];
double sqr(double a, double b){return a*a+b*b;}
double xo, yo;
double xa,xb,ya,yb;

int cmp(double a, double b){return fabs(a-b)>eps?a<b:0;}

int checkd(double x, int a, int b){
    if (b<0) b+=a;
    if (b>=a/2+1) b=a-b;
    return fabs(dist[a][b]-x)<eps;
}


int go(){
    double d1=sqr(xa,ya), d2=sqr(xb,yb), d3=sqr(xa-xb,ya-yb);
    if (d1>d2) swap(d1,d2);
    FOR(i,3,maxn){
        int nx=i/2+1;
        FOR(j,1,nx){
            double scale=d1/dist[i][j];
            int u=lower_bound(dist[i],dist[i]+nx,d3/scale-eps,cmp)-dist[i];
            if (u==nx) continue;

            if (fabs(dist[i][u]-d3/scale)>eps) continue;

            if (checkd(d2/scale,i,u+j)) return i;
            if (checkd(d2/scale,i,j-u)) return i;
        }
    }
    fprintf(stderr,"%lf %lf %lf %lf %lf %lf\n",xo,yo,xa,xb,ya,yb);
    assert(0);
}
int main(){
    FOR(i,3,maxn) REP(j,i/2+1){
        double xx=cos(2*pi/i*j), yy=sin(2*pi/i*j);
        dist[i][j]=100*sqr(xx-1,yy);
    }
    while(scanf(" %lf%lf",&xo,&yo)>0){
        cin>>xa>>ya>>xb>>yb;
        xa-=xo; xb-=xo;
        ya-=yo; yb-=yo;
        printf("%d\n",go());


    }
    return 0;
}

