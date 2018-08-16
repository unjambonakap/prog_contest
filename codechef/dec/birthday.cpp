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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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

const int maxn=111;
int dp[maxn][maxn];//road, toll
int A[maxn][maxn], B[maxn][maxn];
int n, m;


int main(){
    int tn; cin>>tn;
    REP(ti, tn){
        int D;
        cin>>D>>n>>m;

        REP(i, m) REP(j, n) scanf(" %d", &A[i][j]);
        REP(i, m) REP(j, m) scanf(" %d", &B[i][j]);
        REP(k, m) REP(i, m) REP(j, m) checkmin(B[i][j], B[i][k]+B[k][j]);


        memset(dp, 0x7f, sizeof(dp));
        REP(i, m) dp[i][1]=A[i][0];
        FOR(j, 1, n-1) REP(i, m) REP(k, m) checkmin(dp[k][j+1], dp[i][j]+A[k][j]+B[i][k]);
        int ans=INT_MAX;
        REP(i, m) checkmin(ans, dp[i][n]);
        printf("%d\n", ans>D?-1:D-ans);
    }
    return 0;


}




