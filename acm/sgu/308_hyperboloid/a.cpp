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

const int nstepz=70;
const int nstep0=1400;
const double pi=acos(-1);
const double oo=1e9;
const double eps=1e-7;
const int stepline=30;
const int nadj=300;
double distlim=1e-1;

struct point{
    point(){}
    point(double x, double y, double z):x(x),y(y),z(z){}
    double ang()const{return atan2(y,x);}
    double dist(){return sqrt(x*x+y*y+z*z);}
    double dist(const point &a)const{return (*this-a).dist();}
    point operator-(const point &a)const{return point(x-a.x,y-a.y,z-a.z);}

    static point frompos(double z, double a){ double r=sqrt(1+z*z); return point(r*cos(a),r*sin(a),z);}

    void read(){cin>>x>>y>>z;}
    double x,y,z;
    void disp()const{printf(" (%lf %lf %lf)\n",x,y,z);}
};

point pa,pb;

double dps[2][nstep0+10];
double dpt[2][nstep0+10];
double adjdist[2*nadj+1];

point pl[2][nstep0+10];
double nextdist;

double eval_close_dist(const point &a, const point &b){
    double d0=b.ang()-a.ang();
    if (d0>pi) d0=2*pi-d0;
    d0/=stepline;

    double dz=(b.z-a.z)/stepline;
    double res=0;

    point u=a;
    double z=a.z;
    double ang=a.ang();

    REP(i,stepline){
        z+=dz;
        ang+=d0;
        double r=sqrt(1+z*z);
        point nu=point(r*cos(ang),r*sin(ang),z);
        res+=(nu-u).dist();
        u=nu;
    }
    return res;
}

void compute_points(point *tb, double z, int nstep){
    double step=2*pi/nstep;
    nextdist=sqrt(1+z*z)*step;
    REP(i,nstep) tb[i]=point::frompos(z,step*i);
}
void mark_close(point *tb, double *db, point p, int n){
    REP(i,n) if (p.dist(tb[i])<distlim) db[i]=min(db[i],eval_close_dist(tb[i],p));
}

void expand(double *dist, int n){
    REP(k,20) REP(i,n) for (int j=-1; j<=1; j+=2) dist[(i+j)%n]=min(dist[(i+j)%n],dist[i]+nextdist);

}

void go(double *dist0, double *dist1, int n){
    REP(i,n) for (int j=-nadj; j<=nadj; ++j){
        int u=(n+i+j)%n;
        dist1[u]=min(dist1[u],dist0[i]+adjdist[j+nadj]);
    }
}

double compute(double *ds, double *dt, int n){
    double res=oo;
    REP(i,n) res=min(res,ds[i]+dt[i]);
    return res;
}

void init(double *d, int n){ REP(i,n) d[i]=oo; }


const int maxs=150;
double dp[maxs][maxs];
point tbp[maxs][maxs];

point genp(){
    int N=1e6;
    double z=2.*(rand()%N)/N-1;
    double ang=2*pi*(rand()%N)/N;
    return point::frompos(z,ang);
}

double stupid(point pa, point pb){
    double zl=-1, zh=1.;
    double al=0, ah=2*pi;

    int n=maxs;
    double dz=(zh-zl)/(n-1);
    double da=2*pi/(n-1);
    REP(i,n) REP(j,n) tbp[i][j]=point::frompos(zl+i*dz,al+j*da);
    int s1,s2,t1,t2;
    s1=s2=t1=t2=0;

    REP(i,n) REP(j,n) if (pa.dist(tbp[i][j])<pa.dist(tbp[s1][s2])) s1=i, s2=j;
    REP(i,n) REP(j,n) if (pb.dist(tbp[i][j])<pb.dist(tbp[t1][t2])) t1=i, t2=j;
    REP(i,n) REP(j,n) dp[i][j]=oo;

    priority_queue<pair<double,pii> > q;
    q.push(MP(0.,MP(s1,s2)));
    dp[s1][s2]=0.;

    int sq=2;

    while(q.size()){
        double d=-q.top().ST; 
        pii x=q.top().ND;
        q.pop();

        //printf("LAAA\n");
        if (dp[x.ST][x.ND]!=d) continue;
        if (x.ST==t1 && x.ND==t2) return d;

        FOR(i,-sq,sq+1) FOR(j,-sq,sq+1) if (i||j) if (x.ST+i>=0 && x.ST+i<n){
            int ni=x.ST+i, nj=(n+x.ND+j)%n;
            double nd=d+eval_close_dist(tbp[x.ST][x.ND],tbp[ni][nj]);
            //printf("%lf\n",eval_close_dist(tbp[x.ST][x.ND],tbp[ni][nj]));
            //tbp[x.ST][x.ND].disp();
            //tbp[ni][nj].disp();


            //if (i==1 && j==0) exit(0);
            if (dp[ni][nj]>nd) q.push(MP(-(dp[ni][nj]=nd),MP(ni,nj)));
        }
    }
    assert(0);
}

double solve1(){

    int p=0, np=1;

    double stz=min(0.,pa.z), ndz=max(0.,pb.z);
    double dz=(ndz-stz)/nstepz;
    double d0=2*pi/nstep0;

    init(dps[p],nstep0);
    init(dpt[p],nstep0);

    compute_points(pl[p],stz,nstep0);
    mark_close(pl[p],dps[p],pa,nstep0);
    mark_close(pl[p],dpt[p],pb,nstep0);

    expand(dps[p],nstep0);
    expand(dpt[p],nstep0);

    double res=oo;
    res=min(res,compute(dps[p],dpt[p],nstep0));

    REP(i,nstepz){
        init(dps[np],nstep0);
        init(dpt[np],nstep0);

        double z=stz+(i+1)*dz;
        compute_points(pl[np],z,nstep0);
        mark_close(pl[np],dps[np],pa,nstep0);
        mark_close(pl[np],dpt[np],pb,nstep0);

        for (int j=-nadj; j<=nadj; ++j) adjdist[j+nadj]=eval_close_dist(pl[p][0],pl[np][(nstep0+j)%nstep0]);

        //pl[p][0].disp(); pl[np][0].disp(); printf("%lf\n",adjdist[nadj]); exit(0);
        go(dps[p],dps[np],nstep0);
        go(dpt[p],dpt[np],nstep0);

        expand(dps[p],nstep0);
        expand(dpt[p],nstep0);
        res=min(res,compute(dps[np],dpt[np],nstep0));

        swap(p,np);
    }

    assert(res<oo/2);
    return res;

}
int main(){
    int gen=0;
    while(1){

        if (gen){
            pa=genp();
            pb=genp();
        }else{
            pa.read();
            if (cin.eof()) break;
            pb.read();
        }

        if (pa.z>0) pa.z*=-1, pb.z*=-1;
        if (pa.z>pb.z) swap(pa,pb);

        double res;
        //res=stupid(pa,pb);
        res=solve1();
        //double sol=stupid(pa,pb);
        //printf(">> %lf\n",sol);
        printf("%.10lf\n",res);
        puts("");
        break;

    }
    return 0;
}

