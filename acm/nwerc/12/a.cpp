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

const int maxn=2*1111;
const int maxe=4*11111;

int to[maxe], from[maxe], u[maxe], f[maxe], last[maxn], prev[maxe];
int c[maxe];
int P[maxn];
int d[maxn];
int par[maxn];
int vis[maxn];

int ne;
int n;

int adde(int a, int b, int _u, int _c){
    int x=ne; 
    to[ne]=b; from[ne]=a; u[ne]=_u; f[ne]=0; c[ne]=_c;prev[ne]=last[a]; last[a]=ne++;
    to[ne]=a; from[ne]=b; u[ne]=0; f[ne]=0; c[ne]=-_c; prev[ne]=last[b]; last[b]=ne++;
    return x;
}

void init(){
    memset(P,0x1f,sizeof(P));
    P[0]=0;

    priority_queue<pii,vector<pii>, greater<pii> > q;
    q.push(make_pair(0,0));
    while (!q.empty())
    {
        int v=q.top().second;
        if (q.top().first!=P[v])
        {
            q.pop();
            continue;
        }
        q.pop();
        for (int w=last[v];w>=0;w=prev[w])
        {
            if (f[w]<u[w] && P[v]+c[w]<P[to[w]])
            {
                P[to[w]]=P[v]+c[w];
                q.push(make_pair(P[to[w]],to[w]));
            }
        }
    }

}

int augment(){
    REP(i,n) d[i]=1e9;
    d[0]=0;
    par[0]=-1;

    priority_queue<pii,vector<pii>, greater<pii> > q;
    q.push(MP(0,0));
    memset(vis,0,sizeof(vis));
    while(!q.empty()){
        int dx=q.top().ST;
        int p=q.top().ND;
        q.pop();
        if (vis[p]) continue;
        vis[p]=1;

        for (int i=last[p]; i!=-1; i=prev[i]) if (u[i]>f[i] && !vis[to[i]]){
            int nd=dx+c[i]+P[p]-P[to[i]];
            //printf("EDGE %d %d >> %d\n", from[i], to[i], nd);
            //assert(c[i]+P[p]-P[to[i]]>=0.);
            if (d[to[i]]>nd) d[to[i]]=nd, par[to[i]]=i, q.push(MP(nd,to[i]));
        }
    }
    if (!vis[n-1]) return 0;
    REP(i,n) P[i]+=d[i];

    int x=par[n-1];
    while(x!=-1){++f[x]; --f[x^1]; x=par[from[x]]; }
    return P[n-1]-P[0];
}


int main(){
    int m;
    while(scanf(" %d%d",&n,&m)>0){
        ne=0;
        memset(last,-1,sizeof(last));
        memset(c,0,sizeof(c));
        memset(f,0,sizeof(f));
        memset(u,0,sizeof(u));

        REP(i,m){
            int a,b,c; scanf(" %d%d%d",&a,&b,&c);
            adde(n+a-1,b-1,1,c);
        }
        REP(i,n) adde(i,n+i,(i==0||i==n-1?2:1),0);
        int res=0;
        n*=2;
        init();
        REP(j,2) res+=augment();
        printf("%d\n",res);
    }
    return 0;
}

