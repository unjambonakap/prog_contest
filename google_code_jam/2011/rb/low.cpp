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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=2010;
set<set<int> > area;
int u[maxn], v[maxn];
int n;
vi e[maxn];
int col[maxn];
vector<vi> narea;
set<vi> visited;

void add(int a, int b, int prev, set<int> s){
    s.insert(b);
    if (a==b){
        area.insert(s);
        return;
    }
    int na=a-b;
    if (na<0) na+=n;

    int mv=1;
    FE(it, e[b]) if (*it!=prev){
        int c=*it-b;
        if (c<0) c+=n;
        if (c<=na) checkmax(mv, c);
    }
    add(a, (mv+b)%n, b, s);


}

int rec(int a, int p, int nc){
    if (p==narea.size()) return 1;
    const vi &s=narea[p];
    if (a==s.size()){
        int m=0;
        REP(i, a) m|=two(col[s[i]]);
        if (m==two(nc)-1) return rec(0, p+1, nc);
        return 0;
    }

    if (col[s[a]]!=-1) return rec(a+1, p, nc);
    REP(i, nc){
        col[s[a]]=i;
        if (rec(a+1, p, nc)) return 1;
    }
    col[s[a]]=-1;
    return 0;

}

int checkit(int a){
    memset(col, -1, sizeof(col));
    return rec(0, 0, a);
}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int m;
        cin>>n>>m;
        area.clear();
        REP(i, n) e[i].clear();
        REP(i, m) cin>>u[i], --u[i];
        REP(i, m) cin>>v[i], --v[i];
        REP(i, m) e[u[i]].pb(v[i]), e[v[i]].pb(u[i]);

        REP(i, n) e[i].pb((i+1)%n), e[(i+1)%n].pb(i);
        set<int> tmp;
        
        REP(i, m) add(u[i], v[i], u[i], tmp), add(v[i], u[i], v[i], tmp);
        int mc=INT_MAX;
        narea.clear();
        int min_area;
        FE(it, area){
            narea.pb(vi(ALL(*it)));
            if (mc>narea.back().size()) mc=narea.back().size(), min_area=narea.size()-1;

        }
        swap(narea[min_area], narea[0]); 

        int ans=1;
        assert(narea.size()>=2);
        FORV(i, mc, 2) if (checkit(i)){
            ans=i;
            break;
        }
        REP(i, n) assert(col[i]!=-1);
        if (ans!=mc) printf("<< %d\n", ti);
        //if (ti!=100) continue;
        //printf("%d\n", n);
        //out(u, m);
        //out(v, m);
        //REP(i, narea.size()) out(narea[i]);
        //printf("Case #%d: %d\n", ti, ans);
        //REP(i, n-1) printf("%d ", col[i]+1);
        //printf("%d\n", col[n-1]+1);


    }
    return 0;
}



