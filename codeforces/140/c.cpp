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

int mod;
ll r, l;

struct matrix{
    matrix(){memset(m,0,sizeof(m));}
    matrix(const matrix &a){memcpy(m,a.m,sizeof(m));}
    void ident(){m[0][0]=m[1][1]=1;}

    matrix operator*(const matrix &a)const{
        matrix u;
        REP(i,2) REP(j,2) REP(k,2) u.m[i][j]=(u.m[i][j]+1ll*m[i][k]*a.m[k][j])%mod;
        return u;
    }

    int m[2][2];
};

matrix faste(matrix a, ll p){
    matrix x; x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=x*a;
    return x;
}


ll have(ll x){return r/x-(l-1)/x;}

int main(){
    ll k;
    cin>>mod>>l>>r>>k;
    ll best=1;
    int u=sqrt(r);
    FOR(i,1,u+1) if (have(i)>=k) best=i;
    FOR(i,1,u+1) if (have(r/i)>=k){ best=max(best,r/i); break; }
    
    matrix x;
    x.m[0][0]=1;
    x.m[0][1]=1;
    x.m[1][0]=1;
    x=faste(x,best-1);
    cout<<x.m[0][0]%mod<<endl;
    return 0;
}

