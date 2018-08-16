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

const int maxm=111111;
int vx[]={1,1,0,-1,-1,0};
int vy[]={0,1,1,0,-1,-1};

int S;
int n;
int par[maxm];
int par2[11];
int hascorner[maxm];
int hasborder[maxm];
map<pii,int> corner;
map<pii,int> rmp;
int px[maxm], py[maxm];
vi adjl[maxm];

const char *tb[]={"bridge", "fork", "ring"};


int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
void join(int a, int b){
    a=root(a); b=root(b);
    if (a!=b) hascorner[a]|=hascorner[b], hasborder[a]|=hasborder[b], par[b]=a;
}


int root2(int a){return par2[a]==-1?a:par2[a]=root2(par2[a]);}
void join2(int a, int b){
    a=root2(a); b=root2(b);
    if (a!=b) par2[b]=a;
}


int isborder(int x, int y){
    if (corner.count(MP(x,y))) return 0;
    if (x==2*S-1) return 1;
    if (y==2*S-1) return 2;
    if (x==1) return 3;
    if (y==1) return 4;
    if (fabs(x-y)==S-1) return x>S?5:6;
    return 0;
}

int iscorner(int x, int y){return corner.count(MP(x,y))?corner[MP(x,y)]:0;}

int in(int x, int y){return x>=1 && y>=1 && x<2*S && y<2*S && fabs(x-y)<S;}

int go(int a, int b){
    int f=0;

    px[n]=a; py[n]=b;
    rmp[MP(a,b)]=n;
    adjl[n].clear();

    int x=isborder(a,b);
    if (x) hasborder[n]=1<<x;
    x=iscorner(a,b);
    if (x) hascorner[n]=1<<x;

    REP(k,6){
        int nx=a+vx[k], ny=b+vy[k];
        if (in(nx,ny) && rmp.count(MP(nx,ny))) adjl[n].pb(rmp[MP(nx,ny)]);
    }
    int vis=0;
    REP(i,adjl[n].size()) if (!(vis&(1<<i))){
        vi lst;
        int u=root(adjl[n][i]);
        map<int,int> rmp2;
        REP(j,adjl[n].size()) if (root(adjl[n][j])==u) vis|=1<<j, rmp2[adjl[n][j]]=lst.size(), lst.pb(adjl[n][j]);
        if (lst.size()==1) continue;

        memset(par2,-1,sizeof(par2));
        REP(j,lst.size()){
            int x=lst[j];
            REP(k,adjl[x].size()) if (rmp2.count(adjl[x][k])) join2(rmp2[adjl[x][k]],rmp2[x]);
        }
        int fd=0;
        REP(j,lst.size()) if (root2(j)!=root2(0)) fd=1, f|=4;
        if (0) if (fd){
            printf("adjacency list: %d\n", lst.size());
            out(lst);
            REP(j,lst.size()) printf("%d %d\n", px[lst[j]], py[lst[j]]); 
        }
        if (fd) break;
    }

    REP(i,adjl[n].size()) join(n,adjl[n][i]);

    int u=root(n);
    if (count_bit(hascorner[u])>=2) f|=1;
    if (count_bit(hasborder[u])>=3) f|=2;
    ++n;
    return f;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        int M; cin>>S>>M;
        corner.clear();
        int tmp=1;

        corner[MP(1,1)]=tmp++;
        corner[MP(S,1)]=tmp++;
        corner[MP(1,S)]=tmp++;
        corner[MP(S,2*S-1)]=tmp++;
        corner[MP(2*S-1,S)]=tmp++;
        corner[MP(2*S-1,2*S-1)]=tmp++;
        rmp.clear();
        n=0;

        memset(hasborder,0,sizeof(hasborder));
        memset(hascorner,0,sizeof(hascorner));
        memset(par,-1,sizeof(par));

        printf("Case #%d: ", ti+1);
        int fd=0;
        REP(step,M){
            int a, b; scanf(" %d%d", &a,&b);
            if (fd) continue;
            int f=go(a,b);
            if (!f) continue;
            string x;
            REP(i,3) if (f&(1<<i)){ if (x.length()) x+="-"; x+=tb[i]; }
            cout<<x;
            printf(" in move %d\n", step+1);
            fd=1;
        }
        if (!fd) puts("none");

    }
    return 0;
}


