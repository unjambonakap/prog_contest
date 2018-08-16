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
vector<pii> tb;
int a[maxn], b[maxn];

struct node{
    int T, H;
    int val;
    node *l, *r;
    node(int T, int H):T(T),H(H){
        val=0;
        l=r=0;
        if (T+1==H) return;
        l=new node(T,T+H>>1);
        r=new node(T+H>>1,H);
    }

    int query(int a){
        if (a>=H) return val;
        if (a<=T) return 0;
        return max(l->query(a),r->query(a));
    }
    void update(int v, int a){
        if (a<T || a>=H) return;
        val=max(val,v);
        if (!l) return;
        l->update(v,a);
        r->update(v,a);

    }
};

int res[maxn];


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        tb.clear();
        int n; cin>>n;

        vi hl;
        REP(i,n){int u, v; scanf(" %d%d", &u,&v); tb.pb(MP(u,v)); hl.pb(v);}
        sort(ALL(tb));
        sort(ALL(hl));
        REP(i,n) a[i]=tb[i].ST, b[i]=n-(lower_bound(ALL(hl),tb[i].ND)-hl.begin())-1;
        node root(0,n);
        int tx=0;
        memset(res,0,sizeof(res));
        for (int i=n-1; i>=0; --i){
            int u=min(tx,root.query(b[i]+1))+1;
            ++res[u-1];
            root.update(u,b[i]);
            checkmax(tx,u);
        }

        printf("%d\n",tx);
        out(res,tx);
    }
    return 0;
}


