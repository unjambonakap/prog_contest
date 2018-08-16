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

const int maxn=1e5+10;
vi e[maxn];
int n,m;

int block[maxn];
int vis[maxn];
int pos;

vector<pii> e2[maxn];

void dfs(int a, int p=-1){
    vis[a]=++pos;

    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        if (vis[b]){
            if (vis[b]<vis[a]){
                e2[b].pb(MP(a,p));
            }
        }
        else dfs(b,a);
    }
}

int go(int a, int &use, int p=-1){
    vis[a]=1;
    int res=0;
    assert(p!=-1 || !a);

    REP(i,e2[a].size()){
        int x=e2[a][i].ST, y=e2[a][i].ND;
        block[x]=block[y]=1;
        vis[x]=vis[y]=1;
        res+=go(x,use,a);
        res+=go(y,use,a);
    }

    int cnt=0;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (vis[b]) continue;
        assert(b!=a);
        res+=go(b,use,a);
        if (!use) ++cnt;
    }
    res+=cnt/2;
    use=0;
    if (p!=-1 && cnt%2==1 && !block[a]) ++res, use=1;

    return res;

}




int main(){
    while(cin>>n>>m,!cin.eof()){
        REP(i,n) e[i].clear(), e2[i].clear();

        REP(i,m){
            int a,b; scanf(" %d%d",&a,&b);
            --a; --b;
            e[a].pb(b);
            e[b].pb(a);
        }

        pos=0;
        memset(vis,0,sizeof(vis));
        dfs(0);

        memset(block,0,sizeof(block));
        memset(vis,0,sizeof(vis));
        int uu;
        int res=go(0,uu);
        printf("%d\n",res);

    }

    return 0;
}

