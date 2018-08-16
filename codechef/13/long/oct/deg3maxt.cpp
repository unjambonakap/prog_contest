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


const int maxn=111;
const int maxx=9;
const int oo=1e8;
struct res_t{
    int cost; uint ways;
    res_t(int cost=-oo, uint ways=0):cost(cost),ways(ways){}

    res_t mul(const res_t &b)const{ return res_t(cost+b.cost,ways*b.ways); }
    bool operator==(const res_t &a)const{return cost==a.cost && ways==a.ways;}
};


vector<pii> e[maxn];
vector<pii> ecc[maxn];

res_t dp[maxn][2];
int done[maxn];

int vis[maxn];
int when;
vi tb;

int nc,n;
int g[maxx][maxx];
vector<vi> ccl;
vi has[maxn];
int parv[maxn];
int N;

res_t RES;

void clear(){
    REP(i,maxn) e[i].clear();
    REP(i,maxn) ecc[i].clear();

    ccl.clear();
    tb.clear();
    REP(i,maxn) has[i].clear();
}


void update(res_t &a, const res_t &b){
    if (a.cost<b.cost) a=b;
    else if (a.cost==b.cost) a.ways+=b.ways;
}


res_t costx[maxx][2];


res_t dp2[1<<maxx][maxx][maxx+2][3][2];//subtree,cur,last,in deg
int done2[1<<maxx][maxx][maxx+2][3][2];

res_t solve(int m, int a, int last, int d, int force=0){
    if (d==3) return m?res_t(-oo,0):res_t(0,1);

    res_t &r=dp2[m][a][last][d][force];
    if (done2[m][a][last][d][force]++) return r;

    r=res_t(-oo,0);
    if (last==N+1){
        REP(i,3) if (i+d<=3 && (!i || costx[a][i-1].cost>-oo)) update(r,solve(m,a,0,d+i,force).mul(i?costx[a][i-1]:res_t(0,1)));
    }else{
        if (m==0 && !force) r=res_t(0,1);
        FOR(i,last,N) if (g[a][i]!=-oo && (m&1<<i)){
            int nm=m^1<<i;
            for (int j=nm;; j=nm&j-1){
                res_t resa=solve(j,i,N+1,1,0);
                resa.cost+=g[a][i];
                res_t resb=solve(nm^j,a,i+1,d+1,force);

                update(r,resa.mul(resb));
                if (!j) break;
            }
        }
    }
    return r;
}


res_t go2(int a, int d){
    if (done[a]++) return dp[a][d];

    map<int,int> rmp;
    N=ccl[a].size();
    REP(i,N) rmp[ccl[a][i]]=i;

    REP(i,ecc[a].size()) go2(ecc[a][i].ND,1);

    N=ccl[a].size();
    REP(i,N) REP(f,2) costx[i][f]=res_t(-oo,0);

    for (int ii=0; ii<ecc[a].size(); ++ii){
        int j=ii;
        vector<res_t> l1,l2;
        for (;j<ecc[a].size() && ecc[a][ii].ST==ecc[a][j].ST; ++j) l1.pb(go2(ecc[a][j].ND,0)), l2.pb(go2(ecc[a][j].ND,1));
        int nx=l1.size();
        REP(i,nx) REP(j,nx) if (i!=j) update(RES,l1[i].mul(l2[j]));
        REP(i,nx) REP(j,i) REP(k,j) update(RES,l1[i].mul(l1[j]).mul(l1[k]));

        int u=rmp[ecc[a][ii].ST];

        REP(i,nx) update(costx[u][0],l1[i]);
        REP(i,nx) update(costx[u][1],l2[i]);
        REP(i,nx) REP(j,i) update(costx[u][1],l1[i].mul(l1[j]));

        ii=j-1;
    }

    REP(i,N) REP(j,N) g[i][j]=-oo;

    REP(i,N){
        int u=ccl[a][i];
        REP(j,e[u].size()) if (rmp.count(e[u][j].ST)) g[i][rmp[e[u][j].ST]]=e[u][j].ND;
    }
    //printf("GOGOGO cc %d >> ",a); out(ccl[a]);
    //REP(i,N) out(g[i],N);
    //printf(">> >COST\n");
    //REP(i,N) REP(j,2) printf("%d %d >> %d %d\n",i,j,costx[i][j].cost,costx[i][j].ways);
    //printf(">>> PARENT %d\n",parv[a]);
    //puts("");


    REP(f,2) dp[a][f]=res_t(-oo,0);
    memset(done2,0,sizeof(done2));



    REP(i,1<<N) if (i){
        int st=-1;
        REP(j,N) if (i&1<<j){ st=j; break; }

        if (parv[a]!=-1 && (i&1<<rmp[parv[a]])){
            int u=rmp[parv[a]];
            REP(f,2) update(dp[a][f],solve(i^1<<u,u,N+1,2-f,1));
            res_t ans=solve(i^1<<u,u,N+1,0,1);
            update(RES,ans);
        }else{
            res_t ans=solve(i^1<<st,st,N+1,0);
            update(RES,ans);
        }
        
    }
    //REP(f,2) printf("xaxa %d %d\n",dp[a][f].cost, dp[a][f].ways);


    return dp[a][d];
}



void dfs2(int a, int p=-1){
    assert(parv[a]==-1);
    parv[a]=p;
    REP(i,ccl[a].size()){
        int b=ccl[a][i];
        if (b==p) continue;
        REP(j,has[b].size()){
            int x=has[b][j];
            if (x==a) continue;
            dfs2(x,b);
            ecc[a].pb(MP(b,x));
        }
    }
}


