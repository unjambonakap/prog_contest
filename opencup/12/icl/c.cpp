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

const int maxn=1e7+10;
const int maxm=44444;
double val[maxn];
int n, m;
const double inf=1e20;

int xa[maxm], ya[maxm], ra[maxm];
struct event{
    int type, u;
    int x;
    event(int type, int u, int x):type(type), u(u),x(x){}
    bool operator<(const event &e)const{ return x<e.x;}
};

struct cmpa{ bool operator()(int a, int b)const{return ya[a]>ya[b];}};

double go(int x, int r){
    if (fabs(x)>r) return 0.;
    return sqrt(1ll*r*r-1ll*x*x);
}

int main(){
    freopen("ice.in", "r", stdin);
    freopen("ice.out", "w", stdout);

    cin>>n>>m;
    REP(i,m) scanf(" %d%d%d", xa+i,ya+i,ra+i);

    vector<event> el;
    REP(i,m) el.pb(event(1,i,xa[i]-ra[i])), el.pb(event(2,i,xa[i]+ra[i]+1));
    sort(ALL(el));
    
    set<int,cmpa> sl;
    REP(i,n) val[i]=-inf;
    int first=-1;
    int last=0;
    REP(i,n){
        for (; last<el.size() && el[last].x<=i; ++last){
            event &e=el[last];
            if (e.type==1) sl.insert(e.u), first=*sl.begin();
            else{
                sl.erase(e.u);
                first=sl.empty()?-1:*sl.begin();
            }
        }
        if (first!=-1){
            double va=ya[first]+go(xa[first]-i, ra[first]), vb=ya[first]+go(xa[first]-i-1, ra[first]);
            checkmax(val[i],max(va,vb));
            //if (last>0) checkmax(val[last-1],va);
            //if (last+1<n) checkmax(val[last+1],vb);
        }
    }
    REP(i,m) if (xa[i]-ra[i]-1>=0 && xa[i]-ra[i]-1<n) checkmax(val[xa[i]-ra[i]-1],1.*ya[i]);

    double res=0.;
    double best=-inf;

    REP(i,n) checkmax(best,val[i]);
    int cnt=0;
    REP(i,n) if (val[i]!=-inf) res+=best-val[i], ++cnt;
    printf("%.15lf\n", res/cnt);

    return 0;
}


