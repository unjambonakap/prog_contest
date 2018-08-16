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
typedef long double ld;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const ld pi=acosl(-1.);
const ld eps=1e-9;

ld xa[3], ya[3], za[3], ra[3];

ld dist(ld x, ld y, ld z){return x*x+y*y+z*z;}

void crossp(ld a, ld b, ld c, ld u, ld v, ld w, ld &x, ld &y, ld &z){ x=b*w-c*v; y=c*u-w*a; z=a*v-b*u; }
int ispar(ld a, ld b, ld c, ld u, ld v, ld w){
    ld x,y,z;
    crossp(a,b,c,u,v,w,x,y,z);
    return fabs(x)<eps&&fabs(y)<eps&&fabs(z)<eps;
}
ld scalarp(ld a, ld b, ld c, ld u, ld v, ld w){return a*u+b*v+c*w;}


ld area(ld *x, ld *y){
    ld res=0;
    REP(i, 3) res+=x[i]*y[(i+1)%3]-y[i]*x[(i+1)%3];
    return res/2;
}

ld checkit(ld ra, ld rb, ld dx){
    int nstep=10000;

    ld step=2*sqrt(rb)/(nstep+1);
    ld res=0.;
    int coeff[3]={1,4,1};
    REP(i, nstep){
        ld y[3]={-sqrt(ra)+i*step, -sqrt(ra)+i*step+step/2, -sqrt(ra)+(i+1)*step};
        ld tmp=0.;
        REP(j,3){
            y[j]*=y[j];
            tmp+=coeff[j]*max((ld)0., -max(-sqrt(ra-y[j]), dx-sqrt(rb-y[j]))+min(sqrt(ra-y[j]), dx+sqrt(rb-y[j])));
        }
        res+=step*tmp/6;
    }
    return res;
}

ld fx(ld ra, ld rb, ld dx){
    if (ra>rb) swap(ra, rb);
    dx=fabs(dx);

    if (dx+ra<=rb+eps) return ra*ra*pi;
    if (dx>ra+rb) return 0.;

    ld xu, yu, xv, yv;
    ra*=ra; rb*=rb;

    xu=xv=((ra-rb)/dx+dx)/2;
    yu=ra-xu*xu;
    if (yu<0) return 0.;
    yu=sqrt(yu);
    yv=-yu;

    ld aa=atan2l(yu, xu)-atan2(yv, xv);
    ld ab=atan2l(yu, xu-dx)-atan2(yv, xv-dx);
    if (aa>pi) aa=2*pi-aa;
    if (ab>pi) ab=2*pi-ab;
    ld res=aa*ra/2+ab*rb/2;
    ld xt[3]={0,xu,xv}, yt[3]={0,yu,yv};
    ld va=area(xt,yt);
    xt[0]=dx;
    ld vb=area(xt,yt);

    res-=fabs(va)+fabs(vb);
    if ((vb<0 && va<0) || (vb>0 && va>0)) res+=ra*(pi-aa)+2*fabs(va);
    return res;
    ld tmp=checkit(ra,rb,dx);
    return tmp;
    if (fabs(res-tmp)>100){
        printf("%Lf %Lf %Lf\n", sqrt(ra), sqrt(rb), dx);
        printf(" <<< here %Lf %Lf xx %Lf\n", (tmp-res)/(ra*pi), res, tmp);

        assert(0);
    }
    return res;
}

ld getr(ld x, int p){ return ra[p]*ra[p]-(x-xa[p])*(x-xa[p]); }

ld fa(ld x){ return fx(sqrt(getr(x,0)), sqrt(getr(x,2)), ya[2]); }
ld fb(ld x){ return fx(sqrt(getr(x,1)), sqrt(getr(x,2)), ya[2]); }
ld fc(ld x){ return fx(sqrt(min(getr(x,0), getr(x,1))), sqrt(getr(x,2)), ya[2]);}


ld go(ld a, ld b, ld eps, ld A, ld ra, ld rb, ld rc, int d, ld (*f)(ld)){
    double c=(a+b)/2, h=b-a;
    ld u=(a+c)/2, v=(c+b)/2;
    ld ru=f(u), rv=f(v);
    ld sa=h*(ra+rc+4*ru)/12, sb=h*(rc+rb+4*rv)/12;
    ld s=sa+sb;
    if (d<0 ) return s+(s-A)/15;
    //if (d<0 || min(fabsl(s-A),(s-A)/s)<=eps) return s+(s-A)/15;
    return go(a,c,eps/2,sa,ra,rc,ru,d-1,f)+go(c,b,eps/2,sb,rc,rb,rv,d-1,f);
}

