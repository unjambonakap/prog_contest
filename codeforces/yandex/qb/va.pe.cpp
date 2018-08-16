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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=510;
const double eps=1e-9;
int n, h, f;


struct data{
    vector<pdd> p;
    int n;
    double area(){
        double res=0.;
        REP(i, n) res+=p[i].ST*p[i+1].ND-p[i].ND*p[i+1].ST;
        return -res/2;
    }
    void out(){ printf("=== ");REP(i, n) printf("(%lf %lf) ", p[i].ST, p[i].ND); printf("\n");}
};

double crossp(double a, double b, double c, double d){return a*d-b*c;}

pdd proc(pdd a, pdd b){
    double c=(b.ST-a.ST)/(b.ND-a.ND);
    return MP(c, a.ST-c*a.ND);
}
void intersect(set<pdd> &s, pdd a, pdd b, pdd c, pdd d){
    pdd p, ca, cb;
    ca=proc(a, b);//ca.ST*y+ca.ND=x
    cb=proc(c, d);
    if (fabs(ca.ST-cb.ST)>eps){
        pdd p;
        p.ND=(ca.ND-cb.ND)/(cb.ST-ca.ST);
        p.ST=ca.ST*p.ND+ca.ND;
        double x, y;

        if (p.ST>eps+min(max(a.ST, b.ST), max(c.ST, d.ST))
                || p.ST-eps<max(min(a.ST, b.ST), min(c.ST, d.ST))
                || p.ND>eps+min(max(a.ND, b.ND), max(c.ND, d.ND))
                || p.ND-eps<max(min(a.ND, b.ND), min(c.ND, d.ND))) return;
        //printf("line %lf %lf\n", ca.ST, ca.ND);
        //printf("<< %lf %lf xx %lf %lf xx %lf %lf xx %lf %lf\n", a.ST, a.ND, b.ST, b.ND, c.ST, c.ND, d.ST, d.ND);
        //printf("FIND INTERSECT AT %lf %lf\n", p.ST, p.ND);
        s.insert(p);
    }
}

void hull(data &d, const set<pdd> &s){

    FE(it, s){
        int na=d.p.size()-1;
        while(na>=1){
            if (crossp(d.p[na].ST-d.p[na-1].ST, d.p[na].ND-d.p[na-1].ND, it->ST-d.p[na-1].ST, it->ND-d.p[na-1].ND)<0) break;
            --na;
            d.p.pop_back();
        }
        d.p.pb(*it);
    }
    vector<pdd> x;
    FEV(it, s){
        while(x.size()>=2){
            int na=x.size()-1;
            if (crossp(x[na].ST-x[na-1].ST, x[na].ND-x[na-1].ND, it->ST-x[na-1].ST, it->ND-x[na-1].ND)<0) break;
            x.pop_back();
        }
        x.pb(*it);
    }
    d.p.pop_back();
    d.p.insert(d.p.end(), ALL(x));
    d.n=d.p.size()-1;

}

double inter(data &a, data &b){
    data c;
    double xa, xb;
    set<pdd> ps;

    xb=min(a.p[0].ST, b.p[0].ST);
    xa=max(a.p[1].ST, b.p[1].ST);
    if (xa<=xb){
        ps.insert(MP(xa, double(-h)));
        if (xa+eps<xb) ps.insert(MP(xb, double(-h)));
    }

    xb=min(a.p[3].ST, b.p[3].ST);
    xa=max(a.p[2].ST, b.p[2].ST);
    if (xa<=xb){
        ps.insert(MP(xa, double(h)));
        if (xa+eps<xb) ps.insert(MP(xb, double(h)));
    }
    REP(i, 2) REP(j, 2) intersect(ps, a.p[1+2*i], a.p[2+2*i], b.p[1+2*j], b.p[2+2*j]);
    hull(c, ps);
    //c.out();
    //a.out();
    //b.out();
    //printf("<< %lf\n", c.area());
    //printf("\n\n");
    return c.area();



}


int main(){
    cin>>n>>h>>f;
    vector<data> tb[2];
    REP(i, n){
        double a, b;
        cin>>a>>b;
        data d;
        d.p.pb(MP(b, -h)); d.p.pb(MP(a, -h));
        if (fabs(a)<eps) d.p.pb(MP(a, h));
        else d.p.pb(MP(a*double(f+h)/(f-h), h));
        if (fabs(b)<eps) d.p.pb(MP(b, h));
        else d.p.pb(MP(b*double(f+h)/(f-h), h));
        d.n=4;
        tb[0].pb(d);
        tb[0].back().p.pb(d.p[0]);
        reverse(ALL(d.p));
        REP(j, 4) d.p[j].ND*=-1;
        tb[1].pb(d);
        tb[1].back().p.pb(d.p[0]);
    }
    double res=0.;
    REP(i, n) res+=tb[0][i].area();
    res*=2;
    double a=0.;
    REP(i, n) REP(j, i) a+=inter(tb[0][i], tb[1][j]);
    REP(i, n) res-=inter(tb[0][i], tb[1][i]);
    res-=2*a;

    printf("%lf\n", res);


    return 0;
}


