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

const int maxn=3333;
const int oo=1e9;

int dp[maxn][3][2];//pos,rem,covered
vector<pii> e[maxn];
int n;

int go(int a, int u, int f, int p=-1){
    int &r=dp[a][u][f];
    if (r!=-1) return r;

    int val[3][2], nval[3][2];
    memset(val,0x7f,sizeof(val));

    val[u][f]=0;
    if (u) val[u-1][1]=0;
    REP(i,e[a].size()){
        memset(nval,0x7f,sizeof(nval));
        int b=e[a][i].ST, nf=e[a][i].ND;
        if (b==p) continue;
        REP(j,3) REP(k,2){
            int &x=val[j][k];
            if (x>=oo) continue;
            REP(y,j+1){
                nval[y][k]=min(nval[y][k],x+go(b,j-y,1,a)+(nf==1));
                nval[y][1]=min(nval[y][1],x+go(b,j-y,0,a)+(nf==0));
            }
        }
        memcpy(val,nval,sizeof(val));
    }
    
    r=oo;
    REP(i,3) r=min(r,val[i][1]);
    return r;
}

int main(){
    while(scanf(" %d",&n)>0){
        REP(i,n-1){
            int a,b; scanf(" %d%d",&a,&b); --a; --b;
            e[a].pb(MP(b,0));
            e[b].pb(MP(a,1));
        }
        memset(dp,-1,sizeof(dp));
        int res=go(0,2,0);
        printf("%d\n",res);
        REP(i,n) e[i].clear();
    }
    return 0;
}

