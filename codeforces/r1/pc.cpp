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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const double inf=1e7;
const double eps=1e-5;
const int maxo=100;
const double pi=acos(-1.);

double dist(double a, double b){return a*a+b*b;}


int checkit(double a, double b){
    double c=b/a; int nc=c;
    if (c-nc>0.5) ++nc;
    return fabs(b-nc*a)<eps;
}

double proc(double a, double b, double c, double d, double px, double py){
    //ax+by=px; cx+dy=py
    //cx-ax*d/b=py-px*d/b
    //x=(py-px*d/b)/(c-a*d/b)
    if (fabs(b)<eps) return px/a;
    return (py-px*d/b)/(c-a*d/b);
}
int main(){
    double xa, xb, ya, yb, xo, yo, xc, yc;
    cin>>xo>>yo;
    cin>>xa>>ya;
    cin>>xb>>yb;
    xa-=xo; ya-=yo;
    xb-=xo; yb-=yo;


    double k=proc(ya/2, -yb/2, -xa/2, xb/2, xb/2-xa/2, yb/2-ya/2);
    xc=xa/2+ya/2*k;
    yc=ya/2-xa/2*k;




    
    xa-=xc; ya-=yc;
    xb-=xc; yb-=yc;
    xc=-xc; yc=-yc;
    double ra, rb, rc;
    ra=dist(xa, ya);
    rb=dist(xb, yb);
    rc=dist(xc, yc);
     


    double ka=atan2(ya, xa), kb=atan2(yb, xb), kc=atan2(yc, xc);
    kb=fabs(kb-ka); kc=fabs(kc-ka);

    double ans=-1;
    FOR(i, 3, maxo) if (checkit(2*pi/i, kb) && checkit(2*pi/i, kc)){
        double ang=pi/i;
        double dx=dist(xa, ya);
        ans=fabs(dx*cos(ang)*sin(ang))*i;
        break;
    }
    printf("%.10lf\n", ans);


    return 0;
}

