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

const int maxn=33*33;
const int maxt=11111;
const int oo=1e9;

int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};
int r,c;
int n;
int A[33][33];
vector<pii> e[maxn];
int dist[maxn];
int can[maxn];
int vis[maxn];


int dfs(int a){
    if (vis[a]) return 0;
    if (a==n-1) return 1;
    vis[a]=1;
    REP(j,e[a].size()) if (dfs(e[a][j].ST)) return 1;
    return 0;
}


int main(){

    while(cin>>r>>c,r){
        memset(A,0,sizeof(A));
        int nx; cin>>nx;
        n=r*c;
        REP(i,n) e[i].clear();


        REP(i,nx){int a,b; scanf(" %d%d",&a,&b); A[a][b]=1;}
        REP(i,r) REP(j,c) if (!A[i][j]){
            REP(k,4){
                int a=i+vx[k],b=j+vy[k];
                if (a>=0&&a<r&&b>=0&&b<c && !A[a][b]) e[i*c+j].pb(MP(a*c+b,1));
            }
        }
        cin>>nx;

        REP(i,nx){
            int xa,ya,xb,yb,t;
            scanf( "%d%d%d%d%d",&xa,&ya,&xb,&yb,&t);
            e[xa*c+ya].clear();
            e[xa*c+ya].pb(MP(xb*c+yb,t));
        }
        e[n-1].clear();

        memset(dist,0x7f,sizeof(dist));
        dist[0]=0;
        int fd=1;
        REP(i,n-1){
            fd=0;
            REP(j,n) if (dist[j]<oo) REP(k,e[j].size()){
                int b=e[j][k].ST, nd=dist[j]+e[j][k].ND;
                if (dist[b]>nd) dist[b]=nd, fd=1;
            }
            if (!fd) break;
        }

        fd=0;
        REP(step,3){
            REP(i,n) if (dist[i]<oo) REP(k,e[i].size()){
                int b=e[i][k].ST, nd=dist[i]+e[i][k].ND;
                if (dist[b]>nd){fd=1; goto done;}
                dist[b]=min(dist[b],nd);
            }
        }
done:;

     if (fd) puts("Never");
     else if (dist[n-1]>oo) puts("Impossible");
     else printf("%d\n",dist[n-1]);
    }


    return 0;
}

