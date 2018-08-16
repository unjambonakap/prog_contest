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

const int maxn=2222;
const double eps=1e-9;
int vx[]={1,0,-1,0};
int vy[]={0,1,0,-1};

double m[maxn][maxn];
double b[maxn];
int n;
int r,c;

void go(){
    REP(i,n){
        double u=m[i][i];
        b[i]/=u;
        FOR(j,i,i+c+1) m[i][j]/=u;

        FOR(j,i+1,i+c+1){
            double v=m[j][i];
            FOR(k,i,i+c+1) m[j][k]-=m[i][k]*v;
            b[j]-=b[i]*v;
        }
    }
    for (int i=n-1; i>=0; --i) FOR(j,i+1,n) b[i]-=b[j]*m[i][j];
}
int in(int a, int b){return a>=0&&a<r&&b>=0&&b<c;}

int main(){
    while(cin>>r>>c,r){
        n=r*c;
        memset(m,0,sizeof(m));
        REP(k,4) REP(i,r) REP(j,c){
            double x; scanf(" %lf",&x);
            if (in(i+vx[k],j+vy[k])) m[i*c+j][(i+vx[k])*c+j+vy[k]]=x;
        }

        REP(i,n) m[i][i]=-1, b[i]=-1;
        b[n-1]=0;
        go();
        printf("%.10lf\n",b[0]);
    }
    return 0;
}


