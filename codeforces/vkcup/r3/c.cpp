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
const int maxk=55;
const int maxe=maxn*maxn;

int to[maxe], from[maxe], u[maxe], f[maxe], last[maxn], prev[maxe];
int c[maxe];
int P[maxn];
int d[maxn];
int par[maxn];
int vis[maxn];

int ne;
int n;
int cnt;
const int inf=1e9;

int adde(int a, int b, int _u, int _c){
    int x=ne; 
    to[ne]=b; from[ne]=a; u[ne]=_u; f[ne]=0; c[ne]=_c;prev[ne]=last[a]; last[a]=ne++;
    to[ne]=a; from[ne]=b; u[ne]=0; f[ne]=0; c[ne]=-_c; prev[ne]=last[b]; last[b]=ne++;
    return x;
}

void init(){
    memset(P,0x7f,sizeof(P));
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
    if (!vis[1]) return 0;
    REP(i,n) P[i]+=d[i];

    int x=par[1];
    while(x!=-1){ ++f[x]; --f[x^1]; x=par[from[x]]; }
    return P[1]-P[0];
}


int s[maxn], t[maxn], cx[maxn];
int main(){
    int na, k;

    cin>>na>>k;
    REP(i,na) scanf(" %d%d%d", s+i,t+i,cx+i);
    vector<pii> sl;
    REP(i,na) sl.pb(MP(s[i],i));
    sort(ALL(sl));

    memset(last,-1,sizeof(last));
    ne=0;
    n=2*na+2;
    REP(i,na) adde(0,2+i,1,0), adde(2+i+na,1,1,0);

    vi tb(n);
    REP(i,na) tb[i]=adde(2+i,2+i+na,1,-cx[i]);
    REP(i,na-1) adde(2+sl[i].ND,2+sl[i+1].ND,inf,0);
    REP(i,na){
        int pos=lower_bound(ALL(sl),MP(s[i]+t[i],0))-sl.begin();
        if (pos<na) adde(2+i+na,2+sl[pos].ND,inf,0);
    }

    init();
    REP(i,k) if (!augment()) break;
    
    REP(i,na){
        if (i) printf(" ");
        printf("%d",f[tb[i]]);
    }
    puts("");

    return 0;
}

