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
const int oo=maxn*maxn;
int n,m;
char A[maxn][maxn];
int dp[maxn][maxn][2];

int go(int a, int b, int f){
    if (a==n-1 && b==m-1) return 0;
    int &res=dp[a][b][f];
    if (res!=-1) return res;
    int d=a<n-1?A[a+1][b]:0;
    int r=b<m-1?A[a][b+1]:0;

    res=oo;
    if (a<n-1){
        int nc=d+r;
        if (b && f==0) nc+=A[a+1][b-1];
        res=min(res,nc+go(a+1,b,0));
    }

    if (b<m-1){
        int nc=d+r;
        if (a && f==1) nc+=A[a-1][b+1];
        res=min(res,nc+go(a,b+1,1));
    }
    return res;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %d%d",&n,&m);
        REP(i,n) scanf(" %s",A[i]);
        REP(i,n) REP(j,m) A[i][j]-='0';
        memset(dp,-1,sizeof(dp));
        printf("%d\n",go(0,0,0)+A[0][0]);
    }
    return 0;
}

