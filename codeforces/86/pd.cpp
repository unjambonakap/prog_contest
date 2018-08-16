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

const int maxn=11*22;
const double eps=1e-9;

double q[maxn][maxn];
double B[maxn][22];
double inv[maxn][maxn];
double iq[maxn][maxn];
int n, m;
int N;
int rmp[22][22]; 
int g[22][22];
int pos;
double p[22];
int na[22];
int perm[maxn];
double res[22];


int getid(int a, int b){
    assert(a!=b);
    if (rmp[a][b]!=-1) return rmp[a][b];
    return rmp[b][a]=rmp[a][b]=pos++;
}

void go(){ 
    REP(i,N) inv[i][i]=1.;
    REP(i,N) perm[i]=i;
    REP(i,N){
        int pt=i;
        FOR(j,i,N) if (fabs(q[j][i])>fabs(q[pt][i])) pt=j;
        swap(perm[i],perm[pt]);
        FOR(j,i,N) swap(q[pt][j],q[i][j]);
        REP(j,N) swap(inv[pt][j],inv[i][j]);
        assert(fabs(q[i][i])>eps);

        double c=q[i][i];
        REP(j,N) if (j!=i){
            double c=q[j][i]/q[i][i];
            REP(k,N) inv[j][k]-=inv[i][k]*c;
            FOR(k,i,N) q[j][k]-=q[i][k]*c;
        }
        REP(j,N) inv[i][j]/=c;
        FOR(j,i,N) q[i][j]/=c;
    }

    REP(i,N) REP(j,N) iq[i][j]=inv[i][j];
}



int main(){
    int a, b;
    cin>>n>>m>>a>>b;
    --a, --b;

    memset(rmp,-1,sizeof rmp);
    pos=0;
    REP(i,n) g[i][i]=1;
    REP(i,m){int u, v; cin>>u>>v; --u, --v; g[u][v]=g[v][u]=1; ++na[u], ++na[v];}
    REP(i,n) cin>>p[i];

    REP(i,n) REP(j,i) REP(u,n) REP(v,n) if (g[i][u] && g[j][v]){
        double px=1.;
        if (u==i) px*=p[i];
        else px*=(1-p[i])/na[i];
        if (v==j) px*=p[j];
        else px*=(1-p[j])/na[j];

        if (u==v) B[getid(i,j)][u]+=px;
        else q[getid(i,j)][getid(u,v)]+=px;
    }
    N=pos;
    REP(i,N) REP(j,N) q[i][j]=(i==j)-q[i][j];
    go();
    if (a==b) res[a]=1.;
    else{
        int st=rmp[a][b];
        REP(i,n) REP(j,N) res[i]+=iq[st][j]*B[j][i];
    }
    REP(i,n) printf("%.10lf ", res[i]); puts("");
    return 0;
}