int dfs(int a, int p=-1){
    int x=vis[a]=when++;

    tb.pb(a);
    REP(i,e[a].size()){
        int b=e[a][i].ST;
        if (vis[b]==-1){
            int pos=tb.size();
            int v=dfs(b,a);
            x=min(x,v);
            if (v>=vis[a]){
                vi tmp;
                while(tb.size()>pos) tmp.pb(tb.back()), tb.pop_back();
                tmp.pb(a);

                ccl.pb(tmp);
            }
        }else x=min(x,vis[b]);
    }

    return x;
}

res_t go(){
    if (n==1) return res_t(0,1);

    memset(vis,-1,sizeof(vis));
    when=0;


    dfs(0);
    nc=ccl.size();

    int mx=0;
    REP(i,ccl.size()) mx=max(mx,(int)ccl[i].size());
    if (mx>maxx){
        int x=5/0;
        printf("%d\n",x);
    }

    
    REP(i,nc) REP(j,ccl[i].size()) has[ccl[i][j]].pb(i);
    memset(parv,-1,sizeof(parv));
    dfs2(0);

    //puts("cc stats");
    //REP(i,nc) out(ccl[i]);
    //puts("end of 2cc");
    //REP(i,nc){
    //    REP(j,ecc[i].size()) printf("(%d %d) ",ecc[i][j].ST,ecc[i][j].ND);
    //    puts("");
    //}

    int best,bestc;
    memset(done,0,sizeof(done));
    RES=res_t(0,0);
    go2(0,1);

    clear();
    return RES;
}


void adde(int a, int b, int c){
    e[a].pb(MP(b,c));
    e[b].pb(MP(a,c));
}
void parse(){
    cin>>n;
    int m; cin>>m;
    REP(i,m){
        int a,b,c; scanf(" %d%d%d",&a,&b,&c);
        adde(a-1,b-1,c);
    }
}

int stupid_deg[maxn];
int par[maxn];
int root(int a){return par[a]<0?a:par[a]=root(par[a]);}
int join(int a, int b){a=root(a); b=root(b); if (a!=b){ par[a]=b; return 0;} return 1;}

int checkit(){
    int cnt=n;
    memset(par,-1,sizeof(par));
    REP(i,n) REP(j,e[i].size()) cnt-=1-join(i,e[i][j].ST);
    return cnt==1;

}
int randcost(){return rand()%1;}

void get_gen(){
    int type=3;

    if (type==0){
        n=100;
        REP(i,n-1) adde(i,i+1,rand()%1000);
    }else if (type==1){
        n=1;
        REP(i,n) REP(j,i) adde(i,j,rand()%100-50);
    }else if (type==2){
        n=0;
        int ub=40;
        while(n+9<=ub){

            int sz=4+rand()%6;
            sz=9;
            if (n>0) adde(rand()%n,rand()%sz+n,randcost());
            int ne=sz-1+rand()%(sz*(sz-1)/2-sz);

            n+=sz;

            set<pii> has;
            while(has.size()<ne || !checkit()){
                int a=rand()%(sz-1)+1;
                int b=rand()%a;
                if (has.count(MP(a,b))) continue;
                has.insert(MP(a,b));
                adde(a+n-sz,b+n-sz,randcost());
            }

        }


    }else{
        n=9;
        set<pii> has;
        int ub=20;

        while(1){
            has.clear();
            REP(i,n) e[i].clear();

            while(has.size()<ub){
                int a=rand()%(n-1)+1;
                int b=rand()%a;
                if (has.count(MP(a,b))) continue;
                has.insert(MP(a,b));
                adde(a,b,randcost());
            }
            if (checkit()) break;
        }
        //REP(i,n) REP(j,e[i].size()) if (i<e[i][j].ST) printf("%d %d %d\n",i+1,1+e[i][j].ST,e[i][j].ND);
    }
}



res_t stupid(){
    vector<pair<pii,int> > el;
    REP(i,n) REP(j,e[i].size()) if (e[i][j].ST>i) el.pb(MP(MP(i,e[i][j].ST),e[i][j].ND));
    assert(el.size()<=20);
    res_t sol(0,1);

    REP(i,1<<el.size()){
        int c=0;
        memset(stupid_deg,0,sizeof(stupid_deg));
        memset(par,-1,sizeof(par));

        int cnt=0;
        REP(j,el.size()) if (i&1<<j){
            c+=el[j].ND;
            ++stupid_deg[el[j].ST.ST], ++stupid_deg[el[j].ST.ND]; 
            if (join(el[j].ST.ST,el[j].ST.ND)) goto fail;
        }
        REP(j,n) if (stupid_deg[j]>3) goto fail; else if (stupid_deg[j] && par[j]==-1) ++cnt;
        if (cnt!=1) continue;
        if (0&&c==90){
            puts("FUUU");
            REP(j,el.size()) if (i&1<<j) printf("%d %d xx %d\n",el[j].ST.ST,el[j].ST.ND,el[j].ND);
        }


        update(sol,res_t(c,1));
fail:;
    }
    if (sol.cost==0) sol.ways+=n;
    return sol;


}

int main(){
    srand(0);

    int tn; 
    int gen=0;
    int check=0;

    if (!gen) cin>>tn;
    else tn=10000;
start:

    REP(ti,tn){
        if (gen) get_gen();
        else parse();

        res_t sol;
        if (check) sol=stupid();
        res_t res=go();
        if (res.cost==0) ++res.ways;

        if (check){
            printf("%d %d xx %d %d\n",res.cost,res.ways,sol.cost,sol.ways);
            assert(sol==res);
            if (gen) goto start;
        }
        printf("%d %u\n",res.cost,res.ways);

    }

    //if (gen) goto start;

    return 0;
}

