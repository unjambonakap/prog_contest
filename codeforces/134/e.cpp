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

const int maxb=1<<23;
const int leaf=maxb>>1;

int tb[maxb];
int K, n; 
char s[maxb];
int par[maxb];
char res[maxb];
void init(int p, int a, int b){
    if (p>=maxb) return;
    tb[p]=max(0,min(b,K)-a);
    init(2*p,a,a+b>>1);
    init(2*p+1,a+b>>1,b);
}

int query(int x){
    --x;
    int p=1;
    if (x>=tb[1]) return -1;
    for (; p<leaf;){
        int u=tb[p<<1];
        if (x<u) p<<=1;
        else x-=u, p=(p<<1)+1;
    }
    assert(!x && tb[p]==1);
    return p-leaf;
}
void rem(int x){ if (x==-1) return ;for (x+=leaf; x; x>>=1) --tb[x]; }

int main(){
    n=1;
    scanf(" %s", s);
    cin>>K;
    init(1,0,leaf);
    vector<pii> l;
    int m; cin>>m;
    REP(i,m){int a, b; scanf(" %d%d",&a,&b); l.pb(MP(a,b));}


    memset(par,-1,sizeof(par));
    for (int i=m-1; i>=0; --i){
        int a=l[i].ST, b=l[i].ND+1;
        int p=b;
        vi pos;
        for (int x=a+1; x<b && p<=tb[1]; x+=2, ++p){
            int u=query(p);
            pos.pb(u);
            par[u]=query(x);
        }
        for (int x=a; x<b && p<=tb[1]; x+=2, ++p){
            int u=query(p);
            pos.pb(u);
            par[u]=query(x);
        }
        REP(i,p-b) rem(pos[i]);
    }

    int j=0;
    REP(i,K) res[i]=par[i]==-1?s[j++]:res[par[i]];
    printf("%s\n", res);

    return 0;
}


