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

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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

const int maxn=(1<<17)+10;
const double inf=111;
const double infx=55555;
const double eps=1e-5;

int sqr(int a){return a*a;}

struct Missile{
    double a; int c, xo;
    int lp;
    Missile(int p=-2, int x=-1, int y=0):lp(p){ xo=x; c=y; a=1.*-c/sqr(p-xo); }


    int intersection(const Missile &s, double &xa, double &xb)const{
        double A=a-s.a;
        double B=-2*(a*xo-s.a*s.xo);
        double C=xo*xo-s.xo*s.xo+c-s.c;

        double D=B*B-4*A*C;
        if (D<0) return 0;
        if (D<eps){ xa=-B/2/A; return 1; }
        D=sqrt(D);
        xb=(-B-D)/2/A;
        xa=(-B+D)/2/A;
        return 2;
    }
    double eval(double x)const{ return a*sqr(x-xo)+c; }

};



int n;
Missile M[maxn];

int qxa, qxb;


/******SPACE  SEGMENT TREE *********/

struct spaceInt{
    vector<double> tx;
    vector<Missile> F;
    vector<double> from, to;
    int na;

    void clear(int nx=0){
        na=nx;
        tx.clear();
        F=vector<Missile>(na);
        from=to=vector<double>(nx);
    }

    void buildSegTree(){
        int nb=na;
        while(nb&nb-1) nb&=nb-1;
        if (nb!=na) nb<<=1;
        REP(i, nb-na) F.pb(Missile()), from[i]=to[i]=inf;
        na=nb;

        tx=vector<double>(na);
        initSegTree(1,0,na);
    }
    double initSegTree(int p, int T, int H){
        if (T+1==H) return F[p-na].c;
        return tx[p]=max(initSegTree(2*p, T, (T+H)/2), initSegTree(2*p+1, (T+H)/2, H));
    }


    void init(const Missile &a){
        clear(4);
        from[0]=-inf;
        to[0]=from[1]=a.lp;
        to[1]=from[2]=a.xo;
        to[2]=from[3]=2*a.xo-a.lp;
        to[3]=inf;
        F[1]=F[2]=a;

        buildSegTree();
    }

    void init(spaceInt *a, spaceInt *b){

    }


    double queryInt(int p, int a, int b){
        if (b<=from[p] || a>=to[p]) return 0.;
        if (p>=na){
            Missile &x=F[p-na];
            return max(x.eval(max(1.*a, from[p])), x.eval(min(1.*b, to[p])));
        }
        if (a<=from[p] && b>=to[p]) return tx[p];
        return max(queryInt(2*p, a, b), queryInt(2*p+1, a, b));
    }
};



/******TIME  SEGMENT TREE *********/
int HT[maxn], TT[maxn];
spaceInt tree[maxn];

spaceInt *initTree(int p, int T, int H){
    HT[p]=H; TT[p]=T;
    spaceInt *a, *b, *c=tree+p;
    if (T+1==H){ c->init(M[p-n]); return c; }
    int M=(T+H)/2;
    a=initTree(2*p, T, M);
    b=initTree(2*p+1, M, H);
    c->init(a,b);
    return c;

}
double query(int p, int T, int H){
    double ans=inf;
    checkmax(T, HT[p]);
    checkmin(H, HT[p]);
    if (T>=H) return 0.;

    if (T==TT[p] && H==HT[p]) ans=tree[p].queryInt(1, qxa, qxb);
    else ans=max(query(2*p, T, H), query(2*p+1, T, H));
    return ans;
}

int main(){
    cin>>n;
    REP(i, n){
        int p, x, y;
        cin>>p>>x>>y;
        M[i]=Missile(p,x,y);
    }

    int nb=n;
    while(nb&nb-1) nb&=nb-1;
    if (nb!=n) nb<<=1;
    REP(i, nb-n) M[n+i]=Missile(-2,-1,1);
    n=nb;

    initTree(1, 0, n);




    int nq; cin>>nq;
    REP(i, nq){
        int ta, tb;
        cin>>ta>>tb>>qxa>>qxb;
        qxb; ++tb;
        double res=0.;
        res=query(1, ta, tb);
        printf("%lf ", res);
    }
    printf("\n");


    return 0;

}



