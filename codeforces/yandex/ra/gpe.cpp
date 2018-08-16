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
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=5005;
const int mod=1e9+7;
int x[maxn], y[maxn];
int n;
int xa, xb, ya, yb;


pii proc(){
    int res=0;
    REP(i, n){
        int va=max(x[i]-xa, y[i]-ya);
        int vb=max(xb-x[i], yb-y[i]);
        checkmax(res, min(va, vb));
    }
    int cnt=2;
    REP(i, n){
        int va=max(x[i]-xa, y[i]-ya);
        int vb=max(xb-x[i], yb-y[i]);
        if (va<=res && vb<=res) cnt=cnt*2%mod;
    }
    return MP(res, cnt);

}

int main(){
    cin>>n;
    REP(i, n){ int a, b; cin>>a>>b; x[i]=a+b; y[i]=a-b;} 
    xb=yb=INT_MIN; xa=ya=INT_MAX;
    REP(i, n){
        checkmin(xa, x[i]); checkmax(xb, x[i]);
        checkmin(ya, y[i]); checkmax(yb, y[i]);
    }
    pii a, b;
    a=proc();
    REP(i, n) y[i]=ya+yb-y[i];
    b=proc();
    int res=min(a.ST, b.ST);

    int cnt=0;
    if (res>=xb-xa || res>=yb-ya){
        if (a.ST==res) cnt=a.ND;
        else cnt=b.ND;

    }else{
        if (a.ST==res) cnt=(cnt+a.ND)%mod;
        if (b.ST==res) cnt=(cnt+b.ND)%mod;
    }
    printf("%d\n%d\n", res, cnt);

}


