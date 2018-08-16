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

const int maxc=111;
const int maxn=8888;
const int maxm=111111;
int n, c, m;

struct treap{
    treap *l, *r;
    treap *p;
    int id;
    int cnt;
    int f;

    void init(){
        f=0;
        p=l=r=0;
        cnt=1;
        id=rand();
    }
} tx[maxc][maxn];
typedef pair<int,treap*> pit;

void norm(treap *a){
    if (a->f){
        a->f=0; swap(a->l,a->r);
        if (a->l) a->l->f^=1;
        if (a->r) a->r->f^=1;
    }
}



int count(treap *x){return x?x->cnt:0;}
void disp(treap *x){
    if (!x) return;
    norm(x);
    printf("Is %d, have sz %d, children: \n", x->id, x->cnt);
    printf("left:\n");
    disp(x->l);
    printf("right:\n");
    disp(x->r);

}
pit getData(treap *a){

    vector<treap*> stk;
    for (treap *y=a; y; y=y->p) stk.pb(y);
    while(!stk.empty()) norm(stk.back()), stk.pop_back();
    norm(a);
    int x=1+count(a->l);
    for (; a->p; a=a->p) if (a==a->p->r) x+=1+count(a->p->l);
    return MP(x,a);
}

treap *merge(treap *a, treap *b){
    if (!a) return b;
    if (!b) return a;
    norm(a); norm(b);
    if (a->id>=b->id){
        a->cnt+=count(b), a->r=merge(a->r,b), a->r->p=a;
        return a;
    }else{
        b->cnt+=count(a), b->l=merge(a,b->l), b->l->p=b;
        return b;
    }
}

void split(treap *x, treap *&a, treap *&b, int cnt){
    if (!x){assert(cnt==0);a=b=0; return;}
    norm(x);
    if (count(x->l)+1<=cnt){
        split(x->r,x->r,b,cnt-count(x->l)-1);
        if (x->r) x->r->p=x;
        x->cnt-=count(b);
        a=x;
    }else{
        split(x->l,a,x->l,cnt);
        if (x->l) x->l->p=x;
        x->cnt-=count(a);
        b=x;
    }
    x->p=0;
}


int deg[maxc][maxn];
vector<pii> e[maxn];
int with[maxm];


int getid(int a, int b){
    int x=lower_bound(ALL(e[a]), MP(b,0))-e[a].begin();
    if (x==e[a].size() || e[a][x].ST!=b) return -1;
    return e[a][x].ND;
}


void _merge(const pit &x, const pit &y){

    if (!(x.ST==1||x.ST==x.ND->cnt)) printf("PUTAIN %d %d\n", x.ST, x.ND->cnt);
    if (!(y.ST==1||y.ST==y.ND->cnt)) printf("PUTAIN %d %d\n", y.ST, y.ND->cnt);

    assert(x.ST==1||x.ST==x.ND->cnt);
    assert(y.ST==1||y.ST==y.ND->cnt);
    if (x.ST==1) x.ND->f^=1;
    if (y.ST==y.ND->cnt) y.ND->f^=1;
    treap *res=merge(x.ND,y.ND);

}

int main(){
    srand(time(0));
    int t; 
    while(cin>>n>>m>>c>>t,n){
        REP(i,c) REP(j,n) tx[i][j].init();

        memset(deg,0,sizeof(deg));
        REP(i,n) e[i].clear();
        REP(i,m){
            int a, b, k; scanf(" %d%d%d", &a,&b,&k);
            --a; --b; --k;
            ++deg[k][a]; ++deg[k][b];
            e[a].pb(MP(b,i));
            e[b].pb(MP(a,i));
            with[i]=k;
            _merge(getData(tx[k]+a),getData(tx[k]+b));
        }
        REP(i,n) sort(ALL(e[i]));

        REP(step,t){
            int a, b, k; scanf(" %d%d%d",&a,&b,&k);
            --a; --b; --k;
            int u=getid(a,b);
            if (u==-1) puts("No such cable.");
            else if (with[u]==k) puts("Already owned.");
            else if (deg[k][a]==2 || deg[k][b]==2) puts("Forbidden: monopoly.");
            else{
                pit x=getData(tx[k]+a), y=getData(tx[k]+b);
                if (x.ND==y.ND) puts("Forbidden: redundant.");
                else{
                    int oldk=with[u];
                    --deg[oldk][a]; --deg[oldk][b];
                    ++deg[k][a]; ++deg[k][b];
                    with[u]=k;

                    pit xa=getData(tx[oldk]+a), ya=getData(tx[oldk]+b);
                    assert(xa.ND==ya.ND);
                    treap *tmpa, *tmpb;

                    assert(abs(xa.ST-ya.ST)==1);
                    if (xa.ST<ya.ST) split(xa.ND,tmpa,tmpb,xa.ST);
                    else split(xa.ND,tmpa,tmpb,ya.ST);
                    
                    _merge(x,y);
                    puts("Sold.");
                }
            }
        }
        puts("");
    }
    return 0;
}





