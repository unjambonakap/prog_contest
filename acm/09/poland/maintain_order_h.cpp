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
const ll inf=1e9;
const int maxv=4*maxn;
const double ths=2;


int last[maxn], to[maxm], prev[maxm], ne;
int rlast[maxn], rto[maxm], rprev[maxm], nre;
int vis[maxn];
int step;
int n, m;

ll ord[maxn];
int px[maxv],nx[maxv];

int cmp(int a, int b){return ord[a]<ord[b];}

void rem(int a){int u=px[a], v=nx[a]; px[v]=u; nx[u]=v; ord[a]=-1;}
void add(const vi &lst, int b){
    vi la, lb;
    int u=px[b], v=nx[b];
    assert(v);
    if (ord[v]>ord[b]+lst.size()){
        ll dx=(ord[v]-ord[b]+1)/(lst.size()+2);
        assert(dx>0);
        ll pos=ord[b]+dx;
        int y=b;
        REPV(i,lst.size()) nx[y]=lst[i], px[lst[i]]=y, ord[y=lst[i]]=pos, pos+=dx;
        nx[y]=v; px[v]=y;
        return;
    }

    ll oa=ord[b];
    oa^=oa&1;
    ll pw=2;
    double T=1;
    int cnt=1+lst.size();
    while(1){
        T*=ths;

        while(u && ord[u]>=oa){
            ++cnt, la.pb(u), u=px[u];
        }
        while(v<=n && ord[v]<=oa+pw){
            ++cnt, lb.pb(v), v=nx[v];
        }
        while(1){
            int tmp=oa^(oa&pw);
            if (ord[u]>=oa||ord[v]<oa+pw) break;
            pw<<=1;
        }
        if ((pw-cnt)*T>pw){ 
            ll pos=oa;
            ll dx=pw/cnt;
            int na=la.size();
            int y=u;

            assert(dx);
            REPV(i,na) nx[y]=la[i], px[la[i]]=y, ord[y=la[i]]=pos, pos+=dx;

            ord[b]=pos; pos+=dx;
            nx[y]=b, px[b]=y, y=b;
            REPV(i,lst.size()) nx[y]=lst[i], px[lst[i]]=y, ord[y=lst[i]]=pos, pos+=dx;


            int nb=lb.size();
            REP(i,nb) nx[y]=lb[i], px[lb[i]]=y, ord[y=lb[i]]=pos, pos+=dx;
            nx[y]=v; px[v]=y;
            //            REP(i,n){
            //                printf("xaxa on %d %d\n", a, b);
            //                printf(">> %d >> %d %d %d\n", i, ord[i], nx[ord[i]], px[nx[ord[i]]]);
            //                if (nx[ord[i]]) assert(ord[i]==px[nx[ord[i]]]);
            //
            //            }
            return;
        }
        oa^=oa&pw;
        pw<<=1;
    }
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
    if (ord[a]>=ord[b]) return;
    if (vis[a]==step) return;
    vis[a]=step;
    for (int i=last[a]; i!=-1; i=prev[i]) go(to[i],b,lst);
    lst.pb(a);
}


void bench(){
    n=1e5;
    REP(step,1e6){
        int i=rand()%n, j=rand()%n;
        if (j==i) j=(j+1)%n;
        assert(ord[i]!=-1);
        cerr<<step<<endl;

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
        REP(i,m){int a, b; scanf("%d%d", &a,&b); adde(a,b); addre(a,b);}
        step=1; memset(vis,0,sizeof(vis));

        vi lst;
        REP(i,n) dfs(i+1, lst);
        ll sp=inf/n;

        px[lst[0]]=0; nx[lst.back()]=n+1;
        nx[n+1]=n+1; px[0]=0;
        ord[n+1]=inf; ord[0]=-1;

        REP(i,lst.size()){
            if (i) px[lst[i]]=lst[i-1], nx[lst[i-1]]=lst[i];
            ord[lst[i]]=i*sp;
        }
        cerr<<ti<<endl;


        int a, b, c;
        int sw=0;
        int cnt=0;
        while(scanf("%d%d%d", &a,&b,&c), a|b|c){
            ++cnt;
            if (a){
                if (sw) swap(b,c);
                if (ord[b]>=ord[c]){
                    ++step;
                    vi lst;
                    go(c,b,lst);
                    sort(ALL(lst),cmp);
                    REPV(i,lst.size()) rem(lst[i]);
                    if (ti==4) fprintf(stderr, "%d >> %d\n", cnt, lst.size());
                    add(lst,b);
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



