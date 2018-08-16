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


const int maxn=24;

int dp[two(maxn)];
int n;
int x[maxn], y[maxn];
int g[maxn][maxn];
int d[maxn];
int done[maxn];

vi path;
int dist(int x, int y){return x*x+y*y;}


void build(vi &path, int m){
    if (!m) return;
    REP(i, n) if (m&two(i)){
        if (dp[m]==dp[m^two(i)]+d[i]){path.pb(i+1);path.pb(0); build(path, m^two(i)); return;}
        REP(j, i) if (m&two(j)) if (dp[m]==dp[m^two(i)^two(j)]+g[i][j]){path.pb(i+1); path.pb(j+1);path.pb(0); build(path, m^two(i)^two(j));return;}
    }

    assert(0);


}


int solve(){
    memset(dp, 0x7f, sizeof(dp));
    memset(done, 0, sizeof(done));
    dp[0]=0;
    priority_queue<pii> q;
    q.push(MP(0,0));
    while(!q.empty()){
        pii p=q.top();q.pop();
        int i=p.ND;
        if (dp[i]!=-p.ST) continue;
        if (i==two(n)-1) break;

        vi x;
        REP(j, n) if (!(i&two(j))) x.pb(j);
        int ni=i|two(x[0]);
        if (dp[ni]>dp[i]+d[x[0]]) dp[ni]=dp[i]+d[x[0]], q.push(MP(-dp[ni], ni));
        FOR(j, 1, x.size()){
            int ni=i|two(x[0])|two(x[j]);
            if (dp[ni]>dp[i]+g[x[0]][x[j]]) dp[ni]=dp[i]+g[x[0]][x[j]], q.push(MP(-dp[ni], ni));
        }
    }

    path=vi();
    path.pb(0);
    build(path, two(n)-1);

    reverse(ALL(path));
    return dp[two(n)-1];
}

int main(){
    int xa, ya;
    cin>>xa>>ya;
    cin>>n;
    REP(i, n) cin>>x[i]>>y[i], x[i]-=xa, y[i]-=ya;
    
    REP(i, n) d[i]=dist(x[i], y[i]);
    memset(g, 0, sizeof(g));
    REP(i, n) REP(j, i) g[i][j]=g[j][i]=dist(x[i]-x[j], y[i]-y[j])+d[i]+d[j];
    REP(i, n) d[i]*=2;
    

    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve());
    out(path);


    return 0;
}



