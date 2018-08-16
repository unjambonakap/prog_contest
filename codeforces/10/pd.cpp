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

const int maxn=555;
int A[maxn], B[maxn];
int n, m;
int dp[maxn][maxn];
vi nxta[maxn], nxtb[maxn];

int solve(int a, int b){
    if (a==n || b==m) return 0;
    int &r=dp[a][b];
    if (r!=-1) return r;
    if (A[a]!=B[b]) return r=solve(a, b+1);
    r=1;
    FOR(i, a+1, n) if (A[i]>A[a]) checkmax(r, solve(i, b+1)+1);
    return r;
}
void build(int a, int b){
    if (a==n || b==m) return;
    int r=dp[a][b];
    if (A[a]!=B[b]) return build(a, b+1);
    printf("%d ", A[a]);
    FOR(i, a+1, n) if (A[i]>A[a] && solve(i, b+1)+1==r){ build(i, b+1); return;}

}
int main(){
    cin>>n;
    REP(i, n) cin>>A[i];
    cin>>m;
    REP(i, m) cin>>B[i];

    memset(dp, -1, sizeof(dp));
    int best=-1;
    REP(i, n) checkmax(best, solve(i, 0));
    cout<<best<<endl;
    REP(i, n) if (solve(i, 0)==best){build(i, 0); break;}
    printf("\n");
    return 0;
}


