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

const int maxp=111;
const int maxn=505;
const int maxN=maxn*maxn;
const double inf=1e100;
const double thres=2;

const int samplerate=30;

double mp[maxn][maxn];
int A[maxN];
int next[maxN][4];


int vx[]={0,1,0,-1,1,1,-1,-1,0};
int vy[]={1,0,-1,0,1,-1,1,-1,0};

vi C[maxN];
int isb[maxN];
int with[maxN];
int vis[maxN];
int par[maxN];
int added[maxN];
int spe[maxN];

vi nxt[maxN];
vi adj[maxN];

int nc;
int step;

int W, H;
int N;
FILE *F;
int CAN;

vi repr[maxN];
vi peak[maxN];
int done[maxN];

vi ex[maxN];



int par2[maxN];
double cl[maxN], vl[maxN];
int U[maxN];
double D[maxN];


vector<double> res;

int bestA, bestB, bestL;
int depth[maxn];



double measure(int x, int y){ 
    puts("?");
    fprintf(stdout,"%d\n%d\n", x,y);
    fflush(stdout);
    double res; scanf(" %lf", &res);
    return res;
}
double _measure(int x, int y){ assert(CAN); --CAN; return measure(y,x); }


double dist(int a, int b){return sqrt(a*a+b*b);}
int in(int a, int b){return a>=0&&b>=0&&a<H&&b<W;}
double sqr(double a){return a*a;}
double remap(double a){if (a<0) a=0; if (a>100) a=100; return a;}


void dfs1(int a){
    with[a]=nc;
    vi &c=C[nc];
    c.clear(); nxt[nc].clear();
    c.pb(a);

    for (int p=0; p<c.size();){
        a=c[p++];
        REP(k,4){
            int b=next[a][k];
            if (b==-1) isb[nc]=1;
            else if (A[a]==A[b] && with[b]==-1) with[b]=nc, c.pb(b);
        }
    }
    ++nc;
}




double randdouble(double a, double b){
    int u=rand()&(1ll*(1<<31)-1);
    return a+(b-a)*u/(1<<31);
}

void evalp(int a){
    done[a]=1;
    int nv=1;
    REP(j,nv) res[a]=_measure(a/W,a%W);
    res[a]/=nv;
}

void bfs(queue<int> &q, int y){
    ++step;
    while(!q.empty()){
        int a=q.front(); q.pop();
        REP(k,4){
            int b=next[a][k];
            if (b==-1 || with[b]!=y || U[b]==step) continue;
            U[b]=step; par2[b]=par2[a]; q.push(b);
            assert(b!=par2[b]);
            double tmp=dist(b/W-par2[b]/W,b%W-par2[b]%W);
            D[b]=min(D[b],tmp);

            tmp=1/tmp;
            tmp*=tmp;
            cl[b]+=tmp;
            vl[b]+=tmp*res[par2[b]];
        }
    }
}


vi leaflst;
pii dfs2(int a, int p=-1, int d=0){
    pii best1=MP(0,a), best2=MP(0,a);
    depth[a]=d;
    vi tmp;
    REP(i,nxt[a].size()) tmp.pb(nxt[a][i]);
    REP(i,adj[a].size()) tmp.pb(adj[a][i]);
    REP(i,tmp.size()){
        int u=tmp[i];
        REP(j,nxt[u].size()) if (spe[nxt[u][j]]&4) ex[a].pb(nxt[u][j]);
        REP(j,adj[u].size()) if (spe[adj[u][j]]&4) ex[a].pb(adj[u][j]);
    }

    REP(i,ex[a].size()){
        int b=ex[a][i];
        if (b==p) continue;
        pii x=dfs2(b,a,d+1);
        if (x.ST>best1.ST) best2=best1, best1=x;
        else if (x.ST>best2.ST) best2=x;
    }
    if (best1.ST+best2.ST>bestL) bestL=best1.ST+best2.ST, bestA=best1.ND, bestB=best2.ND;
    ++best1.ST;
    return best1;
}

void updatebest(priority_queue<pair<double,int> > &q, int i){
    double bestd=0; int best=-1;
    REP(j,C[i].size()){
        int a=C[i][j];
        if (done[a]) continue;
        res[a]=vl[a]/cl[a];
        if (D[a]>bestd) bestd=D[a], best=a;
    }
    if (best!=-1) q.push(MP(bestd,best));
}

double samplelevel(int a){

}

void dfs3(int a, double dv, int p=-1){

}

