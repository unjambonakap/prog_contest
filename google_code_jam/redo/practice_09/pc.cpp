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
double R, r, f, t, g;

const double eps=1e-9;
const double pi=acos(-1.);
double dist(double a, double b){return a*a+b*b;}


double ang(double x, double y){ return atan2(y, x); }

double bs(double T, double H, double a, double b){
    while(H-T>eps){
        double M=(H+T)/2.;
        if (dist(M, a)<=b) T=M;
        else H=M;
    }
    return T;
}

double bsx(double T, double H, double a, double b){
    while(H-T>eps){
        double M=(H+T)/2.;
        if (ang(M, a)>=b) T=M;
        else H=M;
    }
    return T;

}

double bsy(double T, double H, double a, double b){
    while(H-T>eps){
        double M=(H+T)/2.;
        if (ang(a, M)<=b) T=M;
        else H=M;
    }
    return T;

}

double solve(){
    double res=0.;
    double m=(R-t)*(R-t);

    double x=r, y=r;
    if (g<=0.) return 1.;
    double A=R*R*pi/4.;

    while(dist(x, y)<=m){
        while(dist(x+g, y+g)<=m){res+=g*g; y+=g+2*r;}
        while(dist(x, y)<=m){
            assert(res-eps<=A);

            if (dist(x+g, y+g)<=m) res+=g*g;
            else{
                double xa, xb, ya, yb;
                if (dist(x, y+g)<=m){
                    ya=y+g;
                    xa=bs(x, x+g, ya, m);
                }else{
                    xa=x;
                    ya=bs(y, y+g, xa, m);
                }

                if (dist(y, x+g)<=m){
                    xb=x+g;
                    yb=bs(y, y+g, xb, m);
                }else{
                    yb=y;
                    xb=bs(x, x+g, yb, m);
                }

                double va=ang(xa, ya), vb=ang(xb, yb);
                double tmp=va-vb;
                assert(tmp>=0.);
                assert(tmp<=pi/2);
                double s=m*tmp/2.;
                assert(tmp<=ang(x, y+g)-ang(x+g, y));
                double xc, xd, yc, yd;
                if (ang(x, y)<=va){
                    xc=x;
                    yc=bsy(y, y+g, xc, va);
                }else{
                    yc=y;
                    xc=bsx(x, x+g, yc, va);
                }
                if (ang(x, y)<vb){
                    xd=x;
                    yd=bsy(y, y+g, xd, vb);
                }else{
                    yd=y;
                    xd=bsx(x, x+g, yd, vb);
                }
                assert(fabs(ang(xd, yd)-vb)<eps);
                assert(fabs(ang(xc, yc)-va)<eps);
                if (xc<=x+eps && xd<=x+eps){
                    assert(yc>=yd);
                    s-=x*(yc-yd)/2;
                }else if (yc<=y+eps && yd<=y+eps){
                    assert(xc<=xd);
                    s-=y*(xd-xc)/2;
                }else{

                    s-=x*(yc-y)/2+y*(xd-x)/2;
                }
                s+=g*(xc-x)+(ya-yc)*(xa-xc)/2.;
                s+=g*(yd-y)+(yb-yd)*(xb-xd)/2.;
                assert(s-eps<=g*g);
                res+=s;



            }
            y+=g+2*r;
        }
        x+=g+2*r;
        y=r;

    }

    return 1.-res/A;

}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>f>>R>>t>>r>>g;
        g-=2*f;
        t+=f;
        r+=f;



        double res=solve();
        printf("Case #%d: %lf\n", ti, res);
    }

    return 0;

}



