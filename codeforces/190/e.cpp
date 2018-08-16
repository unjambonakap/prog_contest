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

const int maxn=4444;
const int oo=1e9;
int a[maxn][maxn];
int cost[maxn][maxn];
int n,m;
int dp[2][maxn];
int *ta, *tb;
char buf[maxn*2];

void go(int lb, int ub, int l, int r){
    if (l>r) return;
    int m=l+r>>1;

    int best=oo, bestp=-1;
    int x=min(ub,m);
    for (int i=lb; i<=x; ++i){
        int c=ta[i]+cost[i][m];
        if (c<best) best=c, bestp=i;
    }
    tb[m+1]=best;
    go(lb,bestp,l,m-1);
    go(bestp,ub,m+1,r);
}


int main(){
    while(cin>>n>>m,!cin.eof()){
        fgets(buf,2*maxn,stdin);
        REP(i,n){
            fgets(buf,2*maxn,stdin);
            REP(j,n) a[i+1][j+1]=buf[2*j]-'0';
        }

        REP(i,n) REP(j,n) a[i+1][j+1]+=a[i][j+1]+a[i+1][j]-a[i][j];
        
        REP(i,n) REP(j,i) cost[j][i]=(a[i+1][i+1]-2*a[i+1][j]+a[j][j])>>1;

        memset(dp,0x1f,sizeof(dp));
        ta=dp[0]; tb=dp[1];
        ta[0]=0;
        REP(i,m){
            go(0,n-1,0,n-1);
            swap(ta,tb);
        }

        int res=ta[n];
        printf("%d\n",res);
    }
    return 0;
}

