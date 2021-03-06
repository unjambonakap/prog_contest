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

const int mod=1e9+7;
const int maxk=22;
const int maxm=1e6+10;

int k;
int next[maxm];
int cnt[maxm];
int ifact[maxk];
int tx[maxm];

int dp[maxk];
int nx;
int res[maxk];
int tmp[maxk], tmp2[maxk];
int dp2[maxk][maxk];

int faste(int a, int p){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}

int cnk(int n, int k){
    int res=1;
    REP(i,k) res=1ll*res*(n-i)%mod;
    return 1ll*res*ifact[k]%mod;
}

void go(int st=0){
    if (st==0){
        memset(dp,0,sizeof(dp));
        dp[0]=1;
    }
    for (int i=st; i<nx; ++i) for (int j=k-1; j>=0; --j) dp[j+1]=(dp[j+1]+1ll*tx[i]*dp[j])%mod;
    memcpy(res,dp,sizeof(res));
}

int go2(int a, int b){
    if (!b) return !a;
    int &r=dp2[a][b];
    if (r!=-1) return r;
    int u=0;
    FOR(i,1,a+1) u=(u+1ll*go2(a-i,b-1)*res[i])%mod;
    return r=u;
}

int main(){
    int tn; cin>>tn;
    ifact[0]=1;
    FOR(i,1,maxk) ifact[i]=1ll*ifact[i-1]*faste(i,mod-2)%mod;

    REP(ti,tn){
        int n,a,b,c,m;
        cin>>n>>k>>a>>b>>c>>m;
        memset(cnt,0,sizeof(cnt));
        cnt[a]=1;
        nx=0;
        tx[nx++]=a;
        int x=0, oa=a;
        while(--n){
            ++x;
            next[a]=(1ll*a*b+c)%m;
            a=next[a];
            if (cnt[a]) break;
            tx[nx++]=a;
            ++cnt[a];
        }
        if (n && a==oa){
            nx=0;
            go();
            n+=x;
        }else go();

        int ans=0;

        if (n){
            int oa=a;
            int nc=0;
            tx[nc++]=a;
            while(next[a]!=oa) tx[nc++]=a=next[a];

            nx=n%nc;
            memcpy(tmp,res,sizeof(res));
            go();
            memset(tmp2,0,sizeof(tmp2));
            REP(i,k+1) REP(j,k-i+1) tmp2[i+j]=(tmp2[i+j]+1ll*res[i]*tmp[j])%mod;

            int u=n/nc;
            nx=nc;
            go(n%nc);

            ans=0;
            memset(dp2,-1,sizeof(dp2));
            REP(i,k+1) REP(j,min(u,k)+1) ans=(ans+1ll*tmp2[k-i]*cnk(u,j)%mod*go2(i,j))%mod;
        }else ans=res[k];

        cout<<ans<<endl;
    }
    return 0;
}

