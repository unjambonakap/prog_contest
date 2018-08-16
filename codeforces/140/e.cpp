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

const int nb=18;
const int maxn=1<<nb;


vi e[maxn];
int par[nb][maxn];
int n;
int depth[maxn];
int order[2][maxn];
int pos;

struct tree{
    tree *l,*r;
    int c;
    int T,H;

    void copy(const tree *t){ l=t->l; r=t->r; c=t->c; T=t->T; H=t->H; }
    tree(){}
    tree(int a, int b){
        T=a; H=b;
        c=0;
        if (a+1==b) return;
        l=new tree(a,a+b>>1);
        r=new tree(a+b>>1,b);
    }

    int query(int a){
        if (a>=H) return c;
        if (a<=T) return 0;
        return l->query(a)+r->query(a);
    }

    void update0(int p, int v){
        if (p<T || p>=H) return;
        c+=v;
        if (T+1<H) l->update(p,v), r->update(p,v);
    }

    tree *update(int p, int v){
        if (p<T || p>=H) return this;
        tree *b=new tree();
        b->copy(this); b->c+=v;
        if (T+1<H) b->l=l->update(p,v), b->r=r->update(p,v);
        return b;
    }
};
tree *prev[maxn];



void dfs(int a, int d){
    depth[a]=d;
    order[0][a]=pos++;
    REP(i,e[a].size()) dfs(e[a][i],d+1);
    order[1][a]=pos++;
}

int lca(int a, int b){
    if (depth[a]<depth[b]) swap(a,b);
    for (int i=nb-1; i>=0; --i) if (depth[par[i][a]]>=depth[b]) a=par[i][a];
    for (int i=nb-1; i>=0; --i) if (par[i][a]!=par[i][b]) a=par[i][a], b=par[i][b];
    return a==b?a:par[0][a];
}


int go(int a, int b, int k, tree *x, tree *y){
    int c=lca(a,b);
    int T,H,diff;
    int best=-2;

    if (depth[a]+depth[b]-2*depth[c]<k) return -2;

    T=depth[c]; H=depth[a]-1;
    int oh=H;
    if (c==b) ++T;

    int have=y->query(order[0][a])-x->query(order[0][a]);
    while(T<=H){
        int M=T+H>>1, ok=0;
        int u=a;

        for (int i=nb-1; i>=0; --i) if (depth[par[i][u]]>=M) u=par[i][u];
        int v=y->query(order[0][u])-x->query(order[0][u]);
        if (oh-M+1-(have-v)>=k) ok=1;

        if (ok) T=M+1, best=u;
        else H=M-1;
    }

    if (best!=-2) return best;


    k-=(depth[a]-depth[c])-have+y->query(order[0][c])-x->query(order[0][c]);


    T=depth[c]+1; H=depth[b]-1;
    int ot=T;
    have=y->query(order[0][c]+1)-x->query(order[0][c]+1);

    while(T<=H){
        int M=T+H>>1, ok=0;
        int u=b;

        for (int i=nb-1; i>=0; --i) if (depth[par[i][u]]>=M) u=par[i][u];
        int v=y->query(order[0][u]+1)-x->query(order[0][u]+1);
        if (M-ot+1-(v-have)>=k) ok=1;
        if (ok) H=M-1, best=u;
        else T=M+1;
    }
    return best;
}


int main(){
    cin>>n;
    int root=-1;
    REP(i,n){
        int a; scanf(" %d", &a); --a;
        par[0][i]=a==-1?i:a;
        if (a!=-1) e[a].pb(i);
        else root=i;
    }

    pos=0;
    dfs(root,0);
    FOR(i,1,nb) REP(j,n) par[i][j]=par[i-1][par[i-1][j]];

    tree *last=prev[0]=new tree(0,2*n);

    int nq; cin>>nq;
    REP(i,nq){
        int type; scanf(" %d",&type); 
        if (type==1){
            int a; scanf(" %d",&a); 
            --a;
            last=last->update(order[0][a],1);
            last=last->update(order[1][a],-1);
            
        }else{
            int a, b, k, y; scanf(" %d%d%d%d",&a,&b,&k,&y);
            int res=go(a-1,b-1,k,prev[y],last);
            printf("%d\n",res+1);
        }
        prev[i+1]=last;
    }


    return 0;
}



