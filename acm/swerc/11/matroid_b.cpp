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
int xInt(string s){int a; istringstream(s)>>a; return a;}
string xStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=1222;
const int maxm=666;
int rmp[11111];
int pos;
int m;
int x[maxm],y[maxm];
int have[maxm];
int par[maxn];
int is[maxm];


vi e[maxm];
int q[maxm],na,ne;
int par2[maxm];

int root(int a){return par[a]<0?a:par[a]=root(par[a]);}

int getid(int a){
    if (rmp[a]==-1) rmp[a]=pos++;
    return rmp[a];
}

int go(){
    memset(par,-1,sizeof(par));
    REP(i,m) if (have[i]){
        assert(root(x[i])!=root(y[i]));
        par[root(x[i])]=root(y[i]);
    }
    memset(is,0,sizeof(is));

        
    memset(par2,-1,sizeof(par2));
    na=ne=0;

    REP(i,m){
        if (!have[i] && root(x[i])!=root(y[i])) q[ne++]=i, par2[i]=-2;
        if (!have[i] && !have[i^1]) is[i]=1;
    }

    REP(i,m) if (par2[i]==-2 && is[i]){have[i]=1; return 1;}


    REP(i,m) e[i].clear();

    REP(i,m) if (have[i]){
        have[i]=0;
        memset(par,-1,sizeof(par));
        REP(j,m) if (have[j]) par[root(x[j])]=root(y[j]);

        REP(j,m) if (i!=j && !have[j] && !have[j^1]) e[j].pb(i);
        have[i]=1;
        REP(j,m) if (!have[j] && root(x[j])!=root(y[j])) e[i].pb(j);
    }

    while(na<ne){
        int u=q[na++];

        if (is[u]){
            while(u!=-2) have[u]^=1, u=par2[u];
            return 1;
        }
        REP(i,e[u].size()){
            int v=e[u][i];
            if (par2[v]==-1) par2[v]=u, q[ne++]=v;
        }
    }
    return 0;
}

int main(){
    while(cin>>m,m){
        pos=0; memset(rmp,-1,sizeof(rmp));

        REP(i,m){
            int a,b,c,d;
            scanf(" %d%d%d%d",&a,&b,&c,&d);
            a=getid(a);
            b=getid(b);
            c=getid(c);
            d=getid(d);
            x[2*i]=a;
            y[2*i]=b;
            x[2*i+1]=c;
            y[2*i+1]=d;
        }
        assert(pos<maxn);
        m*=2;
        memset(have,0,sizeof(have));
        int res=0;
        while(go()) ++res;
        printf("%d\n",res*2);

    }
    return 0;
}

