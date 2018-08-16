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

const int maxn=255;
int vis[maxn][maxn];
int mp[maxn][maxn];
int r, c;
int vx[]={1,1,1,0,0,-1,-1,-1};
int vy[]={0,1,-1,1,-1,0,1,-1};
int step;
vector<pii> pl;
char buf[maxn];

int in(int a, int b){return a>=0&&b>=0&&a<r&&b<c;}

void dfs(int a, int b){
    if (vis[a][b]==step) return;
    vis[a][b]=step;
    pl.pb(MP(a,b));
    REP(k,8){
        int x=a+vx[k], y=b+vy[k];
        if (in(x,y)&&mp[x][y]) dfs(x,y);
    }

}

int checkita(vector<pii> &pl){
    int n=pl.size();
    if (n%4) return 0;
    n/=4; ++n;

    for (int i=1; i<n; ++i) if (pl[i].ST!=pl[i-1].ST||pl[i].ND!=pl[i-1].ND+1) return 0;
    for (int i=n; i<pl.size()-n; i+=2) if (pl[i].ST!=pl[i+1].ST || pl[i].ND!=pl[0].ND || pl[i+1].ND!=pl[n-1].ND) return 0;
    int na=pl.size()-1;
    for (int i=1; i<n; ++i) if (pl[na-i].ST!=pl[na-i+1].ST||pl[na-i].ND!=pl[na-i+1].ND-1) return 0;
    if (pl[0].ND!=pl[na-n+1].ND) return 0;
    return 1;
}
int checkitb(vector<pii> &pl){
    int n=pl.size();
    if (n%4) return 0;
    n/=4; ++n;
    for (int i=1; i<n; ++i) if (pl[2*i].ST!=pl[0].ST+i || pl[2*i-1].ST!=pl[0].ST+i
            || pl[2*i].ND!=pl[0].ND+i || pl[2*i-1].ND!=pl[0].ND-i) 
        return 0;
    reverse(ALL(pl));
    for (int i=1; i<n; ++i) if (pl[2*i].ST!=pl[0].ST-i || pl[2*i-1].ST!=pl[0].ST-i
            || pl[2*i].ND!=pl[0].ND-i || pl[2*i-1].ND!=pl[0].ND+i) 
        return 0;

    return 1;
}

int main(){
    int tn; cin>>tn;
    memset(vis,0,sizeof(vis));
    step=0;
    REP(ti,tn){
        cin>>r>>c;
        REP(i,r){
            scanf(" %s", buf);
            REP(j,c) mp[i][j]=buf[j]=='1';
        }

        int res=0;
        ++step;
        REP(i,r) REP(j,c) if (vis[i][j]!=step && mp[i][j]){
            pl.clear();
            dfs(i,j);
            if (pl.size()%2) continue;
            sort(ALL(pl));
            res+=checkita(pl);
            res+=checkitb(pl);
        }
        cout<<res<<endl;
    }
    return 0;
}



