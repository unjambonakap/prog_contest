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

int n;
const int maxn=1001;
struct rect{ int xa, xb, ya, yb; };
int parent[maxn];
vector<rect> tb;

int root(int a){return (parent[a]==-1?a:parent[a]=root(parent[a]));}

int checkit(int a, int b){
    if (tb[a].xb+1<tb[b].xa || tb[b].xb+1<tb[a].xa) return 0;
    if (tb[a].yb+1<tb[b].ya || tb[b].yb+1<tb[a].ya) return 0;
    if (tb[a].xb+1==tb[b].xa) return tb[a].yb+1!=tb[b].ya;
    if (tb[b].xb+1==tb[a].xa) return tb[b].yb+1!=tb[a].ya;
    return 1;
}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int a, b, c, d;
        cin>>n;
        tb.resize(n);
        REP(i, n) cin>>tb[i].xa>>tb[i].ya>>tb[i].xb>>tb[i].yb;
        memset(parent, -1, sizeof(parent));

        REP(i, n) REP(j, n) if (root(i)!=root(j) && checkit(i, j)) parent[root(i)]=root(j);
        vector<vi> lst;
        int rmp[maxn];
        int pos=0;
        memset(rmp, -1, sizeof(rmp));
        REP(i, n){
            int id;
            if (rmp[root(i)]==-1) rmp[root(i)]=pos++, lst.pb(vi());
            id=rmp[root(i)];
            lst[id].pb(i);
        }
        int res=0;
        FE(it, lst){
            int mx, my;
            mx=my=0;
            FE(ita, *it) checkmax(mx, tb[*ita].xb), checkmax(my, tb[*ita].yb);
            FE(ita, *it) checkmax(res, mx-tb[*ita].xa+my-tb[*ita].ya);
        }
        


        printf("Case #%d: %d\n", ti, res+1);
    }
    return 0;
}




