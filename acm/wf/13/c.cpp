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

const int maxn=25555;
const int maxm=1e5+10;;

int n,m,c;
vector<pii> e[maxn];
int dist[maxn];
int when;
int vis[maxn];


int to[maxm], from[maxm], last[maxn], prev[maxm], cc[maxm], f[maxm];
int ne;
void add(int a, int b, int cx){
    cc[ne]=cx; f[ne]=0; from[ne]=a; to[ne]=b; cc[ne]=cx; prev[ne]=last[a]; last[a]=ne++;
    swap(a,b); cx=0;
    cc[ne]=cx; f[ne]=0; from[ne]=a; to[ne]=b; cc[ne]=cx; prev[ne]=last[a]; last[a]=ne++;
}

int dfs(int a){
    if (!a) return 1;
    if (vis[a]==when) return 0;
    vis[a]=when;
    for (int i=last[a]; i!=-1; i=prev[i]) if (f[i]<cc[i] && dfs(to[i])){
        ++f[i]; --f[i^1];
        return 1;
    }

    return 0;
}


int main(){
    while(scanf(" %d%d%d",&n,&m,&c)==3){
        REP(i,maxn) e[i].clear();


        REP(i,m){
            int a,b,x; scanf(" %d%d%d",&a,&b,&x);
            --a; --b;
            e[a].pb(MP(b,x));
            e[b].pb(MP(a,x));
        }

        vi tb(c);
        REP(i,c) scanf(" %d",&tb[i]), --tb[i];

        priority_queue<pii> q;
        q.push(MP(0,0));
        memset(dist,0x7f,sizeof(dist));
        dist[0]=0;

        while(q.size()){
            int d=-q.top().ST, a=q.top().ND; q.pop();
            if (dist[a]!=d) continue;
            REP(i,e[a].size()){
                int b=e[a][i].ST;
                int nd=d+e[a][i].ND;
                if (dist[b]>nd) q.push(MP(-(dist[b]=nd),b));
            }
        }

        ne=0;
        memset(last,-1,sizeof(last));
        REP(i,n) REP(j,e[i].size()) if (dist[i]+e[i][j].ND==dist[e[i][j].ST]) add(e[i][j].ST,i,1);

        vector<pii> ask;
        REP(i,c) ask.pb(MP(dist[tb[i]],tb[i]));
        sort(ALL(ask));

        when=0;

        int res=0;
        REP(i,c){
            int j;
            memset(f,0,sizeof(f));
            for (j=i; j<c && ask[i].ST==ask[j].ST; ++j) ++when, res+=dfs(ask[j].ND);
            i=j-1;
        }

        printf("%d\n",res);
    }

    return 0;
}

