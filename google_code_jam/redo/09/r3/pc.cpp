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

const int maxn=1100;
const int maxr=34;
int n;
set<int> mp[maxr];
map<pii, int> rmp;
int in[maxn];
int deg[maxn];
int x[maxn], y[maxn];
int graph[maxn][maxn];

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        REP(i, maxr) mp[i].clear();
        rmp.clear();
        REP(i, n){
            cin>>x[i]>>y[i];
            --y[i]; --x[i];
            rmp[MP(x[i], y[i])]=i;
            mp[y[i]].insert(x[i]);
        }

        memset(graph, 0, sizeof(graph));
        memset(deg, 0, sizeof(deg));
        memset(in, 0, sizeof(in));
        REP(i, n){
            if (mp[y[i]].lower_bound(x[i]+1)!=mp[y[i]].end()){
                int j=rmp[MP(*mp[y[i]].lower_bound(x[i]+1), y[i])];;
                graph[i][j]=graph[j][i]=1;
            }
            if (y[i]>0 && mp[y[i]-1].lower_bound(x[i]+1)!=mp[y[i]-1].end()){
                int j=rmp[MP(*mp[y[i]-1].lower_bound(x[i]+1), y[i]-1)];
                graph[i][j]=graph[j][i]=1;
            }
            if (y[i]<maxr-1 && mp[y[i]+1].lower_bound(x[i]+1)!=mp[y[i]+1].end()){
                int j=rmp[MP(*mp[y[i]+1].lower_bound(x[i]+1), y[i]+1)];
                graph[i][j]=graph[j][i]=1;
            }
        }
        REP(i, n){
            if (y[i]<maxr-1 && y[i]>0){
                if (*mp[y[i]].begin()==x[i]) goto out;
                if (mp[y[i]].lower_bound(x[i]+1)==mp[y[i]].end()) goto out;
                if (mp[y[i]+1].lower_bound(x[i]+1)==mp[y[i]+1].end()) goto out;
                if (mp[y[i]-1].lower_bound(x[i]+1)==mp[y[i]-1].end()) goto out;
                in[i]=1;
out:;
            }
        }
        REP(i, n) REP(j, i) if (graph[i][j]) ++deg[i], ++deg[j];

        int res=1;
        REP(i, n) if (deg[i]){res=-1; break;}
        if (res==1) goto fd;

        res=2;
        REP(i, n){
            int cnta=0, cntb=0;
            REP(j, n) if (y[j]==y[i]-1 && graph[i][j]) ++cnta; else if (y[j]==y[i]+1 && graph[i][j]) ++cntb;
            if (cnta>=2 || cntb>=2) {res=-1; break;}

        }
        if (res==2) goto fd;
        res=3;
        REP(i, n) if (in[i] && deg[i]&1){res=4; break;}




fd:
        printf("Case #%d: %d\n", ti, res);

    }
    return 0;

}




