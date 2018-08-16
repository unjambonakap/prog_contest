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

const int maxn=1e6+10;
const int maxl=5005;
int mod;

int n, m;
ll cmk[maxl];


int A[maxl][maxl];
ll B[2][maxl];
int pl[100];
int npl;
int cntp[100];


int faste(int a, int p, int mod){
    int x=1;
    for (; p; p>>=1, a=1LL*a*a%mod) if (p&1) x=1LL*x*a%mod;
    return x;
}


int main(){
    cin>>n>>m>>mod;
    int Z=sqrt(mod)+1;
    int op=mod;
    npl=0;
    int tot=1;
    FOR(i, 2, Z) if (op%i==0){
        assert(op);
        pl[npl++]=i;
        int tmp=1;
        while(op%i==0) op/=i, tmp*=i;
        tot*=tmp-tmp/i;
    }
    if (op>1) pl[npl++]=op, tot*=op-1;

    cmk[0]=1;
    ll val=1;
    FOR(i, 1, min(m+1, maxl)){
        ll va=i, vb=m-i+1;
        REP(j, npl){
            while(va%pl[j]==0) va/=pl[j], --cntp[j];
            while(vb%pl[j]==0) vb/=pl[j], ++cntp[j];
        }
        val=val*vb%mod*faste(va, tot-1, mod)%mod;
        ll y=1;
        REP(j, npl) REP(k, cntp[j]) y=y*pl[j]%mod;
        cmk[i]=val*y%mod;
        //printf("%d << %Ld xx %Ld aa %Ld (%d %d\n", i, cmk[i], val, 1LL*va*faste(va, tot-1,mod)%mod, faste(va, tot, mod), va);
    }




    memset(A, 0, sizeof(A));
    A[1][1]=1;
    FOR(i, 2, maxl) FOR(j, 2, i+1) A[i][j]=1LL*(j-1)*(A[i-1][j]+A[i-1][j-1])%mod;
    for (int i=maxl-1; i>=2; --i)  for (int j=i; j>=2; --j) A[i][j]=1LL*j*A[i][j]%mod;


    int p=0, np=1;
    B[p][0]=1;
    int prev=0;

    REP(i, n){
        ll sum=0;
        int na; scanf("%d", &na);
        REP(j, prev+1) sum+=B[p][j];
        sum%=mod;
        REP(j, min(m, na)+1){
            ll v=sum*cmk[j]%mod*A[na][j]%mod-1LL*(j>prev?0:B[p][j])*A[na][j]%mod;
            B[np][j]=(mod+v%mod)%mod;
        }
        prev=na;
        p=np; np^=1; 
    }
    ll ans=0;
    REP(j, prev+1) ans+=B[p][j];
    cout<<ans%mod<<endl;
    return 0;
}

