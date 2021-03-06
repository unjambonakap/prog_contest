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

const int maxn=5555;
int n;
vi e[maxn];
int res[maxn];
int dp[maxn];

int dfs(int a, int p=-1){
    vi tb;
    int u=0;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        int x=dfs(b,a);
        u+=x;
        tb.pb(x);
    }

    if (u!=n-1) tb.pb(n-1-u);
    if (tb.size()>=2){
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        REP(i,tb.size()) for (int j=n-1; j>=0; --j) if (dp[j]) dp[j+tb[i]]=1;
        FOR(i,1,n-1) if (dp[i]) res[i]=1, res[n-1-i]=1;
    }
    return u+1;
}

int main(){
    cin>>n;
    REP(i,n-1){ int a, b; scanf(" %d%d",&a,&b); --a; --b; e[a].pb(b); e[b].pb(a);}
    dfs(0);
    int cnt=0;
    FOR(i,1,n-1) if (res[i]) ++cnt;
    printf("%d\n",cnt);
    FOR(i,1,n-1) if (res[i]) printf("%d %d\n",i,n-1-i);
    return 0;
}


