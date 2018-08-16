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

const int maxn=55;
int a[maxn][maxn];
int n, m;
int g[maxn*maxn][4];
int vis[maxn*maxn];
int NOT;
int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int dfs(int a){
    if (a==NOT) return 0;
    if (vis[a]) return 0;
    vis[a]=1;
    int u=1;
    REP(k,4) if (g[a][k]!=-1) u+=dfs(g[a][k]);
    return u;
}

int in(int a, int b){return a>=0&&b>=0&&a<n&&b<m;}

int main(){
    cin>>n>>m;
    REP(i,n){
        char buf[maxn];
        scanf(" %s", buf);
        REP(j,m) a[i][j]=buf[j]=='#';
    }
    int po=-1, po2;
    memset(g,-1,sizeof(g));
    REP(i,n) REP(j,m) if (a[i][j]){
        if (po==-1) po=i*m+j;
        else po2=i*m+j;

        REP(k,4){
            int x=i+vx[k], y=j+vy[k];
            if (in(x,y) && a[x][y]) g[i*m+j][k]=x*m+y;
        }
    }


    NOT=-1;
    memset(vis,0,sizeof(vis));
    int cnt=dfs(po);
    if (cnt<=2) puts("-1");
    else{
        int fd=0;
        REP(i,n) REP(j,m) if (a[i][j]){
            NOT=i*m+j;
            memset(vis,0,sizeof(vis));
            if (dfs(po==NOT?po2:po)<cnt-1) fd=1;
        }
        if (fd) puts("1");
        else puts("2");
    }



    return 0;
}


