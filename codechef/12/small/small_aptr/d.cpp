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

const int maxn=111111;
int A[maxn];

pii proc(const pii &a, const pii &b){
    if (a.ST>b.ST) return MP(a.ST,max(a.ND,b.ST));
    return MP(b.ST,max(a.ST,b.ND));
}

struct node{
    int T, H;
    pii v;
    node *l, *r;
    node(){}
    node(int T, int H):T(T),H(H){
        l=r=0;
        if (T+1==H){v=MP(A[T],0);; return;}
        l=new node(T,T+H>>1);
        r=new node(T+H>>1,H);
        v=proc(l->v,r->v);
    }

    pii query(int a, int b){
        if (a>=H || b<=T) return MP(0,0);
        if (a<=T && b>=H) return v;
        return proc(l->query(a,b),r->query(a,b));
    }
};

node *update(node *x, int a, int b){
    if (a>=x->H || a<x->T) return x;
    node *u=new node();
    u->T=x->T;
    u->H=x->H;
    if (!x->l){
        u->l=u->r=0;
        u->v=MP(b,0);
        return u;
    }
    u->l=update(x->l,a,b);
    u->r=update(x->r,a,b);
    u->v=proc(u->l->v,u->r->v);
    return u;

}


node *tb[maxn];

int main(){
    int n, m, a,b,c,d;
    cin>>n>>m>>a>>b>>c>>d;
    REP(i,n) scanf(" %d", A+i);
    tb[0]=new node(0,n);

    int r1=0, r2=0;
    int nq; cin>>nq;
    FOR(i,1,nq+1){
        int u, v; scanf(" %d%d", &u,&v);
        int t=(1ll*a*r1+d)%i;
        pii res=tb[t]->query(u,v+1);
        r1=res.ST, r2=res.ND;
        printf("%d %d\n",r1,r2);
        u=(1ll*b*r1+d)%n; v=(1ll*c*r2+d)%m;
        tb[i]=update(tb[i-1],u,v);
    }
    return 0;
}


