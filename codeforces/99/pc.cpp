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

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
const int maxm=11111;

int a[maxn], b[maxm], z[maxm], l[maxn], r[maxn], h[maxn];
int n, m;
int X[101];

struct event{
    int type;
    double x;
    int d;
    event(int type, double x, int d):type(type), x(x), d(d){}

    bool operator<(const event &e)const{
        if (x!=e.x) return x<e.x;
        if (type!=e.type) return type<e.type;
        return d<e.d;
    }
};

int main(){
    cin>>n>>m;
    REP(i, n) cin>>a[i]>>h[i]>>l[i]>>r[i];
    REP(i, m) cin>>b[i]>>z[i];

    vector<event> el;
    REP(i, n) el.pb(event(-1, a[i]-h[i]-0.5, 100-l[i]));
    REP(i, n) el.pb(event(1, a[i]-0.5, 100-l[i]));
    REP(i, n) el.pb(event(-1, a[i]+0.5, 100-r[i]));
    REP(i, n) el.pb(event(1, a[i]+h[i]+0.5, 100-r[i]));
    REP(i, m) el.pb(event(0, b[i], z[i]));

    double ans=0.;
    sort(ALL(el));
    int cnt=0;
    REP(i, el.size()){
        event e=el[i];
        if(!e.type){
            double p=e.d;
            REP(j, 101){
                double z=j/100.;
                int px=X[j];
                while(px){
                    if (px&1) p*=z;
                    px>>=1;
                    z*=z;
                }


            }
            ans+=p;
        }
        else if (e.type==-1) ++X[e.d];
        else --X[e.d]; 

    }
    cout<<ans<<endl;
    return 0;

}


