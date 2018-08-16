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

const int maxn=3333;
const double eps=1e-4;
const double eps2=1e-9;
const int oo=200;


struct point{
    double x,y,z;
    point(){x=y=z=0;}
    point operator+(const point &p)const{
        point res=*this;
        res.x+=p.x;
        res.y+=p.y;
        res.z+=p.z;
        return res;
    }
    point operator-(const point &p)const{
        point res=*this;
        res.x-=p.x;
        res.y-=p.y;
        res.z-=p.z;
        return res;
    }

    point operator*(double v)const{
        point res=*this;
        res.x*=v;
        res.y*=v;
        res.z*=v;
        return res;
    }
    point operator*(const point &p)const{
        point res;
        res.x=y*p.z-z*p.y;
        res.y=z*p.x-x*p.z;
        res.z=x*p.y-y*p.x;
        return res;
    }
    double operator%(const point &p)const{
        double res=0;
        res+=x*p.x;
        res+=y*p.y;
        res+=z*p.z;
        return res;
    }
    double dist()const{return sqrt(*this%*this);}
    bool operator<(const point &p)const{return 0;}
    void disp()const{printf("%lf %lf %lf\n",x,y,z);}
};

int n;
point tx[maxn][3];



int count_inter(point a, point b){
    int res=0;
    REP(i,n){
        point x,y,z;
        x=tx[i][0];
        y=tx[i][1];
        z=tx[i][2];

        point P=(y-x)*(z-x);

        double c1=(a-x)%P;
        double c2=(b-a)%P;
        double k;
        assert(fabs(c2)>eps2);
        k=-c1/c2;

        if (k<-eps2 || k>1+eps2) continue;
        point px=a+(b-a)*k;

        int ok=1;
        REP(j,3){
            point x=tx[i][j];
            point y=tx[i][(j+1)%3];
            point z=tx[i][(j+2)%3];
            point u=(y-x)*(z-x);
            point v=(y-x)*(px-x);
            if (u%v<-eps){ok=0; ;}
        }
        
        res+=ok;
    }
    return res;
}

double trarea(const point &a, const point &b, const point &c){ return ((b-a)*(c-a)).dist()/2; }
double getarea(int u, double zp){
    vector<pair<double,point> > lst;
    REP(i,3) lst.pb(MP(tx[u][i].z-zp,tx[u][i]));
    sort(ALL(lst));
    if (fabs(lst[0].ST-lst[2].ST)<eps2) return lst[0].ST*trarea(lst[0].ND,lst[1].ND,lst[2].ND);

    double k=(lst[1].ST-lst[0].ST)/(lst[2].ST-lst[0].ST);
    
    point mid=lst[0].ND+(lst[2].ND-lst[0].ND)*k;
    double h1=(lst[0].ST-lst[1].ST)/3+lst[1].ST;
    double h2=(lst[2].ST-lst[1].ST)/3+lst[1].ST;

    mid.z=0;
    REP(i,3) lst[i].ND.z=0;
    double a1=h1*trarea(lst[0].ND,lst[1].ND,mid);
    double a2=h2*trarea(lst[2].ND,lst[1].ND,mid);
    return a1+a2;
}

int main(){
    int nn;
    while(cin>>nn,nn){
        double res=0;
        REP(_ni,nn){
            int nf;
            cin>>nf;

            n=0;

            REP(i,nf){
                int np; cin>>np;
                vector<point> tb;
                REP(j,np){
                    point p;
                    scanf(" %lf%lf%lf",&p.x,&p.y,&p.z);
                    tb.pb(p);
                }
                FOR(j,1,np-1) tx[n][0]=tb[0], tx[n][1]=tb[j], tx[n][2]=tb[j+1], ++n;
            }



            REP(i,n){
                point orig;
                REP(j,3) orig=orig+tx[i][j];
                orig=orig*(1./3);
                orig.z-=eps;
                point inf;
                inf.x=oo+rand()%oo;
                inf.y=oo+rand()%oo;
                inf.z=oo+rand()%oo;


                double area=getarea(i,-oo);
                int cnt=count_inter(inf,orig);
                res+=area*(cnt&1?1:-1);
            }
        }
        printf("%.2lf\n",res);
    }
    return 0;
}


