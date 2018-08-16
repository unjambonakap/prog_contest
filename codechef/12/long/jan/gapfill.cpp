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

int faste(int a, int p){
    int x=1;
    for (; p; p>>=1, a=1LL*a*a%mod) if (p&1) x=1LL*x*a%mod;
    return x;
}

//ll A[maxn];
//int can[two(maxn)];
//ll doit(int a, int b){
//    int n=a*b;
//
//    REP(i, a) REP(j, b){
//        ll m=(two(b)-1)<<(i*b);
//        REP(k, a) m|=two(k*b+j);
//        A[i*b+j]=m;
//        //printf("%d %d >>> %d\n", i, j, m);
//    }
//    int p=0;
//    REP(i, n){
//        int x=-1;
//        FOR(j, p, n) if (A[j]&two(i)){x=j; break;}
//        if (x==-1) continue;
//        swap(A[x], A[p]); 
//        FOR(j, p+1, n) if (A[j]&two(i)) A[j]^=A[p];
//        ++p;
//    }
//
//    
//    ll u=faste(2,p);
//    //ll v=b<faste(2, a*(b-1)+1);
//    ll v=0;
//    //printf(" %d %d << %Ld(%d) %Ld\n", a,b,u,p, v);
//    return u;
//
//}

int go(ll n, ll m){
    if (n<m) swap(n,m);
    int ans;
    if (n==1) ans=2;
    else if (n&1) ans=faste(2,m/2%(mod-1)*(2*(n-1)%(mod-1))%(mod-1))*2%mod;
    else ans=faste(2,m/2%(mod-1)*(2*n%(mod-1))%(mod-1))*(m&1?2:1)%mod;
    return ans;

}

int main(){
    int tn; scanf("%d", &tn);
    REP(ti, tn){
        ll n, m; scanf("%Ld %Ld", &n, &m);
        printf("%d\n", go(n,m));
    }
    return 0;
}

