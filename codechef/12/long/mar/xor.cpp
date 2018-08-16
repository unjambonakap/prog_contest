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


const int maxn=111111;

int a[maxn];
int getn[maxn];
vi res;

void gob(int **tb, int *nx, int n, unsigned int d, int k){
    //printf("XAXA %u %d >>\n", d, k);
    //for (int i=0; i<tb.size(); i+=2){
    //    printf("pairs:\n");
    //    out(*tb[i]);
    //    out(*tb[i+1]);

    //}
    if (!d){
        int fuu=0;
        for (int i=0; i<n; i+=2) REP(j,nx[i]) REP(l,nx[i^1]){
            res.pb(tb[i][j]^tb[i^1][l]);
            if (++fuu==k) return;
        }
        return;
    }
    
    int cnt=0;
    int **ntb=(int**)malloc(sizeof(void*)*2*n);
    int *nnx=(int*)malloc(sizeof(void*)*2*n);
    int na=0;
    assert(ntb); assert(nnx);
    for (int i=0; i<n; i+=2) if (nx[i]&&nx[i^1]){
        int *ua, *ub, *va, *vb;
        ua=(int*)malloc(nx[i]*4); va=(int*)malloc(nx[i]*4);
        ub=(int*)malloc(nx[i^1]*4); vb=(int*)malloc(nx[i^1]*4);
        int nua=0, nva=0, nub=0, nvb=0;
        assert(ua&&va);
        assert(ub&&vb);

        REP(j,nx[i]){
            int x=tb[i][j];
            if (x&d) va[nva++]=x;
            else ua[nua++]=x;
        }REP(j,nx[i^1]){
            int x=tb[i^1][j];
            if (x&d) vb[nvb++]=x;
            else ub[nub++]=x;
        }
        cnt+=1ll*nua*nub+1ll*nva*nvb;
        ntb[na]=ua; nnx[na++]=nua; 
        ntb[na]=ub; nnx[na++]=nub; 
        ntb[na]=va; nnx[na++]=nva; 
        ntb[na]=vb; nnx[na++]=nvb; 
    }
    if (cnt>=k){
        //for (int i=0; i<ntb.size(); i+=4) swap(ntb[i], ntb[i+2]);
        gob(ntb,nnx,na,d>>1,k);
    }else{
        int fuu=0;
        for (int i=0; i<na; i+=2) REP(j,nnx[i]) REP(l,nnx[i^1]) res.pb(ntb[i][j]^ntb[i^1][l]);
        for (int i=0; i<na; i+=4) swap(ntb[i], ntb[i+2]), swap(nnx[i],nnx[i+2]);
        k-=cnt;
        gob(ntb,nnx,na,d>>1,k);
    }
    //FE(it,ntb) delete *it;

}

void go(int **tb, int *nx, int n, unsigned int d, int k){
    if (!d){
        REP(i,k) res.pb(0);
        return;
    }
    int cnt=0;
    int **ntb=(int**)malloc(sizeof(void*)*2*n);
    int *nnx=(int*)malloc(sizeof(void*)*2*n);
    int na=0;
    assert(ntb);
    assert(nnx);
    REP(i,n) if (nx[i]>=2){
        int *u=(int*)malloc(nx[i]*4);
        int *v=(int*)malloc(nx[i]*4);
        assert(u&&v);
        int nu=0, nv=0;

        REP(j,nx[i]){
            int x=tb[i][j];
            if (x&d) v[nv++]=x;
            else u[nu++]=x;
        }
        cnt+=getn[nu]+getn[nv];
        ntb[na]=u; nnx[na++]=nu; 
        ntb[na]=v; nnx[na++]=nv; 
    }
    if (cnt>=k) go(ntb,nnx,na,d>>1,k);
    else{
        //for (int i=0; i<ntb.size(); i+=2){
        //    puts("========");
        //    out(*ntb[i]);
        //    out(*ntb[i+1]);
        //}
        REP(i,na) REP(j,nnx[i]) REP(l,j) res.pb(ntb[i][j]^ntb[i][l]);
        k-=cnt;
        gob(ntb,nnx,na,d>>1,k);
    }
    //FE(it,ntb) delete *it;
}

vi checkit(int n, int k){
    vi res;
    REP(i,n) REP(j,i) res.pb(a[i]^a[j]);
    sort(ALL(res));
    res.resize(k);
    return res;
}


int tbx[maxn];
int main(){
    int n,k;
    res.clear();

    if (0){
        n=100000; k=250000;
        srand(time(0));
        REP(i,n) a[i]=rand();
    }else{

        cin>>n>>k;
        REP(i,n) scanf("%d", a+i);
    }
    REP(i,n+1) getn[i]=min(1ll*k,1ll*i*(i-1)/2);

    sort(a,a+n);
    if (k>1ll*n*(n-1)/2) k=n*(n-1)/2;
    int tmp=n;
    int *tmpb=a;
    go(&tmpb,&tmp,1,1<<31,k);
    sort(ALL(res));

    //vi tmp=checkit(n,k);
    //assert(res==tmp);

    REP(i,res.size()) printf("%d ", res[i]); puts("");
    assert(res.size()==k);
    return 0;
}



