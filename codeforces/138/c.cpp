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

const int maxn=2222;
const int mod=1e9+7;
int a[maxn];
int b[maxn];
int ifact[maxn];
int res[maxn];

int faste(int a, int p=mod-2){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}

int cnk(int n, int k){
    int s=ifact[k];
    REP(i,k) s=1ll*s*(n-i)%mod;
    return s;
}

int main(){
    ifact[0]=1;
    FOR(i,1,maxn) ifact[i]=1ll*ifact[i-1]*faste(i)%mod;

    int n,k; cin>>n>>k;
    REP(i,n) scanf(" %d", a+i);
    if (!k) memcpy(res,a,sizeof(res));
    else{
        --k;
        REP(i,n) b[i]=cnk(k+i,i);
        REP(i,n) FOR(j,i,n) res[j]=(res[j]+1ll*a[i]*b[j-i])%mod;
    }
    out(res,n);
    return 0;
}

