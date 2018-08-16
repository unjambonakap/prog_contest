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

int pl[]={2,3,5,7};
const int maxn=44;
const int m1=60, m2=40;
uint dp0[44];
int cnk[maxn][maxn];
        //1,2,3,4,6,8,9
int vx[]={0,1,0,2,1,3,0};
int vy[]={0,0,1,0,1,0,2};

uint dp[20][20][122][82];
uint pw9[maxn], pw10[maxn];


uint go(int a, int b, int v1, int v2){
    uint &r=dp[a][b][v1][v2];
    if (r!=-1) return r;
    r=0;
    if (a){
        REP(k,7) r=r+go(a-1,b,v1-vx[k],v2-vy[k]);
    }else if (b){
        if (v1>m1 || v2>m2) return 0;
        REP(k,7) r=r+go(a,b-1,v1+vx[k],v2+vy[k]);
    }else return r=v1==m1&&v2==m2;
    return r;
}


uint solve0(int n){
    uint &r=dp0[n];
    if (r!=-1) return r;
    r=0;
    if (n<=2) return r=0;

    int ha=(n+1)/2, hb=n/2;
    REP(i,ha-1) r=r+pw9[hb+ha-1-i]*pw10[i];
    return r;
}


uint solve(int n, ll v){
    if (!v) return solve0(n);
    uint res=0;
    int tb[4]={0};
    REP(i,4) while(v%pl[i]==0) ++tb[i], v/=pl[i];
    if (v!=1) return 0;

    int ha=(n+1)/2, hb=n/2;
    int needa=tb[0]/3+tb[1]/2;

    if (ha<needa+tb[2]+tb[3]) return 0;
    int avail=min(ha-needa,hb);
    int rema=ha, remb=hb;

    REP(i5,avail+1){
        rema=ha-(tb[2]+i5);
        remb=hb-i5;
        if (rema<0) continue;
        uint mul1=cnk[hb][remb]*cnk[ha][rema];
        int avail2=min(rema-needa,remb);

        REP(i7,avail2+1){
            int rema2=rema-(tb[3]+i7), remb2=remb-i7;
            if (rema2<0) continue;
            uint mul2=mul1*cnk[rema][rema2]*cnk[remb][remb2];
            res=res+mul2*go(rema2,remb2,m1+tb[0],m2+tb[1]);
        }
    }
    return res;
}

int main(){
    int tn; cin>>tn;
    memset(dp0,-1,sizeof(dp0));
    memset(dp,-1,sizeof(dp));
    REP(i,maxn) cnk[i][0]=cnk[i][i]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=cnk[i-1][j]+cnk[i-1][j-1];

    pw9[0]=pw10[0]=1;
    REP(i,maxn-1) pw9[i+1]=pw9[i]*9;
    REP(i,maxn-1) pw10[i+1]=pw10[i]*10;

    REP(ti,tn){
        int n; ll v;
        scanf(" %d%Ld",&n,&v);
        printf("%u\n",solve(n,v));
    }
    return 0;
}

