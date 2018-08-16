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

const int maxn=1<<17;
const int oo=1e9;
int n;
int A[maxn];
int res, resl, resr;
int wh;

struct node{
    node *l,*r;
    int T,H;
    int tot;
    int minl,maxl,minr,maxr;
    int minlp,maxlp,minrp,maxrp;

    int minv,minpa,minpb;
    int maxv,maxpa,maxpb;
    int mul;


    int ql,qlp,wql,qr,qrp,wqr;

    void init(int a, int b);
    void initleaf(){
        int a=T;
        minl=maxl=minr=maxr=0;
        minlp=maxlp=a;
        minrp=maxrp=a+1;

        minv=maxv=0;
        minpa=minpb=maxpa=maxpb=a;


        tot=A[a];
        if (A[a]<0){
            minv=minl=minr=A[a];
            minlp=a+1;
            minrp=a;
            minpb=a+1;
        }else{
            maxv=maxl=maxr=A[a];
            maxlp=a+1;
            maxrp=a;
            maxpb=a+1;
        }
    }

    void negate(){
        tot*=-1;
        minl*=-1; maxl*=-1;
        minr*=-1; maxr*=-1;
        minv*=-1; maxv*=-1;
        swap(minl,maxl); swap(minr,maxr);
        swap(minlp,maxlp); swap(minrp,maxrp);

        swap(minv,maxv);
        swap(minpa,maxpa); swap(minpb,maxpb);

        mul*=-1;

    }
    void negate(int a, int b){
        norm();
        if (a>=H||b<=T) return;

        if (a<=T&&H<=b){negate(); return; }
        l->negate(a,b);
        r->negate(a,b);
        update();
    }
    void norm(){
        if (mul==1) return;
        mul=1;
        if (T+1!=H){
            l->negate();
            r->negate();
        }
    }
    void modify(int a){
        if (a<T || a>=H) return;
        norm();
        if (T+1==H){initleaf(); return;}
        l->modify(a);
        r->modify(a);
        update();
    }

    void update(){
        tot=l->tot+r->tot;
        if (l->maxl>l->tot+r->maxl) maxl=l->maxl, maxlp=l->maxlp;
        else maxl=l->tot+r->maxl, maxlp=r->maxlp;

        if (r->maxr>r->tot+l->maxr) maxr=r->maxr, maxrp=r->maxrp;
        else maxr=r->tot+l->maxr, maxrp=l->maxrp;

        if (l->minl<l->tot+r->minl) minl=l->minl, minlp=l->minlp;
        else minl=l->tot+r->minl, minlp=r->minlp;

        if (r->minr<r->tot+l->minr) minr=r->minr, minrp=r->minrp;
        else minr=r->tot+l->minr, minrp=l->minrp;

        maxv=-oo;
        minv=oo;
        if (maxv<l->maxv) maxv=l->maxv, maxpa=l->maxpa, maxpb=l->maxpb;
        if (maxv<r->maxv) maxv=r->maxv, maxpa=r->maxpa, maxpb=r->maxpb;
        if (maxv<l->maxr+r->maxl) maxv=l->maxr+r->maxl, maxpa=l->maxrp, maxpb=r->maxlp;

        if (minv>l->minv) minv=l->minv, minpa=l->minpa, minpb=l->minpb;
        if (minv>r->minv) minv=r->minv, minpa=r->minpa, minpb=r->minpb;
        if (minv>l->minr+r->minl) minv=l->minr+r->minl, minpa=l->minrp, minpb=r->minlp;

    }

    void getl(int b){
        norm();
        if (wql==wh) return;
        wql=wh;
        if (b<T){ql=-oo; return;}

        if (H<=b+1){ql=maxl; qlp=maxlp;}
        else{
            l->getl(b); r->getl(b);
            if (l->tot+r->ql>l->ql) ql=l->tot+r->ql, qlp=r->qlp;
            else ql=l->ql, qlp=l->qlp;
        }
    }
    void getr(int a){
        norm();
        if (wqr==wh) return;
        wqr=wh;
        if (H<=a){qr=-oo; return;}

        if (a<=T){qr=maxr; qrp=maxrp;}
        else{
            l->getr(a); r->getr(a);
            if (r->tot+l->qr>r->qr) qr=r->tot+l->qr, qrp=l->qrp;
            else qr=r->qr, qrp=r->qrp;
        }
    }

    void get(int a, int b){
        if (b<=T || a>=H) return;
        norm();
        if (a<=T && H<=b){
            if (res<maxv) res=maxv, resl=maxpa, resr=maxpb;
            return;
        }

        l->get(a,b);
        r->get(a,b);

        l->getr(a); r->getl(b-1);
        if (res<l->qr+r->ql){res=l->qr+r->ql; resl=l->qrp; resr=r->qlp;}

    }
}tb[2*maxn];

int pos;

node *getn(){return tb+pos++;}
void node::init(int a, int b){
    T=a; H=b;
    mul=1;
    if (a+1==b) initleaf();
    else{

        l=getn(); r=getn();
        l->init(a,a+b>>1);
        r->init(a+b>>1,b);
        update();
    }
}



int main(){
    cin>>n;
    REP(i,n) scanf(" %d",A+i);
    node *x=getn();
    x->init(0,n);

    int nq; cin>>nq;
    REP(i,nq){
        int f,a,b,c;
        scanf(" %d%d%d",&f,&a,&b);
        if (f==0){
            --a;
            A[a]=b;
            x->modify(a);
        }else{
            scanf(" %d",&c);
            --a; --b;
            vector<pii> tb;
            int ans=0;
            REP(i,c){
                res=0;
                ++wh;
                x->get(a,b+1);

                if (res<=0) break;
                x->negate(resl,resr);

                tb.pb(MP(resl,resr));
                ans+=res;
            }
            printf("%d\n",ans);
            REP(i,tb.size()) x->negate(tb[i].ST,tb[i].ND);
        }
    }
    return 0;
}

