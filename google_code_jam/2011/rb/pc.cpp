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
int u[maxn], v[maxn];
int n;
vi e[maxn];
int col[maxn];
map<set<int>, int> rmp;
int nc, np;

int visited[maxn];
int graph[maxn][maxn];
vi area[maxn];

int add(int a, int b, int prev, set<int>& s){
    s.insert(b);
    if (a==b){
        if (!rmp.count(s)){
            int tmp=rmp.size();
            area[tmp]=vi(ALL(s));
            rmp[s]=tmp;
        }
        return rmp[s];
    }
    int na=a-b;
    if (na<0) na+=n;

    int mv=1;
    FE(it, e[b]) if (*it!=prev){
        int c=*it-b;
        if (c<0) c+=n;
        if (c<=na) checkmax(mv, c);
    }
    return add(a, (mv+b)%n, b, s);
}

void dfs(int a, int e){
    if (visited[a]) return;
    visited[a]=1;


    vi &b=area[a];

    int na=b.size();
    if (e==-1) REP(i, na) col[b[i]]=i;
    else{
        int p=lower_bound(ALL(b), u[e-1])-b.begin();
        int pa=(p+1)%na;
        if (b[pa]==v[e-1]) p=pa;

        int ca=col[b[p]], cb=col[b[(p+na-1)%na]];
        vi c;
        REP(i, nc) if (i!=ca && i!=cb) c.pb(i);
        if ((nc+na-3)%nc==nc-2) c.pb(ca), c.pb(cb);
        else c.pb(cb), c.pb(ca);
        FOR(i, 1, na-2){
            int v=b[(p+i)%na];
            assert(col[v]==-1);

            col[v]=c[(i-1)%nc];

        }
    }
    
    

    REP(i, np) if (graph[a][i]) dfs(i, graph[a][i]);

}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int m;
        cin>>n>>m;
        REP(i, n) area[i].clear();
        REP(i, n) e[i].clear();


        REP(i, m) cin>>u[i], --u[i];
        REP(i, m) cin>>v[i], --v[i];
        REP(i, m) e[u[i]].pb(v[i]), e[v[i]].pb(u[i]);

        REP(i, n) e[i].pb((i+1)%n), e[(i+1)%n].pb(i);
        
        rmp.clear();
        memset(graph, 0, sizeof(graph));
        REP(i, m){
            set<int> tmp;
            int va=add(u[i], v[i], u[i], tmp);
            tmp.clear();
            int vb=add(v[i], u[i], v[i], tmp);
            graph[va][vb]=graph[vb][va]=i+1;

        }
        np=rmp.size();
        int min_pos;
        nc=INT_MAX;
        assert(np<n);
        REP(i, np) if (area[i].size()<nc) nc=area[i].size(), min_pos=i;
        

        


        memset(col, -1, sizeof(col));
        memset(visited, 0, sizeof(visited));

        dfs(min_pos, -1);
        printf("Case #%d: %d\n", ti, nc);
        REP(i, n-1) printf("%d ", col[i]+1);
        printf("%d\n", col[n-1]+1);


    }
    return 0;
}



