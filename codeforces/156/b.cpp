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

const int maxn=1e6;
int n,c,x,y;

ll go(ll a, ll t){
    ++a;
    if (a>=t) return 0;
    a=t-a;
    return a*(a+1)-a; 
}

ll go2(ll a, ll t){
    a+=2;
    if (a>=t) return 0;
    a=t-a;
    return a*(a+1)/2;
}

ll get(ll M){
    ll u=M==1?1:1+2*M*(M-1);
    u-=go(x,M);
    u-=go(y,M);
    u-=go(n-x-1,M); 
    u-=go(n-y-1,M);
    u+=go2(x+y,M);
    u+=go2(n-x-1+y,M);
    u+=go2(n-x-1+n-y-1,M);
    u+=go2(x+n-y-1,M);
    return u;
}


int in(int a, int b){return a>=0 && a<n && b>=0 && b<n;}
int vx[]={1,-1,0,0};
int vy[]={0,0,1,-1};

int vis[111][111];
int checkit(){
    queue<pii> q;
    int cnt=1;

    memset(vis,0,sizeof(vis));
    q.push(MP(x,y));
    vis[x][y]=1;

    int step=0;
    while(1){
        if (cnt>=c) return step;
        ++step;
        queue<pii> nq;
        while(q.size()){
            int a=q.front().ST, b=q.front().ND;
            q.pop();
            REP(k,4){
                int nx=a+vx[k], ny=b+vy[k];
                if (in(nx,ny) && !vis[nx][ny]) ++cnt, vis[nx][ny]=1, nq.push(MP(nx,ny));
            }
        }
        q=nq;
    }
}

int solve(){
    ll T=1, H=2*n;
    int best=-1;

    while(T<=H){
        ll M=T+H>>1;
        ll u=get(M); 
        if (u>=c) best=M, H=M-1;
        else T=M+1;
    }
    return best-1;
}

int main(){
    cin>>n>>x>>y>>c;
    --x;--y;

    cout<<solve()<<endl;
    return 0;
}

