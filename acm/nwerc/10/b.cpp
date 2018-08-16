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


const int oo=1e9;
const int maxn=1111;

int dp[maxn][maxn];
int dp2[maxn][maxn];
int a[maxn], b[maxn];
int Fa[maxn], Fb[maxn];
int mx[maxn];

int n;
char buf[maxn];
int main(){
    int tn; cin>>tn;

    REP(ti,tn){
        cin>>n;
        scanf(" %s",buf);
        int f=buf[0]=='J';

        vector<pii> tb;
        REP(i,n){
            int a, b; scanf(" %d%d",&a,&b);
            tb.pb(MP(-a,b));
        }

        sort(ALL(tb));
        REP(i,n) a[i]=-tb[i].ST, b[i]=tb[i].ND;
        REP(i,n) Fa[i+1]=a[i]+Fa[i];
        REP(i,n) Fb[i+1]=b[i]+Fb[i];

        mx[0]=0;
        REP(i,n){
            mx[i+1]=mx[i]+f;
            f^=1;
        }

        memset(dp,-1,sizeof(dp));
        dp[0][0]=0; dp2[0][0]=0;
        REP(i,n){
            for (int j=0; j<=mx[i]; ++j) if (dp[i][j]>-1){
                int x=dp[i+1][j], y=dp[i][j];
                if (x<y || (x==y && dp2[i+1][j]>dp2[i][j])) dp[i+1][j]=y, dp2[i+1][j]=dp2[i][j];
                if (j+1<=mx[i+1]){
                    x=dp[i+1][j+1]; y=dp[i][j]+b[i];
                    if (x<y || (x==y && dp2[i+1][j+1]>dp2[i][j]+a[i])) dp[i+1][j+1]=y, dp2[i+1][j+1]=dp2[i][j]+a[i];
                }
            }
        }

        printf("%d %d\n",Fa[n]-dp2[n][mx[n]],dp[n][mx[n]]);
    }

    return 0;
}

