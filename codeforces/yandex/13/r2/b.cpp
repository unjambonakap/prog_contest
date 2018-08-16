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

const int maxp=1e5+10;
const int maxm=11;
int x,mod,k,m;
ll d;
int xp[maxp];
int sum[maxm][maxp];
int next[maxm];

int seen[maxm];


ll go(ll a){

    memset(seen,0,sizeof(seen));
    ll res=0;

    int cur=1;
    vi tb;
    while(1){
        if (!a) return res;
        if (seen[cur]) break;
        seen[cur]=1;
        tb.pb(cur);

        int x=min(1ll*mod-1,a);
        int vx=sum[cur][x];
        a-=x;
        res+=vx;
        cur=next[cur];
    }
    ll n=tb.size()*(mod-1);
    ll r=a/n;

    a-=r*n;
    res+=r*res;

    while(1){
        if (!a) return res;

        seen[cur]=1;
        tb.pb(cur);

        int x=min(1ll*mod-1,a);
        a-=x;
        int vx=sum[cur][x];
        res+=vx;
        cur=next[cur];
    }

    assert(0);
}

int main(){
    while(cin>>x>>mod>>k>>m>>d,!cin.eof()){

        xp[0]=1;
        REP(i,mod) xp[i+1]=1ll*xp[i]*x%mod;

        REP(i,mod-1) xp[i]=xp[i]%m;


        REP(i,m){
            int u=i;
            REP(j,mod-1){
                sum[i][j+1]=sum[i][j];
                u=(u+xp[j+1])%m;
                sum[i][j+1]+=u==0;
            }
            next[i]=u;
        }



        ll T=0, H=1e18;
        ll best=H;
        while(T<=H){
            ll M=T+H>>1;
            ll v=M;
            REP(i,k-1) v=go(v);
            if (M-v>=d) H=M-1, best=M;
            else T=M+1;

        }
        cout<<best<<endl;
    }

    return 0;
}

