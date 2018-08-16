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


const int mod=1000000007;
const int maxn=1111;
ll dp[maxn];
int cnk[maxn][maxn];



int main(){
    int tn; cin>>tn; 

    REP(i, maxn) cnk[i][0]=cnk[i][i]=1;
    REP(i, maxn) REP(j, maxn) if (i&&j) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

    REP(ti, tn){
        int n, m, k;
        cin>>n>>m>>k;


        checkmin(k, n);
        memset(dp, 0, sizeof(dp));
        dp[1]=m;
        --n;

        int x=min(n, k);
        FOR(i, 1, x){
            FORV(j, i, 1){
                ll v=dp[j]%mod;
                dp[j+1]+=v*(m-j);
                dp[j]=v*j;
            }
        }

        REP(i, n-x){
            FORV(j, k, 1){
                ll v=dp[j]%mod;
                if (j<k) dp[j+1]+=v*(m-j);
                dp[j]=v*j;
            }
        }


        ll ans=0;
        REP(i, k+1) ans=(ans+dp[i])%mod;
        cout<<ans<<endl;
    }
    return 0;
}


