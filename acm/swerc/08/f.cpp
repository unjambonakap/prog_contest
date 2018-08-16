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
int n,m,mod;
int aa[maxn], bb[maxn];
int F[maxn];

int cnk[maxn][maxn];
int dp[maxn];
int pw[maxn][maxn];

int go(int a){
    int &r=dp[a];
    if (r!=-1) return r;
    int have=F[a], rem=a-have;

    if (rem<0) return r=0;

    r=pw[a][rem];
    int bad=0;
    REP(j,a) if (F[j+1]-F[j]==0){
        int x=rem-(j-F[j]);
        if (x<0) continue;
        bad=(bad+1ll*go(j)*pw[a-1-j][x]%mod*cnk[rem][x])%mod;
    }
    r=(r+mod-bad)%mod;
    return r;
}

int main(){
    int tn; cin>>tn;

    REP(ti,tn){

        cin>>n>>m>>mod;
        REP(i,n+1) cnk[i][0]=cnk[i][i]=1;
        FOR(i,1,n+1) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

        REP(i,n+1){ pw[i][0]=1; REP(j,n) pw[i][j+1]=1ll*pw[i][j]*i%mod; }


        memset(F,0,sizeof(F));
        REP(i,m) scanf(" %d%d",aa+i,bb+i), --aa[i], --bb[i], ++F[bb[i]+1];
        REP(i,n) F[i+1]+=F[i];


        int fd=0;
        REP(i,n) if (m-F[i]>n-i){fd=1; break;}
        memset(dp,-1,sizeof(dp));

        if (fd) puts("NO");
        else printf("YES %d\n",go(n));
    }
    return 0;
}

