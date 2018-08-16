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

const int maxn=111;
ll dp[11][maxn][maxn][2];//ndigit,factors,sum wanted 
map<int,ll> dpb[11][maxn];
int g[maxn][10];
int can[maxn];
int MASK;
int gcd(int a, int b){if (a<b) return gcd(b,a); return b?gcd(b,a%b):a;}


ll go(int a, int b, int c, int f=0){
    if (c<0) return 0;
    if (!a) return b==1&&!c;
    ll &r=dp[a][b][c][f];
    if (r!=-1) return r;
    r=0;
    REP(i,10) if (f||i) r+=go(a-1,g[b][i],c-i,1);
    return r;
}

ll go(int a){
    ll res=0;
    FOR(i,1,maxn) res+=go(a,i,i,0);
    return res;
}

ll gob(int a, int s, int f){
    if (dpb[a][s].count(f)) return dpb[a][s][f];
    ll &r=dpb[a][s][f];
    r=0;
    FOR(j,max(1,s),maxn) r+=go(a,j/gcd(j,f),j-s,1);
    return r;
}
ll build(int k, int na, int f=1, int s=0, ll prev=0){
    if (!na) return prev;
    REP(i,10) if (i||s){
        int nf=f*i?gcd(f*i,MASK):0;
        ll cnt=gob(na-1,s+i,nf);
        if (cnt<k) k-=cnt;
        else return build(k,na-1,nf,s+i,prev*10+i);
    }
    assert(0);
}

ll gogo(int n){
    FOR(i,1,11){
        ll x=go(i);
        if (x<n) n-=x;
        else return build(n,i);
    }
}

int checkit(int a){
    int s=0, f=1;
    while(a) s+=a%10, f*=a%10, a/=10;
    return f%s==0;
}

int main(){
    memset(dp,-1,sizeof(dp));
    int n; 
    FOR(i,1,maxn) REP(j,10) g[i][j]=i/gcd(i,j);
    MASK=64*81*25*49;

    //int last=1;
    //REP(i,2e4)if (i){
    //    if (checkit(i)){
    //        printf("%d >> %d %Ld\n", last, i, gogo(last));
    //        assert(i==gogo(last));
    //        ++last;
    //    }
    //}
    //return 0;

    while(scanf(" %d", &n), n){
        printf("%Ld\n", gogo(n));
    }
    return 0;
}



