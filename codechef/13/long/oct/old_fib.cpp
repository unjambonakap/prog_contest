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
typedef unsigned int uint;
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

int MOD;
const int n=2;
const int maxn=1e5;


struct matrix{
    int m[n][n];
    matrix(){memset(m,0,sizeof(m));}
    void ident(){REP(i,n) REP(j,n) m[i][j]=i==j;}

    matrix(const matrix &a){memcpy(m,a.m,sizeof(m));}

    matrix operator*(const matrix &a)const{
        matrix res;
        REP(i,n) REP(j,n){
            ll v=0;
            REP(k,n) v=v+1ll*m[i][k]*a.m[k][j];
            res.m[i][j]=v%MOD;
        }
        return res;
    }
};

matrix faste(matrix a, int p){
    matrix x; x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=a*x;
    return x;
}


int pl[maxn];
int is[maxn];
int np;


vector<pii> go(int a){
    vector<pii> res;
    REP(i,np){
        if (pl[i]*pl[i]>a) break;
        int cnt=0;
        while(a%pl[i]==0) a/=pl[i], ++cnt;
        res.pb(MP(pl[i],cnt));
    }
    return res;
}

int main(){
    memset(is,1,sizeof(is));

    np=0;
    FOR(i,2,maxn) if (is[i]){
        if (1.*i*i>maxn) break;
        for (int j=i*i; j<maxn; j+=i) is[j]=0;
        pl[np++]=i;
    }



    int tn; cin>>tn;
    REP(ti,tn){
        int p,c; scanf(" %d%d",&p,&c);
        vector<pii> factor=go(p-1);

    }

    return 0;
}

