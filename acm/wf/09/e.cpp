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

const int maxn=55555;

struct edge{
    int c, id, b;
    edge(int c, int id, int b):c(c),id(id),b(b){}
};

vector<edge> e[maxn], eg[maxn];
int dist[maxn];
int dist2[maxn];
int type[maxn];
int vis[maxn];
int can[maxn];
int n;

void dfs1(int a){
    if (vis[a]) return;
    vis[a]=1;
    if (a==n-1) {can[a]=1, dist[a]=0; return;}
    FE(it,e[a]){
        dfs1(it->b);
        if (!can[it->b]) continue;
        can[a]=1;
        if (type[it->b]&1) type[a]|=1;
        if (dist[a]!=-1 && dist[a]!=it->c+dist[it->b]) type[a]|=1;
        dist[a]=it->c+dist[it->b];
    }
}
void dfs2(int a){
    if (vis[a]) return;
    vis[a]=1;
    if (a==0){ can[a]=1, dist[a]=0; return;}
    FE(it,eg[a]){
        dfs2(it->b);
        if (!can[it->b]) continue;
        can[a]=1;
        if (type[it->b]&2) type[a]|=2;
        if (dist[a]!=-1 && dist[a]!=it->c+dist[it->b]) type[a]|=2;
        dist[a]=it->c+dist[it->b];
    }
}

void checkit(int mx, vector<pii> &res){
    map<int,int> rmp;
    REP(i,res.size()) rmp[res[i].ST]=mx-res[i].ND;
    REP(i,n) FE(it,e[i]) it->c+=rmp[it->id];
    REP(i,n) FE(it,eg[i]) it->c+=rmp[it->id];

    memset(type,0,sizeof(type));
    memset(vis,0,sizeof(vis)); memset(can,0,sizeof(can));
    memset(dist,-1,sizeof(dist));
    dfs1(0);
    REP(i,n) assert(type[i]==0);
    memcpy(dist2,dist,sizeof(dist));

    memset(vis,0,sizeof(vis)); memset(can,0,sizeof(can));
    memset(dist,-1,sizeof(dist));
    dfs2(n-1);
    REP(i,n) assert(type[i]==0);
}

int main(){
    int m;
    int tn=0;
    while(cin>>n>>m,n){
        REP(i,n) e[i].clear(), eg[i].clear();
        REP(i,m){int a, b, c; scanf(" %d%d%d", &a,&b,&c); --a; --b; e[a].pb(edge(c,i,b)); eg[b].pb(edge(c,i,a));}
        memset(type,0,sizeof(type));
        memset(vis,0,sizeof(vis)); memset(can,0,sizeof(can));
        memset(dist,-1,sizeof(dist));
        dfs1(0);
        memcpy(dist2,dist,sizeof(dist));

        memset(vis,0,sizeof(vis)); memset(can,0,sizeof(can));
        memset(dist,-1,sizeof(dist));
        dfs2(n-1);

        printf("Case %d: ", ++tn);


        int fd=0;
        REP(i,n) if (type[i]==3){fd=1; break;}
        if (fd){printf("No solution\n"); continue;}

        vector<pii> res;
        int mx=0;
        int cnt=0;
        REP(a,n) if (type[a]==1){
            FE(it,e[a]) if (can[it->b] && !(type[it->b]&1)){
                int nc=dist[a]+dist2[it->b]+it->c;
                if (mx<nc) mx=nc, cnt=0;
                if (mx==nc) ++cnt;
                res.pb(MP(it->id,nc));
            }
        }
        if (type[n-1]==0) mx=dist[n-1];
        sort(ALL(res));
        //checkit(mx,res);
        printf("%d %d\n", res.size()-cnt, mx);
        REP(i,res.size()) if (res[i].ND!=mx) printf("%d %d\n", res[i].ST+1, mx-res[i].ND);
    }
    return 0;
}



