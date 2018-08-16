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

const double eps=1e-7;
const double oo=1e9;

int gcd(int a, int b){return b?gcd(b,a%b):a;}

int main(){
    freopen("caravan.in","r",stdin);
    freopen("caravan.out","w",stdout);
    int n;
    cin>>n;
    vector<pii> tb;
    REP(i,n){
        int a, b; scanf(" %d%d",&a,&b);
        tb.pb(MP(a,b));
    }

    sort(ALL(tb));
    double T=0,H=1e6+10;
    int a,b;
    a=b=0;
    double best=oo;
    REP(step,100){
        double M=(T+H)/2;
        int ok=1;
        double pos=0;
        int last=0;

        REP(i,n){
            if (pos<tb[i].ST) last=i, pos=tb[i].ST;
            pos+=M;
            if (pos>tb[i].ND){ok=0; break;}
            if (tb[i].ND-pos<best) best=tb[i].ND-pos, a=tb[i].ND-tb[last].ST, b=i-last+1;
        }

        if (ok) T=M;
        else H=M;
    }
    assert(b);
    int d=gcd(max(a,b),min(a,b));
    a/=d; b/=d;
    printf("%d/%d\n",a,b);

    return 0;
}