ld integrate(ld xmin, ld xmax, int nstep, ld (*f)(ld)){
    if (xmin+eps>=xmax) return 0.;
    double step=(xmax-xmin)/(nstep+1);
    ld a=f(xmin), b=f(xmax), c=f((xmin+xmax)/2);
    return go(xmin, xmax, eps, (xmax-xmin)*(a+b+4*c)/6, a, b, c, 7, f);
}


int main(){
    int tn; cin>>tn;
    REP(ti, tn){

        REP(i, 3) cin>>xa[i]>>ya[i]>>za[i]>>ra[i];
        if (ti!=1109) continue;

        REPV(i, 3) xa[i]-=xa[0], ya[i]-=ya[0], za[i]-=za[0];

        if (ispar(xa[1], ya[1], za[1], xa[2], ya[2], za[2])){

            int sgn=1;
            if ((xa[1]>eps && xa[2]<-eps) || (xa[1]<-eps && xa[2]>eps)) sgn=-1;
            if ((ya[1]>eps && ya[2]<-eps) || (ya[1]<-eps && ya[2]>eps)) sgn=-1;
            if ((za[1]>eps && za[2]<-eps) || (za[1]<-eps && za[2]>eps)) sgn=-1;
            xa[1]=sqrt(dist(xa[1], ya[1], za[1]));
            xa[2]=sgn*sqrt(dist(xa[2], ya[2], za[2]));
            ya[1]=za[1]=ya[2]=za[2]=0;
        }else{
            ld xu, yu, zu;
            ld da=sqrt(dist(xa[1], ya[1], za[1])), db=sqrt(dist(xa[2], ya[2], za[2]));
            xa[1]/=da; ya[1]/=da; za[1]/=da;
            xa[2]/=db; ya[2]/=db; za[2]/=db;
            crossp(xa[1], ya[1], za[1], xa[2], ya[2], za[2], xu, yu, zu);
            ld tmp=sqrt(dist(xu,yu,zu));
            xu/=tmp; yu/=tmp; zu/=tmp;

            crossp(xa[1], ya[1], za[1], xu, yu, zu, xu, yu, zu);

            ld a=scalarp(xa[2], ya[2], za[2], xa[1], ya[1], za[1]);
            ld b=scalarp(xa[2], ya[2], za[2], xu, yu, zu);

            xa[2]=db*a; ya[2]=db*b; za[2]=0;
            xa[1]=da; ya[1]=0; za[1]=0;


        }



        ld res=0;
        ld xmin, xmax;
        ld ans;
        int nstep=2000;
        ld step;

        REP(i, 3) res+=4*pi*ra[i]*ra[i]*ra[i]/3.;

        ans=0.;
        xmin=-1e10, xmax=1e10;
        REP(i, 2) checkmax(xmin, xa[i]-ra[i]), checkmin(xmax, xa[i]+ra[i]);
        step=(xmax-xmin)/(nstep+1);
        if (xmin<xmax) REP(i, nstep){
            ld x1=xmin+i*step, x2=x1+step/2, x3=x1+step;
            ld r1=min(getr(x1,0), getr(x1,1));
            ld r2=min(getr(x2,0), getr(x2,1));
            ld r3=min(getr(x3,0), getr(x3,1));
            ans+=step*pi*(r1+4*r2+r3)/6;
        }
        res-=ans;
        REP(i, 2){
            ans=0.;
            xmin=max(xa[i]-ra[i], xa[2]-ra[2])+eps, xmax=min(xa[i]+ra[i], xa[2]+ra[2])-eps;
            res-=integrate(xmin, xmax, nstep, i?fb:fa);
        }


        ans=0.;
        xmin=-1e10, xmax=1e10;
        REP(i, 3) checkmax(xmin, xa[i]-ra[i]), checkmin(xmax, xa[i]+ra[i]);
        xmin+=eps; xmax-=eps;
        res+=integrate(xmin, xmax, nstep, fc);
        


        printf("%.10Lf\n", res);
        //printf("%.10Lf\n", (long double) 4389.0248479862);



    }
    return 0;
}


