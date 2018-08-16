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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=100;
int ga[maxn][maxn];
int gb[maxn][maxn];
vi da[maxn];
vi db[maxn];
int n, m;
int match[maxn][maxn];
vi ca[maxn], cb[maxn];




int graph[maxn][maxn];
int matchz[maxn];
int visited[maxn];
int na, nb;

int dfs(int a){
    if (visited[a]) return 0;
    visited[a]=1;
    REP(i, na) if (graph[a][i] && (matchz[i]==-1 || dfs(matchz[i]))){
        matchz[i]=a;
        return 1;
    }
    return 0;
}

void dfsa(int a, int d, int p){
    da[d].pb(a);
    ca[a].clear();
    REP(i, n) if (ga[a][i] && i!=p){
        ca[a].pb(i);
        dfsa(i, d+1, a);
    }
}

void dfsb(int a, int d, int p){
    db[d].pb(a);
    cb[a].clear();

    REP(i, m) if (gb[a][i] && i!=p){
        cb[a].pb(i);
        dfsb(i, d+1, a);
    }
}



int solve(){
    REP(k, n) db[k].clear();
    dfsb(0, 0, -1);
    REP(i, n){
        REP(k, n) da[k].clear();
        dfsa(i, 0, -1);
        memset(match, 0, sizeof(match));
        REPV(d, n-1){

            REP(u, da[d].size()) REP(v, db[d].size()){
                memset(matchz, -1, sizeof(matchz));
                memset(graph, 0, sizeof(graph));
                vi &va=ca[da[d][u]], vb=cb[db[d][v]];
                na=va.size(); nb=vb.size();
                if (na<nb) continue;
                REP(i, na) REP(j, nb) graph[j][i]=match[va[i]][vb[j]];

                int ok=1;
                REP(j, nb){
                    memset(visited, 0, sizeof(visited));
                    if (!dfs(j)){ok=0; break;}
                }
                match[da[d][u]][db[d][v]]=ok;
            }
        }
        if (match[i][0]){
            return 1;
        }
    }
    return 0;


}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){

        cin>>n;
        memset(ga, 0, sizeof(ga));
        memset(gb, 0, sizeof(gb));
        REP(i, n-1){
            int a, b;
            cin>>a>>b;
            --a; --b;
            ga[a][b]=ga[b][a]=1;
        }

        cin>>m;
        REP(i, m-1){
            int a, b;
            cin>>a>>b;
            --a; --b;
            gb[a][b]=gb[b][a]=1;
        }
        printf("Case #%d: ", ti);
        if (solve()) printf("YES\n");
        else printf("NO\n");

    }
    return 0;
}

