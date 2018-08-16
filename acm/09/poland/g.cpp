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


const int maxn=44444;
const int inf=1e9;
int n, m, d;
int w[maxn];
int v;

int dp[maxn][2];
int go(int a, int f){
    if (a==n) return f?inf:0;
    int &r=dp[a][f];
    if (r!=-1) return r;
    r=inf;
    int sa=w[a], sb=w[a+1];
    int i=2, j=1;
    while(sa<=v && i<=n-a && j<=d){
        if (sb<=v) checkmin(r,go(a+i,f^1)+1);
        sa+=w[a+j];
        sb+=w[a+i]+w[a+i+1]-w[a+j];
        ++j, i+=2;
    }
    
    return r;

}

int checkit(int _v){
    v=_v;
    if (n&1) return 0;
    if (n/2<m-1) return 0;
    memset(dp,-1,sizeof(dp));
    if (go(0,m-1&1)<=m) return 1;
    return 0;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>m>>d;
        REP(i,n) scanf("%d", w+i);
        int T=0, H=inf;
        int best=-1;
        while(T<=H){
            int M=(1ll*T+H)/2;
            if (checkit(M)){best=M; H=M-1;}
            else T=M+1;
        }
        if (best==-1) puts("BAD");
        else printf("%d\n",best);
    }
    return 0;
}


