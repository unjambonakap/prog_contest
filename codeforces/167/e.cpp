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

ll cnt[3];
int m[3][3];
int dp[4][maxn][4];
int cnk[maxn][maxn];
int cnk2[maxn];

int inv[maxn];
int faste(int a, int p=mod-2){ int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x; }
int pw[maxn];
int dp2[maxn];

int state[maxn];

int main(){
    REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

    int n; cin>>n;
    int p; cin>>p;



    FOR(i,1,maxn) inv[i]=faste(i);
    
    REP(i,3) REP(j,3) if (i&&j) m[i][j]=0; else m[i][j]=i==1||j==1?2:1;

    vector<pair<pair<ll,ll>,int> > tb;
    tb.pb(MP(MP(1,2),0));
    int la=0,lb=0;
    ll l=3;

    --p;
    while(l<=p){
        while (tb[la].ST.ND<l/3) ++la;
        while (tb[lb].ST.ND<l-l/3) ++lb;
        ll nl=3ll*tb[la].ST.ND+2;
        int d=tb[lb].ST.ND/2, x=tb[lb].ST.ND&1;
        nl=min(nl,3ll*d+x);

        int c=m[tb[la].ND][tb[lb].ND];
        if (c==tb.back().ND) tb.back().ST.ND=nl;
        else tb.pb(MP(MP(l,nl),c));

        l=nl+1;
    }

    REP(i,tb.size()){
        int a=tb[i].ST.ST;
        int b=min(1ll*p,tb[i].ST.ND);
        int c=tb[i].ND;
        int nx=b-a+1;
        cnt[c]+=1ll*nx*(p-b+1)+1ll*nx*(nx-1)/2;
    }
    
    dp[0][0][0]=1;
    REP(i,3){

        cnt[i]%=mod;
        dp2[0]=1;
        FOR(j,1,n+1) dp2[j]=1ll*dp2[j-1]*cnt[i]%mod;


        REP(f,4) REP(j,n+1){
            if (dp[i][j][f]) REP(k,n-j+1){
                int nf=f;
                if (k&1) nf^=i;
                dp[i+1][j+k][nf]=(dp[i+1][j+k][nf]+1ll*dp[i][j][f]*dp2[k]%mod*cnk[j+k][k])%mod;
            }
        }
        
    }
    int res=0;
    FOR(i,1,4) res=(res+dp[3][n][i])%mod;
    cout<<res<<endl;
    return 0;
}

