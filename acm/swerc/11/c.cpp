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

const int oo=2e9+10;
const int maxn=111111;
const int maxx=1e9+10;

int n;
int tb[maxn*40*5];
int pos, pos2;
int perm[maxn];
int x[maxn], y[maxn];


int cmp(int a, int b){return y[a]<y[b];}

struct node{
    int T,H;
    node *l,*r;
    int *la,*lb,*ra,*rb;
    int *yl,nx;

    void init(int a, int b, int *u, int n);

    int query(int xa, int ya){
        if (!nx) return oo;
        if (xa>=H-1){
            int t=0, h=nx-1, best=-1;
            while(t<=h){
                int m=t+h>>1;
                if (y[yl[m]]<=ya) t=m+1, best=m;
                else h=m-1;
            }
            int res=oo;
            if (best!=-1) res=min(res,la[best]+xa+ya);
            if (best==-1 || y[yl[best]]<ya) ++best;
            if (best!=nx) res=min(res,lb[best]+xa-ya);
            return res;

        }else if (xa<=T){
            int t=0, h=nx-1, best=-1;
            while(t<=h){
                int m=t+h>>1;
                if (y[yl[m]]<=ya) t=m+1, best=m;
                else h=m-1;
            }
            int res=oo;
            if (best!=-1) res=min(res,ra[best]-xa+ya);
            if (best==-1 || y[yl[best]]<ya) ++best;
            if (best!=nx) res=min(res,rb[best]-xa-ya);
            return res;

        }else return min(l->query(xa,ya),r->query(xa,ya));

    }
}tx[maxn*70];

void node::init(int a, int b, int *u, int n){
    if (!n){ nx=0; l=r=0; return;}

    T=a; H=b; nx=n;
    yl=tb+pos; pos+=n;
    REP(i,n) yl[i]=u[i];
    sort(yl,yl+n,cmp);

    la=tb+pos; pos+=n;
    lb=tb+pos; pos+=n;
    ra=tb+pos; pos+=n;
    rb=tb+pos; pos+=n;

    int best=oo;
    REP(i,n){
        best=min(best,-x[yl[i]]-y[yl[i]]);
        la[i]=best;
    }

    best=oo;
    REPV(i,n){
        best=min(best,-x[yl[i]]+y[yl[i]]);
        lb[i]=best;
    }

    best=oo;
    REP(i,n){
        best=min(best,x[yl[i]]-y[yl[i]]);
        ra[i]=best;
    }

    best=oo;
    REPV(i,n){
        best=min(best,x[yl[i]]+y[yl[i]]);
        rb[i]=best;
    }

    l=r=0;
    if (T+1==H) return;
    l=tx+pos2++;
    r=tx+pos2++;
    assert(pos2<70*maxn);
    int na=0;
    int M=T+H>>1;
    REP(i,n) if (x[u[i]]<M) swap(u[i],u[na++]);
    l->init(T,M,u,na);
    r->init(M,H,u+na,n-na);
}


int main(){
    int tc=0;
    while(cin>>n,n>0){
        if (tc++) puts("");

        REP(i,n) scanf(" %d%d",x+i,y+i);

        REP(i,n) perm[i]=i;
        pos2=pos=0;

        tx[pos2++].init(0,maxx,perm,n);

        int nq; cin>>nq;
        REP(step,nq){
            int xa,ya; scanf(" %d%d",&xa,&ya);
            int res=tx[0].query(xa,ya);
            printf("%d\n",res);
        }

    }
    return 0;
}

