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

typedef long double ld;
const int maxn=1111;
const ld eps=1e-6;
const ld pi=acosl(-1.);

int w,h,n;
ld x[maxn], y[maxn], r[maxn];


ld dist(ld a, ld b){return sqrt(a*a+b*b);}
ld sqr(ld a){return a*a;}

int solve(ld a, ld b, ld c, ld &xa, ld &xb){
    ld d=b*b-4*a*c;
    //printf("HAVE %Lf\n",d);
    if (d<0) return 0;
    d=sqrt(d);
    xa=(-b-d)/2/a;
    xb=(-b+d)/2/a;
    return 2;
}


void add(ld aa, ld bb, int i, int j, vector<pair<ld,int> > &tb){
    if (aa<0) aa+=2*pi; if (bb<0) bb+=2*pi;
    if (aa>bb) swap(aa,bb);

    ld cc=(aa+bb)/2;
    if (sqr(x[i]+r[i]*cosl(cc)-x[j])+sqr(y[i]+r[i]*sinl(cc)-y[j])>
            sqr(x[i]-r[i]*cosl(cc)-x[j])+sqr(y[i]-r[i]*sinl(cc)-y[j]))
        aa+=2*pi, swap(aa,bb);
    tb.pb(MP(aa,1)); tb.pb(MP(bb,-1));
}


int main(){
    int tn; cin>>tn;
    //tn=1000;
    REP(ti,tn){
        scanf(" %d%d%d",&w,&h,&n);
        REP(i,n) scanf(" %Lf%Lf%Lf",x+i,y+i,r+i), assert(x[i]>=-eps), assert(y[i]>=-eps);
        ld res=0;
        //w=rand()%50+1, h=rand()%50+1;
        //n=rand()%1000+1;
        //REP(i,n) x[i]=rand()%int(1e9)/1e7, y[i]=rand()%int(1e9)/1e7, r[i]=rand()%int(1e9)/1e8;

        //if (ti!=0) continue;
        REP(i,n){
            //if (i!=5) continue;

            vector<pair<ld,int> > tb;

            ld aa,bb;
            if (solve(1,-2*y[i],-sqr(r[i])+sqr(y[i])+sqr(x[i]),aa,bb)){
                aa=atan2l(aa-y[i],0-x[i]);
                bb=atan2l(bb-y[i],0-x[i]);

                if (aa<0) aa+=2*pi; if (bb<0) bb+=2*pi;
                if (aa>bb) swap(aa,bb);


                if (cosl((aa+bb)/2)>0) aa+=2*pi, swap(aa,bb);
                tb.pb(MP(aa,1)); tb.pb(MP(bb,-1));
            }

            if (solve(1,-2*y[i],-sqr(r[i])+sqr(y[i])+sqr(w-x[i]),aa,bb)){
                aa=atan2l(aa-y[i],w-x[i]);
                bb=atan2l(bb-y[i],w-x[i]);

                if (aa<0) aa+=2*pi; if (bb<0) bb+=2*pi;
                if (aa>bb) swap(aa,bb);


                if (cosl((aa+bb)/2)<0) aa+=2*pi, swap(aa,bb);
                tb.pb(MP(aa,1)); tb.pb(MP(bb,-1));
            }

            if (solve(1,-2*x[i],-sqr(r[i])+sqr(y[i])+sqr(x[i]),aa,bb)){
                aa=atan2l(0-y[i],aa-x[i]);
                bb=atan2l(0-y[i],bb-x[i]);

                if (aa<0) aa+=2*pi; if (bb<0) bb+=2*pi;
                if (aa>bb) swap(aa,bb);


                if (sinl((aa+bb)/2)>0) aa+=2*pi, swap(aa,bb);
                tb.pb(MP(aa,1)); tb.pb(MP(bb,-1));
            }

            if (solve(1,-2*x[i],-sqr(r[i])+sqr(h-y[i])+sqr(x[i]),aa,bb)){
                aa=atan2l(h-y[i],aa-x[i]);
                bb=atan2l(h-y[i],bb-x[i]);

                if (aa<0) aa+=2*pi; if (bb<0) bb+=2*pi;
                if (aa>bb) swap(aa,bb);


                if (sinl((aa+bb)/2)<0) aa+=2*pi, swap(aa,bb);
                tb.pb(MP(aa,1)); tb.pb(MP(bb,-1));
            }

            int ok=1;
            if (x[i]-r[i]+eps>=w) continue;
            if (y[i]-r[i]+eps>=h) continue;


            REP(j,n) if (j!=i){
                ld dx=dist(x[i]-x[j],y[i]-y[j]);
                if (dx+r[i]<r[j]+eps){ok=0; break;}
                if (dx+r[j]<r[i]+eps) continue;

                if (fabs(x[i]-x[j])>fabs(y[i]-y[j])){
                    ld A=-2*(y[j]-y[i]);
                    ld B=sqr(r[i])-sqr(r[j])-sqr(x[i])-sqr(y[i])+sqr(x[j])+sqr(y[j]);
                    A/=2*(x[j]-x[i]);
                    B/=2*(x[j]-x[i]);

                    if (solve(1+A*A,-2*y[j]+2*A*(B-x[j]),-sqr(r[j])+sqr(y[j])+sqr(B-x[j]),aa,bb)){
                        aa=atan2l(aa-y[i],A*aa+B-x[i]);
                        bb=atan2l(bb-y[i],A*bb+B-x[i]);
                        add(aa,bb,i,j,tb);
                    }
                }else if (fabs(y[i]-y[j])>eps){
                    ld A=-2*(x[j]-x[i]);
                    ld B=sqr(r[i])-sqr(r[j])-sqr(x[i])-sqr(y[i])+sqr(x[j])+sqr(y[j]);
                    A/=2*(y[j]-y[i]);
                    B/=2*(y[j]-y[i]);

                    if (solve(1+A*A,-2*x[j]+2*A*(B-y[j]),-sqr(r[j])+sqr(x[j])+sqr(B-y[j]),aa,bb)){
                        aa=atan2l(A*aa+B-y[i],aa-x[i]);
                        bb=atan2l(A*bb+B-y[i],bb-x[i]);
                        add(aa,bb,i,j,tb);
                    }
                }
            }

            if (!ok) continue;

            int open=0;
            REP(j,tb.size()) if (tb[j].ST>=2*pi) tb[j].ST-=2*pi, ++open;

            //printf("OK %d %Lf %Lf %Lf >> %d\n",i,x[i],y[i],r[i],open);
            sort(ALL(tb));
            tb.pb(MP(2*pi,0));
            ld last=0;
            REP(j,tb.size()){
                //printf(">> %Lf %d >> %Lf %Lf\n",tb[j].ST, tb[j].ND, x[i]+r[i]*cosl(tb[j].ST),y[i]+r[i]*sinl(tb[j].ST));
                if (0 && tb[j].ST-eps>last){
                    double cc=(last+tb[j].ST)/2;
                    double xo=x[i]+r[i]*cosl(cc), yo=y[i]+r[i]*sinl(cc);

                    int ok=1;

                    if (xo<0 || yo<0 || xo>w || yo>h) ok=0;
                    REP(k,n) if (ok && k!=i) if (sqr(x[k]-xo)+sqr(y[k]-yo)<r[k]*r[k]) ok=0;
                    //printf("TRYING %lf >> %d  %d\n",cc,ok,open);
                    assert(ok!=bool(open));
                }
                if (!open) res+=(tb[j].ST-last)*r[i];
                last=tb[j].ST;
                open+=tb[j].ND;
            }

        }
        printf("%.10Lf\n",res);
    }
    return 0;
}

