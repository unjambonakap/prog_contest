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

const int maxn=55555;
const int maxb=1<<17;
int a[maxn], p[maxn];
int n, d;
int l[2*maxn];

long double b[maxb];
void add(int p, long double v){ for (++p; p<maxb; p+=p&-p) b[p]+=v; }
long double get(int p){double u=0; for (; p; p&=p-1) u+=b[p]; return u;}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>d;
        REP(i,n) scanf(" %d", a+i);
        REP(i,n) scanf(" %d", p+i);
        REP(i,n) l[2*i]=a[i], l[2*i+1]=a[i]+d;
        sort(l,l+2*n);

        long double res=0;
        memset(b,0,sizeof(b));
        REP(i,n){
            int u=lower_bound(l,l+2*n,a[i])-l;
            int v=lower_bound(l,l+2*n,a[i]+d)-l;
            long double px=p[i]/100.;
            add(u,1-px); add(v,px);
        }

        REP(i,n){
            int u=lower_bound(l,l+2*n,a[i])-l;
            int v=lower_bound(l,l+2*n,a[i]+d)-l;
            long double px=p[i]/100.;
            add(u,px-1); add(v,-px);
            res+=px*get(v)+(1-px)*get(u);
        }
        printf("%.4Lf\n", res);
    }
    return 0;
}


