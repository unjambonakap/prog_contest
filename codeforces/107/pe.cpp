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
const int inf=1e9;
int par[maxn];
int c[maxn];
int d[maxn];
vector<pii> e[maxn];
int L, R;
int w[maxn];
int n;
int resa, resb;

void dfs(int a, int p){
    d[a]=0;
    FE(it, e[a]) if (it->ST!=p){
        par[it->ST]=a;
        c[it->ST]=it->ND;
        dfs(it->ST,a);
        checkmax(d[a], d[it->ST]+1);
    }
}

pii operator+(const pii &a, const pii &b){return MP(a.ST+b.ST,a.ND+b.ND);}


struct segTree{
    segTree *l, *r;
    int T, H;
    int x;
    int best;
    int pad;

    segTree(int a, int b){
        l=r=0;
        best=-inf;
        pad=0;
        T=a; H=b;
        if (a+1==b) return;
        int M=(a+b)/2;
        l=new segTree(a,M);
        r=new segTree(M,b);
    }
    ~segTree(){ if (l){ delete l; delete r;} }

    void update(){
        if (l){ 
            if (l->best+l->pad>r->best+r->pad) best=l->best+l->pad, x=l->x;
            else best=r->best+r->pad, x=r->x;
        }
    }

    void add(int a, int b, int v){
        if (T>=b||H<=a) return;
        if (T>=a&&H<=b) pad+=v;
        else{
            l->add(a,b,v);
            r->add(a,b,v);
            update();
        }

    }
    void insert(int p, int v, int w){
        if (T>p||H<=p) return;
        if (!l){
            if (v>best+pad) best=v, x=w, pad=0;
        }else{
            l->pad+=pad; r->pad+=pad;
            pad=0;
            l->insert(p,v,w);
            r->insert(p,v,w);
            update();
        }
    }

    pii get(int a, int b){
        if (T>=b||H<=a) return MP(-inf,-1);
        if (T>=a&&H<=b) return MP(best+pad,x);
        return max(l->get(a,b),r->get(a,b))+MP(pad,0);
    }
};

int V;

void go(int p, segTree &r, int dx){

    int pick=-1;
    REP(i,e[p].size()){
        int a=e[p][i].ST;
        if (a!=par[p] && (pick==-1 || d[pick]<d[a])) pick=a;
    }
    if (pick!=-1){
        go(pick,r,dx+1);
    }


    REP(i,e[p].size()){
        int a=e[p][i].ST;
        if (a==par[p] || a==pick) continue;
        segTree x(0,d[a]+1);
        go(a,x,0);
        REP(i,d[a]+1){
            pii v=x.get(i,i+1);
            int lb=L-i+dx-1, ub=R-i+dx-1;
            pii u=r.get(lb,ub+1);

            if (u.ST+v.ST>=0){
                resa=u.ND, resb=v.ND;
                throw 72;
            }
        }
        REP(i,d[a]+1){
            pii v=x.get(i,i+1);
            r.insert(dx+1+i,v.ST,v.ND);
        }
        
    }
    if (par[p]!=-1){
        r.insert(dx,0,p);
        r.add(dx,inf,c[p]>=V?1:-1);
        pii u=r.get(dx+L-1, dx+R);
        if (u.ST>=0){ resa=par[p]; resb=u.ND; throw 72;}
    }


}

int checkit(int _V){
    V=_V;
    segTree x(0,d[0]+1);
    try{ go(0,x,0);
    }catch(int fuu){return 1;}
    return 0;
}

int main(){
    cin>>n>>L>>R;
    REP(i,n-1){
        int x,y,z; scanf("%d%d%d",&x,&y,&z); 
        --x; --y;
        e[x].pb(MP(y,z));
        e[y].pb(MP(x,z));
    }

    par[0]=-1;
    dfs(0,-1);

    int T=0, H=1e9;
    int best=-1;
    while(T<=H){
        int M=(T+H)/2;
        if (checkit(M)) best=M, T=M+1;
        else H=M-1;
    }

    assert(best!=-1);
    cout<<resa+1<<" "<<resb+1<<endl;



    return 0;
}



