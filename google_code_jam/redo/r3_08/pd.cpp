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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int mod=10007;
const int maxw=1e8;
const int maxh=1e8;
const int maxn=15;

int n;
int w, h;
pii rock[maxn];
int fact[mod];
int ifact[mod];


int _cnk(int n, int k){
    if (n<k) return 0;
    return ((fact[n]*ifact[k])%mod*ifact[n-k])%mod;
}
int cnk(int n, int k){
    assert(n>=k);
    //if (n<k) return 0;
    int res=1;
    while(n) res=res*_cnk(n%mod, k%mod)%mod, n/=mod, k/=mod;
    return res;
}

int fast_exp(int a, int p){
    int b=1;
    while(p){
        if (p&1) b=(b*a)%mod;
        a=(a*a)%mod;
        p>>=1;
    }
    return b;

}


/*
 *
 * 2a+b=x
 * a+2b=y
 * 3b=2y-x
 * a=y-2b
 * */
int solve(int m){
    int x=0, y=0;
    int cnt=1;
    REP(j, n) if (m&two(j)){
        int nx=rock[j].ST, ny=rock[j].ND;
        if (nx<x || ny<y) return 0;

        cnt=cnt*cnk(nx-x+ny-y, nx-x)%mod;
        x=nx; y=ny;

    }
    if (x>w || y>h) return 0;

    return cnt*cnk(w-x+h-y, w-x)%mod;


}

int main(){
    int tn;
    cin>>tn;
    fact[0]=1;
    ifact[0]=1;
    FOR(i, 1, mod-1) fact[i]=(fact[i-1]*i)%mod, ifact[i]=fast_exp(fact[i], mod-2);

    FOR(ti, 1, tn){
        cin>>w>>h>>n;
        --w; --h;
        int pos=0;
        REP(i, n){
            cin>>rock[pos].ST>>rock[pos].ND;
            --rock[pos].ST;
            --rock[pos].ND;
            int tmp=2*rock[pos].ND-rock[pos].ST;
            if (tmp%3!=0) continue;
            tmp/=3;

            rock[pos].ST=rock[pos].ND-2*tmp;
            rock[pos].ND=tmp;
            ++pos;
        }
        n=pos;
        sort(rock, rock+n);
        int res=0;
        int tmp=2*h-w;
        if (tmp%3==0){
            tmp/=3;
            w=h-2*tmp;
            h=tmp;
            REP(i, two(n)) res=(mod+res+solve(i)*(count_bit(i)&1?-1:1))%mod;
        }

        printf("Case #%d: %d\n", ti, res);
    }

    return 0;
}

