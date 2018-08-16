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

const int maxn=101;
const int maxv=222;
const int inf=1e8;



vector<pii> e[maxn];
int dp[maxn][maxv];
int n, M;



int go(int a, int x, int p=-1){
    if (x<0) return inf;
    if (x>M) x=M;
    int &r=dp[a][x];
    if (r!=-1) return r;
    r=inf;

    int cnt=0;
    REP(i,e[a].size()){
        int b=e[a][i].ST, c=e[a][i].ND%60, c2=c?60-c:0;
        if (b==p) continue;
        ++cnt;
        REP(nx,x+1){
            int u=min(max(0,go(b,nx-c,a)-c),go(b,nx+c2,a)+c2);

            int fd=1;
            //printf("FUUFUFUF %d %d XX %d\n", a, nx, u);
            REP(j,e[a].size()) if (j!=i){
                int b2=e[a][j].ST, c=e[a][j].ND%60, c2=c?60-c:0;
                if (b2==p) continue;
                int l=min(nx,M-nx);

                int nu=min(max(0,go(b2,l-c,a)-c),go(b2,l+c2,a)+c2);
                assert(nu>=0);
                //printf("on %d , need %d %d >> get %d\n", b2, l, u, nu);
                if (u+nu>M){fd=0; break;}
                u=max(u,nu);
            }
            //printf("FIND %d >> %d\n", b, u);
            if (fd) r=min(r,u);
        }
    }
    if (!cnt) r=0;
    //printf("%d %d >> %d\n", a, x, r);
    if (r>M) r=inf;
    return r;
}


int par[maxn];
int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
int g[22][22];
int g2[22][22];
vector<pair<pii,int> > el;


void gen(){

    vi tbe[maxn]; 
    memset(par,-1,sizeof(par));
    n=15;
    printf("%d\n",n);
    memset(g,0x1f,sizeof(g));
    el.clear();
    REP(i,n-1){
        int a=rand()%n;
        vi u;
        REP(j,n) if (root(a)!=root(j)) u.pb(j);
        int b=u[rand()%u.size()];
        par[root(a)]=root(b);
        int c=rand()%300;
        printf("%d %d %d\n", a+1,b+1, c);
        e[a].pb(MP(b,c));
        e[b].pb(MP(a,c));
        el.pb(MP(MP(a,b),c));
        g[a][b]=g[b][a]=c;
    }
}

int stupid(){
    int best=inf;
    puts(""); puts(""); puts("");
    REP(i,n) g[i][i]=0;
    REP(k,n) REP(i,n) REP(j,n) g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    REP(i,n) out(g[i],n);


    REP(mask,two(n-1)){
        memset(g2,0x1f,sizeof(g2));
        REP(j,n-1){
            int c,c2;
            c=el[j].ND/60*60; c2=(el[j].ND+59)/60*60;
            int a=el[j].ST.ST, b=el[j].ST.ND;
            g2[a][b]=g2[b][a]=mask&two(j)?c:c2;
        }

        REP(i,n) g2[i][i]=0;
        REP(k,n) REP(i,n) REP(j,n) g2[i][j]=min(g2[i][j],g2[i][k]+g2[k][j]);
        puts("");
        REP(i,n) out(g2[i],n);
        int ans=0;
        REP(i,n) REP(j,n) ans=max(ans,abs(g2[i][j]-g[i][j]));
        printf(">> %d\n", ans);
        best=min(best,ans);
    }
    return best;

}

int main(){
    int tn=0;

    while(cin>>n,n){
start:
        ++tn;
        REP(i,n) e[i].clear();
        REP(i,n-1){
            int a, b, t; scanf(" %d%d%d", &a,&b,&t); 
            --a; --b;
            e[a].pb(MP(b,t));
            e[b].pb(MP(a,t));
        }
        //gen();

        memset(dp,-1,sizeof(dp));
        //if (tn!=3) continue;
        //M=60;
        //M=16;
        //printf("%d\n",go(n-1,0));
        //return 0;
        //printf("%d\n", go(n-1,14));
        //return 0;


        int T=0, H=maxv-1, best=H;
        while(T<=H){
            M=T+H>>1;

            memset(dp,-1,sizeof(dp));
            int fd=0; REP(i,M+1) if (go(n-1,i)<=M){fd=1;break;}

            if (fd) H=M-1, best=M;
            else T=M+1;
        }
        //int res2=stupid();
        //printf(">> %d %d\n", best, res2);
        //assert(best==res2);

        printf("Case %d: %d\n", tn, best);
        //goto start;


    }
    return 0;
}


