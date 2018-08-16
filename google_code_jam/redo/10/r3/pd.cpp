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

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxb=70;
const int maxn=32;
const int mod=1e9+7;
ll dp[maxb][maxb+1][maxb];//digit, num of equations, carry
map<int, ll> cnt[maxb+1][maxb][maxb+1][2];//base, digit, n operands, zero, carry => number
ll cnk[maxb+1][maxb+1];
ll fact[maxb+1], ifact[maxb+1];

ll inv(ll a){
    int p=mod-2;
    ll i=1;
    while(p){
        if (p&1) i=i*a%mod;
        p>>=1;
        a=a*a%mod;
    }
    return i;
}

int b, n;
int num[maxn];

ll proc(int d, int na, int c){
    if (d==n) return c==0;
    ll &r=dp[d][na][c];
    if (r!=-1) return r;

    r=0;
    int v=(b+num[d]-c)%b;
    int nc=c>num[d];
    FOR(i, 0, (d==n-1?0:na)){
        REP(f, 2) if (!f || d<n-1){
            ll tmp=0;
            FE(it, cnt[b][v][na][f]){
     //           printf("<< %d neq %d nc %d f %d %Ld ans: %Ld\n", d+1, i, nc+it->ST, f, it->ND, proc(d+1, i, nc+it->ST));
     //           printf("%d %d %d %d %d => %Ld\n", b, v, na, f, it->ST, it->ND);
     //           printf("\n\n");
                tmp=(tmp+proc(d+1, i, nc+it->ST)*it->ND)%mod;

            }
            r=(r+tmp*fact[i]%mod*cnk[na-f][i-f])%mod;
        }
    }
    //printf("%d %d %d => %Ld\n", d, na, c, r);

    return r;
}

int main(){
    int tn;
    cin>>tn;

    fact[0]=ifact[0]=1;
    FOR(i, 1, maxb) fact[i]=i*fact[i-1]%mod, ifact[i]=inv(fact[i]);

    memset(cnk, 0, sizeof(cnk));
    REP(i, maxb+1) cnk[i][0]=1;
    FOR(i, 1, maxb) FOR(j, 1, i) cnk[i][j]=(cnk[i-1][j-1]+cnk[i-1][j])%mod;
    FOR(i, 2, maxb){
        cnt[i][0][0][0][0]=cnt[i][0][1][1][0]=1;
        REP(f, 2) FOR(j, 1, i-1) REPV(k, i) REP(u, i) FE(it, cnt[i][u][k][f]){

            cnt[i][(j+u)%i][k+1][f][it->ST+(j+u>=i)]+=it->ND;
            cnt[i][(j+u)%i][k+1][f][it->ST+(j+u>=i)]%=mod;
            //printf("%d %d %d %d x %d=> %Ld\n", i, (j+u)%i, k+1, f, it->ST+(j+u>=i), cnt[i][(j+u)%i][k+1][f][it->ST+(j+u>=i)]);
        }
    }
    
    FOR(ti, 1, tn){
        ll l;
        cin>>l>>b;
        n=0;
        //if (ti!=1)continue;
        while(l) num[n++]=l%b, l/=b;
        memset(dp, -1, sizeof(dp));
        ll ans=0;
        FOR(i, 1, b){
     //       printf("\n\n try with %d eq\n", i);
            ans=(ans+proc(0, i, 0))%mod;
      //      printf("now %Ld\n", ans);
        }
        printf("Case #%d: %Ld\n", ti, ans);
    }
    return 0;
}




