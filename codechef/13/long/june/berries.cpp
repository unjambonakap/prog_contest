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

const int maxn=1<<18;
const int mod=3046201;

int A[maxn];
int have[maxn];
char buf[11];
int fact[mod];

int get(int a){int res=0; for (++a; a; a&=a-1) res+=A[a]; return res;}
void update(int a, int b){for (++a; a<maxn; a+=a&-a) A[a]+=b;}
int powm(int a, int p=mod-2){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}
int cnk(int n, int k){return 1ll*fact[n]*powm(fact[k])%mod*powm(fact[n-k])%mod;}

int go(int N, int a){
    return 1ll*fact[N]*cnk(a,N%a)%mod*powm(1ll*powm(fact[N/a],a-N%a)*powm(fact[N/a+1],N%a)%mod)%mod; 
}

int main(){
    int n,nq;

    fact[0]=1;
    FOR(i,1,mod) fact[i]=1ll*i*fact[i-1]%mod;

    cin>>n;
    REP(i,n) scanf(" %d", have+i), update(i+1,have[i]);
    cin>>nq;

    REP(qq,nq){
        int a,b;
        scanf(" %s %d%d",buf,&a,&b);

        if (buf[0]=='c') update(a,b-have[a-1]), have[a-1]=b;
        else printf("%d\n", go(get(b)-get(a-1), b-a+1));
    }
    return 0;
}

