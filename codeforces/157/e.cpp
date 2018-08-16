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

const int maxn=1e5+10;
const int maxm=maxn*100;
struct node{
    int T,H;
    int l,r;
    int has;
};
int res[maxn];
int pos;
node tb[maxm];
vi with[maxn];
int n;
int st[maxn], nd[maxn];
int U;
vi e[maxn];


int init(int a, int b){
    node *x=tb+pos++;
    x->T=a; x->H=b;
    x->l=x->r=-1;
    if (a+1!=b){
        x->l=init(a,a+b>>1);
        x->r=init(a+b>>1,b);
        x->has=tb[x->l].has+tb[x->r].has;
    }
    return x-tb;
}

void dfs(int a, int p=-1){
    st[a]=U;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        dfs(b,a);
    }
    nd[a]=++U;
}

int update(int u, int a, int b){
    node *x=tb+u;
    if (x->T>=b || x->H<=a) return u;
    if (x->has==x->H-x->T) return u;
    u=pos++;
    assert(pos<maxm);
    tb[u]=*x;
    x=tb+u;
    if (a<=x->T && x->H<=b) x->has=x->H-x->T;
    else{
        x->l=update(x->l,a,b);
        x->r=update(x->r,a,b);
        x->has=tb[x->l].has+tb[x->r].has;
    }
    return u;
}

void go(int a, int x, int p=-1){
    if (with[a].size()){
        with[a].pb(a);
        sort(ALL(with[a]));
        with[a].resize(unique(ALL(with[a]))-with[a].begin());
        REP(i,with[a].size()){
            int b=with[a][i];
            x=update(x,st[b],nd[b]);
        }
    }
    res[a]=tb[x].has-1;
    if (res[a]<0) res[a]=0;


    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        go(b,x,a);
    }
}

int main(){
    int m;
    cin>>n>>m;
    REP(i,n-1){
        int a, b;
        scanf(" %d%d",&a,&b); --a; --b;
        e[a].pb(b); e[b].pb(a);
    }
    dfs(0);
    REP(i,m){
        int a,b; scanf(" %d%d",&a,&b); --a; --b;
        with[a].pb(b);
        with[b].pb(a);
    }
    int x=init(0,n);
    go(0,x);

    REP(i,n) printf("%d ",res[i]); puts("");
    return 0;
}

