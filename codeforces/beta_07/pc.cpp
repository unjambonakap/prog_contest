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
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const ll inf=5*1000000000000000000LL;

ll gcd(ll a, ll b){return !b?a:gcd(b, a%b);}
ll bezout(ll a, ll ua, ll va, ll b, ll ub, ll vb, ll &u, ll &v){
    if (!b){ u=ua; v=va; return a; }
    return bezout(b, ub, vb, a%b, ua-(a/b)*ub, va-(a/b)*vb, u, v);
}

int solve(ll a, ll b, ll c, ll &x, ll &y){
    if (abs(a)<abs(b)) return solve(b, a, c, y, x);
    if (b==0){
        if (c%a) return -1;
        x=-c/a; y=0;
        return 0;
    }
    ll d=gcd(abs(a), abs(b));
    c=-c;
    if (c%d) return 1;
    ll u, v;
    d=bezout(a, 1, 0, b, 0, 1, u ,v);
    ll ka=b/d, kb=-a/d;
    u*=c/d; v*=c/d;
    ka*=c/d; kb*=c/d;


    ll xa, xb, ya, yb;
    if (ka<0){
        xa=(u-inf)/-ka;
        xb=(u+inf)/-ka;
    }else{
        xb=(u+inf)/ka;
        xa=(u-inf)/ka;
    }
    if (kb<0){
        ya=(v-inf)/-kb;
        yb=(v+inf)/-kb;
    }else{
        yb=(v+inf)/kb;
        ya=(v-inf)/kb;
    }

    checkmax(xa, ya);
    checkmin(xb, yb);
    if (xa>xb) return 1;
    xa=(xa+xb)/2;

    x=u+ka*xa;
    y=v+kb*xa;
    return 0;
}


int main(){
    ll a, b, c;
    cin>>a>>b>>c;
    ll x, y;
    if (solve(a, b, c, x, y)) printf("-1\n");
    else cout<<x<<" "<<y<<endl;
    
    return 0;
}


