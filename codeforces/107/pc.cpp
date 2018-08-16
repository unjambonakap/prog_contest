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

const int maxn=1<<20;
const int leaf=maxn>>1;
const double inf=1e10;
int n, m, c;
int px[maxn];
int x[maxn];

double tree[maxn][3];//io,i,o
double sum[maxn];
int T[maxn], H[maxn];


void init(int p, int a, int b){
    T[p]=a; H[p]=b;
    if (a+1==b){
        double k=-2*c*px[a]/100.;
        tree[p][0]=max(0.,k+x[b]-x[a]);
        tree[p][1]=max(-x[a]+k,-1.*x[b]);
        tree[p][2]=max(x[b]+k,1.*x[a]);
        return;
    }
    int M=(a+b)/2;
    init(2*p,a,M);
    init(2*p+1,M,b);
    double *x=tree[2*p], *y=tree[2*p+1];
    double *u=tree[p];
    u[1]=max(x[1]+sum[b]-sum[M], y[1]);
    u[2]=max(y[2]+sum[M]-sum[a], x[2]);
    u[0]=x[1]+y[2];
    checkmax(u[0],x[0]);
    checkmax(u[0],y[0]);
}
double querys(int p, int a, int b){
    checkmax(a,T[p]);
    checkmin(b,H[p]);
    if (a>=b) return 0.;
    return sum[b]-sum[a];

}

double query(int p, int a, int b, int cnd){
    if (a>=H[p]||b<=T[p]) return -inf;
    if (a<=T[p]&&b>=H[p]){
        return tree[p][cnd];
    }
    int u=2*p, v=u+1;
    double res;
    if (cnd==0){
        res=max(query(u,a,b,1)+query(v,a,b,2),max(query(u,a,b,0),query(v,a,b,0)));
    }
    else if (cnd==1) res=max(query(u,a,b,1)+querys(v,a,b),query(v,a,b,1));
    else{ res=max(query(v,a,b,2)+querys(u,a,b),query(u,a,b,2)); }

    return res;

}



int main(){
    cin>>n>>m>>c;
    REP(i,n) scanf("%d", x+i);
    REP(i,n-1) scanf("%d", px+i);
    sum[0]=0.;
    REP(i,n-1) sum[i+1]=sum[i]-2*c*px[i]/100.;
        

    init(1,0,n-1);
    double res=0.;

    REP(step,m){
        int a, b; scanf("%d%d", &a,&b); --a; --b;
        double v=query(1,a,b,0)/2.;
        res+=v;
    }
    printf("%.10lf\n", res);
    return 0;
}



