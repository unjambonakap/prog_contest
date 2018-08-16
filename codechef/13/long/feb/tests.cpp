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
#include<sys/resource.h>
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

const int maxn=3e5+1000;
const int maxv=2e6+10;

int A[maxn],u[maxv];
vi e[maxn];
int n;
int used[maxn];
int tb[maxn];

int pp[maxv];

int lst[maxn];
int have[maxn];
int mx[maxn];
int pos;

ll _val[maxn], _val2[maxn], *val, *val2;
int _cnt[maxn], _cnt2[maxn], *cnt,*cnt2;

int dfs1(int a, int p){
    have[a]=1;
    lst[pos++]=a;
    mx[a]=0;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        int z=dfs1(b,a);
        have[a]+=z;
        if (mx[a]<z) mx[a]=z;
    }
    return have[a];
}

int dfs2(int a, int d, int f, int p=-1){
    int ret=d;

    f+=A[a];
    ++cnt2[f]; val2[f]+=d;
    REP(j,e[a].size()){
        int b=e[a][j];
        if (b==p) continue;
        ret=max(ret,dfs2(b,d+1,f,a));
    }
    return ret;
}


ll go(){
    memset(used,0,sizeof(used));
    ll res=0;

    REP(i,n) tb[i]=i;
    int x=0;

    val=_val+maxn/2;
    val2=_val2+maxn/2;
    cnt=_cnt+maxn/2;
    cnt2=_cnt2+maxn/2;

    while(1){
        while(x<n && used[tb[x]]) ++x;
        if (x==n) break;
        int y=tb[x];

        pos=0;
        int nx=dfs1(y,-1);
        int best=-1, bestv=n;
        REP(i,pos){
            int a=lst[i];
            int vv=max(mx[a],nx-have[a]);
            if (vv<bestv) bestv=vv, best=a;
        }
        //assert(bestv<=nx/2);
        
        //printf("%d\n",x);

        int md=1;

        int ff=A[best];
        cnt[0]=1;

        REP(i,e[best].size()){
            int x=e[best][i];

            int dx=dfs2(x,1,0,best)+2;

            FOR(j,-dx,dx+1) val[j]+=val2[j], cnt[j]+=cnt2[j];


            ll ans=0;
            //assert(cnt2[dx+1]==0);
            for (int j=dx; j>=-dx; --j) cnt2[j]+=cnt2[j+1];
            FOR(j,-dx,dx+1) ans+=val2[j]*cnt2[-j-ff];
            REP(j,dx+1) if (2*j+ff>=0) ans-=val2[j];

            ll npath=0;
            FOR(j,-dx,dx+1) npath+=1ll*(cnt2[j]-cnt2[j+1])*cnt2[-j-ff];
            REP(j,dx+1) if (2*j+ff>=0) npath-=cnt2[j]-cnt2[j+1];
            //assert(npath%2==0);
            npath/=2;

            ans+=npath;
            res-=ans;

            FOR(j,-dx,dx+1) val2[j]=cnt2[j]=0;

            md=max(md,dx);
        }

        int dx=md;
        ll ans=0;
        for (int j=dx; j>=-dx; --j) cnt[j]+=cnt[j+1];

        FOR(j,-dx,dx+1) ans+=val[j]*cnt[-j-ff];
        REP(j,dx+1) if (2*j+ff>=0) ans-=val[j];

        ll npath=0;
        FOR(j,-dx,dx+1) npath+=1ll*(cnt[j]-cnt[j+1])*cnt[-j-ff];
        REP(j,dx+1) if (2*j+ff>=0) npath-=cnt[j]-cnt[j+1];
        //assert(npath%2==0);
        npath/=2;
        ans+=npath;
        res+=ans;


        if (ff==1) ++res;

        REP(i,e[best].size()){
            int a=e[best][i];
            int nx=e[a].size();
            REP(j,nx) if (e[a][j]==best){swap(e[a][j],e[a][nx-1]); e[a].pop_back(); break;}
        }
        used[best]=1;
        FOR(j,-dx,dx+1) val[j]=cnt[j]=0;
    }

    return res;
}

int checkit1(int a){
    int s=0;
    FOR(i,1,a+1) if (a%i==0) s^=i&1;
    return s;
}

int dfs3(int a, int b, int x, int y, int p){
    ++x;
    y+=A[a];
    if (a==b) return y>=0?x:0;
    REP(i,e[a].size()){
        int aa=e[a][i];
        if (aa==p) continue;
        int r=dfs3(aa,b,x,y,a);
        if (r) return r;
    }
    return 0;
}

int checkit2(){
    int res=0;
    REP(i,n) REP(j,i+1) res+=dfs3(i,j,0,0,-1);
    
    return res;
}

void setstack(){

    const rlim_t kStackSize = 256 * 1024L * 1024L;   // min stack size = 64 Mb
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
                exit(-1);
            }
        }
    }
}

int main(){
    setstack();
    memset(pp,0,sizeof(pp));
    FOR(i,2,1e4) if (!pp[i]){
        for (int j=i*i; j<maxv; j+=i) pp[j]=i;
    }
    u[1]=1;
    FOR(i,2,maxv){
        if (!pp[i]) u[i]=i+1&1;
        else{
            ll x=1;int y=i, p=pp[i];
            while(y%p==0) y/=p, x*=p;
            u[i]=((x*p-1)/(p-1))&u[y];
        }
        //assert(u[i]==checkit1(i));
    }

    srand(0);

    while(1){
        int rnd=0;
        if (rnd==1) n=rand()%600+3;
        else if (rnd==2) n=rand()%int(3e5)+1;
        else cin>>n;

        REP(i,n-1){
            int a,b;
            if (rnd) a=i+2, b=rand()%(i+1)+1;
            else scanf(" %d%d",&a,&b);

            --a; --b;
            e[a].pb(b); e[b].pb(a);
        }

        REP(i,n){
            int x;
            if (rnd) x=rand()%(20-1)+1;
            else scanf(" %d",&x);
            A[i]=2*u[x]-1;
        }


        ll ans=0;
        if (rnd==1) ans=checkit2(), cout<<ans<<endl;
        ll res=go();
        cout<<res<<endl;

        if (rnd==1) assert(ans==res);
        else if (!rnd) break;
        REP(i,n) e[i].clear();
    }

    return 0;
}

