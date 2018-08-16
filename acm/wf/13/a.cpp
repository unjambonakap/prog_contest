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


const int maxn=44444;

vi has[64];
int next[maxn][4];
int n;
char buf[22];
int on[64];

int vis[64];
int dfs(int a){
    if (vis[a]) return on[a];
    vis[a]=1;

    on[a]=1;


    a^=32;
    REP(i,has[a].size()){
        int fd=0;
        int u=has[a][i];
        REP(j,4){
            int b=next[u][j];
            if (b==-1) continue;
            if ((b!=a || fd) && dfs(b)) return 1;
            if (b==a) fd=1;
        }
    }
    on[a^32]=0;

    return 0;
}

int main(){
    while(cin>>n,!cin.eof()){

        REP(i,n){
            scanf(" %s",buf);
            REP(j,4){
                if (buf[2*j]=='0') next[i][j]=-1;
                else next[i][j]=(buf[2*j]-'A')+32*(buf[2*j+1]=='-');
            }
        }
        REP(i,64) has[i].clear();
        REP(i,n) REP(j,4) if (next[i][j]!=-1) has[next[i][j]].pb(i);

        memset(vis,0,sizeof(vis));
        memset(on,0,sizeof(on));

        int fd=0;
        REP(i,64){
            if (!vis[i] && dfs(i)){fd=1; break;}
        }
        puts(!fd?"bounded":"unbounded");
    }

    return 0;
}

