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

const int maxb=18;
const int maxn=200222;
const int maxs=4*2*maxb*100111;//node per update * nupdate
vi e[maxn];
int n;
char buf[11];

int par[maxb][maxn];
int d[maxn];
int md;

int lst[maxn], sgn[maxn];
int st[maxn], nd[maxn];
int N;

int T[maxn], H[maxn];
ll s[maxn][2];
int pos2;

struct node{
    int dx;
    int v[2];
    ll val;
    int l,r;

}tb[maxs];

int pos;
int root[maxn];


int getn(){assert(pos<maxs);return pos++;}

void copy(node *a, node *x){ a->dx=x->dx; a->v[0]=x->v[0]; a->v[1]=x->v[1]; a->val=x->val; a->l=x->l; a->r=x->r; }
void init(int _x, int a, int b){
    node *x=tb+_x;
    x->dx=pos2++;
    T[x->dx]=a; H[x->dx]=b;
    if (a+1==b){
        s[x->dx][0]=sgn[a];
        s[x->dx][0]=md-d[lst[a]]+1;
    }else{
        x->l=getn(); x->r=getn();
        init(x->l,a,a+b>>1);
        init(x->r,a+b>>1,b);
        REP(f,2) s[x->dx][f]=s[tb[x->l].dx][f]+s[tb[x->r].dx][f];
    }
}

ll getv(node *x){return x->val+s[x->dx][0]*x->v[0]+s[x->dx][1]*x->v[1];}
ll getv(int _x, int a, int b){
    node *x=tb+_x;
    if (T[x->dx]>=b || H[x->dx]<=a) return 0;
    if (a<=T[x->dx] && H[x->dx]<=b) return getv(x);
    return getv(x->l,a,b)+getv(x->r,a,b);
}

int update(int _x, int a, int b, int v0, int v1){
    node *x=tb+_x;
    if (T[x->dx]>=b || H[x->dx]<=a) return _x;
    int _nx=getn();
    node *nx=tb+_nx;
    copy(nx,x);

    if (a<=T[x->dx] && H[x->dx]<=b){ nx->v[0]+=v0, nx->v[1]+=v1; return _nx;}
    nx->l=update(x->l,a,b,v0,v1);
    nx->r=update(x->r,a,b,v0,v1);
    nx->val=getv(tb+nx->l)+getv(tb+nx->r);
    return _nx;
}


int lca(int a, int b){
    if (d[a]<d[b]) swap(a,b);
    for (int i=maxb-1; i>=0; --i) if (d[par[i][a]]>=d[b]) a=par[i][a];
    for (int i=maxb-1; i>=0; --i) if (par[i][a]!=par[i][b]) a=par[i][a], b=par[i][b];
    if (a!=b) a=par[0][a];
    return a;
}

void dfs(int a, int p=-1){
    par[0][a]=p==-1?a:p;
    lst[N]=a; sgn[N]=1; st[a]=N++;

    d[a]=p==-1?0:d[p]+1;
    md=max(d[a],md);
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        dfs(b,a);
    }
    lst[N]=a; sgn[N]=-1; nd[a]=N++;
}

int main(){
    int nq; cin>>n>>nq;
    REP(i,n-1){
        int a, b;
        scanf(" %d%d",&a,&b);
        --a; --b;
        e[a].pb(b);
        e[b].pb(a);
    }

    N=0;
    dfs(0);
    REP(i,maxb-1) REP(j,n) par[i+1][j]=par[i][par[i][j]];

    ll ans=0;
    int ns=0;
    int cur=root[ns++]=getn();
    init(cur,0,N);

    printf(">> %d\n",sizeof(node));
    printf("%d\n",sizeof(tb)/1024/1024);
    REP(qq,nq){
        scanf(" %s",buf);
        if (buf[0]=='c'){
            int a,b,A,B; 
            scanf(" %d%d%d%d",&a,&b,&A,&B);

            a=(a+ans)%n;
            b=(b+ans)%n;
            int c=lca(a,b);

            int dd=md-d[a]+1;
            int df=d[a]+d[b]-2*d[c];
            printf("update root > %d\n",a);
            cur=update(cur,0,nd[a]+1,A-1ll*dd*B,B);
            cur=update(cur,0,nd[c]+1,-(A-1ll*dd*B),-B);

            dd=md-d[b]+1;
            cur=update(cur,0,nd[b]+1,A-1ll*dd*B+1ll*df*B,-B);
            if (par[0][c]!=c) cur=update(cur,0,nd[par[0][c]]+1,-(A-1ll*dd*B+1ll*df*B),B);

            root[ns++]=cur;
        }else if (buf[0]=='q'){
            int x,y;
            scanf(" %d%d",&x,&y);
            x=(x+ans)%n;
            y=(y+ans)%n;
            int c=lca(x,y);
            ll res=getv(cur,0,st[x]+1)+getv(cur,0,st[y]+1);
            res-=getv(cur,0,st[c]+1)+getv(cur,0,st[c]);

            printf("%Ld\n",res);
            ans=res;
        }else{
            int uu;
            scanf(" %d",&uu);
            uu=(uu+ans)%ns;
            cur=root[uu];
        }
    }
    return 0;
}

