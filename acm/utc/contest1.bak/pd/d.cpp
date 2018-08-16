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
const int inf=1e9;

ll a[maxn][maxn];
int b[maxn][maxn];
int dp[maxn][maxn];
int U, k;
int r, c;

int go(int a, int b){
    int &r=dp[a][b];
    if (r!=-1) return r;
    r=inf;
    if (a<r-1) r=min(r,go(a+1,b));
    if (b<c-1) r=min(r,go(a,b+1));
    return r=min(inf,r+b[a][b]);
}

int go1(int p){
    U=p;
    memset(b,0,sizeof(b)); memset(dp,-1,sizeof(dp));
    REP(i,r) REP(j,c){
        if (a[i][j]==0) 
        while(a[i][j]%p==0) ++b[i][j], a[i][j]/=p;
    }
    int x=go(0,0);
    return x==inf?-1:x;
}

int main(){
    cin>>r>>c>>k;
    if (k==1){puts("-1"); return 0;}

    REP(i,r) REP(j,c) scanf(" %Ld", a[i]+j);
    int res=inf;
    for (int i=2; i<=k && res!=-1; ++i) if (k%i==0 && (k/i)%i){ res=min(res,go1(i)); k/=i; }
    cout<<res<<endl;
    return 0;
}

