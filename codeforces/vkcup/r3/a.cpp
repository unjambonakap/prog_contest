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

const int maxn=111111;
vi e[maxn];
vi eg[maxn];
int f[maxn];
int n, m;
int vis[maxn];
int mark1[maxn], mark2[maxn];

void dfs(int a){
    if (mark1[a]) return;
    mark1[a]=1;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (f[b]!=1) dfs(b);
    }
}

void dfs2(int a){
    if (mark2[a]) return;
    mark2[a]=1;
    REP(i,eg[a].size()){
        int b=eg[a][i];
        if (f[b]!=1) dfs2(b);
    }
}


int main(){
    cin>>n>>m;
    REP(i,n) scanf(" %d", f+i);
    REP(i,m){int a, b; scanf(" %d%d", &a, &b); --a; --b; e[a].pb(b); eg[b].pb(a);}
    REP(i,n) if (f[i]==1) dfs(i);
    REP(i,n) if (f[i]==2) dfs2(i);
    
    int cnt=0;
    REP(i,n){
        int fd=0;
        if (f[i]==0 && mark1[i]&&mark2[i]) fd=1;
        else if (f[i]==1){
            REP(j,e[i].size()) if (mark2[e[i][j]]){fd=1; break;}
        }else if (f[i]==2){
            REP(j,eg[i].size()) if (f[eg[i][j]]==1||mark1[eg[i][j]]){fd=1; break;}
        }
        printf("%d\n", fd);
    }



    return 0;
}

