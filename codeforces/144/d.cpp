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

const int maxn=222222;
const int maxb=20;
const int leaf=1<<maxb-1;
const int oo=1e9+10;

struct query{
    int sgn, id, T, H;
    query(int sgn, int id, int T, int H):sgn(sgn),id(id),T(T),H(H){}
};


int h[maxn];
int rmp[maxn], tmp[maxn];
int lcp[maxb][maxn];
int A[maxn];
int X;
int n;
int res[maxn];

vector<query> qw[maxn];

int cmp(int a, int b){
    int u=rmp[a], v=rmp[b];
    if (u!=v) return u<v;
    u=X+a<n?rmp[a+X]:-oo;
    v=X+b<n?rmp[b+X]:-oo;
    return u<v;
}

int tree[1<<maxb];
int get(int a){
    a+=leaf;
    int res=0;
    for (; a>1; a>>=1) if (a&1) res+=tree[a^1];
    return res;
}
void update(int a, int v){ for (a+=leaf; a; a>>=1) tree[a]+=v; }

int main(){
    cin>>n;
    int oldn=n;
    REP(i,n) scanf(" %d",h+i);
    REP(i,n-1) h[i]=h[i+1]-h[i], h[n+i]=-h[i];
    h[n-1]=-oo+1;
    n*=2;
    h[n-1]=-oo;
    REP(i,n) rmp[i]=h[i];

    for (int b=1; b<maxb; ++b){
        REP(i,n) A[i]=i;
        X=1<<(b-1);
        sort(A,A+n,cmp);
        tmp[A[0]]=0;
        REP(i,n-1){
            tmp[A[i+1]]=tmp[A[i]];
            if (cmp(A[i],A[i+1])) ++tmp[A[i+1]];
        }
        memcpy(rmp,tmp,sizeof(rmp));
    }

    int u=0;
    A[n]=n-1;
    REP(i,n-1){
        int j=A[rmp[i]+1];
        if (u<0) u=0;
        for (; h[i+u]==h[j+u]; ++u);
        lcp[0][rmp[i]]=u;
        --u;
    }
    for (int i=1; i<maxb; ++i) REP(j,n) lcp[i][j]=min(lcp[i-1][j],(j+(1<<i-1)>=n?0:lcp[i-1][j+(1<<i-1)]));

    int nq; cin>>nq;
    REP(qq,nq){
        int l, r; scanf(" %d%d",&l,&r);
        --l; --r;
        if (l==r){res[qq]=oldn-1; continue;}

        int m=r-l;
        int u=rmp[oldn+l];
        int T=u,H=u;
        for (int i=maxb-1; i>=0; --i) if (H+(1<<i)<n && lcp[i][H]>=m) H+=1<<i;
        for (int i=maxb-1; i>=0; --i) if (T-(1<<i)>=0 && lcp[i][T-(1<<i)]>=m) T-=1<<i;
        l-=m;
        if (l>=1) qw[l-1].pb(query(1,qq,T,H));
        qw[r].pb(query(-1,qq,T,H));
        qw[oldn-1].pb(query(1,qq,T,H));
    }

    REP(i,oldn){
        if (i!=oldn-1) update(rmp[i],1);
        REP(j,qw[i].size()){
            int v=get(qw[i][j].H+1)-get(qw[i][j].T);
            res[qw[i][j].id]+=v*qw[i][j].sgn;
        }
    }

    REP(i,nq) printf("%d\n",res[i]);
    return 0;
}

