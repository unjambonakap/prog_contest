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

const int maxn=1111;
int n;
int x[maxn], y[maxn];

vi e[maxn];

int vis[maxn], par[maxn];
int when;

int dfs(int a){
    if (vis[a]==when) return 0;
    vis[a]=when;

    REP(i,e[a].size()){
        int b=e[a][i];
        if (par[b]==-1 || dfs(par[b])){par[b]=a; return 1;}
    }
    return 0;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        REP(i,n) scanf(" %d%d",x+i,y+i);
        vi xl,yl;
        REP(i,n) xl.pb(x[i]), yl.pb(y[i]);

        sort(ALL(xl));
        sort(ALL(yl));
        xl.resize(unique(ALL(xl))-xl.begin());
        yl.resize(unique(ALL(yl))-yl.begin());

        REP(i,n) x[i]=lower_bound(ALL(xl),x[i])-xl.begin();
        REP(i,n) y[i]=lower_bound(ALL(yl),y[i])-yl.begin();

        REP(i,xl.size()) e[i].clear();
        REP(i,n) e[x[i]].pb(y[i]);

        int res=0;
        memset(vis,0,sizeof(vis));
        memset(par,-1,sizeof(par));
        when=1;
        REP(i,xl.size()){
            ++res;
            if (!dfs(i)){
                ++when;
                if (!dfs(i)) --res;
            }
        }

        printf("%d\n",res);




    }
    return 0;
}

