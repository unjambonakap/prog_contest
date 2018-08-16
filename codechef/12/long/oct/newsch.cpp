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

const int mod=1e9+7;
struct matrix{
    int m[4][4];
    matrix(){memset(m,0,sizeof(m));}
    void ident(){REP(i,4) m[i][i]=1;}
    matrix(const matrix &a){memcpy(m,a.m,sizeof(m));}
    matrix operator*(const matrix &a)const{
        matrix b;
        REP(i,4) REP(j,4) REP(k,4) b.m[i][j]=(b.m[i][j]+1ll*m[i][k]*a.m[k][j])%mod; return b;
    }
};

matrix faste(matrix a, int p){matrix x; x.ident(); for (; p; p>>=1, a=a*a) if (p&1) x=x*a; return x;}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        int n; cin>>n;
        matrix a;
        REP(i,4) REP(j,4) if (i!=j) a.m[i][j]=1;
        a=faste(a,n-1);

        int res=0;
        REP(i,4) REP(j,4) if (i!=j) res=(res+a.m[i][j])%mod;
        cout<<res<<endl;
    }
    return 0;
}

