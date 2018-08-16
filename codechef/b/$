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
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int mod=1000000007;
const int n=15;
struct matrix{
    matrix(){ memset(m, 0, sizeof(m)); }
    matrix(const matrix &x){ memcpy(m, x.m, sizeof(m)); } 
    void ident(){ REP(i, n) REP(j, n) m[i][j]=i==j; }

    matrix mul(const matrix &a)const{
        matrix r;
        REP(i, n) REP(j, n) REP(k, n) r.m[i][j]=(r.m[i][j]+m[i][k]*a.m[k][j])%mod;
        return r;
    }
    ll m[n][n];
};


ll fast_exp(matrix a, ll p){
    matrix x; x.ident();
    while(p){
        if (p&1) x=x.mul(a);
        p>>=1;
        a=a.mul(a);
    }
    return x.m[0][0];
}

int main(){
    int tn; cin>>tn;
    REP(ti, tn){
        ll K; cin>>K;
        int A; cin>>A;
        matrix m;
        REP(i, n-1) m.m[i][i+1]=1;
        REP(i, A){
            int b; cin>>b;
            m.m[b-1][0]=1;
        }
        ll res=fast_exp(m, K);
        cout<<res<<endl;
    }
    return 0;
}



