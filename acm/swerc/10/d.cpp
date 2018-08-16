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

const int maxn=222;
const int maxe=2*(maxn+80*80);
int to[maxe], from[maxe], u[maxe], f[maxe], prev[maxe], last[maxn];
int FIX[maxe];
int ne;
int n;
int vis[maxn];
int nt,np;
int STEP;

void adde(int a, int b, int c){
    to[ne]=b; from[ne]=a; u[ne]=c; f[ne]=0; prev[ne]=last[a]; last[a]=ne++;
    swap(a,b);
    to[ne]=b; from[ne]=a; u[ne]=0; f[ne]=0; prev[ne]=last[a]; last[a]=ne++;
}

int dfs(int a){
    if (a==n-1) return 1;
    if (vis[a]==STEP) return 0;
    vis[a]=STEP;
    for (int i=last[a]; i!=-1; i=prev[i]) if (!FIX[i>>1] && f[i]<u[i] && dfs(to[i])){
        ++f[i]; --f[i^1];
        return 1;
    }
    return 0;
}

int dfs2(int a){
    if (a==n-1) return 1;
    if (vis[a]==STEP) return 0;
    vis[a]=STEP;
    for (int i=last[a]; i!=-1; i=prev[i]) if (!FIX[i>>1] && f[i]==u[i] && dfs2(to[i])){
        --f[i]; ++f[i^1];
        return 1;
    }
    return 0;
}

int maxflow(){
    int x=0;
    while(1){
        ++STEP;
        if (!dfs(n-2)) break;
        ++x;
    }
    return x;
}

void build(){
    int pos=0;
    REP(i,nt){
        REP(j,np){
            FIX[pos>>1]=1;
            if (!f[pos]) printf("N");
            else{
                ++STEP;
                assert(dfs2(nt+j));
                --f[pos]; ++f[pos^1];
                ++STEP;
                if (dfs(i)) printf("N");
                else{
                    ++f[pos]; --f[pos^1];
                    printf("Y");
                    assert(dfs(nt+j));
                }
            }
            pos+=2;
        }
        puts("");

    }

}




int main(){
    int uu=0;
    while(cin>>nt>>np,nt){
        if (uu++) puts("");
        n=2+nt+np;
        memset(last,-1,sizeof(last));
        memset(FIX,0,sizeof(FIX));
        ne=0;

        REP(i,nt) REP(j,np) adde(i,j+nt,1);
        int sa=0, sb=0;
        int ok=1;
        REP(i,nt){int x; scanf(" %d",&x); if (x>np) ok=0; adde(n-2,i,x); sa+=x;}
        REP(i,np){int x; scanf(" %d",&x); adde(nt+i,n-1,x); sb+=x;}

        if (sa!=sb) ok=0;

        memset(vis,0,sizeof(vis));
        STEP=0;

        if (!ok || maxflow()!=sa) puts("Impossible");
        else build();
    }
    return 0;
}

