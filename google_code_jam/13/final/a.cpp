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

const int maxc=1111;
int c;
ll x,n;
ll s[maxc], e[maxc], t[maxc];

struct data{
    ll s,t,dt;
    data(ll s, ll t, ll dt):s(s),t(t),dt(dt){}
    bool operator<(const data &d)const{return t<d.t;}
};

ll rot1(ll p, ll t){return (n+(p-t)%n)%n;}
ll rot2(ll p, ll t){return (p+t)%n;}

ll go(ll p, ll tt){
    ll res=x;
    REP(i,c){
        if (e[i]<tt) continue;
        ll st=max(tt,t[i]);

        ll p1=rot1(p,st-tt);
        if (p1<0) p1+=n;

        ll p2=rot2(s[i],st-t[i]);


        ll dt=e[i]-st;
        ll x1=(n+p1-p2)%n;
        REP(f,2){
            if (x1%2==0 && x1/2<=dt) res=min(res,st+x1/2-1);
            ++x1;
        }
    }

    return res-tt;
}


ll go0(){
    ll res=0;
    if (c==0) return x;
    REP(i,c) res=max(res,go((2*n+s[i]+2*(e[i]-s[i]))%n,0));
    REP(i,n) res=max(res,go(i,0));
    return res;
}

int main(){
    int tn; cin>>tn;

    REP(ti,tn){
        cin>>c>>x>>n;
        REP(i,c) scanf(" %Ld%Ld%Ld",s+i,e+i,t+i);

        REP(i,c) --s[i], --e[i];
        REP(i,c) e[i]=t[i]+(n+e[i]-s[i])%n;

        ll res=0;
        REP(i,c) res=max(res,go(s[i],t[i]+1));
        REP(i,n) REP(j,x) res=max(res,go(i,j));
        res=max(res,go0());

        printf("Case #%d: %Ld\n",ti+1,res);
    }

    return 0;
}

