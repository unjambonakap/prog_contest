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

const int maxn=411;
const double eps=1e-7;
const double pi=acos(-1);

int n,r;
int x[maxn], y[maxn];

struct point{
    double x,y;
    point(){}
    point(double x, double y):x(x),y(y){}
    bool operator<(const point &p)const{
        if (fabs(x-p.x)>eps) return x<p.x;
        if (fabs(y-p.y)>eps) return y<p.y;
        return 0;
    }
    double ang()const{return atan2(y,x);}
    bool operator==(const point &p)const{ return fabs(x-p.x)<eps && fabs(y-p.y)<eps;}
    double dist()const{return sqrt(x*x+y*y);}

};

map<point,int> rmp;
point pl[maxn];
int np;
vi e[maxn];
int vis[maxn];
vi edge;

int getp(point p){
    if (!rmp.count(p)) pl[np]=p, rmp[p]=np, ++np;
    return rmp[p];
}

double area(const point &a, const point &b){ return a.x*b.y-a.y*b.x;}

point findmid(double xa, double ya, double xb, double yb){
    double T=0, H=1;
    point res;
    REP(step,50){
        double M=(T+H)/2;
        
        res=point(xa*M+xb*(1-M), ya*M+yb*(1-M));
        if (res.dist()>r) T=M;
        else H=M;
    }
    return res;
}
struct cmp{ bool operator()(int a, int b)const{return pl[a]<pl[b];} };


void proc(double xa, double ya, double xb, double yb){
    double da=sqrt(xa*xa+ya*ya);
    double db=sqrt(xb*xb+yb*yb);
    if (da>r-eps && db>r-eps) return;
    int ia,ib;

    if (da<r) ia=getp(point(xa,ya));
    else edge.pb(ia=getp(findmid(xb,yb,xa,ya)));

    if (db<r) ib=getp(point(xb,yb));
    else edge.pb(ib=getp(findmid(xa,ya,xb,yb)));

    if (ia==ib) return;
    e[ia].pb(ib);
    e[ib].pb(ia);

}


int main(){
    while(cin>>n>>r, !cin.eof()){
        REP(i,maxn) e[i].clear();
        np=0;
        rmp.clear();
        edge.clear();

        REP(i,n) scanf(" %d%d",x+i,y+i);
        x[n]=x[0];
        y[n]=y[0];

        REP(i,n){
            double T=0, H=1;
            int xa=x[i], ya=y[i], xb=x[i+1], yb=y[i+1];
            REP(step,50){
                double l=(2*T+H)/3, r=(T+2*H)/3;
                double va=point(l*xa+(1-l)*xb,l*ya+(1-l)*yb).dist();
                double vb=point(r*xa+(1-r)*xb,r*ya+(1-r)*yb).dist();

                if (va>vb) T=l;
                else H=r;
            }

            point p=point(T*xa+(1-T)*xb,T*ya+(1-T)*yb);
            proc(p.x,p.y,xa,ya);
            proc(p.x,p.y,xb,yb);
        }


        //FE(it,rmp) printf("%lf %lf\n",it->ST.x,it->ST.y);
        //out(edge);
        sort(ALL(edge),cmp());
        edge.resize(unique(ALL(edge))-edge.begin());
        assert(edge.size()%2==0);

        double res=0;
        REP(i,edge.size()/2){
            int a=edge[2*i];
            int b=edge[2*i+1];
            //printf("%lf %lf %lf %lf\n",pl[a].x,pl[a].y,pl[b].x,pl[b].y);
            double val=fabs(area(pl[a],pl[b]))/2;
            double ang=pl[a].ang()-pl[b].ang();
            if (ang<0) ang+=2*pi;
            if (ang>pi) ang=2*pi-ang;
            res+=r*r*ang/2-val;

            e[a].pb(b);
            e[b].pb(a);

        }

        memset(vis,0,sizeof(vis));
        REP(i,np) if (!vis[i]){

            int x=e[i][0], p=i;
            int st=0;
            double ans=0;
            for (; !vis[p];){
                vis[p]=1;
                assert(e[x].size()==2);
                int nx=e[x][1]==p?e[x][0]:e[x][1];
                ans+=area(pl[p],pl[x]);
                p=x;
                x=nx;
            }

            ans=fabs(ans)/2;
            res+=ans;
        }


        printf("%.9lf\n",res);
    }


    return 0;
}

