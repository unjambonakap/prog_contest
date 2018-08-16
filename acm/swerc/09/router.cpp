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

const int maxn=(1<<13)+10;

int a[maxn], b[maxn];

int res[33][maxn];
int rmpa[maxn], rmpb[maxn];
int *aa, *bb;
int xx, yy, nn, nnn;
int tmp[maxn];

void dfs(int u, int f){
    if (u&1) f^=1;
    u>>=1;
    if (res[xx][yy+u]!=-1) return;
    
    res[xx][yy+u]=f;
    int a=aa[2*u+f], b=aa[2*u+1-f];
    int c=rmpb[a], d=rmpb[b];
    res[xx+2*nnn-2][yy+(c/2)]=c&1;
    res[xx+2*nnn-2][yy+(d/2)]=(d^1)&1;
    dfs(rmpa[bb[c^1]],1); dfs(rmpa[bb[d^1]],0);
}

void go(int n, int x, int y, int *a, int *b){
    if (n==1){ res[x][y]=a[0]!=b[0]; return; }

    REP(i,1<<n) rmpa[a[i]]=i, rmpb[b[i]]=i;
    aa=a; bb=b;
    xx=x; yy=y; nn=1<<n-1;
    nnn=n;

    int N=1<<n-1;
    REP(i,N) if (res[x][y+i]==-1) dfs(2*i,0);
    memcpy(tmp,a,sizeof(int)*2*N);
    REP(i,N){
        int u=tmp[2*i], v=tmp[2*i+1];
        int da=i, db=i+N;
        if (res[x][y+i]) swap(u,v);
        a[da]=u; a[db]=v;
    }

    
    memcpy(tmp,b,sizeof(int)*2*N);
    REP(i,N){
        int u=tmp[2*i], v=tmp[2*i+1];
        int da=i, db=i+N;
        if (res[x+2*n-2][y+i]) swap(u,v);
        b[da]=u; b[db]=v;
    }
    go(n-1,x+1,y,a,b);
    go(n-1,x+1,y+N/2,a+N,b+N);
}

int main(){
    int n;
    int st=0;
    while(cin>>n,n){
        if (st) puts(""); st=1;

        REP(i,1<<n) a[i]=i;
        REP(i,1<<n) scanf(" %d",b+i);
        memset(res,-1,sizeof(res));
        go(n,0,0,a,b);
        REP(i,2*n-1){ REP(j,1<<n-1) printf("%d",res[i][j]); puts("");}
    }
    return 0;
}

