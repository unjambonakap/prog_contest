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

const double pi=acos(-1.);
const double eps=1e-9;

double go(double w, double h, double d, int f){
    double ar=pi*d*d/4;
    if (f) swap(w,h);
    if (w<d*pi) return 0;
    return ar*h;
}

double stupid(double w, double h){
    double res=0;
    REP(f,2){
        REP(i,2){
            double T=0, H=h/2.;
            REP(step,100){
                double l=(2*T+H)/3, r=(T+2*H)/3;
                double xl=go(h,w-l,l,f), xr=go(h,w-r,r,f);
                res=max(res,max(xl,xr));
                if (xl<xr) T=l;
                else H=r;
            }
            swap(w,h);
        }
    }
    REP(f,2) REP(i,2){
        swap(w,h);
        double T=0, H=min(w,2*h);
        REP(step,100){
            double l=(2*T+H)/3, r=(T+2*H)/3;
            double xl=go(h,w-l,l/2,f), xr=go(h,w-r,r/2,f);
            res=max(res,max(xl,xr));
            if (xl<xr) T=l;
            else H=r;
        }
    }
    return res;
}

int main(){
    srand(0);
    int tn; cin>>tn;
    int gen=1;
    if (gen) tn=4e5;
    REP(ti,tn){
        int w,h; 
        if (gen) w=rand()%int(1e6)+1, h=rand()%int(1e6)+1;
        else scanf(" %d%d",&w,&h);

        double res=0;
        REP(i,2){
            swap(w,h);
            double da=w/(pi+1);
            double dh=h/pi;
            da=min(da,(double)h/2.);

            dh=min(dh,(double)2.*w/3);
            //w on perimeter
            res=max(res,da*da/4*pi*h);

            //h on perimeter
            res=max(res,dh*dh/4*pi*(w-dh));
        }
        REP(i,2){
            swap(w,h);
            double dd=min((double)h,w/(pi+2));
            res=max(res,dd*dd/4*pi*h);
        }
        double res2=stupid(w,h);

        printf("%d %d >> %.10lf %.10lf\n",w,h,res,res2);
        assert(fabs(res-res2)<1e-11*res2);

        //printf("%.15lf\n",res);
    }

    return 0;
}
