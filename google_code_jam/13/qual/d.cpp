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

const int maxn=20;

int n,K;
vi tb[maxn];
vi st;
map<int,int> rmp;
int type[maxn];
char lowb[1<<maxn];

int prev[1<<maxn];
int sum[1<<maxn][maxn];
int have[maxn][maxn];
int vis[1<<maxn];

int dfs(int a, int p=0){
    if (vis[a]) return 0;
    vis[a]=1;

    prev[a]=p;
    if (a==(1<<n)-1) return 1;
    REP(i,n) if (!(a&1<<i) && sum[a][type[i]] && dfs(a|(1<<i),a)) return 1;
    return 0;
}

int main(){
    int tn; cin>>tn;
    FOR(i,2,1<<maxn) lowb[i]=i&1?0:lowb[i>>1]+1;

    REP(ti,tn){
        cin>>K>>n;

        st.resize(K);
        REP(i,K) cin>>st[i];

        rmp.clear();
        int pos=0;

        REP(i,n){
            int t,k;
            cin>>t>>k;
            if (!rmp.count(t)) rmp[t]=pos++;

            type[i]=rmp[t];
            tb[i].resize(k);
            REP(j,k) cin>>tb[i][j];
        }

        memset(have,0,sizeof(have));
        REP(i,n) REP(j,tb[i].size()) if (rmp.count(tb[i][j])) ++have[i][rmp[tb[i][j]]];

        memset(sum,0,sizeof(sum));
        REP(i,K) if (rmp.count(st[i])) ++sum[0][rmp[st[i]]];
        FOR(i,1,1<<n){
            int b=lowb[i];
            int oi=i^(1<<b);
            REP(j,pos) sum[i][j]=sum[oi][j]+have[b][j];
            --sum[i][type[b]];
        }

        memset(vis,0,sizeof(vis));

        printf("Case #%d: ",ti+1);
        if (!dfs(0)) puts("IMPOSSIBLE");
        else{
            int x=(1<<n)-1;
            vi ans;
            while(x) ans.pb(lowb[prev[x]^x]), x=prev[x];
            REPV(i,n) printf("%d ",ans[i]+1);
            puts("");
        }
    }
    return 0;
}

