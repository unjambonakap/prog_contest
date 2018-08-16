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

const int maxn=110, maxnr=57;
map<string, int> mp;
int n, nr, st;
int graph[maxn][maxn];
int ng[maxn][maxn];
int ta[maxnr], tb[maxnr];
int cost[maxnr];
double prob[maxnr];
int seen[maxn];
int parent[maxn][maxn], visited[maxn];
int cnte[maxn][maxn];

void update(int a, int b){
    if (visited[a]) return;
    visited[a]=1;
    REP(i, n) if (parent[a][i]) cnte[i][a]*=b, update(i, b);

}

void solve(){
    memset(prob, 0, sizeof(prob));

    int cnta=0;
    REP(i, n) if (graph[st][i]!=-1) ++cnta;
    --cnta;


    REP(i, n) if (i!=st && graph[st][i]!=-1){
        priority_queue<pii> q;
        q.push(MP(-0, st));

        memset(seen, 0, sizeof(seen));
        memset(parent, 0, sizeof(parent));
        memset(cnte, 0, sizeof(cnte));
        while(!q.empty()){
            pii p=q.top(); q.pop();
            int a=p.ND;
            if (seen[a]) continue;
            seen[a]=1;
            if (a==i) break;

            int cnt=0;
            if (a==st) cnt=1;
            else REP(j, n) if (parent[a][j]) cnt+=cnte[j][a];

            int mul=0;
            REP(j, n) if (ng[a][j] && graph[j][i]!=-1 && graph[a][i]==graph[a][j]+graph[j][i]){
                mul+=ng[a][j];
                cnte[a][j]+=ng[a][j]*cnt;
                parent[j][a]=1;
                q.push(MP(-graph[st][j], j));
            }

            memset(visited, 0, sizeof(visited));
            update(a, mul);
        }
        int cntb=0;
        REP(j, n) cntb+=cnte[st][j];
        REP(j, nr) prob[j]+=cnte[ta[j]][tb[j]]/double(cnta*cntb);


    }



}

int main(){
    int ti, tn;
    cin>>tn;

    FOR(ti, 1, tn){
        mp.clear();
        string sts;

        cin>>nr>>sts;


        memset(graph, -1, sizeof(graph));
        memset(ng, 0, sizeof(ng));
        n=0;
        REP(i, nr){
            string sa, sb;
            int t;
            cin>>sa>>sb>>t;
            cost[i]=t;
            if (!mp.count(sa)) mp[sa]=n++;
            if (!mp.count(sb)) mp[sb]=n++;
            ta[i]=mp[sa]; tb[i]=mp[sb];
            int a=ta[i], b=tb[i];
            if (ng[a][b]==0 || graph[a][b]>t) ng[a][b]=1, graph[a][b]=t;
            else if (graph[a][b]==t) ++ng[a][b];
        }
        if (ti!=71)continue;
        out(ta, nr);
        out(tb, nr);
        out(cost, nr);

        REP(i, n) graph[i][i]=0;

        st=mp[sts];

        REP(k, n) REP(i, n) REP(j, n) if (graph[i][k]!=-1 && graph[k][j]!=-1 && (graph[i][j]==-1 || graph[i][k]+graph[k][j]<graph[i][j])) graph[i][j]=graph[i][k]+graph[k][j];
        printf("<< %d\n", st);
        REP(i, n) out(graph[i], n);
        printf("%d\n", ng[0][1]);
        solve();
        printf("Case #%d: ", ti);
        REP(i, nr) printf(" %0.7lf", (cost[i]==graph[ta[i]][tb[i]]?prob[i]/ng[ta[i]][tb[i]]:0.));
        printf("\n");
    }
    return 0;


}

