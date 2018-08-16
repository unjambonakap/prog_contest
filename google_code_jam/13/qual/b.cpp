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

const int maxn=111;
int a[maxn][maxn];
int n,m;
int cntr[maxn], cntc[maxn];

int solve(){
    vector<pii> tb;
    REP(i,n) REP(j,m) tb.pb(MP(a[i][j],i*m+j));
    sort(ALL(tb));
    REP(i,n) cntr[i]=m;
    REP(i,m) cntc[i]=n;

    REP(i,n*m){
        int j=i;
        for (; j<n*m && tb[i].ST==tb[j].ST; ++j) --cntr[tb[j].ND/m], --cntc[tb[j].ND%m]; 
        for (; i<j; ++i) if (cntr[tb[i].ND/m]&&cntc[tb[i].ND%m]) return 0;
        --i;
    }
    return 1;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>m;
        REP(i,n) REP(j,m) scanf(" %d",a[i]+j);
        printf("Case #%d: ",ti+1);
        puts(solve()?"YES":"NO");
    }
    return 0;
}


