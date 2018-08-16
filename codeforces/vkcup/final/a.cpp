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

const int maxn=555;
const int maxe=2*6666;
int n, m, t;
int g[maxn][maxn];
int da[maxn], db[maxn];
int id[maxe];
int REM;

struct maxflow{
    int ne;
    int s,t;
    int to[maxe], from[maxe], c[maxe], f[maxe], prev[maxe], last[maxn];
    int vis[maxn];
    maxflow(int s, int t):ne(0),s(s),t(t){memset(last,-1,sizeof(last)); memset(f,0,sizeof(f));}

    void adde(int a, int b, int cx){
        to[ne]=b; from[ne]=a; c[ne]=cx; prev[ne]=last[a]; last[a]=ne++; 
        swap(a,b); cx=0;
        to[ne]=b; from[ne]=a; c[ne]=cx; prev[ne]=last[a]; last[a]=ne++; 
    }

    int go(){
        memset(vis,0,sizeof(vis));
        int res=0;
        while(1){
            ++res;
            if (!dfs(s)){
                --res;
                memset(vis,0,sizeof(vis));
                if (!dfs(s)) break;
                ++res;
            }
        }
        return res;
    }

    int dfs(int a){
        if (vis[a]) return 0;
        vis[a]=1;
        if (a==t) return 1;
        for (int i=last[a]; i!=-1; i=prev[i]) if (c[i]>f[i] && dfs(to[i])){++f[i]; --f[i^1]; return 1;}
        return 0;
    }

    int dfs2(int a){
        if (vis[a]) return 0;
        int F=a<n;
        vis[a]=1;
        if (F && f[2*a]>da[a]/REM){ --f[2*a]; return 1; }

        for (int i=last[a]; i!=-1; i=prev[i]) if (to[i]<n+m && (f[i]<c[i]) && dfs2(to[i])){
            ++f[i], --f[i^1];
            return 1;
        }
        return 0;
    }

    int dfs2b(int a){
        if (vis[a]) return 0;
        int F=a>=n;
        vis[a]=1;
        if (F && f[2*a]>db[a-n]/REM){ --f[2*a]; return 1; }

        for (int i=last[a]; i!=-1; i=prev[i]) if (to[i]<n+m && (f[i]==c[i]) && dfs2b(to[i])){
            --f[i], ++f[i^1];
            return 1;
        }
        return 0;
    }


    void norm(){
        REP(i,n){
            memset(vis,0,sizeof(vis));
            for (; f[2*i]<da[i]/REM; ++f[2*i]){
                if (!dfs2(i)){
                    memset(vis,0,sizeof(vis));
                    assert(dfs2(i));
                }
            }
        }
        REP(i,m){
            memset(vis,0,sizeof(vis));
            for (; f[2*(n+i)]<db[i]/REM; ++f[2*(n+i)]){
                if (!dfs2b(n+i)){
                    memset(vis,0,sizeof(vis));
                    assert(dfs2b(n+i));
                }
            }
        }

    }

    void go2(int x){
        for (int i=2*(n+m); i<ne; i+=2) if (f[i]){
            int a=from[i], b=to[i]-n;
            assert(from[i]<n && to[i]>=n);
            --da[a]; --db[b];
            assert(g[a][b]);
            id[g[a][b]-1]=x;
            g[a][b]=0;
        }
        REP(i,n){
            int cnt=0;
            REP(j,m) if (g[i][j]) ++cnt;
            assert(da[i]==cnt);
        }
        REP(i,m){
            int cnt=0;
            REP(j,n) if (g[j][i]) ++cnt;
            assert(db[i]==cnt);
        }
    }

};

int main(){
    int ne;
    cin>>n>>m>>ne>>t;
    REP(i,ne){ int a, b; scanf(" %d%d", &a,&b); --a; --b; g[a][b]=i+1; ++da[a], ++db[b];}
    int res=0;
    REP(i,n) res+=da[i]%t?1:0;
    REP(i,m) res+=db[i]%t?1:0;


    cout<<res<<endl;
    int rem=t;
    REP(step,t){
        maxflow mf(n+m,n+m+1);
        REP(i,n) mf.adde(n+m,i,(da[i]+rem-1)/rem);
        REP(i,m) mf.adde(n+i,n+m+1,(db[i]+rem-1)/rem);
        REP(i,n) REP(j,m) if (g[i][j]) mf.adde(i,n+j,1);
        REM=rem;
        mf.go();
        mf.norm();
        mf.go2(step+1);
        --rem;
    }

    out(id,ne);

    return 0;
}


