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


int n;
vector<pii> pl;

int checkit(int a, int b, pii x, int k){
    ++k;
    int ob=b;
    for (++a, --b; a<ob; ++a){
        pii np=MP(2*x.ST-pl[a].ST, 2*x.ND-pl[a].ND);
        while(pl[b]>np && k) --b;
        if (pl[b]!=np) --k;
        else --b;
        if (!k) return 0;
    }
    return 1;
}

int main(){

    int K;
    cin>>n>>K;
    if (K>=n){printf("-1\n"); return 0;}

    REP(i, n){ int a, b; cin>>a>>b; pl.pb(MP(2*a, 2*b)); }
    sort(ALL(pl));
    set<pii> res;
    REP(a, K+1) for (int b=n-1; n-1-b+a<=K; --b){
        pii x=MP((pl[a].ST+pl[b].ST)/2, (pl[a].ND+pl[b].ND)/2);
        if (checkit(a, b, x, K-(n-1-b+a))) res.insert(x);
    }

    cout<<res.size()<<endl;
    FE(it, res) printf("%lf %lf\n", it->ST/2., it->ND/2.);
    return 0;
}

