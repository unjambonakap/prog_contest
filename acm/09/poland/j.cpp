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

const int maxn=1111;
int n, m;
vi e[maxn];
int vis[maxn];
int pos;
int rem[maxn];
int backe[maxn];
vector<pii> ans;
int fd;
int changed;

pii dfs(int a, int p=-1){
    backe[a]=pos;
    vis[a]=pos++;
    int sz=1;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (rem[b])continue;
        if (b==p) continue;
        if (vis[b]==-1){
            pii x=dfs(b,a);
            checkmin(backe[a],x.ST);
            if (rem[a]) return MP(INT_MAX,0);
            sz+=x.ND;
        }else checkmin(backe[a],backe[b]);
    }

    if (backe[a]==vis[a] && p!=-1){
        assert(!rem[a] && !rem[p]);
        rem[a]=1; rem[p]=1;
        if (!(sz&1)) throw "fail";
        
        changed=1;
        ans.pb(MP(min(a,p),max(a,p)));
    }
    return MP(backe[a],sz+1);
}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>m;
        REP(i,n) e[i].clear();
        REP(i,m){int a, b; scanf(" %d%d", &a,&b); --a; --b; e[a].pb(b); e[b].pb(a);}
        memset(vis,-1,sizeof(vis));
        ans.clear();
        memset(rem,0,sizeof(rem));
        pos=0;
        fd=1;
        try{
            changed=0;
            for (int i=0; i<n; ++i){
                while(i<n&&rem[i]) ++i;
                if (i==n) break;
                memset(vis,-1,sizeof(vis));
                dfs(i);
                if (!changed) break;
            }
        }catch(string){ fd=0; }

        
        REP(i,n) if (!rem[i]) fd=0;
        if (!fd) printf("NO\n");
        else{
            sort(ALL(ans));
            puts("YES");
            assert(ans.size()==n/2);
            REP(i,ans.size()) printf("%d %d\n", ans[i].ST+1, ans[i].ND+1);
        }
    }
    return 0;
}





