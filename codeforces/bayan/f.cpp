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



const int maxn=111;
const int maxc=27;

int n,m,K;
int old;

int g[maxc][maxc];
int A[maxn][maxn];
char buf[1111];

int dist[maxn][maxn];
pii prev[maxn][maxn];

int ra[maxc], ca[maxc];
int ri,ci,rf,cf;

int vx[]={1,-1,0,0};
int vy[]={0,0,1,-1};

int in(int a, int b){return a>=0 && a<n && b>=0 && b<m;}

void go(int xa, int ya){
    memset(dist,0x7f,sizeof(dist));
    priority_queue<pii> q;
    q.push(MP(0,xa*m+ya));
    dist[xa][ya]=0;

    while(q.size()){
        int x=q.top().ND/m, y=q.top().ND%m;
        int d=-q.top().ST;
        q.pop();
        if (dist[x][y]!=d) continue;
        int nd=d;
        if (A[x][y]>0) nd+=A[x][y];
        else{
            if (xa!=x || ya!=y) continue;
            ++nd;
        }

        REP(k,4){
            int nx=x+vx[k], ny=y+vy[k];
            if (!in(nx,ny)) continue;
            if (A[nx][ny]!=0 && dist[nx][ny]>nd) prev[nx][ny]=MP(x,y), dist[nx][ny]=nd, q.push(MP(-nd,nx*m+ny));
        }
    }
}


void go(int u){
    if (ra[u]==-1) return;
    memset(dist,0x7f,sizeof(dist));
    priority_queue<pii> q;
    q.push(MP(0,ra[u]*m+ca[u]));
    dist[ra[u]][ca[u]]=0;

    while(q.size()){
        int x=q.top().ND/m, y=q.top().ND%m;
        int d=-q.top().ST;
        q.pop();
        if (dist[x][y]!=d) continue;
        int nd=d;
        if (A[x][y]<0) g[u][-A[x][y]-1]=d;

        if (A[x][y]>0) nd+=A[x][y];
        else{
            ++nd;
            if (A[x][y]!=-u-1) continue;
        }

        REP(k,4){
            int nx=x+vx[k], ny=y+vy[k];
            if (!in(nx,ny)) continue;
            if (A[nx][ny]!=0 && dist[nx][ny]>nd) dist[nx][ny]=nd, q.push(MP(-nd,nx*m+ny));
        }
    }
}

void find(int ra, int ca, int rb, int cb, int K){
    K-=dist[rb][cb];
    while(K<0){
        pii x=prev[rb][cb];
        rb=x.ST; cb=x.ND;
        if (A[rb][cb]>0) K+=A[rb][cb];
        else ++K;
    }
    printf("%d %d\n",rb+1,cb+1);
}

void doit(){
    int ns=strlen(buf);

    go(ri,ci);
    int u=buf[0]-'a';
    int dx=dist[ra[u]][ca[u]];
    if (dx>=K){find(ri,ci,ra[u],ca[u],K); return;}
    K-=dx;

    REP(i,ns-1){
        int ua=buf[i]-'a', ub=buf[i+1]-'a';
        int dx=g[ua][ub];
        if (dx>=K){
            go(ra[ua],ca[ua]);
            find(ra[ua],ca[ua],ra[ub],ca[ub],K);
            return;
        }
        K-=dx;
    }


    u=buf[ns-1]-'a';
    go(ra[u],ca[u]);
    dx=dist[rf][cf];
    K=min(K,dx);
    find(ra[u],ca[u],rf,cf,K);
}


int main(){
    cin>>n>>m>>K;
    memset(ra,-1,sizeof(ra));
    memset(g,1,sizeof(g));
    REP(i,n){
        scanf(" %s",buf);
        REP(j,m){
            if (buf[j]=='#') A[i][j]=0;
            else if (buf[j]<='9') A[i][j]=buf[j]-'0';
            else A[i][j]=-(buf[j]-'a'+1), ra[buf[j]-'a']=i,ca[buf[j]-'a']=j;
        }
    }
    int nx=maxc;

    old=K;
    REP(i,nx) go(i);

    scanf(" %d %d %s %d %d\n",&ri,&ci,buf,&rf,&cf);
    --ri; --ci; --rf; --cf;

    doit();

    return 0;
}

