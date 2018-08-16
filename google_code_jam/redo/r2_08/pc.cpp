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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=1010;
const double phi=(1+sqrt(5))/2.;
const double rphi=2-phi;

int x[maxn], y[maxn], z[maxn], d[maxn];
int n;

const double inf=1e7;
const double eps=1e-10;

double val;

inline double f(double xa, double ya, double za){
    double v=0;
    REP(i, n) checkmax(v, (double)(fabs(xa-x[i])+fabs(ya-y[i])+fabs(za-z[i]))/d[i]);
    return v;

}
double gsz(double xa, double ya){
    double va, vb, vc, vd;
    double fb, fc;
    va=0.; vd=inf;

    vb=va+(vd-va)/(1+phi);
    fb=f(xa, ya, vb);
    while(fabs(vd-va)>eps){

        vb=va+(vd-va)/(1+phi);
        vc=(va+vd-vb);
        fc=f(xa, ya, vc);
        fb=f(xa, ya, vb);
        if (fc<fb){
            va=vb;
            vb=vc; fb=fc;
        }else{
            vd=va;
            va=vc;
        }

    }
    val=fb;
    return va;
}
double gsy(double xa, double za){
    double va, vb, vc, vd;
    double fb, fc;
    va=0.; vd=inf;

    vb=va+(vd-va)/(1+phi);
    fb=f(xa, vb, za);
    while(fabs(vd-va)>eps){

        vb=va+(vd-va)/(1+phi);
        vc=(va+vd-vb);
        fc=f(xa, vc, za);
        fb=f(xa, vb, za);
        if (fc<fb){
            va=vb;
            vb=vc; fb=fc;
        
        }else{
            vd=va;
            va=vc;
        }

    }
    val=fb;
    return va;
}
double gsx(double ya, double za){
    double va, vb, vc, vd;
    double fb, fc;
    va=0.; vd=inf;

    vb=va+(vd-va)/(1+phi);
    fb=f(vb, ya, za);
    while(fabs(vd-va)>eps){

        vb=va+(vd-va)/(1+phi);
        vc=(va+vd-vb);
        fc=f(vc, ya, za);
        fb=f(vb, ya, za);
        if (fc<fb){
            va=vb;
            vb=vc; fb=fc;
        }else{
            vd=va;
            va=vc;
        }

    }
    val=fb;
    return va;
}
int main(){
    int tn;
    srand(time(0));
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        double xo, yo, zo;
        REP(i, n) cin>>x[i]>>y[i]>>z[i]>>d[i];
        double ans=1.5*inf;
        REP(j, 100){
            xo=rand()%int(inf);
            yo=rand()%int(inf);
            zo=rand()%int(inf);

            xo=yo=zo=0.;
            val=10*inf;
            REP(k, 10000){
                double oval=val;
                yo=gsy(xo, zo);
                zo=gsz(xo, yo);
                xo=gsx(yo, zo);
                if (fabs(oval-val)<eps) break;

            }

            checkmin(ans, val);
        }
        printf("Case #%d: %.8lf\n", ti, ans);
    }
    return 0;

}
