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

const int maxn=1111;
int n, na;
vi e[maxn];
int have[maxn];
int cnt[maxn];

double cnk[maxn][maxn];

double dp[maxn][maxn];
int vis[maxn][maxn];
int tb[maxn];

double go(int a, int b){
    if (a<b) return 0;
    if (!b) return 1.;
    double &r=dp[a][b];
    if (vis[a][b]) return r;
    vis[a][b]=1;
    double u=1.*(a-b)/a;
    int x=tb[a-1];
    r=u*go(a-1,b);
    r+=(1-u)*go(a-1,b-1)*(have[x]+1)/(cnt[x]-have[x]);
    return r;
}


int main(){
    int m;
    cin>>m>>n;
    REP(i,maxn) cnk[i][0]=cnk[i][i]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=cnk[i-1][j]+cnk[i-1][j-1];

    vector<pii> l;
    REP(i,n){
        scanf(" %d",cnt+i);
        REP(j,cnt[i]){int a; scanf(" %d",&a); l.pb(MP(a,i));}
    }
    sort(ALL(l));
    reverse(ALL(l));
    int i=0;
    for (; l[i].ST!=l[m-1].ST; ++i) ++have[l[i].ND];
    int need=m-i;
    for (; l[i].ST==l[m-1].ST && i<l.size(); ++i) tb[na++]=l[i].ND;
    double px=1;
    REP(i,n) px*=1./cnk[cnt[i]][have[i]];
    px*=go(na,need);
    printf("%.15lf\n",px);
    return 0;
}

