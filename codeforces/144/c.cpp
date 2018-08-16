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

const int maxn=83;
const ll oo=1e18;
ll u[maxn];
ll dx[maxn];
ll dp[maxn][2];
ll sa[maxn][2], sb[maxn][2];
int tb[maxn];
int tba[maxn], tbb[maxn];

ll go2n(int a);

ll go21(int a){
    if (a==0) return dp[a][0]=0;
    if (a==1) return dp[a][0]=tb[a];

    ll &r=dp[a][0];
    if (r!=-1) return r;

    if (tb[a]) r=1+go21(a-2);
    else r=min(go21(a-1),go2n(a-1)+2);
    return r;

}
ll go2n(int a){
    if (a==0) return dp[a][1]=0;
    if (a==1) return dp[a][1]=tb[a]^1;

    ll &r=dp[a][1];
    if (r!=-1) return r;

    if (tb[a]) r=go2n(a-2);
    else r=min(go21(a-1),go2n(a-1))+1+dx[a-2];
    return r;
}

ll go1(int a, int b){
    if (tba[a]) return go1(a-2,b-2);
    else if (!tbb[b]){
        ll res=go1(a-1,b-1);
        ll da1=sa[a][0], dan=sa[b][1];
        ll db1=sb[a][0], dbn=sb[b][1];

        //printf("get %Ld %Ld %Ld %Ld xx %d %d\n",da1,dan,db1,dbn,a,b);
        res=min(res,da1+db1);
        res=min(res,dan+dbn);
        res=min(res,da1+2+dbn);
        res=min(res,dan+2+db1);
        //printf(">> %Ld\n",res);
        return res;
    }

    ll da1=b==1?0:sa[a-1][0], dan=b==1?0:sa[a-1][1];
    ll db1=b==1?0:sb[b-2][0], dbn=b==1?0:sb[b-2][1];
    ll res=min(da1,dan)+1+db1;
    return res;
}


int main(){
    int tt,n; cin>>tt>>n;
    u[0]=1;
    u[1]=2;
    FOR(i,2,maxn) u[i]=u[i-1]+u[i-2];

    if (n>=maxn) n=maxn-1;

    dx[0]=0; dx[1]=1;
    memset(tb,0,sizeof(tb));
    memset(dp,-1,sizeof(dp));
    FOR(i,2,maxn) dx[i]=go2n(i);


    REP(ti,tt){
        ll a,b; 
        //scanf(" %Ld%Ld",&a,&b);
        scanf(" %I64d%I64d",&a,&b);

        ll res;
        if (a==b) res=0;
        else{
            --a; --b;
            if (b<a) swap(a,b);
            for (int i=n; i>=1; --i) if (a>=u[i-1]) tb[i]=1, a-=u[i-1], --i; else tb[i]=0;
            memset(dp,-1,sizeof(dp)); go21(n); go2n(n);
            memcpy(sa,dp,sizeof(sa)); memcpy(tba,tb,sizeof(tb));


            for (int i=n; i>=1; --i) if (b>=u[i-1]) tb[i]=1, b-=u[i-1], --i; else tb[i]=0;
            memset(dp,-1,sizeof(dp));
            go21(n); go2n(n);
            memcpy(sb,dp,sizeof(sb)); memcpy(tbb,tb,sizeof(tb));

            res=go1(n,n);
        }
        //printf("%Ld\n",res);
        printf("%I64d\n",res);

    }
    return 0;
}

