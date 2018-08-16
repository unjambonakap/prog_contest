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

const int maxb=64;
const int maxn=1e5+maxb+10;

ll x[maxn];
ll a[maxb][maxn/maxb];
ll b[maxb][maxn/maxb];
int dst[maxb];
int dstb[maxb];

int res[maxn];
int st[maxb];

int n;

int solve(int m){
    memcpy(a,b,sizeof(a[0])*m);
    memcpy(dst,dstb,sizeof(dst));
    int u=0;
    int nb=(n+maxb-1)/maxb;

    REP(i,n){
        int p=-1;
        FOR(j,u,m) if (a[j][i>>6]&(1ll<<(i&0x3f))){p=j; break;}
        if (p==-1) continue;
        REP(j,nb) swap(a[u][j],a[p][j]);

        swap(dst[u],dst[p]);
        st[u]=i;

        
        REP(j,m) if (j!=u && (a[j][i>>6]&(1ll<<(i&0x3f)))){
            REP(k,nb) a[j][k]^=a[u][k];
            dst[j]^=dst[u];
        }
        ++u;
    }

    FOR(j,u,m) if (dst[j]) return 0;
    memset(res,-1,sizeof(res));
    
    REP(p,u){
        int v=dst[p];
        FOR(j,st[p]+1,n) if (a[p][j>>6]&(1ll<<(j&0x3f))){
            if (res[j]==-1) res[j]=0;
            v^=res[j];
        }
        res[st[p]]=v;

    }

    REP(i,n) if (res[i]==-1) res[i]=1;

    return 1;
}


int main(){

    cin>>n;
    REP(i,n) scanf(" %I64d",x+i);
    //REP(i,n) scanf(" %Ld",x+i);

    int u=0;
    REPV(i,maxb){
        

        int m=0;
        memset(b[u],0,sizeof(b[u]));
        REP(j,n) if (x[j]&(1ll<<i)) b[u][j>>6]|=1ll<<(j&0x3f), ++m;
        if (!m) continue;
        if (m&1) continue;
        ++u;

        dstb[u-1]=1;
        if (solve(u)) continue;

        --u; continue;

        dstb[u-1]=0;
        assert(solve(u));//just checking :)
    }
    REPV(i,maxb){
        

        int m=0;
        memset(b[u],0,sizeof(b[u]));
        REP(j,n) if (x[j]&(1ll<<i)) b[u][j>>6]|=1ll<<(j&0x3f), ++m;
        if (!(m&1)) continue;
        ++u;

        dstb[u-1]=1;
        if (solve(u)) continue;
        --u; continue;

        dstb[u-1]=0;
        assert(solve(u));//just checking :)
    }
    solve(u);
    REP(i,n){
        if (i) printf(" ");
        printf("%d",1+res[i]);
    }
    
    puts("");


    return 0;
}

