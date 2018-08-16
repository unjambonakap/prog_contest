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

const int maxn=21;
int n,m;
int adj[maxn];
int q[1<<maxn];
int par[1<<maxn];
int na,ne;
int pre[maxn+1], suf[maxn+1];

void go(){
    na=ne=0;
    memset(par,-1,sizeof(int)*(1<<n));
    q[ne++]=(1<<n)-1;
    par[(1<<n)-1]=-2;
    while(na<ne && par[0]==-1){
        int a=q[na++];
        REP(j,n+1) pre[j]=suf[j]=0;
        REP(j,n) pre[j+1]=pre[j]|(a&1<<j?adj[j]:0);
        REPV(j,n) suf[j]=suf[j+1]|(a&1<<j?adj[j]:0);

        REP(j,n) if (a&(1<<j)){
            int ns=pre[j]|suf[j+1];
            if (par[ns]==-1) q[ne++]=ns, par[ns]=(a<<5)|j;
        }
    }
    if (par[0]==-1) puts("Impossible");
    else{
        int x=0;
        vi lst;
        while(par[x]!=-2) lst.pb(par[x]&0x1f), x=par[x]>>5;
        
        printf("%d:",lst.size());
        for (int i=lst.size()-1; i>=0; --i) printf(" %d",lst[i]); puts("");
    }

}

int main(){
    while(scanf(" %d%d",&n,&m),n){
        memset(adj,0,sizeof(adj));
        REP(i,m){int a, b; scanf(" %d%d",&a,&b); adj[a]|=1<<b; adj[b]|=1<<a;}
        if (m!=n-1) puts("Impossible");
        else go();
    }

    return 0;
}

