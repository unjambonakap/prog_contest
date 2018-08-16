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

const int maxn=1e5+10;
const int maxb=19;
const int oo=1e9;
const int mod=1e9+9;
int h[maxn];

int oh[maxn];
int rmp[maxn], tmp[maxn];
int lcp[maxn];
int A[maxn];
int X;
int n;


int cmp(int a, int b){
    int u=rmp[a], v=rmp[b];
    if (u!=v) return u<v;
    u=X+a<n?rmp[a+X]:-oo;
    v=X+b<n?rmp[b+X]:-oo;
    return u<v;
}

void go(){
    rmp[0]=oo/2;
    rmp[1]=-oo/2;
    REP(i,n) rmp[i+2]=h[i];
    n+=2;
    oh[n]=-oo;
    memcpy(oh,rmp,sizeof(int)*n);

    for (int b=1; b<maxb; ++b){
        REP(i,n) A[i]=i;
        X=1<<(b-1);
        sort(A,A+n,cmp);
        tmp[A[0]]=0;
        REP(i,n-1){
            tmp[A[i+1]]=tmp[A[i]];
            if (cmp(A[i],A[i+1])) ++tmp[A[i+1]];
        }
        memcpy(rmp,tmp,sizeof(int)*n);
    }

    memset(lcp,0,sizeof(int)*n);
    int u=0;
    A[n]=n-1;
    FOR(i,2,n){
        if (rmp[i]==n-1) assert(0);
        int j=A[rmp[i]+1];

        if (i==j) assert(0);
        if (u<0) u=0;
        for (; oh[i+u]==oh[j+u]; ++u);
        lcp[rmp[i]]=u;
        --u;
    }
    int res=0;
    FOR(i,2,n){
        res=(res+n-i)%mod;
        res=(res+mod-lcp[rmp[i]])%mod;
    }
    printf("%d\n",res);

}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %d",&n);
        REP(i,n) scanf(" %d",h+i);

        --n;
        REP(i,n) h[i]-=h[i+1];
        go();

    }

    return 0;
}

