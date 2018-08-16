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

const int maxm=22222222;
int na, nb, m, r;
int a[111111], b[111111];
ll F[111111], G[111111];
char u[maxm];

void doit(int *a, ll *res, int na){

    int x=0;
    ll w=0;
    REP(i,m){
        x+=a[i];
        u[i]=min(na+1,x);
        x-=u[i];
        w+=x;
    }
    int last=m;
    while(x>=na) x-=na, w+=x, ++last;
    int rem=x;
    
    vi slot;
    res[m]=w;
    REPV(i,m){
        if (u[i]>na){
            if (slot.size()) w+=slot.back()-i, slot.pop_back();
            else{ if (rem==na) ++last, rem=0; w+=last-i, ++rem; }
        }else FOR(j,u[i],na) slot.pb(i);
        res[i]=w;
    }
}

void doitb(int *a, ll *res, int na){

    int x=0;
    ll w=0;
    vi slot;
    memset(u,0,sizeof(u));
    REP(i,m){
        x+=a[i];
        int can=na+(i>=r);
        int use=min(can,x);
        u[i]=use;
        FOR(j,use,can) slot.pb(i);
        x-=use;
        w+=x;
    }
    int last=m;
    while(x>=na+1) u[last]=na+1, x-=na+1, w+=x, ++last;
    int rem=x;
    u[last]=x;

    reverse(ALL(slot));
    
    res[0]=w;
    FOR(i,r,m+r){
        while(slot.size()&&slot.back()<=i) slot.pop_back();
        int v=u[i];
        while(v>na){
            checkmax(last,i+1);
            if (slot.size()){
                ++u[slot.back()];
                w+=slot.back()-i, slot.pop_back();
            }
            else{ if (rem>=na+1) ++last, rem=0; ++u[last]; w+=last-i, ++rem; }
            --v;
        }
        res[i-r+1]=w;
    }
}

int main(){
    cin>>na>>nb>>m>>r;
    REP(i,m) scanf(" %d%d", a+i, b+i);

    doit(a,F,na);
    doitb(b,G,nb);
    ll res=1e18;
    int best=0;
    REP(i,m) if (F[i]+G[i]<res) res=F[i]+G[i], best=i;

    cout<<best+1<<endl;
    return 0;
}



