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

const int maxp=111;;
const int maxn=505;
const int maxN=maxn*maxn;
const int Fmin=100, Fmax=199;
const double phi=(1+sqrt(5))/2.;
const double Wmin=0.3, Wmax=0.8;
const double inf=1e100;

double mp[maxn][maxn];
int A[maxN];
int next[maxN][8];


vi C[maxN];
int isb[maxN];
int with[maxN];
int vis[maxN];
int par[maxN];
int added[maxN];
int sz[maxN];
int spe[maxN];

vi nxt[maxN];
vi adj[maxN];
double zc[maxN];

double zp[maxp], zeval[maxp];
int peak[maxp];
int np;
double Wi[maxp];
int Fi[maxp];

int nc;
int step;

int W, H;
int N;
FILE *F;
int CAN;

int vx[]={0,1,0,-1,1,1,-1,-1};
int vy[]={1,0,-1,0,-1,1,1,-1};

double peak_coeff[maxp], peak_val[maxp];
double peak_coefflst[maxp][maxp];

double gen_coeff[maxN], gen_val[maxN];
double gen_coefflst[maxN][maxp];
int repr[maxN];
double zrepr[maxN];
double ztmp[maxN];
int ne;



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

//int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
//void join(int a, int b){a=root(a); b=root(b); if (a!=b) isb[a]|=isb[b], par[b]=a;}


int plx[]={214,67,351,54,371,441,396,162,398,461,343,33,237,145,314,428};

int ply[]={354,164,132,238,36,116,176,122,170,174,185,317,97,384,19,87};

int plz[]={54, 54, 89, 92, 82, 27, 25, 35, 14, 75, 84, 57, 22, 15, 93, 40}; 
int plf[]={102, 190, 100, 105, 163, 141, 195, 134, 122, 148, 153, 170, 142, 157, 160, 111}; 
double plw[]={0.4831419301672461, 0.621142346948274, 0.636646264548064, 0.38197367877533345, 0.7469415720030981, 0.710423678215099, 0.6129876718541154, 0.6875275984479802, 0.6153967688818547, 0.6029599584584651, 0.47065213925299126, 0.5066612063179509, 0.7812555118493727, 0.7165031805193924, 0.46900211403603353, 0.34601206158292735};
//x=214, y=354; res[y*W+x]=100; x=67, y=164; res[y*W+x]=100; x=351, y=132;
    //res[y*W+x]=100; x=54, y=238; res[y*W+x]=100; x=371, y=36; res[y*W+x]=100;
    //x=441, y=116; res[y*W+x]=100; x=396, y=176; res[y*W+x]=100; x=162, y=122;
    //res[y*W+x]=100; x=398, y=170; res[y*W+x]=100; x=461, y=174; res[y*W+x]=100;
    //x=343, y=185; res[y*W+x]=100; x=33, y=317; res[y*W+x]=100; x=237, y=97;
    //res[y*W+x]=100; x=145, y=384; res[y*W+x]=100; x=314, y=19; res[y*W+x]=100;
    //x=428, y=87; res[y*W+x]=100;



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

int dfs_sz(int a){
    if (sz[a]!=-1) return sz[a];
    sz[a]=C[a].size();
    REP(i,nxt[a].size()) sz[a]+=dfs_sz(nxt[a][i]);
    return sz[a];
}


double randdouble(double a, double b){
    int u=rand()&(1ll*(1<<31)-1);
    return a+(b-a)*u/(1<<31);
}






double init_peak(){
    double cf=0;
    double zmin=inf, zmax=-inf;
    REP(i,np){
        peak_coeff[i]=peak_val[i]=0;
        REP(k,np){
            peak_coefflst[i][k]=pow(dist(peak[i]/W-peak[k]/W,peak[i]%W-peak[k]%W)+Fi[k],-Wi[k]);
            peak_coeff[i]+=peak_coefflst[i][k];
            peak_val[i]+=peak_coefflst[i][k]*zp[k];
        }
        ztmp[i]=peak_val[i]/peak_coeff[i];
        checkmax(zmax,ztmp[i]);
        checkmin(zmin,ztmp[i]);
    }
    REP(i,np) cf+=sqr(100*(ztmp[i]-zmin)/(zmax-zmin)-zeval[i]);
    return cf;

}

