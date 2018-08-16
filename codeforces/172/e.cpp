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
inline int countbit(int n){return (n==0)?0:1+countbit(n&(n-1));}
inline int lowbit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=6666;
const double eps=1e-9;
const double oo=1e9;

double mx,a,b;
int x[maxn];
int n;
double res;
double respos[maxn];


struct line{
    double a,b,xo;
    line(double xo, double a, double b):xo(xo),a(a),b(b){}
    line(){}
    double eval(double x){return a*x+b;}
    double point0(){return -b/a;}
    double findmin(double xa, double xb){
        double ya=eval(xa), yb=eval(xb);
        if (ya<-eps && yb>eps) return point0();
        if (fabs(ya)<fabs(yb)) return xa;
        return xb;
    }
};
line ta[3*maxn], tb[3*maxn], tc[3*maxn];
int na,nb,nc;

void find0(line *tb, int nx, int &id0, double &pos0){
    REP(i,nx-1){
        double xa=tb[i].xo, xb=tb[i+1].xo;
        if (tb[i].eval(xa)>-eps){id0=i; pos0=xa; return; }
        if (tb[i].eval(xb)>-eps){id0=i, pos0=fabs(tb[i].a)<eps?tb[i].xo:tb[i].point0(); return;}
    }
    id0=nx-2;
    pos0=tb[id0+1].xo;
}


double solve(int p){
    na=nb=0;
    REP(i,nc) if (i==nc-1 || tc[i].xo<tc[i+1].xo-eps) tb[nb++]=tc[i];

    int id0; double pos0;
    find0(tb,nb,id0,pos0);
    if (p==n) return pos0;


    int j=0;
    REP(i,id0+1) if (tb[i].xo+a<mx+eps) ta[na++]=line(tb[i].xo+a,tb[i].a,tb[i].b-a*tb[i].a);
    
    if (pos0+a<mx+eps){
        ta[na++]=line(pos0+a,0,0);
        if (pos0+b<mx+eps) ta[na++]=line(pos0+b,tb[id0].a,tb[id0].b-b*tb[id0].a);
    }

    for (int i=id0+1; i+1<nb && tb[i].xo+b<mx+eps; ++i)
        ta[na++]=line(tb[i].xo+b,tb[i].a,tb[i].b-b*tb[i].a);
    ta[na++]=line(mx,oo,oo);
    assert(na<3*n+10);

    REP(i,na) ta[i].a+=2, ta[i].b-=2*x[p];

    memcpy(tc,ta,sizeof(ta));
    nc=na;

    double xx=solve(p+1);
    xx=max(xx,1+p*a);
    respos[p]=xx;
    res+=(x[p]-xx)*(x[p]-xx);

    
    double df=xx-pos0;
    df=max(df,a);
    df=min(df,b);
    return xx-df;

}

int main(){
    cin>>n>>mx>>a>>b;
    REP(i,n) scanf(" %d",x+i);
    tc[nc++]=line(1-a,0,0);
    tc[nc++]=line(mx,maxn,maxn);

    solve(0);
    REP(i,n) printf("%.10lf ",respos[i]);
    puts("");
    printf("%.10lf\n",res);

    return 0;
}

