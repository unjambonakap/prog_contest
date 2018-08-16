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

#include<unistd.h>

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

const int maxn=95;
const int oo=1e9;

int n,m;
int A[maxn][maxn];
int f[maxn][maxn];
int bak[maxn][maxn], bakA[maxn][maxn];

int g[maxn][maxn];
map<char,int> rmpa, rmpb;
char bufa[maxn], bufb[maxn];
char buf[5];
int fx[maxn], vis[2*maxn];
int par[2*maxn];
int q[2*maxn];

int with[maxn];
int WHEN;
char str[int(1e7)];


int dfs(int a){
    if (vis[a]==WHEN) return 0;
    vis[a]=WHEN;
    REP(i,m) if (g[a][i] && (with[i]==-1 || dfs(with[i]))){
        with[i]=a;
        return 1;
    }
    return 0;
}

int go(){
    int res=0, cnt=0;

    memset(vis,0,sizeof(vis));
    memset(with,-1,sizeof(with));
    int sz=-1;
    REP(i,m) q[++sz]=i;
    WHEN=0;

    REP(i,m) REP(j,m) if (A[i][j]) g[i][j]=1;
    while(1){

        while(sz>=0){
            ++WHEN;
            if (!dfs(q[sz--])) goto fail;
        }
        int md=oo;
        REP(i,m) md=min(md,A[with[i]][i]);
        REP(j,m){
            int i=with[j];
            f[i][j]+=md;
            if (!(A[i][j]-=md)) g[i][j]=0, q[++sz]=i, with[j]=-1;
        }
        res+=md;
    }

fail:
    return res;
}

int augment(){
    memset(fx,0,sizeof(fx)); memset(vis,0,sizeof(vis));
    WHEN=1;
    int ok=1;

    REP(step,m){
        int u=0;
        q[u]=step;
        par[step]=-1;
        ++WHEN;
        vis[step]=WHEN;
        int fd=0;

        while(u>=0){
            int a=q[u--];
            REP(i,m) if (vis[i+m]!=WHEN && A[a][i]-g[a][i]>0){
                par[i+m]=a;
                vis[i+m]=WHEN;
                if (fx[i]){
                    REP(j,m) if (vis[j]!=WHEN && g[j][i]+f[j][i]>0) vis[j]=WHEN, q[++u]=j, par[j]=i+m;
                }else{fx[i]=1; fd=i+m; goto done;}
            }
        }
        return 0;
done:
        int x=fd;
        while(1){
            int y=par[x];
            ++g[y][x-m];
            x=par[y];
            if (x==-1) break;
            --g[y][x-m];
        }
    }
    return 1;
}
int go2(){
    int res=0, cnt=0;

    while(1){
        memcpy(bak,f,sizeof(f)); memcpy(bakA,A,sizeof(A));
        memset(g,0,sizeof(g));
        if (!augment()) break;

        int md=oo;
        REP(i,m) REP(j,m){
            if (g[i][j]>0) md=min(md,A[i][j]/g[i][j]);
            else if (g[i][j]<0) md=min(md,f[i][j]/-g[i][j]);
        }
        res+=md;
        REP(i,m) REP(j,m) f[i][j]+=g[i][j]*md, A[i][j]-=g[i][j]*md;
    }
    memcpy(f,bak,sizeof(f)); memcpy(A,bakA,sizeof(A));
    return res;
}



void build(){
    int res=0, cnt=0;

    memset(vis,0,sizeof(vis));
    memset(with,-1,sizeof(with));
    int sz=-1;
    REP(i,m) q[++sz]=i;
    WHEN=0;

    memcpy(g,f,sizeof(f));
    int N=0;
    memset(str,0,sizeof(str));
    while(1){

        while(sz>=0){
            ++WHEN;
            if (!dfs(q[sz--])) goto fail;
        }
        int md=oo;
        REP(i,m) md=min(md,g[with[i]][i]);
        N+=sprintf(str+N,"%d",md);
        REP(i,m) if (with[i]<n){
            str[N++]=' ', str[N++]=bufa[with[i]], str[N++]=bufb[i];
        }
        str[N++]='\n';
        ++cnt;

        REP(j,m){
            int i=with[j];
            if (!(g[i][j]-=md)) q[++sz]=i, with[j]=-1;
        }
        res+=md;
    }
fail:;
     printf("%d\n",cnt);
     printf("%s",str);

}


void bench(){
    n=m=maxn-1;
    REP(i,n) REP(j,m) A[i][j]=rand()%int(1e6+1);
    REP(i,n) bufa[i]=33+i, rmpa[33+i]=i;
    REP(i,n) bufb[i]=33+i, rmpb[33+i]=i;

}

int main(){
    srand(0);
    int tn; cin>>tn;
    REP(ti,tn){
        rmpa.clear(); rmpb.clear();
        cin>>n;
        scanf(" %s",bufa);
        REP(i,n) rmpa[bufa[i]]=i;

        cin>>m;
        scanf(" %s",bufb);
        REP(i,m) rmpb[bufb[i]]=i;

        REP(i,n) REP(j,m){
            int x;
            scanf(" %s %d",buf,&x);
            A[rmpa[buf[0]]][rmpb[buf[1]]]=x;
        }
        if (n>m) puts("0\n0");
        else{
            //bench();
            FOR(i,n,m) REP(j,m) A[i][j]=oo;

            memset(f,0,sizeof(f));
            int res=0;
            res+=go();
            res+=go2();
            printf("%d\n",res);
            build();
        }
    }
    return 0;
}