double init_gen(){
    double cf=0;
    double zmin=inf, zmax=-inf;
    REP(i,ne){
        gen_coeff[i]=gen_val[i]=0;
        int b=repr[i];
        REP(k,np){
            gen_coefflst[i][k]=pow(dist(b/W-peak[k]/W,b%W-peak[k]%W)+Fi[k],-Wi[k]);

            gen_coeff[i]+=gen_coefflst[i][k];
            gen_val[i]+=gen_coefflst[i][k]*zp[k];
        }
        ztmp[i]=gen_val[i]/gen_coeff[i];
        checkmax(zmax,ztmp[i]);
        checkmin(zmin,ztmp[i]);
    }
    REP(i,ne) cf+=sqr(100*(ztmp[i]-zmin)/(zmax-zmin)-zrepr[i]);
    return cf;
}


double solve1(int a, double dz){
    if (zp[a]+dz>100 || zp[a]+dz<0) return inf;
    double cf=0;
    double zmin=inf, zmax=-inf;
    REP(i,ne){
        ztmp[i]=(gen_val[i]+dz*gen_coefflst[i][a])/gen_coeff[i];
        checkmax(zmax,ztmp[i]);
        checkmin(zmin,ztmp[i]);
    }
    REP(i,ne) cf+=sqr(100*(ztmp[i]-zmin)/(zmax-zmin)-zrepr[i]);
    return cf;
}

double solve2(int a, double df, double dw){
    return inf;
    if (Wi[a]+dw<Wmin || Wi[a]+dw>Wmax) return inf;
    if (Fi[a]+df<80) return inf;
    double cf=0;
    double zmin=inf, zmax=-inf;
    REP(i,ne){
        int b=repr[i];
        double oc=gen_coefflst[i][a];
        double nc=pow(dist(b/W-peak[a]/W,b%W-peak[a]%W)+Fi[a]+df,-Wi[a]-dw);
        ztmp[i]=(gen_val[i]+(nc-oc)*zp[a])/(gen_coeff[i]+nc-oc);
        checkmax(zmax,ztmp[i]);
        checkmin(zmin,ztmp[i]);
    }
    REP(i,ne) cf+=sqr(100*(ztmp[i]-zmin)/(zmax-zmin)-zrepr[i]);

    return cf;
}



void update1(int a, double dz){ REP(i,ne){int b=repr[i]; gen_val[i]+=dz*gen_coefflst[i][a];} zp[a]+=dz; }

void update2(int a, double df, double dw){
    REP(i,ne){
        int b=repr[i];
        double oc=gen_coefflst[i][a];
        double nc=pow(dist(b/W-peak[a]/W,b%W-peak[a]%W)+Fi[a]+df,-Wi[a]-dw);
        gen_val[i]+=(nc-oc)*zp[a];
        gen_coefflst[i][a]=nc;
        gen_coeff[i]+=nc-oc;
    }
    Fi[a]+=df; Wi[a]+=dw;
}


void printgen(){
    double zmin=inf, zmax=-inf;
    REP(i,ne){
        ztmp[i]=gen_val[i]/gen_coeff[i];
        checkmax(zmax,ztmp[i]);
        checkmin(zmin,ztmp[i]);
    }

    double cf=0;
    REP(i,ne){
        double nz=100*(ztmp[i]-zmin)/(zmax-zmin);
        fprintf(F,"%lf >> %lf\n", nz, zrepr[i]);
        cf+=sqr(nz-zrepr[i]);
    }
    fprintf(F,"val>> %lf\n",cf);


}


