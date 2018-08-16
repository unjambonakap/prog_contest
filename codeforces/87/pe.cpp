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

const int maxn=1<<19;
const ll inf=1e15;
vector<pii> e[maxn];
ll tree[maxn+1];
int H[maxn+1], T[maxn+1];
ll add[maxn+1];
int leaf;
int c[maxn];

ll update(int p, int a, int v){
    if (a<T[p]) return tree[p]+add[p];
    if (a>=H[p]-1){ add[p]+=v; return tree[p]+add[p];}
    tree[p]=max(update(2*p, a, v), update(2*p+1, a, v));
    return tree[p]+add[p];
}


ll init(int p, int a, int b){
    T[p]=a; H[p]=b;
    if (a+1==b) return tree[p]=a==0?0:-inf;
    int M=(a+b)/2;
    return tree[p]=max(init(2*p, a, M), init(2*p+1, M, b));
}
int main(){
    int n, m; cin>>n>>m;
    REP(i,n) scanf("%d", c+i);
    REP(i,m){
        int a, b,x; scanf("%d %d %d", &a,&b,&x);
        --a; --b;
        e[b].pb(MP(a,x));
    }
    leaf=maxn>>1;
    init(1,0,leaf);
    REP(i,n){
        int p=leaf+i+1;
        while(p) tree[p]=tree[1], p>>=1;
        update(1,i,-c[i]);
        FE(it,e[i]) update(1,it->ST,it->ND);
    }
    cout<<tree[1]<<endl;
    return 0;

}


