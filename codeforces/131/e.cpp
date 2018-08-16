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
const int mul=200003;
int imul;
const int maxn=222222;

ll pw[maxn];
int A[maxn], B[maxn], inv[maxn];
int n,m;


ll faste(int a, int p=mod-2){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}

struct node{
    int a, b, cnt;
    ll v;
    ll z;
    node *l, *r;
    node(int t, int h){
        a=t; b=h;
        l=r=0; v=cnt=0; z=1;
        if (t+1==h) return;
        l=new node(t,t+h>>1);
        r=new node(t+h>>1,h);
    }

    void norm(){
        v=v*z%mod;
        if (l && z!=1) l->z=l->z*z%mod, r->z=r->z*z%mod;
        z=1;
    }

    void add(int p, ll x){
        if (p<a || p>=b) return;
        norm();
        ++cnt;
        v+=x;
        if (l) l->add(p,x), r->add(p,x);
    }
    int count(int p){
        if (p<a) return 0;
        if (p+1>=b) return cnt;
        return l->count(p)+r->count(p);
    }

    ll mul(int t, int h, int x){
        norm();
        if (h<=a || t>=b) return v;
        if (t<=a && b<=h) z=z*x%mod;
        else v=l->mul(t,h,x)+r->mul(t,h,x);
        return v*z%mod;
    }
    int rem(int p){
        norm();
        if (p<a || p>=b) return 0;
        --cnt;
        int u=l?l->rem(p)+r->rem(p):v;
        v=(v+mod-u)%mod;
        return u;
    }

};


int main(){
    pw[0]=1;
    FOR(i,1,maxn) pw[i]=pw[i-1]*mul%mod;
    imul=faste(mul);

    cin>>n>>m;
    REP(i,n) scanf(" %d", A+i), --A[i];
    REP(i,m) scanf(" %d", B+i), --B[i];
    REP(i,m) inv[B[i]]=i;


    ll add=0; REP(i,n) add+=pw[i]; add%=mod;
    ll H=0; REP(i,n) H+=(A[i]+1)*pw[i]%mod;
    H%=mod;

    node r(0,m);
    int cnt=0;
    REP(i,m) if (B[i]<n) r.add(i, pw[cnt++]*(B[i]+1)%mod);
    
    int res=0;
    REP(i,m-n+1){
        //printf("HAVE %Ld %Ld\n", H, r.v*r.z%mod);
        if (H==r.v*r.z%mod) ++res;
        H+=add;
        if (H>=mod) H-=mod;


        r.rem(inv[i]);
        r.mul(inv[i]+1,m,imul);
        if (i<m-n) r.mul(inv[i+n]+1,m,mul), r.add(inv[i+n],pw[r.count(inv[i+n])]*(i+n+1)%mod);
        
        
    }


    cout<<res<<endl;
    return 0;
}


