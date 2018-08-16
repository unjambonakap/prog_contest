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
#include<unistd.h>

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


const int maxb=17;
const int maxn=1<<maxb;
const int oo=2e9;

int n,m,N;
vector<pii> e[maxn];
int st[maxn], nd[maxn];
int fx[maxn];
int cost[maxn];
int rmq[maxb][maxn];

int par[maxb][maxn];
int cp[maxn];
int d[maxn];
vi lst[maxn];
int A,B;

int tree[4*maxn];


int cmp(int a, int b){return st[a]<st[b];}

int lca(int a, int b){
    if (d[a]<d[b]) swap(a,b);
    for (int i=maxb-1; i>=0; --i) if (d[a]-(1<<i)>=d[b]) a=par[i][a];
    if (a==b) return a;
    for (int i=maxb-1; i>=0; --i) if (par[i][a]!=par[i][b]) a=par[i][a], b=par[i][b];
    return par[0][a];
}

void dfs(int a, int p=-1){
    cost[a]=p==-1?0:cost[p]+cp[a];
    d[a]=p==-1?0:d[p]+1;
    par[0][a]=p==-1?a:p;
    st[a]=N++;
    REP(i,e[a].size()){
        int b=e[a][i].ST;
        if (b==p) continue;
        cp[b]=e[a][i].ND;
        dfs(b,a);
    }
    nd[a]=N++;
}
int succ(int a, int c){
    for (int i=maxb-1; i>=0; --i) if (d[c]<d[a]-(1<<i)) a=par[i][a]; 
    return a;
}

void update(int a, int v){a+=2*maxn; tree[a]=v; for (; a>1; a>>=1) tree[a>>1]=max(tree[a],tree[a^1]);}
int get(int a, int b){
    a+=2*maxn; b+=2*maxn-1;
    int res=max(tree[a],tree[b]);
    for (; b-a>1; a>>=1, b>>=1){
        if (!(a&1) && res<tree[a^1]) res=tree[a^1];
        if ((b&1) && res<tree[b^1]) res=tree[b^1];
    }
    return res;
}

int get2(int a, int b){
    int res=oo;
    for (int i=maxb-1; i>=0; --i) if (d[a]-(1<<i)>=d[b]) res=min(res,rmq[i][a]), a=par[i][a];
    return res;
}

void go(int l, int r, int last=-1, int costlast=-2){
    if (l>=r) return;

    int a=lca(fx[l],fx[r-1]);
    if (a==fx[l]){
        ++l;
        if (last==-1) last=a, costlast=0;
    }

    if (last!=-1) costlast+=cost[a]-cost[last];
    if (l>=r){
        if (A==costlast) B=min(B,get2(a,last));
        return;
    }

    assert(lst[a].size());
    lst[a].pb(r-1);
    int nl=l;

    int best=0, best2=0;
    int bestv=-1, bestv2=-1;
    vector<pair<int,pii> > tb;

    REP(i,lst[a].size()){
        if (nl==lst[a][i]+1) continue;

        int val=get(st[fx[nl]],st[fx[lst[a][i]]]+1)-cost[a];
        tb.pb(MP(val,MP(nl,lst[a][i]+1)));
        if (bestv<=val){
            if (bestv<val) bestv2=bestv, best2=best, best=0;
            ++best; bestv=val;
        }else if (bestv2<=val){
            if (bestv2<val) best2=0;
            ++best2; bestv2=val;
        }
        nl=lst[a][i]+1;
    }

    if (last!=-1){
        int val=costlast;

        if (bestv<=val){
            if (bestv<val) bestv2=bestv, best2=best, best=0;
            ++best; bestv=val;
        }else if (bestv2<=val){
            if (bestv2<val) best2=0;
            ++best2; bestv2=val;
        }
    }

    assert(best+best2>1);

    int f1=0, f2=0;
    if (best>1){
        if (bestv+bestv>A){ 
            A=bestv+bestv;
            B=oo;
            if (best==2) f1=1;
        }else if (bestv+bestv==A){
            assert(costlast==bestv);
            if (best==2) f1=1;
        }
    }else{
        if (bestv+bestv2>A){
            A=bestv+bestv2;
            B=oo;
            f1=1;
            if (best2==1) f2=1;
        }else if (bestv+bestv2==A){
            f1=1;
            if (best2==1) f2=1;
        }
    }
    if (!f1 && costlast==bestv){ B=oo; return;}
    if (!f2 && costlast==bestv2) B=oo;

    if (f2){
        if (costlast==bestv2) B=min(B,get2(a,last));
        REP(i,tb.size()) if (tb[i].ST==bestv2){
            int ncost=bestv;
            go(tb[i].ND.ST,tb[i].ND.ND,a,ncost);
        }
    }
    if (f1){
        if (costlast==bestv) B=min(B,get2(a,last));
        REP(i,tb.size()) if (tb[i].ST==bestv){
            int ncost=best==2?bestv:bestv2;
            go(tb[i].ND.ST,tb[i].ND.ND,a,ncost);
        }
    }
}

void checkit(int A, int B){
    int ca=0;
    REP(i,m) REP(j,i){
        int k=lca(fx[i],fx[j]);
        int cx=cost[fx[i]]+cost[fx[j]]-2*cost[k];
        ca=max(ca,cx);
        //printf("%d %d >> %d\n",fx[i],fx[j],cx);
    }
    //printf("HAVE %d, sol %d\n",A,ca);
    assert(ca==A);

}

int main(){
    srand(2);
    int gen=0;
    if (gen) n=90;
    else cin>>n;


    REP(i,n-1){
        int a, b, c; 
        if (gen){
            a=i+1;
            b=rand()%(i+1);
            c=rand()%10;
            printf("%d %d %d\n",a,b,c);
        }else{
            scanf(" %d%d%d",&a,&b,&c); --a; --b;
        }
        e[a].pb(MP(b,c));
        e[b].pb(MP(a,c));
    }
    dfs(0);

    REP(i,maxb-1) REP(j,n) par[i+1][j]=par[i][par[i][j]];

    REP(i,n) rmq[0][i]=cp[i];
    rmq[0][0]=oo;
    REP(i,maxb-1) REP(j,n) rmq[i+1][j]=min(rmq[i][j],rmq[i][par[i][j]]);


    int nq; 
    if (gen) nq=100;
    else cin>>nq;

    REP(qq,nq){
        if (gen){
            set<int> uu;
            while(uu.size()<n/2) uu.insert(rand()%n);
            m=0;
            FE(it,uu) fx[m++]=*it;
            m=4;
        }else{
            scanf(" %d",&m);
            REP(i,m) scanf(" %d",fx+i), --fx[i];
        }
        sort(fx,fx+m,cmp);
        REP(i,m) update(st[fx[i]],cost[fx[i]]);

        vi el;
        REP(i,m-1){
            int c=lca(fx[i],fx[i+1]);
            el.pb(c);
            lst[c].pb(i);
        }

        A=-1;
        B=oo;
        go(0,m);

        if (B==oo) B=-1;
        assert(A!=-1);

        if (gen){
            checkit(A,B);
        }else{
            printf("%d %d\n",A,B);
        }

        REP(i,el.size()) lst[el[i]].clear();
        REP(i,m) update(st[fx[i]],0);
        assert(tree[1]==0);
    }


    return 0;
}

