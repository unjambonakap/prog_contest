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


const int maxn=22222;
const int maxm=22222;
const int S=0, T=1;

int to[maxm], from[maxm], a[maxm], b[maxm], prev[maxm], last[maxn];
int tmp[maxn], tmp2[maxn];
int uu[maxn];

int ne;
int n,m,p;
vi tb;
void adde(int u, int v, int aa, int bb){
    to[ne]=v; from[ne]=u; a[ne]=aa; b[ne]=bb; prev[ne]=last[u]; last[u]=ne++;
}

void go(int *cost, int s, int *res, int c0=0, int block=-1){
    priority_queue<pii> q;
    memset(res,0x7f,sizeof(int)*n);
    q.push(MP(-(res[s]=c0),s));
    while(q.size()){
        int a=q.top().ND, d=-q.top().ST;
        q.pop();
        if (res[a]!=d) continue;
        if (d>uu[a]) continue;

        for (int i=last[a]; i!=-1; i=prev[i]){
            if (i==block) continue;
            int b=to[i];
            int nd=cost[i]+d;
            if (res[b]>nd) res[b]=nd, q.push(MP(-nd,b));
        }
    }
}


int solve(vi tb){
    int cost=0;
    memset(uu,0x7f,sizeof(uu));
    int best=INT_MAX;
    REP(pp,p){
        int x=tb[pp];
        go(b,from[x],tmp,cost,x);
        go(a,to[x],tmp2,cost+a[x]);
        REP(i,n) uu[i]=min(uu[i],tmp[i]);
        if (tmp2[T]>uu[T]) return x;
        cost+=a[x];

    }

    return -1;

}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        tb.clear();
        cin>>n>>m>>p;

        memset(last,-1,sizeof(last));
        ne=0;
        REP(i,m){
            int u,v,aa,bb;
            scanf(" %d%d%d%d",&u,&v,&aa,&bb);
            --u; --v;
            adde(u,v,aa,bb);
        }

        vi tb;
        REP(i,p){
            int x; scanf(" %d",&x); --x;
            tb.pb(x);
        }


        int res=solve(tb);
        printf("Case #%d: ",ti+1);
        if (res==-1) puts("Looks Good To Me");
        else printf("%d\n",res+1);
    }
    return 0;
}



