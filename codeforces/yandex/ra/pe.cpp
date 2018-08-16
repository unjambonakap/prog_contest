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

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int mod=1e9+7;
const int maxn=5000;
int x[maxn], y[maxn];
int dist[maxn][maxn];
int n;

pii z;
int ans;
int M;
int type[maxn];


inline int _dist(int a, int b){
    int c=x[a]-x[b];
    int d=y[a]-y[b];
    if (c<0) c=-c;
    if (d<0) d=-d;
    return c+d;
}

inline int dfs(int a, int t){
    if (type[a]!=-1) return type[a]!=t;

    type[a]=t;
    REP(i, n) if (dist[i][a]>M && dfs(i, t^1)) return 1;
    return 0;
     
}


int checkit(){
    int cnt=1;
    memset(type, -1, sizeof(type));
    REP(i, n) if (type[i]==-1){
        cnt=cnt*2%mod;
        if (dfs(i, 0)) return 0;
    }
    return cnt;
}


int main(){
    cin>>n;
    REP(i, n) cin>>x[i]>>y[i];
    z=MP(0, 1);
    REP(i, n) REP(j, i+1) dist[i][j]=dist[j][i]=_dist(i, j);
    REP(i, n) REP(j, i) if (dist[i][j]>dist[z.ST][z.ND]) z=MP(i, j);

    int T=0, H=dist[z.ST][z.ND];

    while(T<H){
        M=(T+H)/2;
        int res=checkit();
        if (res) H=M, ans=res;
        else T=M+1;
    }
    printf("%d\n%d\n", T, ans);
    return 0;


}

