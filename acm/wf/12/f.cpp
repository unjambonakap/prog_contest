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

const int maxn=55;

vi e[maxn];
int type[maxn];
int n;
int rmp[128];
char buf[3];
int cnt[maxn][3];
int col[maxn];
int dp[maxn][2];

int vis[maxn];
vi lst;
void dfs(int a){
    if (vis[a]) return;
    lst.pb(a);
    vis[a]=1;
    REP(i,e[a].size()) dfs(e[a][i]);
}


int get(char c){
    if (rmp[c]!=-1) return rmp[c];
    if (c>='a') type[n]=2;
    else type[n]=c<='M';
    return rmp[c]=n++;
}


int go(int a, int f, int p=-1){
    int &r=dp[a][f];
    if (r!=-1) return r;
    r=maxn;
    if (col[a]==(f^1)) return r;

    r=0;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (type[b]!=2 || b==p) continue;
        int best=maxn;
        REP(nf,2) best=min(best,go(b,nf,a)+(f!=nf)*2);
        r+=best;
    }
    return r;
}


pii solve(){

    vi t[3];

    REP(i,n) t[type[i]].pb(i);
    pii best=MP(maxn,maxn);
    memset(cnt,0,sizeof(cnt));

    if (t[2].size()==1 && t[0].size() && t[1].size()) return best;

    int nc=t[2].size();
    set<int> seenc;

    REP(i,nc){
        int a=t[2][i];
        REP(j,e[a].size()) ++cnt[a][type[e[a][j]]];
        col[a]=cnt[a][0]==cnt[a][1]?-1:cnt[a][0]<cnt[a][1];
        seenc.insert(col[a]);
    }

    if (t[0].size()==0 || t[1].size()==0){
        memset(vis,0,sizeof(vis));

        int na=0;
        REP(j,2) REP(i,t[j].size()) if (!vis[t[j][i]]) ++na, dfs(t[j][i]);
        if (na==0) na=1;
        return MP(0,na-1);
    }

    int basec=0;
    REP(i,nc) basec+=min(cnt[t[2][i]][0],cnt[t[2][i]][1]);


    REP(c1,nc) REP(c2,nc) if (c1!=c2){
        int a=t[2][c1], b=t[2][c2];
        int oca=col[a], ocb=col[b];
        col[a]=0; col[b]=1;

        int cost=basec-min(cnt[a][0],cnt[a][1])-min(cnt[b][0],cnt[b][1])+cnt[a][1]+cnt[b][0];

        memset(vis,0,sizeof(vis));
        memset(dp,-1,sizeof(dp));
        pii ans=MP(cost,0);
        if (cost<=best.ST){
            REP(i,nc){
                int xx=t[2][i];
                if (vis[xx]) continue;

                lst.clear(); dfs(xx);

                int fd=0;
                REP(j,lst.size()) if (type[lst[j]]==2 && (cnt[lst[j]][0]+cnt[lst[j]][1] || col[lst[j]]!=-1)){fd=1; break;}
                if (!fd) continue;


                int bestv=maxn;
                REP(f,2) bestv=min(bestv,go(xx,f)+1);

                ans.ND+=bestv;
            }
            assert(ans.ND>=2);
            ans.ND-=2;
            best=min(best,ans);
        }

        col[a]=oca; col[b]=ocb;

    }
    best.ST*=2;
    return best;
}

int main(){
    int ti=0;
    while(1){
        REP(i,n) e[i].clear();
        ++ti;

        n=0;
        memset(rmp,-1,sizeof(rmp));
        while(1){
            if (scanf(" %s",buf)<=0) return 0;
            if (buf[0]=='0') break;
            int a=get(buf[0]), b=get(buf[1]);
            e[a].pb(b);
            e[b].pb(a);
        }

        pii res=solve();
        printf("Case %d: ",ti);
        if (res.ST==maxn) puts("impossible");
        else printf("%d %d\n",res.ST, res.ND);
    }

    return 0;
}

