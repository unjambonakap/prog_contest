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

const int maxn=4444;
char s[2*maxn];
int n;
int par[maxn];
int d[maxn];

vector<vi> res;
vi lvl[maxn];
vi tb;

int dfs(int a, int p=-1){
    int u=n++;
    par[u]=p;
    d[u]=p==-1?0:d[p]+1;

    ++a;
    while(s[a]!=')') a=dfs(a,u); 
    return a+1;
}

void solve(vi &x){
    if (x.size()==1){
        int a=x[0];
        REP(i,d[a]) tb.pb(1);
        res.pb(tb);
        REP(i,d[a]) tb.pop_back();
        return;
    }
    sort(ALL(x));

    vector<pii> px;
    REP(i,x.size()){
        if (!px.size() || px.back().ND!=par[x[i]]) px.pb(MP(0,par[x[i]]));
        ++px.back().ST;
    }
    sort(ALL(px));
    reverse(ALL(px));

    vi nx;
    for (int i=0; i<px.size(); ++i){
        int j=i;
        for (; j<px.size() && px[j].ST==px[i].ST; ++j) nx.pb(px[j].ND);
        int next=j==px.size()?0:px[j].ST;

        tb.pb(0);
        FOR(k,next,px[i].ST) tb.back()=k+1, solve(nx);
        tb.pop_back();
        i=j-1;
    }
}

int main(){
    while(1){
        scanf(" %s",s);
        if (s[0]=='0') break;
        n=0;
        dfs(0);
        REP(i,n) lvl[i].clear();

        res.clear();
        REP(i,n) lvl[d[i]].pb(i);
        REP(i,n) if (lvl[i].size()){
            tb.clear();
            tb.pb(0);
            solve(lvl[i]);
        }


        REP(i,res.size()) reverse(ALL(res[i]));

        sort(ALL(res));
        REP(i,res.size()) REP(j,res[i].size()) printf("%d%c",res[i][j]," \n"[j==res[i].size()-1]);
    }

    return 0;
}


