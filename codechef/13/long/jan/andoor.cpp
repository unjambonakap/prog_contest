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

void norm(ld &aa, ld &bb){
    while (aa<0) aa+=2*pi; while (aa>=2*pi) aa-=2*pi;
    while (bb<0) bb+=2*pi; while (bb>=2*pi) bb-=2*pi;
    if (aa>bb) swap(aa,bb);

}

void add(ld aa, ld bb, int i, int j, vector<pair<ld,int> > &tb){
    norm(aa,bb);

    ld cc=(aa+bb)/2;
    if (sqr(x[i]+r[i]*cosl(cc)-x[j])+sqr(y[i]+r[i]*sinl(cc)-y[j])>
            sqr(x[i]-r[i]*cosl(cc)-x[j])+sqr(y[i]-r[i]*sinl(cc)-y[j]))
        aa+=2*pi, swap(aa,bb);
    tb.pb(MP(aa,1)); tb.pb(MP(bb,-1));
}

void go(int i, ld a, ld b, ld c, vector<pair<ld,int> >&tb){
    ld aa,bb;

    ld dx=sqr(a*x[i]+b*y[i]+c)/(sqr(a)+sqr(b));
    if (dx+eps>=sqr(r[i])) return;

    ld xo,yo,xb,yb;
    if (fabs(a)>fabs(b)){
        xo=xb=-c/a;
        yo=y[i]+sqrt(sqr(r[i])-sqr(xo-x[i]));
        yb=2*y[i]-yo;
    }else{
        yo=yb=-c/b;
        xo=x[i]+sqrt(sqr(r[i])-sqr(yo-y[i]));
        xb=2*x[i]-xo;
    }
    aa=atan2(yo-y[i],xo-x[i]);
    bb=atan2(yb-y[i],xb-x[i]);

    norm(aa,bb);
    xo=x[i]+cos((aa+bb)/2)*r[i], yo=y[i]+sin((aa+bb)/2)*r[i];
    if (xo*a+yo*b+c>0) aa+=2*pi, swap(aa,bb);

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

        //if (ti!=1) continue;
        REP(i,n){
            //if (i!=6) continue;

            vector<pair<ld,int> > tb;

            ld aa,bb;

            int ok=1;
            if (x[i]-r[i]+eps>=w) continue;
            if (y[i]-r[i]+eps>=h) continue;
            if (x[i]+r[i]-eps<=0) continue;
            if (y[i]+r[i]-eps<=0) continue;
            go(i,1,0,0,tb);
            go(i,-1,0,w,tb);
            go(i,0,1,0,tb);
            go(i,0,-1,h,tb);


            REP(j,n) if (j!=i){
                ld dx=sqr(x[i]-x[j])+sqr(y[i]-y[j]);
                ld d=sqrt(dx);

                if (dx<=sqr(r[i]-r[j])+eps){
                    if (r[i]<r[j]){ok=0; break;}
                    continue;
                }
                if (dx+eps>=sqr(r[i]+r[j])) continue;

                ld ax=acosl((dx+sqr(r[i])-sqr(r[j]))/(2*d*r[i]));
                aa=atan2(y[j]-y[i],x[j]-x[i])+ax; bb=aa-2*ax;
                //printf("%d %d >> %Lf\n",i,j,ax);

                add(aa,bb,i,j,tb);
            }

            if (!ok) continue;

            int open=0;
            REP(j,tb.size()) if (tb[j].ST>=2*pi) tb[j].ST-=2*pi, ++open;

            //printf("OK %d %Lf %Lf %Lf >> %d\n",i,x[i],y[i],r[i],open);
            sort(ALL(tb));
            tb.pb(MP(2*pi,0));
            ld last=0;
            REP(j,tb.size()){
                //printf("on %d >>> %Lf %Lf with %d (( %Lf\n",i,last,tb[j].ST,open,res);
                if (!open) res+=(tb[j].ST-last)*r[i];
                last=tb[j].ST;
                open+=tb[j].ND;
            }

        }
        printf("%.18Lf\n",res);
    }
    return 0;
}