void adjustpeaks(){
    vector<pii> infl_lst;
    REP(i,np){
        int u=with[peak[i]];
        if (par[u]!=-1) infl_lst.pb(MP(sz[par[u]],i));
        else{
            assert(adj[u].size()>0);
            infl_lst.pb(MP(sz[adj[u][0]],i));
        }
    }
    sort(ALL(infl_lst));
    int va=infl_lst[0].ST, vb=infl_lst[np-1].ST;
    REP(i,np){
        //Wi[infl_lst[i].ND]=Wmin+1.*(infl_lst[i].ST-va)/(vb-va)*(Wmax-Wmin);
        Wi[i]=0.5;
        Fi[infl_lst[i].ND]=Fmin+1.*(vb-infl_lst[i].ST)/(vb-va)*(Fmax-Fmin);
    }

    double cf=init_peak();
    REP(i,np){
        peak_coeff[i]=peak_val[i]=0;
        REP(k,np){
            peak_coefflst[i][k]=pow(dist(peak[i]/W-peak[k]/W,peak[i]%W-peak[k]%W)+Fi[k],-Wi[k]);

            peak_coeff[i]+=peak_coefflst[i][k];
            peak_val[i]+=peak_coefflst[i][k]*zp[k];
        }
        assert(fabs(peak_coeff[i])>1e-6);
        cf+=sqr(peak_val[i]/peak_coeff[i]-zeval[i]);
    }
    double U=11;
    REP(step,0){
        REP(i,np) for (int sgn=-1; sgn<=1; sgn+=2){
            double ncf=0;
            if (zp[i]+sgn*U>100 || zp[i]+sgn*U<0) continue;

            REP(k,np) ncf+=sqr((peak_val[k]+sgn*U*peak_coefflst[k][i])/peak_coeff[k]-zeval[k]);
            if (ncf<cf){
                REP(k,np) peak_val[k]+=sgn*U*peak_coefflst[k][i];
                cf=ncf;
                zp[i]+=U*sgn;
            }
        }
        if (step%np==0) U/=phi;
    }


    REP(i,np){
        double sx=0, s=0;
        REP(k,np){
            double cx=pow(dist(peak[i]/W-peak[k]/W,peak[i]%W-peak[k]%W)+Fi[k],-Wi[k]);
            //fprintf(F,"%d %d >> %lf\n", i, k, cx);
            sx+=cx;
            s+=cx*zp[k];
        }
        //fprintf(F,"%d >> %lf over %lf\n", i,s/sx,zeval[i]);

        //fprintf(F,"%lf\n", res[i*W+j]);

    }

}

void searchspace(){
    //    fprintf(F,">>%d\n", np);
    //    REP(i,np){
    //        Fi[i]=rand()%(Fmax-Fmin+1)+Fmin;
    //        Wi[i]=randdouble(Wmin,Wmax);
    //        fprintf(F,"SET %d %lf\n", Fi[i], Wi[i]);
    //    }

    double dz=55, df=(Fmax-Fmin)/2.,dw=(Wmax-Wmin)/2.;
    double cf=init_gen();

    double phi=1.05;
    REP(k,np) fprintf(F,"%lf ", zp[k]); fprintf(F,"\n");
    fprintf(F,"start with %lf\n", cf);
    REP(step,200){

        REP(i,np) for (int sgn=-1; sgn<=1; sgn+=2){
            double ncf;

            ncf=solve1(i,sgn*dz);
            if (ncf<cf) cf=ncf, update1(i,sgn*dz);

            ncf=solve2(i,sgn*df,0);
            if (ncf<cf) cf=ncf, update2(i,sgn*df,0);

            ncf=solve2(i,0,sgn*dw);
            if (ncf<cf) cf=ncf, update2(i,0,sgn*dw);
        }
        if (step%np==0) dz/=phi, df/=phi, dw/=phi;
    }
    fprintf(F,"END AT %lf\n", 1.*clock()/CLOCKS_PER_SEC);
    fprintf(F,"finish with %lf\n", cf);


    printgen();
}


