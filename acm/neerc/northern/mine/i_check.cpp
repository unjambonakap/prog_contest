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

const int maxn=20;
int g[maxn][maxn];
int n, m;

int geta(int ec){
    int c, nc; cin>>c;
    int a, b;

    int d;
    int seen;
    int p;


    cin>>a;
    nc=0;
    d=0;
    seen=1;
    cin>>p;
    if (p--!=1) return ec;
    REP(i, a){
        int x; cin>>x;
        --x;
        d+=g[p][x];
        seen|=two(x);
        p=x;
    }
    checkmax(nc, d);
    d=0;
    cin>>a; cin>>p;
    if (p--!=1) return ec;
    REP(i, a){
        int x; cin>>x;--x;
        d+=g[p][x];
        seen|=two(x);
        p=x;
    }
    checkmax(nc, d);
    if (seen!=two(n)-1) return ec;
    return nc;
}

int main(){
    cin>>n>>m;
    memset(g, 1, sizeof(g));
    REP(i, n) g[i][i]=0;
    REP(i, m){
        int a, b, c; cin>>a>>b>>c;
        --a; --b;
        g[a][b]=g[b][a]=c;
    }

    if (geta(-2)!=geta(-1)) return 1;
    return 0;
}
