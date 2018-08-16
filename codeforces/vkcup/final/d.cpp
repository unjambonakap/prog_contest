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

const int maxn=1111111;
int a[maxn],n;
int lv[maxn], rv[maxn];
ll res[maxn];

ll F[maxn];

int main(){
    cin>>n;
    REP(i,n) scanf(" %d", a+i);
    memset(lv,-1,sizeof(lv));
    memset(rv,-1,sizeof(rv));
    vector<pii> tb;
    REP(i,n){
        while(tb.size() && tb.back().ST>a[i]) tb.pop_back();
        if (tb.size()) lv[i]=tb.back().ND;
        tb.pb(MP(a[i],i));
    }
    tb.clear();
    for (int i=n-1; i>=0; --i){
        while(tb.size() && tb.back().ST>=a[i]) tb.pop_back();
        if (tb.size()) rv[i]=tb.back().ND;
        tb.pb(MP(a[i],i));
    }

    REP(i,n){
        int u=i-lv[i]-1, v=(rv[i]==-1?n:rv[i])-i-1;
        if (v<u) swap(u,v);
        F[1]+=a[i];
        F[u+2]-=a[i];
        F[v+2]-=a[i];
        F[u+v+3]+=a[i];
    }


    ll x=0, c=0;
    FOR(i,1,n+1) x+=F[i], res[i]=c+=x;

    int m; cin>>m;
    REP(i,m){int u; scanf(" %d", &u); printf("%.10lf\n", 1.*res[u]/(n-u+1));}
    return 0;
}


