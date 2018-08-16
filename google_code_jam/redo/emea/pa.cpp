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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

int xua, xub, yua, yub;
int xa, xb, ya, yb;
int xuc, xud, yuc, yud;
const double eps=1e-10;

double m[2][2];
double b[2];
double x[2];

double sqr(double a){return a*a;}

void linsolve(){
    int n;
    n=2;
    REP(i, n){
        int p=i;
        FOR(j, i+1, n-1) if (fabs(m[j][i])>fabs(m[p][i])) p=j;
        REP(j, n) swap(m[p][j], m[i][j]);
        swap(b[p], b[i]);
        if (fabs(m[i][i])<eps) assert(0);
        REP(j, n) if (j!=i && fabs(m[j][i])>eps){
            double c=m[j][i]/m[i][i];
            REP(k, n) m[j][k]-=c*m[i][k];
            b[j]-=c*b[i];
        }
    }
    REP(i, n) x[i]=b[i]/m[i][i];
}

void solve(){

    m[0][0]=xua-xuc;
    m[0][1]=xub-xud;
    m[1][0]=yua-yuc;
    m[1][1]=yub-yud;
    b[0]=xb-xa;
    b[1]=yb-ya;
    linsolve();

    /*
     * xa+ xua*a+b*xub =  xb+xuc*a+b*xud
     * ya+ yua*a+b*yub =  yb+yuc*a+b*yud
     * (xua-xuc xub-xud) ( a) = (xb-xa)
     * (
     */
    m[0][0]=xua-xuc;
    m[0][1]=xub-xud;
    m[1][0]=yua-yuc;
    m[1][1]=yub-yud;
    b[0]=xb-xa;
    b[1]=yb-ya;
    printf("%lf %lf\n", xa+xua*x[0]+xub*x[1], ya+yua*x[0]+yub*x[1]);

}


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>xa>>ya;
        cin>>xua>>yua>>xub>>yub;
        xua-=xa; yua-=ya;
        xub-=xa; yub-=ya;
        cin>>xb>>yb;
        cin>>xuc>>yuc>>xud>>yud;
        xuc-=xb; yuc-=yb;
        xud-=xb; yud-=yb;
        printf("Case #%d: ", ti);
        solve();



    }

    return 0;

}


