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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=1010;
const long double eps=1e-9;

int n;
long double prob[maxn];
long double fact[maxn], factb[maxn];
long double cnk[maxn][maxn];

long double solve(int a){
    if (a==0) return 0.;
    if (a==1) return 0.;
    long double &r=prob[a];
    if (r>-eps) return r;
    long double pa;
    r=0.;
    pa=0.;

    REP(i, a) r+=(1+solve(i))*factb[i]*cnk[a][a-i], pa+=factb[i]*cnk[a][a-i];
    

    r/=fact[a];
    pa/=fact[a];
    assert(pa>eps);
    r+=(1-pa);
    r/=pa;

    if (r<0.) r=0.;
    return r;


}

int main(){
    int tn;
    fact[0]=1.;
    FOR(i, 1, maxn-1) fact[i]=fact[i-1]*i;
    memset(cnk, 0, sizeof(cnk));
        cnk[0][0]=1.;
    FOR(i, 1, maxn-1){
        cnk[i][0]=1.;
        FOR(j, 1, i) cnk[i][j]=cnk[i-1][j-1]+cnk[i-1][j];
    }
    factb[0]=1; factb[1]=0;
    FOR(i, 2, maxn-1){
        factb[i]=fact[i];
        FOR(j, 1, i) factb[i]-=factb[i-j]*cnk[i][j];
    }


    REP(i, maxn) prob[i]=-1.;

    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        int cnt=0;
        REP(i, n){
            int a;
            cin>>a;
            if (a!=i+1) ++cnt;
        }


        printf("Case #%d: %Lf\n", ti, solve(cnt));

    }
    return 0;


}


