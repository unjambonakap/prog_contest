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
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=5010;
int prev[maxn];
int c[maxn];
int prio[maxn];
int perm[maxn];
int res[maxn];

int n;
vector<pii> e[maxn];

int next[maxn][maxn];
int root(int a, int b){return next[a][b]==-1?b:next[a][b]=root(a, next[a][b]);}
int cnt[maxn][maxn];


struct cmpA{ bool operator()(int a, int b){return prio[a]<prio[b];} };

void dfs(int a, int p){
    prev[a]=p;
    FE(it, e[a]) if (it->ST!=p) dfs(it->ST, a), prev[it->ST]=a, c[it->ST]=it->ND;
}

int solve(int a){
    int t=0;
    while(a!=0){
        t=root(a, t);
        if (++cnt[a][t]==c[a]) next[a][t]=root(a, t+1);
        ++t;
        a=prev[a];
    }

    return t;
}

int main(){

    cin>>n;
    REP(i, n) cin>>prio[i];
    REP(i, n) perm[i]=i;
    sort(perm, perm+n, cmpA());


    memset(cnt, 0, sizeof(cnt));
    memset(next, -1, sizeof(next));
    REP(i, n-1){
        int a, b, c;
        cin>>a>>b>>c;
        --a; --b;
        e[a].pb(MP(b, c));
        e[b].pb(MP(a, c));
    }

    dfs(0, -1);
    REP(i, n) res[perm[i]]=solve(perm[i]);

    out(res, n);

    return 0;
}


