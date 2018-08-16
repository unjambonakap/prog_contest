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
const int maxm=222222;
const int ths=8;

const int maxv=1<<21, leaf=maxv>>1;

int last[maxn], to[maxm], prev[maxm], ne;
int rlast[maxn], rto[maxm], rprev[maxm], nre;
int vis[maxn];
int step;
int n, m;

int tree[maxv];
int ord[maxn];
int inv[leaf];

int cmp(int a, int b){return ord[a]<ord[b];}


void init(){memset(tree,0,sizeof(tree));}
void rem(int a){ assert(inv[a-leaf]!=-1);inv[a-leaf]=-1; for(; a; a>>=1) --tree[a]; }
void add(int a, int c){assert(inv[a]==-1);inv[a]=c; ord[c]=a; for (a+=leaf; a; a>>=1) ++tree[a];}
void insert(int c, int x){
    int a=ord[x];
    if (a==leaf || inv[a+1]!=-1){
        a+=leaf;
        int oa=a;
        for (int pw=1; a; a>>=1, oa^=(oa&pw), pw<<=1) if ((pw-tree[a]-1)*ths>pw){
            //remaping ob >> ob+pw
            vi lst;
            REP(i,pw) if (inv[oa+i-leaf]!=-1){
                lst.pb(inv[oa+i-leaf]); rem(oa+i); 
                if (oa+i==ord[x]+leaf) lst.pb(c);
            }
            int b=pw/lst.size();
            assert(b);
            REP(i,lst.size()){
                add(oa+i*b-leaf,lst[i]);
            }
            return;
        }
        assert(0);
    }else add(a+1,c);
}





int adde(int a, int b){prev[ne]=last[a]; last[a]=ne; to[ne]=b; ++ne;}
int addre(int a, int b){rprev[nre]=rlast[b]; rlast[b]=nre; rto[nre]=a; ++nre;}

void dfs(int a, vi &lst){
    if (vis[a]==step) return;
    vis[a]=step;
    for (int i=last[a]; i!=-1; i=prev[i]) dfs(to[i], lst);
    lst.pb(a);
}

void go(int a, int b, vi &lst){
    assert(a!=b);
    if (ord[a]>ord[b]) return;
    if (vis[a]==step) return;
    vis[a]=step;
    for (int i=last[a]; i!=-1; i=prev[i]) go(to[i],b,lst);
    lst.pb(a);
}


void bench(){
    n=1e5;
    memset(tree,0,sizeof(tree));
    memset(inv,-1,sizeof(inv));
    REP(i,n) add(i,i);
    REP(step,1e6){
        int i=rand()%n, j=rand()%n;
        if (j==i) j=(j+1)%n;
        assert(ord[i]!=-1);
        cerr<<step<<endl;
        rem(ord[i]+leaf);
        insert(i,j);

    }
    exit(0);

}

int main(){
    int tn; cin>>tn;
    //bench();
    REP(ti,tn){
        ne=nre=0;
        memset(last,-1,sizeof(last));
        memset(rlast,-1,sizeof(rlast));
        cin>>n>>m;
        REP(i,m){int a, b; scanf("%d%d", &a,&b); --a; --b; adde(a,b); addre(a,b);}
        step=1; memset(vis,0,sizeof(vis));

        vi lst;
        REP(i,n) dfs(i, lst);
        reverse(ALL(lst));
        int sp=leaf/n;
        memset(tree,0,sizeof(tree));
        memset(inv,-1,sizeof(inv));
        REP(i,lst.size()) add(i*sp, lst[i]);
        cerr<<ti<<endl;


        int a, b, c;
        int sw=0;
        int cnt=0;
        while(scanf("%d%d%d", &a,&b,&c), a|b|c){
            cerr<<cnt++<<endl;
            --b; --c;
            if (a){
                if (sw) swap(b,c);
                if (ord[b]>=ord[c]){
                    ++step;
                    vi lst;
                    go(c,b,lst);
                    sort(ALL(lst),cmp);
                    REPV(i,lst.size()){
                        rem(ord[lst[i]]+leaf);
                        insert(lst[i], b);

                    }
                }
                adde(b,c); addre(b,c);
            }else{
                if (ord[b]<ord[c]) puts("YES");
                else puts("NO"), sw^=1;
            }
        }
    }
    return 0;
}



