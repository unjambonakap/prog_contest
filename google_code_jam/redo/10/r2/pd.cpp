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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

typedef long double ld;
const int maxn=5005;
const int maxm=1001;
const ld eps=1e-12;
const ld inf=1e8;
const ld pi=acosl(-1);
ld _px[maxn], _py[maxn];
ld px[maxn], py[maxn];
ld qx[maxm], qy[maxm];
int n, m;


struct point{
    int id;
    ld a, b;
    int v;
    bool operator<(const point &p)const{return a<p.a;}
};
ld dist(ld a, ld b){return a*a+b*b;}
ld crossProd(ld a, ld b, ld c, ld d){return a*d-b*c;}

void inverse(ld xa, ld ya, ld &xb, ld &yb){
    ld d=dist(xa, ya)/2;
    xb=xa/d;
    yb=ya/d;
}

vector<point> procUH(const vector<point> &_t){
    vector<point> t=_t;
    vector<point> q;
    sort(ALL(t));
    
    REP(i, t.size()){
        while(q.size()>=2 && crossProd(q.back().a-q[q.size()-2].a, q.back().b-q[q.size()-2].b, t[i].a-q.back().a, t[i].b-q.back().b)>=0) q.pop_back();
        q.pb(t[i]);
    }
//    reverse(ALL(q));
    return q;
}
ld solve(ld xp, ld yp){
    //printf("\n\n");
    //printf("testing bucket %lf %lf\n", xp, yp);
    ld va, vb, vc, vd;
    vb=vd=2*pi;
    va=vc=0.;
    ld ang[maxn];
    REP(i, n) px[i]=_px[i]-xp, py[i]=_py[i]-yp;
    REP(i, n){
        ld tmpa, tmpb, tmpc, tmpd, tmp;
        tmp=atan2l(py[i], px[i])-pi/2;
        if (tmp<0) tmp+=2*pi;
        ang[i]=tmp;
        if (tmp+pi>2*pi) tmpc=tmp, tmpd=2*pi, tmpa=0, tmpb=tmp-pi;
        else tmpa=tmpc=tmp, tmpb=tmpd=tmp+pi;

        checkmax(va, tmpa); checkmin(vb, tmpb);
        checkmax(vc, tmpc); checkmin(vd, tmpd);
        if (va+eps>vb && vc+eps>vd) return 0.;
    }
    ld v;
    if (va+eps<vb) v=vb-pi;
    else v=vd-pi;
    if (v<0) v+=2*pi;
    v-=pi/2+eps;

    REP(i, n){
        ang[i]=ang[i]-v;
        if (ang[i]<0) ang[i]+=2*pi;
        if (ang[i]>=2*pi) ang[i]-=2*pi;
        assert(ang[i]<=3*pi/2-eps);
        assert(ang[i]>=pi/2);
    }
    
    REP(i, n){
        ld x, y;
        x=cosl(-v)*px[i]-sinl(-v)*py[i];
        y=sinl(-v)*px[i]+cosl(-v)*py[i];
        px[i]=x; py[i]=y;
    }

    vector<point> pl(n);
    REP(i, n){
        pl[i].id=i;
        pl[i].a=-px[i]/py[i];
        pl[i].b=-1/py[i];
    }
    vector<point> hull=pl;
    hull=procUH(pl);
    vector<pair<ld, ld> > intersect(hull.size());
    intersect[0]=MP(0, 0);
    REP(i, hull.size()-1){
 //       printf("HLUL %lf %lf %lf %lf\n", hull[i].a, -hull[i].b, hull[i+1].a, -hull[i+1].b);
        int a, b;
        a=hull[i].id; b=hull[i+1].id;
        ld tmp=px[a]*py[b]-px[b]*py[a];
        intersect[i+1].ST=(py[b]-py[a])/tmp;
        intersect[i+1].ND=(px[a]-px[b])/tmp;
        inverse(intersect[i+1].ST, intersect[i+1].ND, intersect[i+1].ST, intersect[i+1].ND);
    }
    
    int na=intersect.size();
    //REP(i, na) printf("<< INTERECT at %Lf %Lf\n", intersect[i].ST, intersect[i].ND);
    ld res=0., area=0.;
    //printf("\n\n\n");
    REP(i, na){
        ld xa, ya, xb, yb, xc, yc;
        xa=intersect[i].ST, ya=intersect[i].ND;
        xb=intersect[(i+1)%na].ST, yb=intersect[(i+1)%na].ND;
        xc=px[hull[i].id], yc=py[hull[i].id];

        ld anga, angb, angc, angz;
        anga=atan2l(ya-yc, xa-xc);
        angb=atan2l(yb-yc, xb-xc);
        angz=anga-angb;
        if (angz>2*pi) angz-=2*pi;
        else if (angz<0) angz+=2*pi;
    //    printf("ang %.10Lf on center %Lf %Lf => %Lf %Lf %Lf %Lf\n", angz, xc, yc, xa, ya, xb, yb);
    //    printf("ang : %Lf %Lf\n", anga, angb);
        //assert(fabs(dist(xc-mid[i].ST, yc-mid[i].ND)-dist(xc, yc))<eps);
        //assert(fabs(dist(xc-xa, yc-ya)-dist(xc, yc))<eps);
        //assert(fabs(dist(xc-xb, yc-yb)-dist(xc, yc))<eps);

        area+=xa*yb-xb*ya;
 //       printf("%d\n", angz>pi);
//        printf("<<<<<<<<<<<< %Lf %Lf %Lf %Lf %Lf %Lf\n", xa, ya, xb, yb, xc, yc);
//        printf("%Lf\n", angz*dist(xc, yc)/2-(angz>pi?-1:1)*fabsl(((xb-xc)*(ya-yc)-(yb-yc)*(xa-xc))/2));
//        printf("TR: %.10Lf\n", fabsl(((xb-xa)*(yc-ya)-(yb-ya)*(xc-xa))/2));
        res+=angz*dist(xc-xa, yc-ya)/2-(angz>pi?-1:1)*fabsl(((xb-xa)*(yc-ya)-(yb-ya)*(xc-xa))/2);
    //    printf("on res %lf\n", res);
    }
 //   printf("\n");
 //   printf("<< res %Lf\n", fabs(area)/2);
    //printf("<< res %Lf\n", fabs(area)/2+res);
    //printf("\n\n");


    //exit(0);


    return fabs(area)/2+res;


}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n>>m;
        REP(i, n) cin>>_px[i]>>_py[i];
        REP(i, m) cin>>qx[i]>>qy[i];
        

        printf("Case #%d:", ti);
        REP(i, m) printf(" %.10Lf", solve(qx[i], qy[i]));
        printf("\n");
    }
    return 0;
}



