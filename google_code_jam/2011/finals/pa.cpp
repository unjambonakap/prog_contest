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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxc=5e5;
const int maxm=26;
const int maxr=101;
const int mod=1000003;

ll fact[maxc], ifact[maxc];
int cnt[maxm];
int dp[maxm][maxr];
int seen[maxm];


int bezout(int a, int b, int ua, int va, int ub, int vb){
    if (b==0) return va;
    return bezout(b, a%b, ub, vb, ua-ub*(a/b), va-vb*(a/b));
}

int inv(int a){ int ans=bezout(mod, a, 1, 0, 0, 1); return (ans%mod+mod)%mod; }
ll cnk(int n, int k){return k>n?0:fact[n]*ifact[k]%mod*ifact[n-k]%mod;}

int main(){

    int ti, tn;
    cin>>tn;
    fact[0]=ifact[0]=1;
    FOR(i, 1, maxc-1) ifact[i]=inv(fact[i]=fact[i-1]*i%mod);
    REP(i, maxc) assert(ifact[i]*fact[i]%mod==1);
    
    FOR(ti, 1, tn){
        string s; 
        cin>>s;



        memset(cnt, 0, sizeof(cnt));
        int nr=0;
        memset(seen, -1, sizeof(seen));
        int m=0;
        REP(i, s.length()){
            if (!i || s[i]!=s[i-1]) ++nr;
            int c=s[i]-'a';
            if (seen[c]==-1) seen[c]=m++;
            ++cnt[seen[c]];
        }
        memset(dp, 0, sizeof(dp));
        dp[0][1]=1;
        int F=cnt[0];
        FOR(i, 1, m-1){
            REP(j, nr+1) if (dp[i-1][j]) REP(x, 3) REP(y, j) for (int z=0; z<=F-j && x+y+2*z+j<=nr; ++z) if (x+y+z){
                int &r=dp[i][x+y+2*z+j];
                int a=dp[i-1][j];
                r+=a*cnk(cnt[i]-1, x+y+z-1)%mod*cnk(2, x)*cnk(j-1, y)%mod*cnk(F-j, z)%mod;
                r%=mod;
            }
            F+=cnt[i];

        }


        printf("Case #%d: %d\n", ti, dp[m-1][nr]);
    }

    return 0;

}


