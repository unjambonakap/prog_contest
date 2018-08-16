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

const int maxn=666;
int mod;
int m[maxn][maxn];
int n, ne;
int dega[maxn], degb[maxn];
vi e[maxn];
int isa[maxn], isb[maxn];
int dp[maxn][maxn];
int na;

int go(int a, int b){
    if (a==b) return 1;
    int &r=dp[a][b];
    if (r!=-1) return r;
    r=0;
    REP(i,e[a].size()) r=(r+go(e[a][i],b))%mod;
    return r;
}

int inv(int a, int p){
    int x=1;
    for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod;
    return x;
}


int det(){
    int res=1;
    REP(i,na){
        int p=-1;
        FOR(j,i,na) if (m[j][i]!=0){p=j; break;}
        if (p==-1) return 0;
        if (p!=i) res=(mod-res)%mod;
        REP(j,na) swap(m[i][j],m[p][j]);
        int aa=inv(m[i][i],mod-2);
        res=1ll*res*m[i][i]%mod;
        FOR(j,i,na) m[i][j]=1ll*m[i][j]*aa%mod;
        FOR(j,i+1,na){
            int bb=m[j][i];
            FOR(k,i,na) m[j][k]-=1ll*bb*m[i][k]%mod, m[j][k]=(mod+m[j][k])%mod;
        }
    }
    return res;
}

int main(){
    cin>>n>>ne>>mod;
    REP(i,ne){
        int a, b; scanf(" %d%d", &a,&b);
        --a; --b;
        e[a].pb(b);
        ++dega[a]; ++degb[b];
    }

    vi la, lb;
    REP(i,n){
        if (!dega[i]) la.pb(i);
        if (!degb[i]) lb.pb(i);
    }
    memset(dp,-1,sizeof(dp));
    na=la.size();
    REP(i,na) REP(j,na) m[i][j]=go(lb[i],la[j]);
    cout<<det()<<endl;

    return 0;
}

