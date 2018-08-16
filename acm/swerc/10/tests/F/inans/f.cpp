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
const int oo=1e9;
int n,m;
int adj[1<<maxn];
int q[1<<maxn];
int par[1<<maxn];
char par2[1<<maxn];
int na,ne;

void go(){
    na=ne=0;
    memset(par,-1,sizeof(int)*(1<<n));
    q[ne++]=(1<<n)-1;
    par[(1<<n)-1]=-2;
    while(na<ne){
        int a=q[na++];
        if (!a) break;
        REP(j,n) if (a&(1<<j)){
            int ns=adj[a^(1<<j)];
            if (par[ns]==-1){
                q[ne++]=ns, par[ns]=a, par2[ns]=j;
                if (!ns) goto done;
            }
        }
    }
done:;
    if (par[0]==-1) puts("Impossible");
    else{
        int x=0;
        vi lst;
        while(par[x]!=-2) lst.pb(par2[x]), x=par[x];
        
        printf("%d:",lst.size());
        for (int i=lst.size()-1; i>=0; --i) printf(" %d",lst[i]); puts("");
    }

}

int main(){
    while(cin>>n>>m,n){
        memset(adj,0,sizeof(int)*(1<<n));
        REP(i,m){int a, b; scanf(" %d%d",&a,&b); adj[1<<a]|=1<<b; adj[1<<b]|=1<<a;}
        if (m!=n-1) puts("Impossible");
        else{
            for (int i=1; i<1<<n; ++i) adj[i]|=adj[i&-i]|adj[i&(i-1)];
            go();
        }
    }

    return 0;
}

