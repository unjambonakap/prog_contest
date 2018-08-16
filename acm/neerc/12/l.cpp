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
int r,c;
char buf[maxn];
int A[maxn][maxn];
int vis[maxn][maxn];
int par[maxn*maxn];
int dp[maxn][maxn];

int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int in(int a, int b){return a>=0&&b>=0&&a<r&&b<c;}
int root(int a){return par[a]<0?a:par[a]=root(par[a]);}
void join(int a, int b){a=root(a); b=root(b); if (a!=b) par[a]=b;}

int fx[2][maxn][maxn];
int fy[2][maxn][maxn];


void bfs(){
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(0);
    while(q.size()){
        int a=q.front(); q.pop();
        int x=a%r, y=a/r;
        REP(k,4){
            int nx=x+vx[k],ny=y+vy[k];
            if (in(nx,ny) && !A[nx][ny] && !vis[nx][ny]) vis[nx][ny]=1, q.push(nx+ny*r);
        }
    }
}


int checkit(int i, int j, int u){
    int ff[2]={0};
    if (i+u==r&&j+u==c) return 0;
    if (i==0) ++ff[1];
    if (i+u==r) ++ff[0];
    if (j==0) ++ff[0];
    if (j+u==c) ++ff[1];
    REP(k,2){
        for (int s=-1; s<=u; s+=u+1) if (i+s>=0) ff[k]+=fx[k][i+s][min(c,j+u+1)]-fx[k][i+s][max(0,j-1)];
        for (int s=-1; s<=u; s+=u+1) if (j+s>=0) ff[k]+=fy[k][min(r,i+u+1)][j+s]-fy[k][max(0,i-1)][j+s];
    }
    return ff[0]&&ff[1];
}

int main(){
    freopen("labyrinth.in","r",stdin);
    freopen("labyrinth.out","w",stdout);
    cin>>c>>r;
    REP(i,r){
        scanf(" %s",buf);
        REP(j,c) A[i][j]=buf[j]=='#';
    }
    bfs();
    REP(i,r) REP(j,c) if (!vis[i][j]) A[i][j]=1;
    memset(par,-1,sizeof(par));

    int U=r*c,V=U+1;
    REP(i,r) REP(j,c) if (A[i][j]) FOR(dx,-1,2) FOR(dy,-1,2) if (dx||dy){
        int x=i+dx, y=j+dy;
        if (in(x,y) && A[x][y]) join(x+y*r,i+j*r);
    }


    REP(i,r){
        if (A[i][0]) join(i,U);
        if (A[i][c-1]) join(i+(c-1)*r,V);
    }

    REP(i,c){
        if (A[0][i]) join(i*r,V);
        if (A[r-1][i]) join(r-1+i*r,U);
    }

    A[r-1][c-1]=1;
    REPV(i,r) REPV(j,c) if (!A[i][j]){
        int u=min(dp[i][j+1],dp[i+1][j]);
        if (!A[i+u][j+u]) ++u;
        dp[i][j]=u;
    }
    A[r-1][c-1]=0;

    int tb[]={U,V};
    REP(k,2){
        REP(i,r) REP(j,c) fx[k][i][j+1]=fx[k][i][j]+(root(i+j*r)==root(tb[k]));
        REP(j,c) REP(i,r) fy[k][i+1][j]=fy[k][i][j]+(root(i+j*r)==root(tb[k]));
        //REP(i,r){
        //    REP(j,c) printf("%d ",(root(i+j*r)==root(tb[k])));
        //    puts("");
        //}
        //puts("===");
    }




    int best,bestx,besty;
    best=maxn;
    REP(i,r) REP(j,c) if (!A[i][j]){
        if (!i&&!j) continue;
        if (!checkit(i,j,dp[i][j])) continue;
        int T=1, H=min(dp[i][j],best-1);
        while(T<=H){
            int u=T+H>>1;
            if (checkit(i,j,u)) H=u-1, best=u,bestx=i,besty=j;
            else T=u+1;
        }

    }
    if (best==maxn) puts("Impossible");
    else printf("%d %d %d\n",best,besty+1,bestx+1);

    return 0;
}



