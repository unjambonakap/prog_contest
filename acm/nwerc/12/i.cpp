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


const int maxn=2*1111;
vi e[maxn];
vi et[maxn];
int n;
int vis[maxn];
vi ord;
int wh[maxn];
int STEP;

void adde(int a, int b){e[a].pb(b); et[b].pb(a);}

void dfs1(int a){
    if (vis[a]) return;
    vis[a]=1;
    REP(i,e[a].size()) dfs1(e[a][i]);
    ord.pb(a);
}

void dfs2(int a){
    if (wh[a]!=-1) return;
    wh[a]=STEP;
    REP(i,et[a].size()) dfs2(et[a][i]);
}



int main(){
    int m;
    while(scanf(" %d%d",&n,&m)>0){
        REP(i,m){
            int a, b; scanf(" %d%d",&a,&b);
            int fa=a<0, fb=b<0;
            a=abs(a);
            b=abs(b);
            --a;
            --b;
            adde(2*a+1-fa,2*b+fb);
            adde(2*b+1-fb,2*a+fa);
        }
        adde(1,0);


        memset(vis,0,sizeof(vis));
        ord.clear();
        REP(i,2*n) if (!vis[i]) dfs1(i);

        STEP=0;
        memset(wh,-1,sizeof(wh));
        for (int i=2*n-1; i>=0; --i) if (wh[ord[i]]==-1){
            ++STEP;
            dfs2(ord[i]);
        }
        int ok=1;
        REP(i,2*n) if (wh[i]==wh[i^1]){ok=0; break;}
        puts(ok?"yes":"no");

        REP(i,2*n) e[i].clear(), et[i].clear();

    }
    return 0;
}

