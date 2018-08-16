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
typedef unsigned int uint;
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
const int mod=1e4+7;

int dpl[maxn][maxn][maxn][2];
int dpr[maxn][maxn][maxn][2];
int tb[maxn];
int n;
int cnk[maxn][maxn];

int gol(int p, int c, int v, int f){
    if (c<0) return 0;
    if (p==-1) return c==0&&!f;

    int &r=dpl[p][c][v][f];
    if (r!=-1) return r;
    r=0;
    if (tb[p]>=v && (!f || tb[p]==v)) r+=gol(p-1,c,tb[p],0);
    r+=gol(p-1,c-1,v,f)*c;
    r%=mod;

    return r;
}
int gor(int p, int c, int v, int f){
    if (c<0) return 0;
    if (p==n) return c==0&&!f;

    int &r=dpr[p][c][v][f];
    if (r!=-1) return r;
    r=0;
    if (tb[p]<=v && (!f || tb[p]==v)) r+=gor(p+1,c,tb[p],0);
    r+=gor(p+1,c-1,v,f)*c;
    r%=mod;

    return r;
}

int main(){
    int tn; cin>>tn;
    REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

    REP(ti,tn){
        cin>>n;
        REP(i,n) scanf(" %d",tb+i);
        vi lst;
        REP(i,n) lst.pb(tb[i]);

        sort(ALL(lst));
        REP(i,n) tb[i]=lower_bound(ALL(lst),tb[i])-lst.begin();

        memset(dpl,-1,sizeof(dpl));
        memset(dpr,-1,sizeof(dpr));

        int res=0;
        REP(i,n) REP(cl,i+1) REP(cr,n-i+1){
            REP(j,n) if (j!=tb[i]) res=(res+1ll*cnk[cr+cl][cl]*gol(i-1,cl,j,j<tb[i])*gor(i+1,cr,j,j>tb[i]))%mod;
        }
        if (res==0) res=1;

        printf("Case #%d: %d\n", ti+1, res);
    }

    return 0;
}

