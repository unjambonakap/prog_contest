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

const int maxn=1555;
vector<pii> e[maxn];
int key[maxn];
int keypos[maxn];
int have[maxn];
int seen[maxn];
int disp[maxn];

pii block[maxn];
int vis[maxn];
int STEP;
int n, m;
int s, t;
vi res, tmp;
vi lst;
int tc=0;

void dfs(int a){
    if (vis[a]) return;
    vis[a]=1;

    if (block[key[a]].ST!=-1) lst.pb(key[a]); 
    disp[key[a]]=1;

    REP(j,e[a].size()){
        int kx=e[a][j].ND;
        if (have[kx]) dfs(e[a][j].ST);
        else{
            block[kx]=MP(a,e[a][j].ST);
            if (disp[kx]==1) lst.pb(kx);
        }
    }
}

int dfs2(int a, int b){
    if (a==b) return 1;
    if (seen[a]==STEP) return 0;
    seen[a]=STEP;
    REP(i,e[a].size()) if (dfs2(e[a][i].ST,b)){tmp.pb(a); return 1;}
    return 0;
}

void printpath(int a, int b){
    ++STEP;
    if (a==b) return;
    dfs2(a,b);
    for (int i=tmp.size()-1; i>=0; --i) res.pb(tmp[i]);
    tmp.clear();
}

int go(){
    res.clear(); lst.clear();
    memset(have,0,sizeof(have));
    memset(vis,0,sizeof(vis));
    have[0]=1;
    memset(seen,0,sizeof(seen)); STEP=0;
    memset(disp,0,sizeof(disp));
    REP(i,m) block[i].ST=-1;

    int pos=s;
    while(1){
        dfs(pos);
        if (vis[t]){ printpath(pos,t); res.pb(t);return 1; }
        if (!lst.size()) return 0;
        int kh=lst.back(); lst.pop_back();
        assert(block[kh].ST!=-1);

        printpath(pos,keypos[kh]);
        printpath(keypos[kh],block[kh].ND);
        pos=block[kh].ND;

        have[kh]=1;
        dfs(pos);
    }
}

int main(){
    while(cin>>n>>m>>s>>t,n){
        ++tc;

        memset(key,0,sizeof(key));
        REP(i,m){int a; scanf(" %d",&a); keypos[i+1]=a; key[a]=i+1;}
        REP(i,n-1){ int a,b,l; scanf(" %d%d%d",&a,&b,&l); e[a].pb(MP(b,l+1)); e[b].pb(MP(a,l+1));}
        ++m;


        if (!go()) puts("Impossible");
        else{
            assert(res.size()-1<=4*n*(m+1));
            assert(res[0]==s);
            assert(res.back()==t);
            printf("%d:",res.size()-1);
            REP(i,res.size()) printf(" %d",res[i]); puts("");
        }
        REP(i,n) e[i].clear();
    }
    return 0;
}

