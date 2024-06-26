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
typedef unsigned int uint;
typedef unsigned char uchar;
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

const int maxn=2222;
int n;
int a[maxn], b[maxn];
int x[maxn];
vi e[maxn];
int deg[maxn];

void proc (int u, int v){
    assert(u<v);
    if (b[v]>=b[u]) e[u].pb(v);
    if (a[u]>=a[v]) e[v].pb(u);


}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        REP(i,n) scanf(" %d",a+i);
        REP(i,n) scanf(" %d",b+i);

        //edge i j if ai<aj
        REP(i,n) REP(j,i) proc(j,i);
        REP(i,n) REPV(j,i) if (a[i]==a[j]+1){e[j].pb(i);break;}
        REP(i,n) FOR(j,i+1,n) if (b[i]==b[j]+1){e[j].pb(i);break;}
        
        memset(deg,0,sizeof(deg));
        REP(i,n) REP(j,e[i].size()) ++deg[e[i][j]];
        priority_queue<int> q;
        REP(i,n) if (!deg[i]) q.push(-i);

        int pos=0;
        while(q.size()){
            int a=-q.top(); q.pop();
            x[a]=pos++;
            REP(i,e[a].size()) if (!--deg[e[a][i]]) q.push(-e[a][i]);
        }

        assert(pos==n);

        printf("Case #%d:",ti+1);
        REP(i,n) printf(" %d",x[i]+1);
        puts("");
        REP(i,n) e[i].clear();
    }
    return 0;
}


