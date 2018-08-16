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

const int mod=1e8+7;
const int maxn=366666;
int s,n;
int a[maxn];
int p[maxn];

int gcd(int a, int b){return b?gcd(b,a%b):a;}

int faste(int a, int p){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}

int go(int p){
    int res=0;
    REP(i,n) if (i%p==0){//rotation by i => num of orbits: 
        int x=gcd(n,i);
        res=(res+faste(s,x))%mod;
    }
    return 1ll*res*faste(n/p,mod-2)%mod;
}

int main(){
    int tc=0;
    while(cin>>s>>n,n!=-1){
        ++tc;
        REP(i,n) scanf(" %d",a+i);
        sort(a,a+n);
        a[n]=a[0]+360000;
        REP(i,n) a[i]=a[i+1]-a[i];

        p[0]=-1;
        p[1]=0;
        int u=-1;
        FOR(i,1,n){
            for (++u;u>=0&&a[i]!=a[u];u=p[u]);
            p[i+1]=u+1;
        }

        int x=n-p[n];
        u=p[n];
        while(u>0){
            if (u-max(p[u],0)!=x){x=n; break;}
            u=p[u];
        }

        printf("%d\n",go(x));
    }
    return 0;
}

