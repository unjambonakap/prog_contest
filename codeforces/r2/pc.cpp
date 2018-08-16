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

const double eps=1e-5;
double dist(double a, double b){return a*a+b*b;}

double proc(double a, double b, double c, double d, double px, double py, double qx, double qy){
    //(a, b)*u-(c, d)*v=(qx-px, qy-py)
    qx-=px; qy-=py;
    if (fabs(d)<eps) return qx/b;
    return (px-py*c/d)/(a-b*c/d);
}


void doit(double x, double y, double ra, double rb, double &xo, double &yo, double &ro){
    double A=2*x, B=2*y, C=x*x+y*y, D=ra*ra-rb*rb;
    D/=ra*ra;
    xo=A/D/2.;
    yo=B/D/2.;
    ro=-C/D+xo*xo+yo*yo;
    //printf("%lf %lf %lf %lf => %lf %lf %lf\n", x, y, ra, rb, xo, yo, ro);
    assert(ro>=0.);



    //double xe=xo, ye=yo+sqrt(ro);
    //double anga=2*asin(ra/sqrt(dist(xe, ye)));
    //double angb=2*asin(rb/sqrt(dist(xe-x, ye-y)));

    //printf("%lf %lf\n", anga, angb);
    //exit(0);


}


int solve(double a, double b, double c, double &ka, double &kb){
    double d=b*b-4*a*c;
    //printf("<< %lf\n", d);
    if (d<0) return 0;
    d=sqrt(d);
    ka=(-b-d)/a/2; 
    kb=(-b+d)/a/2;
    return 1;
}

int main(){
    double xa, ya, xb, yb, xc, yc, ra, rb, rc;
    cin>>xa>>ya>>ra;
    cin>>xb>>yb>>rb;
    cin>>xc>>yc>>rc;
    xb-=xa; yb-=ya;
    xc-=xa; yc-=ya;

    double da, db;
    da=fabs(ra-rb);
    db=fabs(ra-rc);
    if (db<eps) swap(xb, xc), swap(yb, yc), swap(rb, rc), swap(da, db);

    double xe, ye;
    if (da<eps && db<eps){
        double k=proc(yb/2, -xb/2, yc/2, -xc/2, xb/2, yb/2, xc/2, yc/2);

        xe=xb/2+yb/2*k; ye=yb/2-xb/2*k;
    }else if (da<eps){
        double xo, yo, ro;
        doit(xc, yc, ra, rc, xo, yo, ro);
        double vx=yb/2, vy=-xb/2, px=xb/2, py=yb/2;

        double a, b, c;
        xo-=px; yo-=py;
        c=xo*xo+yo*yo-ro;
        a=vx*vx+vy*vy;
        b=-2*(vx*xo+vy*yo);
        double ka, kb;
        xo+=px; yo+=py;

        if (!solve(a, b, c, ka, kb)) return 0;

        double xf, yf;
        xe=px+vx*ka, ye=py+vy*ka;


        xf=px+vx*kb, yf=py+vy*kb;
        if (dist(xe, ye)>dist(xf, yf)) swap(xe, xf), swap(ye, yf);
        assert(fabs(dist(xe-xo, ye-yo)-ro)<eps);
        assert(fabs(dist(xf-xo, yf-yo)-ro)<eps);

    }else{
        double xp, yp, rp, xq, yq, rq;
        doit(xb, yb, ra, rb, xp, yp, rp);
        doit(xc, yc, ra, rc, xq, yq, rq);
        xq-=xp; yq-=yp;
        double B=(rp-rq+xq*xq+yq*yq)/(2*yq);
        double A=-xq/yq;//y=A*x+B
        double a, b, c;
        a=1+A*A;
        b=2*A*B;
        c=B*B-rp;
        double xf, yf;
        if (!solve(a, b, c, xe, xf)) return 0;

        ye=sqrt(rp-xe*xe);
        if (fabs(dist(xe-xq, ye-yq)-rq)>eps) ye=-ye;
        assert(fabs(dist(xe-xq, ye-yq)-rq)<=eps);
        yf=sqrt(rp-xf*xf);
        if (fabs(dist(xf-xq, yf-yq)-rq)>eps) yf=-yf;
        assert(fabs(dist(xf-xq, yf-yq)-rq)<=eps);

        xe+=xp; ye+=yp;
        xf+=xp; yf+=yp;


        if (dist(xe, ye)>dist(xf, yf)) swap(xe, xf), swap(ye, yf);
    }

//    double anga, angb, angc;
//    anga=2*asin(ra/sqrt(dist(xe, ye)));
//    angb=2*asin(rb/sqrt(dist(xe-xb, ye-yb)));
//    angc=2*asin(rc/sqrt(dist(xe-xc, ye-yc)));
//    printf("<< res: %lf %lf %lf\n", anga, angb, angc);


    printf("%lf %lf\n", xe+xa, ye+ya);




    return 0;
}


