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



const int maxn=410;
int n, m;
vector<int> e[maxn];
int graph[maxn][maxn];
int step[maxn];
int na;
int mem[maxn][maxn];
int dist[maxn];
int visited[maxn];


void dfs(int a){
    if (visited[a]) return;
    visited[a]=1;
    step[a]=na-dist[a];
    if (a==1) return;
    FE(it, e[a]) if (dist[*it]+1==dist[a]) dfs(*it);
}
void proc(){
    queue<pii> q;
    q.push(MP(1, 0));
    memset(visited, 0, sizeof(visited));
    memset(dist, -1, sizeof(step));
    while(!q.empty()){
        pii p=q.front(); q.pop();
        if (visited[p.ST])continue;
        visited[p.ST]=1;
        dist[p.ST]=p.ND;
        if (p.ST==0) break;

        FE(it, e[p.ST]) if (!visited[*it]) q.push(MP(*it, p.ND+1));
    }
    na=dist[0];
    memset(visited, 0, sizeof(visited));
    memset(step, 0x7f, sizeof(step));
    dfs(0);

}





int solve(int a, int b){
    if (step[a]==na-1) return e[a].size();
    int &r=mem[a][b];
    if (r!=-1) return r;

    int cnta=-maxn;
    FE(it, e[a]){
        int c=*it;
        if (step[c]!=step[a]+1)continue;
        int tmp=0;
        FE(it, e[c]) if (*it==a || graph[*it][a] || graph[*it][b]) ++tmp;
        checkmax(cnta, solve(c, a)-tmp);
//        printf("%d %d %d => %d %d\n", a, b, c, solve(c, a), tmp);
    }


    r=e[a].size()+cnta;
    return r;
}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n>>m;
        REP(i, n) e[i].clear();
        memset(graph, 0, sizeof(graph));
        string s;
        getchar();
        getline(cin, s);
        FE(it, s) if (*it==',') *it=' ';
        istringstream ss(s);
        REP(i, m){
            int a, b;
            ss>>a>>b;

            graph[a][b]=graph[b][a]=1;
            e[a].pb(b);
            e[b].pb(a);
        }







        proc();




 //       out(step, n);
 //       out(dist, n);
        memset(mem, -1, sizeof(mem));
        int res=solve(0, 0)-na+1;


        printf("Case #%d: %d %d\n", ti, na-1, res);

    }
    return 0;

}



