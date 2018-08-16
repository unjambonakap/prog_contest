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

const int maxn=111;
const int mod=1e9+7;

int cnk[maxn*maxn][maxn];
int dp[maxn][maxn];
int go2(int n, int m);

int go1(int n, int m){
    if (n==1) return 0;
    int &r=dp[n][m];
    if (r!=-1) return r;
    r=0;
    FOR(i,1,n) REP(j,m+1) r=(r+1ll*cnk[i*(i-1)/2][j]*go2(n-i,m-j)%mod*cnk[n-1][i])%mod;
    return r;
}

int go2(int n, int m){return (mod+cnk[n*(n-1)/2][m]-go1(n,m))%mod;}



int main(){
    REP(i,maxn) cnk[i][i]=1;
    REP(i,maxn*maxn) cnk[i][0]=1;

    FOR(i,1,maxn*maxn) FOR(j,1,min(maxn,i)) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

    memset(dp,-1,sizeof(dp));
    int n,m;
    while(scanf(" %d%d", &n,&m),n) printf("%d\n", go2(n,m));
    
    return 0;
}


