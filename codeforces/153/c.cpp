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

const int V=360360;
const int n=16;
const ll oo=4e18;


int dist[V+2*n];
int q[V+2*n],na,ne;
int nd[n];

struct matrix{
    ll a[n][n];
    matrix(){memset(a,0x3f,sizeof(a));}
    matrix(const matrix &b){memcpy(a,b.a,sizeof(a));}
    void ident(){REP(i,n) a[i][i]=0;}
    matrix operator*(const matrix &b)const{
        matrix r;
        REP(i,n) REP(j,n){
            ll u=oo;
            REP(k,n) u=min(u,a[i][k]+b.a[k][j]);
            r.a[i][j]=u;
        }
        return r;
    }
};


matrix faste(matrix a, ll p){
    matrix x; x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=a*x;
    return x;
}


int main(){
    ll a,b;
    int k;
    cin>>a>>b>>k;

    matrix m;
    ll dx=(a-b)/V;

    memset(nd,0x3f,sizeof(nd));
    REP(i,n){
        memset(dist,-1,sizeof(dist));
        na=ne=0;
        q[ne++]=i; dist[i]=0;
        while(na<ne){
            int x=q[na++];
            int d=dist[x]+1;
            int nv=(2*V+a-x)%V;
            if (dist[x+1]==-1) dist[x+1]=d, q[ne++]=x+1;

            FOR(u,3,k+1){
                int nx=x+nv%u;
                if (nx>V+n) continue;
                if (dist[nx]==-1) dist[nx]=d, q[ne++]=nx;
            }
        }
        ll pos=i+(V+a-i-b)%V;
        nd[i]=dist[pos];

        REP(j,n) m.a[i][j]=dist[j+V];
    }

    ll res=oo;
    m=faste(m,dx);

    REP(i,n) res=min(res,m.a[0][i]+nd[i]);
    cout<<res<<endl;

    return 0;
}