vector<double> buildres(){
    vector<double> res(N);
    double zmin=inf, zmax=-inf;
    REP(i,H) REP(j,W){
        double sx=0, s=0;
        REP(k,np){
            double cx=pow(dist(i-peak[k]/W,j-peak[k]%W)+Fi[k],-Wi[k]);
            //fprintf(F,"%lf %d %lf >> %lf\n", dist(i-peak[k]/W,j-peak[k]%W),Fi[k], Wi[k], cx);
            sx+=cx;
            s+=cx*zp[k];
        }
        res[i*W+j]=s/sx;
        checkmax(zmax,res[i*W+j]);
        checkmin(zmin,res[i*W+j]);
        //fprintf(F,"%lf\n", res[i*W+j]);
    }
    REP(i,N) res[i]=100*(res[i]-zmin)/(zmax-zmin);
    return res;
}

vector<double> getMap(vs cm){
    H=cm.size();
    W=cm[0].size();
    REP(i,H) REP(j,W) A[i*W+j]=cm[i][j]=='1';
    REP(i,H) fprintf(F,"%s\n", cm[i].c_str());
    fprintf(F,"\n");

    N=W*H;
    CAN=sqrt(N);

    REP(i,H) REP(j,W) REP(k,8){
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
        int step=0;
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


    memset(spe,0,sizeof(spe));
    memset(sz,-1,sizeof(sz));
    np=0;
    REP(i,N) if (A[i]){
        int fd=1;
        REP(k,4) if (next[i][k]==-1 || !A[next[i][k]]){fd=0; break;}
        if (fd && np<maxp) peak[np++]=i, spe[i]=2;
    }
    int xaxa=sizeof(plx)/sizeof(int);
    np=xaxa;
    REP(i,xaxa) peak[i]=ply[i]*W+plx[i];


    REP(i,nc) dfs_sz(i);
    vi lst_glob;
    REP(i,nc) if (!A[C[i][0]] && (nxt[i].size() || adj[i].size()==1)) lst_glob.pb(i), spe[i]=1;




    if (0) REP(i,nc) if (!A[C[i][0]]){
        int u=rand()%C[i].size();
        zc[i]=_measure(C[i][u]/W,C[i][u]%W);
    }
    REP(i,np) zeval[i]=zp[i]=zc[with[peak[i]]]=_measure(peak[i]/W,peak[i]%W);


    ne=0;



    REP(i,np) zrepr[i]=zeval[i];
    REP(i,np) repr[i]=peak[i];
    ne=np;

    REP(i,nc) if (!A[C[i][0]]){
        int u=min((int)C[i].size(),int(sqrt(C[i].size())+1));
        vi tmp=C[i];
        REP(i,u){
            int x=rand()%tmp.size();
            zrepr[ne]=zc[with[tmp[x]]];
            repr[ne++]=tmp[x];
            swap(tmp[x],tmp[tmp.size()-1]);
            tmp.pop_back();
        }
    }



    adjustpeaks();
    searchspace();

    REP(i,np) zp[i]=plz[i], Wi[i]=0.5, Fi[i]=plf[i];

    vector<double> res=buildres();
    REP(i,ne) fprintf(F,"%lf %lf\n", res[repr[i]], zrepr[i]);

    //res=vector<double>(N,0);
    //REP(i,np) res[peak[i]]=100;

    //int x, y;
    //x=214, y=354; res[y*W+x]=100; x=67, y=164; res[y*W+x]=100; x=351, y=132;
    //res[y*W+x]=100; x=54, y=238; res[y*W+x]=100; x=371, y=36; res[y*W+x]=100;
    //x=441, y=116; res[y*W+x]=100; x=396, y=176; res[y*W+x]=100; x=162, y=122;
    //res[y*W+x]=100; x=398, y=170; res[y*W+x]=100; x=461, y=174; res[y*W+x]=100;
    //x=343, y=185; res[y*W+x]=100; x=33, y=317; res[y*W+x]=100; x=237, y=97;
    //res[y*W+x]=100; x=145, y=384; res[y*W+x]=100; x=314, y=19; res[y*W+x]=100;
    //x=428, y=87; res[y*W+x]=100;
    return res;
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


