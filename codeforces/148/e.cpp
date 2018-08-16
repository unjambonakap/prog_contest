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

const int maxn=111;
const int oo=1e9;
int G[maxn][maxn];
int g[maxn][maxn];
int n,m;

int s[maxn], t[maxn];
int wh[maxn][maxn];
int is[maxn][maxn];
vi prev[maxn][maxn];

int K;
int aa,bb;

int dist[maxn];
int q[maxn],na,ne;

int dp[maxn], in[maxn];
int STEP;
vi add;

void go(int i){
    memset(in,0,sizeof(in));
    REP(j,n) dp[j]=dist[j]<oo?STEP:oo;

    vi tb;
    tb.pb(t[i]);
    while(tb.size()){
        vi nt;
        REP(j,tb.size()){
            int a=tb[j];
            if (dist[a]<oo) dp[a]=dist[a];
            REP(k,prev[i][a].size()){
                int b=prev[i][a][k];
                dp[b]=max(dp[b],dp[a]);
                if (!in[b]){
                    dp[b]=dp[a];
                    in[b]=1, nt.pb(b);
                }
            }
        }
        tb=nt;
    }

    REP(j,n) if (is[i][j] && dp[j]!=-1 && dp[j]<oo && dist[j]>=oo) add.pb(j);
    
    
}

int solve(){
    memset(dist,0x3f,sizeof(dist));
    na=ne=0;
    dist[bb]=0;
    STEP=0;
    add.pb(bb);
    while(add.size()){
        REP(i,add.size()) dist[add[i]]=STEP;
        add.clear();
        ++STEP;
        if (dist[aa]<oo) return dist[aa];
        REP(i,K) go(i);
    }
    return oo;
}

int main(){
    while(scanf(" %d%d%d%d",&n,&m,&aa,&bb)>0){
        --aa; --bb;

        memset(g,0,sizeof(g));
        memset(G,0x3f,sizeof(g));
        REP(i,n) G[i][i]=0;
        REP(i,m){
            int a,b; scanf(" %d%d",&a,&b);
            --a; --b;
            g[a][b]=G[a][b]=1;
        }
        cin>>K;
        REP(i,K) scanf(" %d%d",s+i,t+i), --s[i], --t[i];


        REP(k,n) REP(i,n) REP(j,n) G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
        memset(wh,-1,sizeof(wh));
        memset(is,0,sizeof(is));

        REP(i,K){
            int x=s[i], y=t[i];
            if (G[x][y]>oo) continue;

            vi tb; tb.pb(x);
            wh[i][x]=0;
            int step=0;
            while(tb[0]!=y){
                if (tb.size()==1) is[i][tb[0]]=1;

                ++step;
                vi nt;
                REP(j,tb.size()){
                    int a=tb[j];
                    REP(k,n) if (g[a][k] && G[k][y]+1==G[a][y]){
                        prev[i][k].pb(a);
                        if (wh[i][k]==-1) wh[i][k]=step, nt.pb(k);
                    }
                }
                tb=nt;
            }
        }
        int res=solve();
        if (res>=oo) res=-1;
        printf("%d\n",res);
        REP(i,K) REP(j,n) prev[i][j].clear();
    }
    return 0;
}

