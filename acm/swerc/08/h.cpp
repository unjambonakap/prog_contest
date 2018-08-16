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

const int maxn=1001;
int n,s,l,r,mod;
int v[maxn];

struct matrix{
    int a[maxn];
    matrix(){memset(a,0,sizeof(a));}
    void ident(){a[0]=1;}
    matrix(const matrix &b){memcpy(a,b.a,sizeof(a));}

    matrix operator*(const matrix &b)const{
        matrix x;
        REP(j,n) REP(k,n) x.a[j]=(x.a[j]+1ll*a[k]*b.a[(j+n-k)%n])%mod;
        return x;
    }
};

matrix faste(matrix a, int p){
    matrix x; x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=a*x;
    return x;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        int tmp;
        scanf(" %d%d%d%d%d",&n,&s,&l,&r,&tmp);
        REP(i,n) scanf(" %d",v+i);
        mod=1;
        REP(i,tmp) mod*=10;
        matrix m;
        m.a[0]=1;
        m.a[1]=r;
        m.a[n-1]=l;
        m=faste(m,s);
        REP(i,n){
            int res=0;
            REP(j,n) res=(res+1ll*m.a[j%n]*v[(i+j)%n])%mod;
            printf("%d",res);
            if (i<n-1) printf(" ");
        }
        puts("");

    }
    return 0;
}

