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

const int maxn=11;
const int maxv=1111;
typedef pair<ll,ll> pll;


map<ll,vector<pll> > lx, ly;

int gox(ll xa, ll xb, ll y){
    vector<pll> A;
    FE(it,lx[y]) A.pb(*it);
    sort(ALL(A));
    A.pb(pll(1e18,1e18));
    ll nd=xa-1;
    map<ll,vector<pll> >::iterator itx=ly.begin();
    int cnt=0;
    REP(i,A.size()){
        if (A[i].ST<=nd+1) checkmax(nd,A[i].ND);
        else{
            ll ub=min(A[i].ST-1,xb);
            cnt+=ub-nd;
            while(itx!=ly.end() && itx->ST<=nd) ++itx;
            while(itx!=ly.end() && itx->ST<=ub){
                int fd=0;
                REP(j,itx->ND.size()) if (itx->ND[j].ST<=y &&itx->ND[j].ND>=y){fd=1; break;}
                cnt-=fd;
                ++itx;
            }
            nd=A[i].ND;

        }
        if (nd>=xb) break;
    }
    return cnt;

}

int goy(ll ya, ll yb, ll x){
    vector<pll> A;
    FE(it,ly[x]) A.pb(*it);
    sort(ALL(A));
    ll nd=ya-1;
    map<ll,vector<pll> >::iterator itx=lx.begin();
    A.pb(pll(1e18,1e18));

    int cnt=0;
    REP(i,A.size()){
        if (A[i].ST<=nd+1) checkmax(nd,A[i].ND);
        else{
            ll ub=min(yb,A[i].ST-1);
            cnt+=ub-nd;
            while(itx!=lx.end() && itx->ST<=nd) ++itx;
            while(itx!=lx.end() && itx->ST<=ub){
                int fd=0;
                REP(j,itx->ND.size()) if (itx->ND[j].ST<=x && itx->ND[j].ND>=x){fd=1; break;}
                cnt-=fd;
                ++itx;
            }
            nd=A[i].ND;
        }
        if (nd>=yb) break;
    }
    return cnt;

}

int main(){
    int n; cin>>n;
    ll x=0, y=0;
    REP(i,n){
        char d; int u; scanf(" %c %d", &d,&u);
        int cnt=0;
        if (d=='U') cnt=goy(y+1,y+u,x);
        else if (d=='D') cnt=goy(y-u,y-1,x);
        else if (d=='R') cnt=gox(x+1,x+u,y);
        else if (d=='L') cnt=gox(x-u,x-1,y);



        if (d=='U') ly[x].pb(pll(y,y+u)), y+=u;
        else if (d=='D') ly[x].pb(pll(y-u,y)), y-=u;
        else if (d=='R') lx[y].pb(pll(x,x+u)), x+=u;
        else if (d=='L') lx[y].pb(pll(x-u,x)), x-=u;

        printf("%d\n",cnt);

    }
    return 0;
}



