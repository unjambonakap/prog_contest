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

int nk;
ll a[111], p[111];
ll ax[111][111];
ll best;
ll besta, bestb, bestc;
ll V;
ll lb, lb2;
ll A, B;
ll Va;


void go2(int b){
    //if (best<=B*C+A*(2*B*sqrt(C/B))) return;
    if (b==nk){
        ll C=Va/B;
        if (best>Va+A*B+A*C){best=B*C+A*B+A*C; besta=A; bestb=B; bestc=C;}
        return;
    }
    ll ob=B;
    for (int i=a[b]; i>=0; --i){
        B=ob*ax[b][i];
        if (B<lb2) go2(b+1);
    }
    B=ob;

}

set<ll> seen;
void query(ll x){
    //if (seen.count(x)) return;
    //seen.insert(x);
    double tmp=sqrt(V/x);
    if (best<=ceil(x*2*tmp+V/x)) return;
    A=x;
    Va=V/x;
    B=1;
    go2(0);
}

void go(int b, int x){
    lb2=sqrt(V/x)+1;
    
    if (b==nk){
        query(x);
        return;
    }
    int u=a[b];
    for (a[b]=0; u>=0; ++a[b],--u) if (x*ax[b][u]<lb) go(b+1,x*ax[b][u]);
    --a[b];
}

int main(){
    int tn;
    cin>>tn;
    REP(ti,tn){
        cin>>nk;
        REP(i,nk) cin>>p[i]>>a[i];
        V=1;
        REP(i,nk){
            ax[i][0]=1;
            REP(j,a[i]) ax[i][j+1]=ax[i][j]*p[i];
        }

        REP(i,nk) V*=ax[i][a[i]];
        lb=pow(V,1/3.)+2;
        best=5e18;
        seen.clear();
        go(0,1);
        cout<<2*best<<' '<<besta<<' '<<bestb<<' '<<bestc<<endl;
    }
    return 0;
}

