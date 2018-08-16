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

const int maxn=1222;
const int maxe=maxn*maxn;

int rmp[11111];
int ea[maxn], eb[maxn], used[maxn];
int par[maxn];
int m;
int pos,n;
int vis[maxn];
int d[maxn], pare[maxn];

int to[maxe],from[maxe],last[maxn],prev[maxe];
int sink[maxn];
int ne;
vector<pii> ex[maxn];

int q[maxn],na,nb;
int parx[maxn];

void adde(int a, int b){ to[ne]=b; from[ne]=a; prev[ne]=last[a]; last[a]=ne; ne++; }



int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
int mp(int a){return rmp[a]==-1?rmp[a]=pos++:rmp[a];}

void dfs(int a, int p, int pid=-1){
    d[a]=p==-1?0:d[p]+1;
    pare[a]=pid;
    vis[a]=1;
    REP(i,ex[a].size()){
        int u=ex[a][i].ND;
        int b=ex[a][i].ST;
        if (!used[u]) continue;
        if (b!=p) dfs(b,a,u);
    }

}

int go(int a, int j){
    int u=pare[a]; adde(j,u);
    return ea[u]==a?eb[u]:ea[u];
}

void bfs(int a1, int a2){
    memset(parx,-1,sizeof(parx));
    na=nb=0;
    q[nb++]=a1; q[nb++]=a2;
    while(na<nb){
        int a=q[na++];
        if (sink[a]){
            while(a!=-1){
                used[a]^=1;
                a=parx[a];
            }
            break;
        }

        for (int i=last[a]; i>=0; i=prev[i]){
            int b=to[i];
            if (parx[b]==-1) parx[b]=a, q[nb++]=b;
        }
    }
}

int main(){
    while(cin>>m,m){
        memset(used,0,sizeof(used));
        memset(rmp,-1,sizeof(rmp));
        pos=0;
        REP(i,m){
            int a,b,c,d; scanf(" %d%d%d%d",&a,&b,&c,&d);
            ea[2*i]=mp(a);
            eb[2*i]=mp(b);
            ea[2*i+1]=mp(c);
            eb[2*i+1]=mp(d);
        }
        n=pos;

        memset(last,-1,sizeof(last));

        REP(i,maxn) ex[i].clear();
        REP(i,m){
            memset(par,-1,sizeof(int)*n);
            REP(j,2*i) if (used[j]){
                assert(root(ea[j])!=root(eb[j]));
                par[root(ea[j])]=root(eb[j]);

            }


            memset(vis,0,sizeof(vis));
            REP(j,n) if (!vis[j]) dfs(j,-1);

            ne=0;
            memset(sink,0,sizeof(sink));
            int N=2*i+2;
            memset(last,-1,sizeof(int)*N);
            REP(j,N){
                if (used[j]) adde(j,j^1);
                else{
                    int a=ea[j], b=eb[j];
                    if (root(a)!=root(b)) sink[j]=1;
                    else{
                        if (d[a]<d[b]) swap(a,b);
                        while(d[a]>d[b]) a=go(a,j);
                        while(a!=b) a=go(a,j), b=go(b,j);
                    }
                }
            }

            bfs(2*i,2*i+1);


            int p=2*i;
            ex[ea[p]].pb(MP(eb[p],p));
            ex[eb[p]].pb(MP(ea[p],p));
            ++p;
            ex[ea[p]].pb(MP(eb[p],p));
            ex[eb[p]].pb(MP(ea[p],p));
        }

        int res=0;
        REP(i,2*m) res+=used[i];
        printf("%d\n",2*res);
    }
    return 0;
}

