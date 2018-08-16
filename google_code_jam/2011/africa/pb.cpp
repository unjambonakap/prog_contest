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

const int maxn=1010;
int deg[maxn];
int graph[maxn][maxn];
int parent[maxn];
int visited[maxn];
int n;


int dfs(int a, int b){
    if (visited[a]) return 0;
    visited[a]=1;
    parent[a]=b;
    int ans=0;
    REP(i, n) if (graph[a][i]) ans+=dfs(i, b);
    return ans+deg[a]%2;
}



int main(){

    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int r;
        cin>>n;
        cin>>r;
        memset(deg, 0, sizeof(deg));
        memset(graph, 0, sizeof(graph));
        REP(i, r){
            int a, b;
            cin>>a>>b;
            graph[a][b]=graph[b][a]=1;
            ++deg[a];
            ++deg[b];
        }
        memset(parent, -1, sizeof(parent));
        memset(visited, 0, sizeof(visited));

        multiset<int> tmp;
        REP(i, n) if (deg[i] && parent[i]==-1) tmp.insert(dfs(i, i));
        

        int ans=0;
        while(tmp.size()>1){
            int a=*tmp.begin();
            int b=*tmp.rbegin();
            tmp.erase(tmp.begin());
            tmp.erase(--tmp.end());
            if (a==0) a=1;
            else --a;
            if (b==0) b=1;
            else --b;
            tmp.insert(a+b);
            ++ans;
        }
        assert(*tmp.begin()%2==0);
        
        printf("Case #%d: %d\n", ti, *tmp.begin()/2+ans);

        
    }
    return 0;
}
