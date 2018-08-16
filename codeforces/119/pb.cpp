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

const int maxn=61;
const int maxk=1001;

int dist[maxn][maxk];

int M[maxn][maxn][maxn];
int best[maxn][maxn];
int n, m;
vector<pair<pii,int> > dest[maxn];
int res[111111];

int main(){
    int r; cin>>n>>m>>r;
    REP(i,m) REP(j,n) REP(k,n) scanf(" %d", M[i][j]+k);

    REP(u,m) REP(k,n) REP(i,n) REP(j,n) M[u][i][j]=min(M[u][i][j],M[u][i][k]+M[u][k][j]);
    memset(best,0x7f,sizeof(best));
    REP(i,m) REP(j,n) REP(k,n) best[j][k]=min(best[j][k],M[i][j][k]);

    
    REP(i,r){
        int a, b, c; scanf(" %d%d%d", &a,&b,&c);
        --a; --b;
        dest[b].pb(MP(MP(a,c),i));
    }
    REP(d,n) if (dest[d].size()){
        memset(dist,0x7f,sizeof(dist));
        REP(i,n) dist[i][0]=best[i][d];
        REP(i,maxk-1) REP(j,n) REP(k,n) dist[k][i+1]=min(dist[k][i+1],dist[j][i]+best[k][j]);
        REP(i,dest[d].size()) res[dest[d][i].ND]=dist[dest[d][i].ST.ST][dest[d][i].ST.ND];
    }

    REP(i,r) printf("%d\n", res[i]);

    return 0;
}