vector<double> getMap(vs cm){
    H=cm.size();
    W=cm[0].size();
    REP(i,H) REP(j,W) A[i*W+j]=cm[i][j]=='1';
    REP(i,H) fprintf(F,"%s\n", cm[i].c_str());
    fprintf(F,"\n");

    N=W*H;
    CAN=sqrt(N);

    REP(i,H) REP(j,W) REP(k,4){
        int x=i+vx[k],y=j+vy[k];
        next[i*W+j][k]=in(x,y)?x*W+y:-1;
    }

    memset(isb,0,sizeof(isb));
    memset(with,-1,sizeof(with));
    nc=0;

    REP(i,N) if (with[i]==-1) dfs1(i);


    {
        memset(vis,0,sizeof(vis));
        memset(par,-1,sizeof(par));
        vi q[2];
        int p=0, np=1;
        REP(i,nc) if (isb[i]) q[p].pb(i), vis[i]=1;


        memset(added,0,sizeof(added));
        step=0;
        while(q[p].size()){
            q[np].clear();
            REP(i,q[p].size()){
                ++step;
                int u=q[p][i];
                vi tmp;
                REP(j,C[u].size()) REP(k,4){
                    int b=next[C[u][j]][k];
                    if (b==-1) continue;
                    b=with[b];
                    if (b!=u && added[b]!=step) adj[u].pb(b), added[b]=step;
                    if (!vis[b]){
                        if (par[b]==-1) par[b]=u, q[np].pb(b);
                        else if (par[b]!=u) par[b]=-2;
                    }
                }
            }
            p=np; np^=1;
            REP(i,q[p].size()){
                int u=q[p][i];
                vis[u]=1;
                if (par[u]!=-2) nxt[par[u]].pb(u);
            }
        }

    }

    REP(i,nc) REP(j,adj[i].size()) if (par[adj[i][j]]==i) swap(adj[i][j],adj[i][adj[i].size()-1]), --j, adj[i].pop_back();





    REP(i,nc) spe[i]=A[C[i][0]];
    REP(i,nc) peak[i].clear(), repr[i].clear();




    memset(done,0,sizeof(done));
    res=vector<double>(N,0);
    REP(i,N) if (spe[with[i]]==1){
        int fd=1;
        REP(k,4) if (next[i][k]==-1 || !A[next[i][k]]){fd=0; break;}
        if (fd) spe[with[i]]|=2, peak[with[i]].pb(i), evalp(i);
    }


    REP(i,nc) if ((spe[i]&1) && adj[i].size()+nxt[i].size()>1) spe[i]|=4;

    REP(i,nc) ex[i].clear();
    bestA=bestB=bestL=0;
    int st=-1;
    leaflst.clear();
    REP(i,nc) if (spe[i]&4){st=i, dfs2(st); break;}
    double va=samplelevel(bestA);
    double vb=samplelevel(bestB);
    dfs3(bestB,vb,(vb-va)/bestL);


    REP(i,nc) if (spe[i]&1){
        int want=min((int)sqrt(C[i].size()),(int)C[i].size()/samplerate);
        want=8;
        want=min(want,(int)C[i].size());
        if (want==0) ++want;
        if (spe[i]&2) repr[i]=peak[i];
        want-=repr[i].size();
        if (want<0) want=0;

        vi tmp;
        REP(j,C[i].size()) if (!done[C[i][j]]) tmp.pb(C[i][j]);
        REP(j,want){
            int u=rand()%tmp.size();
            repr[i].pb(tmp[u]);
            swap(tmp[u],tmp[tmp.size()-1]);
            tmp.pop_back();
        }
    }



    memset(done,0,sizeof(done));
    REP(i,nc) REP(j,repr[i].size()) evalp(repr[i][j]);



    REP(i,nc) if (spe[i]){
        REP(j,C[i].size()){
            int a=C[i][j];
            if (done[a])continue;
            double v=0, c=0;
            REP(j,repr[i].size()){
                int b=repr[i][j];
                double cx=1./dist(b/W-a/W,a%W-b%W);
                c+=cx;
                v+=res[b]*cx;
            }
            res[a]=v/c;
        }
    }

    memset(cl,0,sizeof(cl)); memset(vl,0,sizeof(vl)); memset(U,0,sizeof(U));
    REP(i,N) D[i]=inf;

    REP(i,nc) if (!spe[i]){
        vi ul=nxt[i];
        REP(j,adj[i].size()) ul.pb(adj[i][j]);
        int step=0;
        REP(_i,ul.size()){
            queue<int> q;
            int ii=ul[_i];
            REP(j,C[ii].size()) q.push(C[ii][j]), par2[C[ii][j]]=C[ii][j];
            bfs(q,i);
        }
    }

    priority_queue<pair<double,int> > q;
    REP(i,nc) if (!spe[i]) updatebest(q,i);

    if (0) while(!q.empty()){
        double dx=q.top().ST;
        int a=q.top().ND;
        q.pop();
        fprintf(F,"SELECXT %lf >> %d >> %d %d\n", dx,a,a/W,a%W);
        if (!CAN) break;
        if (dx<thres) break;
        evalp(a);
        queue<int> q2;
        q2.push(a); par2[a]=a;
        U[a]=step+1; D[a]=0;
        bfs(q2,with[a]);

        updatebest(q,with[a]);
    }

    vector<double> nres(N,0);
    REP(i,H) REP(j,W){
        double u=0;
        int cnt=0;
        REP(k,9){
            int x=i+vx[k], y=j+vy[k];
            if (in(x,y)) u+=res[x*W+y], ++cnt;
        }
        nres[i*W+j]=u/cnt;
    }
    return nres;
}



int main(){
    int H; cin>>H;
    F=fopen("res.out", "w");
    vs tb;
    getchar();
    REP(i,H){ string s; cin>>s; tb.pb(s); }
    vector<double> res=getMap(tb);
    puts("!");
    REP(i,res.size()) fprintf(stdout,"%lf\n", res[i]);
    fflush(stdout);
    fclose(F);
    return 0;
}


