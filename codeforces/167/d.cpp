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

const int mod=1e9+7;
const int maxn=152;

int n,m;
int dp[4][maxn][maxn];
int dp2[4][maxn][maxn];
int sum[4][maxn][maxn];

int gets(int f, int a, int b, int c, int d){ if (a>b || c>d) return 0; return (1ll*sum[f][b+1][d+1]-sum[f][b+1][c]-sum[f][a][d+1]+sum[f][a][c])%mod; }

int main(){
    int res=0;
    cin>>n>>m;
    REP(i,m) REP(j,i+1) dp[3][j][i]=1;

    REP(u,n){

        memset(dp2,0,sizeof(dp2));
        int ans=0;
        REP(f,4){
            REP(i,m) REP(j,m) sum[f][i+1][j+1]=(1ll*mod+dp[f][i][j]+sum[f][i+1][j]+sum[f][i][j+1]-sum[f][i][j])%mod;
            ans=(ans+sum[f][m][m])%mod;
        }
        res=(res+1ll*ans*(n-u))%mod;


        REP(xb,m) REP(xa,xb+1){
            dp2[0][xa][xb]=
                (1ll*gets(0,0,xa,xb,m-1)+
                +gets(1,0,xa-1,xb,m-1)
                +gets(2,0,xa,xb+1,m-1)
                +gets(3,0,xa-1,xb+1,m-1)
                )%mod;

            dp2[1][xa][xb]=(gets(1,xa,xb,xb,m-1)+gets(3,xa,xb,xb+1,m-1))%mod;
            dp2[2][xa][xb]=(gets(2,0,xa,xa,xb)+gets(3,0,xa-1,xa,xb))%mod;
            dp2[3][xa][xb]=gets(3,xa,xb,xa,xb);
        }
        memcpy(dp,dp2,sizeof(dp));
    }
    cout<<res<<endl;
    return 0;
}

