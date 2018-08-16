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

const int maxn=2222;
const int mod=1e9+7;

int n,m;
int dp[maxn][maxn];

int main(){

    REP(i,maxn) dp[0][i]=1;

    REP(i,maxn-1){
        int s=0;
        REP(j,maxn-1){
            s=(s+dp[i][j])%mod;
            dp[i+1][j]=((j?dp[i+1][j-1]:0)+s)%mod;
        }
    }

    while(cin>>n>>m,cin.good()){
        int res=0;
        //E A x B E
        REP(i,n+1) out(dp[i],m+1);
        REP(i,m-1){
            int s=1, u=0;
            int tmp=0;
            REPV(j,n){
                u=(u+s)%mod;
                tmp=(tmp+1ll*dp[j][i]*u)%mod;
                s=(1ll*s+mod+dp[n-j][i]-dp[n-1-j][i])%mod;
            }
            res=(res+1ll*(m-1-i)*tmp)%mod;
        }

        cout<<res<<endl;
    }
    return 0;
}

