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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

int dist(int a, int b){return a*a+b*b;}

const int maxn=510;
int graph[maxn][maxn];
int rn[maxn][maxn];
int x[maxn], y[maxn], r[maxn], c[maxn];
int n;
int s, t;
int visited[maxn], parent[maxn];


int dfs(int a, int b){
    if (a==b) return 1;
    if (visited[a]) return 0;
    visited[a]=1;
    REP(i, n) if (graph[a][i]>rn[a][i] && dfs(i, b)){
        parent[i]=a;
        return 1;
    }
    return 0;

}
int solve(){
    int f=0;
    while(1){
        memset(visited, 0, sizeof(visited));
        memset(parent, -1, sizeof(parent));
        if (!dfs(s, t)) break;
        int p, np;
        p=t;
        int ca=INT_MAX;
        while(p!=s){
            np=parent[p];
            checkmin(ca, graph[np][p]-rn[np][p]);
            p=np;
        }
        p=t;
        while(p!=s){
            np=parent[p];
            rn[np][p]+=ca; rn[p][np]-=ca;
            p=np;
        }
        f+=ca;
    }
    return f;

}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        REP(i, n) cin>>x[i]>>y[i]>>r[i]>>c[i];
        memset(graph, 0, sizeof(graph));
        REP(i, n) REP(j, n) if (dist(x[i]-x[j], y[i]-y[j])<=r[i]*r[i]) graph[i][j]=1e9;
        s=n; t=n+1;
        int ans=0;
        REP(i, n) if (c[i]>0) graph[s][i]=c[i], ans+=c[i]; else if (c[i]<0) graph[i][t]=-c[i];
        n+=2;
        memset(rn, 0, sizeof(rn));
        printf("Case #%d: %d\n", ti, ans-solve());
    }
    return 0;

}


