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

const int maxn=1e5+10;
const int oo=1e9;
int c[maxn];
int n;
int par[maxn];
int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}

int main(){
    cin>>n;
    int m; cin>>m;
    int cnt=n;
    memset(par,-1,sizeof(par));
    REP(i,m){
        int a,b; scanf(" %d%d",&a,&b);
        a=root(a-1); b=root(b-1);
        if (a!=b) par[a]=b, --cnt;
    }

    memset(c,-1,sizeof(c));
    int best=oo;
    int ans=0;
    int ocnt=cnt;

    REP(i,n){
        int u; scanf(" %d",&u);
        if (u<0) continue;
        int x=root(i);
        best=min(best,u);

        if (c[x]==-1) c[x]=u, --cnt, ans+=u;
        if (c[x]>u) ans+=u-c[x], c[x]=u;
    }
    if (ocnt==1) puts("0");
    else if (cnt) puts("-1");
    else cout<<ans+best*(ocnt-2)<<endl;

    return 0;
}

