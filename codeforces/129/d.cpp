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


const int mod=1e9+7;
const int maxn=1111111;

int n,k;
char a[maxn];
int Fx[maxn], Fa[maxn], Fb[maxn];
int A[maxn], B[maxn];
int val[maxn];

int cnta(int l, int r){return Fa[r]-Fa[l];}
int cntb(int l, int r){return Fb[r]-Fb[l];}
int cntx(int l, int r){return Fx[r]-Fx[l];}


int goa(int p){
    if (p<0) return 1;
    int &r=A[p];
    if (r!=-1) return r;
    r=goa(p-1);
    if (a[p]=='X') r*=2;

    if (p-k>=-1) if (cntb(p-k+1,p+1)==0 && (p-k==-1 || a[p-k]!='a')) r-=goa(p-k-1);
    if (r<0) r+=mod;
    if (r>=mod) r-=mod;
    return r;
}


int gob(int p){
    if (p>=n) return 1;
    int &r=B[p];
    if (r!=-1) return r;
    r=gob(p+1);
    if (a[p]=='X') r*=2;

    if (p+k<=n) if (cnta(p,p+k)==0 && (p+k==n || a[p+k]!='b')) r-=gob(p+k+1);
    if (r<0) r+=mod;
    if (r>=mod) r-=mod;
    return r;

}


int main(){
    cin>>n>>k;
    scanf(" %s", a);
    REP(i,n) if (a[i]=='B') a[i]='a'; else if (a[i]=='W') a[i]='b';
    REP(i,n) Fx[i+1]=Fx[i]+(a[i]=='X');
    REP(i,n) Fa[i+1]=Fa[i]+(a[i]=='a');
    REP(i,n) Fb[i+1]=Fb[i]+(a[i]=='b');

    ll s=0;
    memset(A,-1,sizeof(A));
    memset(B,-1,sizeof(B));

    int u=1;
    FOR(i,k,n-k+1){
        if (cnta(i,i+k)) val[i]=0;
        else val[i]=i+k<n && a[i+k]=='b'?0:gob(i+k+1);
        s+=1ll*u*val[i], s%=mod;
        if (a[i]=='X') u=2*u%mod;
    }
    ll res=0;
    REP(i,n-2*k+1){
        if (!cntb(i,i+k) && (!i || a[i-1]!='a')) res+=1ll*s*goa(i-2), res%=mod;
        s-=val[i+k];
        if (s<0) s+=mod;
        if (a[i+k]=='X') s=s*(mod+1)/2%mod;
    }
    cout<<res<<endl;
    return 0;
}


