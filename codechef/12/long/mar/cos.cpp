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

const int maxn=33;
int m, n; double x;
int vis[maxn][maxn][maxn];//used,m rem, last
double mem[maxn][maxn][maxn];
double val[maxn];

double cnk(int n, int k){
    double res=1.;
    REP(i,k) res*=1.*(n-i)/(k-i);
    return res;
}

double go(int p, int a, int b){
    if (!a) return 1.;
    if (p==m) return 0.;
    if (b>a) return 0.;

    double &r=mem[p][a][b];
    if (vis[p][a][b]) return r;
    vis[p][a][b]=1;
    r=go(p,a,b+1);

    double v=1.;
    FOR(i,1,n+1){
        v*=val[b];
        int na=a-i*b;
        if (na<0) break;
        r+=cnk(m-p,i)*go(p+i,na,b+1)*v;
    }
    return r;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>m>>n>>x;
        REP(i,n+1) val[i]=cos(i*x/n);
        memset(vis,0,sizeof(vis));
        printf("%.10lf\n", go(0,n,1));

    }
    return 0;
}


