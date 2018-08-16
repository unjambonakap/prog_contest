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
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=110;

int px[2*maxn];
int n;
int res[2*maxn];
ll mem[maxn][maxn];
ll cnk[maxn][maxn];
ll dp[maxn][maxn][maxn];//ya, xb, yb=> dyck path from (0,ya) to (xb, yb)


int main(){
    int a, b;
    ll K;
    cin>>a>>b>>K;
    n=a+b-1;
    memset(px, 0x7f, sizeof(px));
    REP(i, a) REP(j, b){
        int x; cin>>x;
        checkmin(px[i+j], x);
    }

    REP(i, n+1) cnk[i][0]=cnk[i][i]=1;
    REP(i, n+1) REP(j, i) if (i&&j) cnk[i][j]=cnk[i-1][j]+cnk[i-1][j-1];


    vector<pii> perm;
    FOR(i, 1, n-1) perm.pb(MP(px[i], i));
    sort(ALL(perm));

    memset(dp, 0, sizeof(dp));
    dp[0][0][0]=1;
    REP(xb, n+1) FORV(ya, n, 1) FOR(yb, xb, n){
        if (ya<yb) dp[ya][xb][yb]+=dp[ya+1][xb][yb];
        if (xb && ya) dp[ya][xb][yb]+=dp[ya-1][xb-1][yb-1];
    }

    set<int> seen;
    seen.insert(0); seen.insert(n-1);
    memset(res, -1, sizeof(res));
    res[0]=0; res[n-1]=1;

    memset(mem, 0, sizeof(mem));
    mem[0][0]=0; mem[n-1][n-1]=1;

    REP(i, n){
        ll A=0;
        int a=perm[i].ND;
        set<int>::iterator itx=seen.insert(a).ST;
        int u, v; u=*(--itx); ++itx; v=*(++itx);
        ll tmp=0;
        REP(j, u+1) FOR(k, v, n) if (mem[u][j] && mem[v][k]){
            tmp+=mem[


        }

    }


    REP(i, a){
        REP(j, b) cout<<res[i+j]?')':'(';
        cout<<endl;
    }
    return 0;
}


