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

const int maxn=333;

int A[maxn][maxn];
int dp[maxn][maxn];
int dp2[maxn][maxn];
int n;

int main(){
    cin>>n;
    REP(i,n) REP(j,n) scanf(" %d", A[i]+j);
    memset(dp,0x80,sizeof(dp));
    dp[0][0]=A[0][0];
    REP(p,n-1){
        memset(dp2,0x80,sizeof(dp2));
        REP(i,n){
            int s=INT_MIN;
            if (i<n) dp[i+1][i+1]=max(dp[i+1][i+1],dp[i][i]+A[p][i+1]);
            FOR(j,i,n){
                s=max(s,dp[i][j]);
                dp2[i][j]=max(dp2[i][j],s+A[p+1][i]+(i==j?0:A[p+1][j]));
                if (j>i) dp[i+1][j]=max(dp[i+1][j],dp[i][j]+(i+1==j?0:A[p][i+1]));
                s+=A[p][j+1];
            }
        }
        memcpy(dp,dp2,sizeof(dp));
    }
    int best=INT_MIN;
    REP(j,n) REP(i,j+1){
        int res=dp[i][j];
        FOR(k,i+1,n) if (k!=j) res+=A[n-1][k];
        best=max(best,res);
    }
    cout<<best<<endl;
    return 0;
}


