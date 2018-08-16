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
int A[maxn][maxn];
int n, m;
char s[maxn];
int vx[]={0,1,0,-1};
int vy[]={1,0,-1,0};
int vis[maxn][maxn];
int with[maxn][maxn];
vector<pii> next[4*maxn];
vector<pii> e[4*maxn];
int nc;
int besta[4*maxn];
int bestb[4*maxn];
int vis2[4*maxn];

char buf[maxn];

int in(int x, int y){return x>=0&&y>=0&&x<n&&y<m;}

void dfs(int x, int y){
    stack<int> q; 
    q.push(x*m+y); vis[x][y]=1;

    while(q.size()){
        x=q.top(); y=x%m; x/=m; q.pop();
        with[x][y]=nc;
        REP(k,4){
            int nx=x+vx[k], ny=y+vy[k];
            if (A[(nx+n)%n][(ny+m)%m]) continue;
            if (in(nx,ny)){ if (!vis[nx][ny]) q.push(nx*m+ny), vis[nx][ny]=1;}
            else next[nc].pb(MP(((nx+n)%n)*m+(ny+m)%m,k));
        }
    }
    int oc=nc++;
    REP(i,next[oc].size()) if (!vis[next[oc][i].ST/m][next[oc][i].ST%m]) dfs(next[oc][i].ST/m,next[oc][i].ST%m);
}

int dfs2(int a){
    memset(besta,-1,sizeof(besta));
    memset(bestb,-1,sizeof(bestb));
    stack<int> q;
    q.push(a);
    memset(vis2,0,sizeof(vis2));
    
    vis2[a]=1;
    besta[a]=bestb[a]=0;
    while(q.size()){
        a=q.top(); q.pop();
        REP(i,e[a].size()){
            int b=e[a][i].ST;
            int k=e[a][i].ND;
            int na=besta[a]+vx[k], nb=bestb[a]+vy[k];
            if (!vis2[b]) vis2[b]=1, besta[b]=na, bestb[b]=nb, q.push(b);
            else if (besta[b]!=na || bestb[b]!=nb) return 1;
        }
    }
    return 0;
}

int main(){
    cin>>n>>m;
    int xo, yo;
    REP(i,n){
        scanf(" %s", buf);
        REP(j,m){
            A[i][j]=buf[j]=='#';
            if (buf[j]=='S') xo=i, yo=j;
        }
    }
    dfs(xo,yo);
    REP(i,nc) REP(j,next[i].size()) e[i].pb(MP(with[next[i][j].ST/m][next[i][j].ST%m],next[i][j].ND));
    

    int res=dfs2(0);
    puts(res?"Yes":"No");
    return 0;
}


