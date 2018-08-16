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
double px[maxn];
int v1, v2;
int a[maxn];
int n, l;


struct event{
    double t;
    int type;
    event(double t, int type):t(t), type(type){}
    bool operator<(const event &e)const{ return t<e.t; }
};


int main(){
    cin>>n>>l>>v1>>v2;
    REP(i,n) scanf(" %d", a+i);
    double tot=1.*l/(v1+v2);
    double d=tot*v2;
    REPV(i,n) a[i]-=a[0];

    vector<event> el;
    el.pb(event(2*l,2));
    int last=1;
    int have=0;
    for (; a[last]<d && last<n; ++last){
        el.pb(event(a[last],1));
        ++have;
        el.pb(event(2.*l+a[last]-d,0));
    }

    for (int i=last; i<n; ++i){ el.pb(event(a[i]-d,0)); el.pb(event(a[i],1));}

    el.pb(event(2*l-d,0));
    sort(ALL(el));
    double ot=0.;
    REP(i,el.size()){
        event &e=el[i];
        if (ot<e.t) px[have]+=(e.t-ot)/2/l;
        if (e.type==2) break;
        if (e.type==0) ++have;
        else --have;
        ot=e.t;
    }



    REP(i,n+1) printf("%.11lf\n", px[i]);
    return 0;
}


