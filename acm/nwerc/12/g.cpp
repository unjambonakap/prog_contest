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

const int maxn=11111;
int nb;

vi tb[maxn];
vi e[maxn];
int na[maxn];
int par[maxn];
vi next[maxn];
int ord[maxn], pos;


int dp[maxn][2];
int have[11], c[11][2];
ll cover[1<<11];
int rmp[11][11];
int U;

int getid(int a, int b){
    if (rmp[a][b]!=-1) return rmp[a][b];
    return rmp[a][b]=rmp[b][a]=U++;
}

int read(){
    int u=nb++;
    if (scanf(" %d",na+u)<=0) return 0;
    int m,w; scanf(" %d%d",&m,&w);

    REP(i,m){
        int a, b; scanf(" %d%d",&a,&b);
        --a; --b;
        e[a].pb(b);
        e[b].pb(a);
        tb[u].pb(a); tb[u].pb(b);
    }
    sort(ALL(tb[u]));
    tb[u].resize(unique(ALL(tb[u]))-tb[u].begin());

    REP(i,w){
        int a, b; scanf(" %d%d",&a,&b);
        --a; --b;
        par[nb]=b;
        next[a].pb(nb);
        read();
    }
    ord[pos++]=u;
}


int main(){

    while(1){
        nb=0;
        pos=0;
        if (!read()) break;

        memset(dp,0x1f,sizeof(dp));
        REP(aa,nb){
            int u=ord[aa];
            int nx=na[u];
            REP(i,nx) have[i]=tb[u][i];
            memset(rmp,-1,sizeof(rmp)); U=0;

            int px=par[u]==-1?nx:lower_bound(have,have+nx,par[u])-have;

            REP(i,nx){
                int a=have[i];
                ll v=0;
                REP(j,e[a].size()) v|=1ll<<getid(i,lower_bound(have,have+nx,e[a][j])-have);
                cover[1<<i]=v;

                c[i][1]=1;
                c[i][0]=0;
                REP(j,next[a].size()) c[i][1]+=dp[next[a][j]][0], c[i][0]+=dp[next[a][j]][1];
            }
            ll need=(1ll<<U)-1;

            FOR(i,0,1<<nx){
                cover[i]=cover[i&-i]|cover[i&(i-1)];
                if (cover[i]==need){
                    int cx=0;
                    REP(j,nx){
                        if (i&1<<j) cx+=c[j][1];
                        else cx+=c[j][0];
                    }
                    int f=0;

                    if (i&1<<px) f=1;
                    dp[u][f]=min(dp[u][f],cx);
                }
            }
            dp[u][0]=min(dp[u][0],dp[u][1]);
        }
        printf("%d\n",dp[0][0]);

        REP(i,maxn) tb[i].clear();
        REP(i,maxn) next[i].clear();
        REP(i,maxn) e[i].clear();


    }
    return 0;
}

