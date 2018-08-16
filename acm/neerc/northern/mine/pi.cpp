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

const int maxn=18;
const int inf=1e5;

int n, m;
int dp[maxn][two(maxn)];
int g[maxn][maxn];
int og[maxn][maxn];

void dfs(int a, int b, vi &tb){
    if (og[a][b]==g[a][b]) return;
    REP(i, n) if (i!=a && g[a][i]==og[a][i] && g[a][i]+g[i][b]==g[a][b]){ assert(i!=b);tb.pb(i), dfs(i, b, tb); break;}
}


int proc(int a, int m){
    if (!m) return g[a][0];
    int &r=dp[a][m];
    if (r!=-1) return r;
    r=inf;
    REP(i, n) if (i&&(m&two(i))) checkmin(r, proc(i, m^two(i))+g[a][i]);
    return r;
}


void build(vi &x, int a, int m){
    if (!m){ assert(a);x.pb(a); dfs(a, 0, x); x.pb(0); return; }
    int r=proc(a, m);
    REP(i, n) if (i && (m&two(i)) && proc(i, m^two(i))+g[a][i]==r){
        x.pb(a);
        dfs(a, i, x);
        build(x, i, m^two(i));
        return;
    }
    assert(0);
}
int main(){
    cin>>n>>m;
    memset(g, 1, sizeof(g));
    REP(i, n) g[i][i]=0;
    REP(i, m){
        int a, b, c; cin>>a>>b>>c;
        --a; --b;
        g[a][b]=g[b][a]=c;
    }
    memcpy(og, g, sizeof(g));
    REP(k, n) REP(i, n) REP(j, n) checkmin(g[i][j], g[i][k]+g[k][j]);


    if (n==1){ printf("0\n0 1\n0 1\n");return 0;}
    memset(dp, -1, sizeof(dp));

    pii xa, xb;
    int best=inf;
    REP(i, n) REP(j, n) REP(k, two(n)) if (i && j && (k&two(i))){
        int a=k, b=(two(n)-1^k);
        if (a&two(i)) a^=two(i);
        if (a&1) a^=1;
        if (b&1) b^=1;
        if (b&two(j)) b^=two(j);

        int z=max(proc(i, a), proc(j, b));

        assert(z);
        if (z<best){
            best=z, xa=MP(i, a), xb=MP(j, b);
        }
    }

    vi a, b;
    build(a, xa.ST, xa.ND);
    build(b, xb.ST, xb.ND);
    reverse(ALL(a));
    reverse(ALL(b));

    REP(i, a.size()) ++a[i];
    REP(i, b.size()) ++b[i];
    printf("%d\n", best);
    printf("%d ", a.size()-1); out(a);
    printf("%d ", b.size()-1); out(b);



    return 0;
}



