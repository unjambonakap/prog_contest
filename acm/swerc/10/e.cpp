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

const int maxn=11111;
const int maxt=6006;
int n,t;

char rmp[256];
char buf[maxn];

int par[maxn];
int tb[maxn];
int val[maxn];
int with[maxn];
int mod[maxn];
int fix[maxn];

int rmp2[maxn];
int STEP;
int vis[maxn];

vi ta[maxn];
int cntb[16];
int mid[16];
int when[maxn];


vi order,order2;
vi e[maxn], et[maxn];



int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
void join(int a, int b){a=root(a); b=root(b); if (a!=b) par[a]=b;}

void dfs(int a){
    if (vis[a]) return;
    vis[a]=1;
    REP(i,e[a].size()) dfs(e[a][i]);
    order.pb(a);
}

void dfst(int a){
    if (vis[a]) return;
    vis[a]=1;
    order2.pb(a);
    REP(i,et[a].size()) dfst(et[a][i]);

}


int go(){

    int na=0;
    memset(with,-1,sizeof(with));
    memset(fix,0,sizeof(fix));
    memset(val,0,sizeof(val));
    memset(mod,0,sizeof(mod));

    REP(i,n){
        int u=root(i);
        int x=with[u]==-1?na++:with[u];

        val[x]|=1<<buf[i];
        with[i]=with[u]=x;
        ta[x].pb(i);
    }

    REP(i,na) if (val[i]==15) return 0;

    vi lst;
    REP(i,na) if (cntb[val[i]]==3){
        fix[i]=1;
        REP(j,ta[i].size()){
            int a=ta[i][j];
            if (buf[a]!=mid[val[i]]) mod[a]=1, lst.pb(a);
        }
    }

    while(lst.size()){
        int a=lst.back(); lst.pop_back();
        for (int i=a-1; i<=a+1; i+=2) if (i>=0&&i<n){
            int u=with[i];
            if (fix[u] || cntb[val[u]]==1) continue;
            assert(cntb[val[u]]==2);

            fix[u]=1;
            REP(j,ta[u].size()){
                int b=ta[u][j];
                if (buf[b]!=buf[i]) mod[b]=1, lst.pb(b);
            }
        }
    }
    REP(i,n-1) if (mod[i]&&mod[i+1]) return 0;


    //now 2sat

    memset(rmp2,-1,sizeof(rmp2));
    int nc=0;
    REP(i,na) if (!fix[i]&&cntb[val[i]]==2){
        rmp2[i]=nc;
        nc+=2;
    }

    REP(i,n-1){
        int u=with[i], v=with[i+1];
        if (rmp2[u]==-1 || rmp2[v]==-1) continue;
        int fu=buf[i]!=mid[val[u]], fv=buf[i+1]!=mid[val[v]];
        //fu or fv
        e[rmp2[u]+1-fu].pb(rmp2[v]+fv);
        e[rmp2[v]+1-fv].pb(rmp2[u]+fu);
    }
    REP(i,nc) REP(j,e[i].size()) et[e[i][j]].pb(i);



    int res=0;

    order.clear();
    memset(vis,0,sizeof(vis));
    REP(i,n) if (!vis[i]) dfs(i);

    memset(vis,0,sizeof(vis));
    memset(when,-1,sizeof(when));
    REPV(i,n) if (!vis[order[i]]){
        order2.clear();
        dfst(order[i]);
        REP(j,order2.size()){
            if (when[order2[j]/2]==i) goto fail;
            when[order2[j]/2]=i;
        }
    }
    res=1;
fail:;

    REP(i,nc) e[i].clear(), et[i].clear();;
    return res;

}

int main(){
    rmp['A']=0; rmp['G']=1;
    rmp['T']=2; rmp['C']=3;

    REP(i,16){
        cntb[i]=count_bit(i);
        vi pos;
        REP(j,4) if (i&(1<<j)) pos.pb(j);
        if (cntb[i]==1) mid[i]=pos[0];
        else if (cntb[i]==2){
            if (pos[0]+1==pos[1]) mid[i]=pos[0];
            else if (pos[1]-3==pos[0]) mid[i]=pos[1];
            else cntb[i]=3, mid[i]=pos[0]+1;
        }else if (cntb[i]==3){
            REP(j,4) if (!(i&1<<j)){mid[i]=(j+2)%4; break;}
        }
    }




    int tc=0;
    while(cin>>n>>t,n){
        scanf(" %s",buf);
        REP(i,n) buf[i]=rmp[buf[i]];

        memset(par,-1,sizeof(par));
        REP(i,t){
            int na; scanf("%d:",&na);
            REP(j,na) scanf(" %d",tb+j);
            REP(j,na/2) join(tb[j],tb[na-1-j]);
        }
        puts(go()?"YES":"NO");

        REP(i,n) ta[i].clear();
    }
    return 0;
}

