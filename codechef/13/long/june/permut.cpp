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

const int maxn=1e6+10;
const int mod=1e9+7;

int tb[maxn];
int fact[maxn];
int powm(int a, int p){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}

int stupid(int n, int m){
    REP(i,n) tb[i]=i+1;
    int res=0;
    do{
        int ok=1;
        REP(i,n-1) if (tb[i]+tb[i+1]>m){ok=0; break;}
        res+=ok;
    }while(next_permutation(tb,tb+n));
    return res;
}

int go(int n, int m){
    int u=m-n;
    int v=n-u-1;

    int res=fact[u+1];
    res=1ll*res*powm(u,(v+1)/2)%mod*powm(u+1,v/2)%mod;
    return res;
}

int main(){
    //test(5);
    //FOR(i,3,12) test(i);

    int tn; cin>>tn;
    fact[0]=1;
    FOR(i,1,maxn) fact[i]=1ll*i*fact[i-1]%mod;

    if (0){
        FOR(i,1,10){
            printf("ROW %d >> ",i);
            FOR(j,i+1,2*i) printf("%d ",stupid(i,j));
            puts("");
        }

        FOR(i,1,10){
            FOR(j,i+1,2*i){
                printf("%d %d >> %d %d\n",i,j,go(i,j),stupid(i,j));
                assert(go(i,j)==stupid(i,j));
            }
        }
    }

    REP(ti,tn){
        int n,m; scanf(" %d%d",&n,&m);
        printf("%d\n",go(n,m));
    }

    return 0;
}

