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

const int maxn=222;
const int mod=1e9+9;

int fact[maxn], ifact[maxn];
int inv(int a, int p=mod-2){
    int x=1;
    for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod;
    return x;
}
struct matrix{
    matrix(const matrix &a){
        n=a.n;
        memcpy(m,a.m,sizeof(m));
    }
    matrix(int n):n(n){memset(m,0,sizeof(m));}
    void ident(){
        memset(m,0,sizeof(m));
        REP(i,n) m[i][i]=1;
    }

    matrix operator*(const matrix &a)const{
        matrix res(n);
        REP(i,n) REP(j,n) REP(k,n) res.m[i][j]=(res.m[i][j]+1ll*m[i][k]*a.m[k][j])%mod;
        return res;
    }

    int m[maxn][maxn];
    int n;
};

matrix faste(matrix a, int p){
    matrix x(a.n); x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=a*x;
    return x;
}


int dp[2][maxn];

int main(){
    int tn; cin>>tn;
    fact[0]=ifact[0]=1;
    FOR(i,1,maxn) fact[i]=1ll*i*fact[i-1]%mod, ifact[i]=inv(fact[i]);


    REP(ti,tn){
        int n,m,k; cin>>n>>m>>k;
        int res=0;
        if (m<=k) res=1;
        else if (n<k) res=0;
        else{
            int p=0, np=1;
            memset(dp,0,sizeof(dp));
            dp[p][0]=1;
            REP(step,k+1){
                memset(dp[np],0,sizeof(dp[np]));
                REP(j,n+1){
                    int a=j<n;
                    int b=j-min(step,k);
                    dp[np][j]=(dp[np][j]+1ll*b*dp[p][j])%mod;
                    dp[np][j+1]=(dp[np][j+1]+1ll*a*dp[p][j])%mod;
                }
                p=np; np^=1;
            }
            matrix x(n-k);
            FOR(i,k+1,n+1) x.m[i-k-1][i-k-1]=i-k, x.m[i-k-1][i-k]=1;
            REP(i,n-k) out(x.m[i],n-k);
            puts("");
            x=faste(x,m-k-1);


            FOR(i,k+1,n+1) if (dp[p][i]){
                ll u=0;
                REP(j,n-k) u+=x.m[i-k-1][j];
                u=1ll*u%mod*dp[p][i];
                res+=u%mod;
            }
            res%=mod;
        }
        cout<<res<<endl;

        break;
    }
    return 0;
}


