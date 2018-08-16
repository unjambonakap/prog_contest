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

const int maxn=222;
double dp[maxn][2*maxn][maxn];
int vis[maxn][2*maxn][maxn];
double px[maxn];
int A[maxn];
int n;

double go(int a, int b, int c){
    if (a==n) return !c&&b>=maxn?1.:0.;
    double &r=dp[a][b][c];
    if (vis[a][b][c]) return r;
    vis[a][b][c]=1;
    if (A[a]==-1) r=go(a+1,b-1,max(0,c-1))*px[a]+(1-px[a])*go(a+1,b,c);
    else r=go(a+1,min(2*maxn-1,b+A[a]),max(0,c-1))*px[a]+(1-px[a])*go(a+1,b,c);
    return r;

}

int main(){
    int k, l;
    cin>>n>>l>>k;
    REP(i,n) cin>>px[i], px[i]/=100;
    REP(i,n) cin>>A[i];
    printf("%.10lf\n",go(0,maxn+k,l));
    return 0;
}

