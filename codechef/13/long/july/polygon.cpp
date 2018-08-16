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

const int maxm=11111;
const int maxn=555;
const double pi=acos(-1.);
const double eps=1e-8;
const double oo=1e9;

struct point;
struct line;
double phi;
//set<pii> islist;

struct point{
    point(double x,double y):x(x),y(y){}
    point():x(0),y(0){}
    double x,y;
    void disp(){printf("(%lf %lf)\n",x,y);}
    bool operator<(const point &p)const{
        if (fabs(x-p.x)>eps) return x<p.x;
        if (fabs(y-p.y)>eps) return y<p.y;
        return 0;
    }
    pii topii()const{return MP(int(x+0.5),int(y+0.5));}

    bool operator==(const point &p)const{return fabs(x-p.x)<eps && fabs(y-p.y)<eps;}
    bool operator!=(const point &p)const{return !(p==*this);}
    point operator+(const point &p)const{ return point(x+p.x,y+p.y); }
    point operator-(const point &p)const{ return point(x-p.x,y-p.y); }
    point operator-()const{return point(-x,-y);}
    point operator*(double v)const{return point(x*v,y*v);}
    double operator%(const point &p)const{return x*p.x+y*p.y;}
    point rotate(double ang)const{ return point(x*cos(-ang)-y*sin(ang),y*cos(ang)+x*sin(ang)); }

    double dist()const{return sqrt(*this%*this);}
    point perp()const{return point(-y,x);}
};

int intersect(line a, line b, point &res);
double dist(point a, line l);


point operator*(double a, const point &p){return point(a*p.x,a*p.y);}
double det(double xa, double ya, double xb, double yb){return xa*yb-ya*xb;}
double det(point a, point b){return det(a.x,a.y,b.x,b.y);}
int sgn(double a){return fabs(a)<eps?0:a<0?-1:1;}

int gcd(int a, int b){
    a=abs(a);
    b=abs(b);
    if (a<b) swap(a,b); return b?gcd(b,a%b):a;
}


struct line{
    point a,b;
    point v;
    double ang;
    double dist0;
    double lastdist;


    double dk;
    point p0;

    int id;
    void disp(){
        printf("line (%lf %lf) (%lf %lf)\n",a.x,a.y,b.x,b.y);
    }

    line(point _a, point _b, double _dk=-1, point _p0=point(+oo,+oo)):a(_a),b(_b),dk(_dk),p0(_p0) {
        if (b<a) swap(a,b);
        v=b-a;
        lastdist=-1;

        if (dk<0){
            int dd=gcd(v.x,v.y);
            dk=point(v.x,v.y).dist()/dd;
        }


        v=v*(1./v.dist());
        ang=atan2(v.y,v.x);
        if (fabs(p0.x-oo)<eps) p0=a;

        dist0=dist(point(0,0),*this);
    }
    double operator()(double x){return a.y+v.y*(x-a.x)/v.x;}

    bool operator<(const line &x)const{
        if (fabs(ang-x.ang)>eps) return ang<x.ang;
        if (fabs(dist0-x.dist0)>eps) return dist0<x.dist0;
        return a<x.a;
    }
    bool aligned(const line &x)const{ return fabs(ang-x.ang)<eps && fabs(dist0-x.dist0)<eps;}

    line rotate(double phi)const{return line(a.rotate(phi),b.rotate(phi),dk);}

    int go(point pp, int is){
        if (lastdist<0) lastdist=(p0-pp).dist();
        int x1=floor(eps+(pp-p0).dist()/dk);
        int x2=floor(eps+lastdist/dk);

        if (is) assert((pp-p0).dist()/dk-x1*dk<eps);
        lastdist=(x1+0.5)*dk;
        return x1-x2;
    }
};

int intersect(line a, line b, point &res){
    double d=det(a.v,-b.v);
    if (fabs(d)<eps) return 0;
    double k=det(b.a-a.a,-b.v)/d;
    double k2=det(a.v,b.a-a.a)/d;

    if (k<-eps || k>(a.b-a.a).dist()+eps) return 0;
    if (k2<-eps || k2>(b.b-b.a).dist()+eps) return 0;
    res=a.a+k*a.v;

    assert(res==b.a+k2*b.v);
    return 1;
}

double dist(point a, line l){ return det(a-l.a,l.v)/det(l.v.perp(),l.v); }

double findrot(vector<line> &lst){
    sort(ALL(lst));
    lst.pb(lst[0]);
    lst.back().ang+=pi;
    int best=0;
    REP(i,lst.size()-1) if (lst[best+1].ang-lst[best].ang<lst[i+1].ang-lst[i].ang) best=i;
    lst.pop_back();

    double ang=pi/2-(lst[best+1].ang+lst[best].ang)/2.;
    return ang;
}


vector<line> merge(const vector<line> &tb){
    vector<line> res;
    REP(i,tb.size()){
        int j=i;
        point p=tb[i].b;
        int st=i;
        for (; j<tb.size() && tb[i].aligned(tb[j]); ++j){
            //printf("MERGIN> >> %d >> ",st); tb[j].rotate(-phi).disp();
            if (p<tb[j].a){
                //printf("SPLIT HERE\n");
                //tb[st].rotate(-phi).disp();
                //tb[j].rotate(-phi).disp();
                res.pb(line(tb[st].a,p,tb[i].dk,tb[st].p0)), st=j;
            }
            p=max(p,tb[j].b);
        }

        //if (j>i+1) printf("HAVE MORE THAN ONE HERE\n");
        res.pb(line(tb[st].a,p,tb[i].dk,tb[st].p0));
        //res.back().rotate(-phi).disp();
        i=j-1;
    }
    return res;
}




int n,m;
int xo[maxn], yo[maxn];
int xa[maxm], ya[maxm], xb[maxm], yb[maxm];
vector<line> la,lb;

int N;
vector<line> lst;
double X;


struct cmp{
    bool operator()(int a, int b){
        double ya=lst[a](X), yb=lst[b](X);
        //printf("have %lf %lf %lf\n",ya,yb, (ya-yb)/eps);
        if (fabs(ya-yb)>eps) return ya<yb;
        return lst[a].ang<lst[b].ang;
    }
};


struct event{
    int type;//0 for insertion, 1 deletion, 2 intersect
    point p;
    int a,b;

    event(int type, point p, int a, int b=-1):type(type),p(p),a(a),b(b){}

    bool operator<(const event &e)const{
        if (p!=e.p) return e.p<p;
        return type<e.type;
    }
};



set<int,cmp> sl;
priority_queue<event> q;

void add(int a, int b, double X){
    point px;
    if (intersect(lst[a],lst[b],px)) if (px.x>X) q.push(event(2,px,a,b));
    
}

int go(){
    lst=la;
    //islist.clear();
    REP(i,m) lst.pb(lb[i]);

    sort(ALL(lst));
    lst=merge(lst);
    N=lst.size();
    REP(i,N) lst[i].id=i;


    REP(i,N) q.push(event(0,lst[i].a,i)), q.push(event(1,lst[i].b,i));
    
    lst.pb(lst[0]);
    X=-oo;

    sl.clear();
    int res=0;
    int nstep=0;
    while(q.size()){
        vector<event> el;
        X=q.top().p.x;
        while(q.size() && fabs(q.top().p.x-X)<eps) el.pb(q.top()), q.pop();

        for (int i=0; i<el.size(); ++i){
            int j=i;

            set<int> sin,sout;
            set<int> isnew;
            for (; j<el.size() && el[i].p==el[j].p; ++j){
                //printf("on %d >> event %d %d %d",j,el[j].type,el[j].a,el[j].b); el[j].p.rotate(-phi).disp();
                if (el[j].type==0) sin.insert(el[j].a), isnew.insert(el[j].a);
                else if (el[j].type==1) sout.insert(el[j].a);
                else sin.insert(el[j].a), sin.insert(el[j].b);
            }

            ++nstep;
            point pp=el[i].p;
            /* 
               everyone intersect at point pp
               => remove them then reinsert (sorted by angle)
               then add intersection w/ above and below

               updating res:
               -add is
               -for all line alreay in, floor(dist_p0/dk)-floor(lastdist/dk)
               -for all line, set lastdist to floor(dist_p0/dk)*dk+dk/2
               */

            set<int>::iterator ita,itb;
            lst[N]=line(pp,point(pp.x+1,pp.y));
            lst[N].ang=-oo;
            //FE(it,sl) printf("HAVE ELEM >>  %lf xx %lf elem %d",lst[*it](X), fabs(lst[*it](X)-pp.y)/eps, *it), lst[*it].rotate(-phi).disp();
            //printf(">>>>START\n");

            ita=sl.lower_bound(N);
            for (;ita!=sl.end() && fabs(lst[*ita](X)-pp.y)<eps; ){
                //printf("REMOVING %d\n",*ita);
                itb=ita; ++itb;
                if (!sin.count(*ita) && !sout.count(*ita)) sin.insert(*ita);
                //lst[*ita].rotate(-phi).disp();
                sl.erase(ita);
                ita=itb;
            }



            int is=0;

            line &l=lst[el[i].a];

            double dd=(pp-l.p0).dist();
            dd=dd-floor(dd/l.dk)*l.dk;
            if (dd<eps||l.dk-dd<eps) is=1;
            //printf("RESLUT OF IS >>> %lf >> %d\n",dd,is);

            res+=is;


            FE(it,sin) if (!sout.count(*it)){
                res+=max(0,lst[*it].go(pp,is)-is);
                //printf("qwerty insert %d >> AT POS XAXA %lf\n",*it, lst[*it](X));
                sl.insert(*it);
            }
            FE(it,sout) res+=max(0,lst[*it].go(pp,is)-is);
            //printf("xaxa end on %d\n",res);

            //printf("STATE OF THE LINE %d\n",N);
            //FE(it,sl) printf("HAVE ELEM >>  %lf xx %lf elem %d",lst[*it](X), fabs(lst[*it](X)-pp.y)/eps, *it), lst[*it].disp();
            //now add intersections
            ita=sl.lower_bound(N);
            if (ita!=sl.begin()){
                itb=ita;
                --ita;
                //printf("MAYBE INTER %d %d\n",*ita, *itb); 
                add(*ita,*itb,X);
            }

            lst[N].ang=oo;
            ita=sl.lower_bound(N);
            if (ita!=sl.end() && ita!=sl.begin()){
                //printf("FUUU %d\n",cmp()(N,*ita));
                itb=ita;
                --ita;
                //printf("MAYBE INTER 2 %d %d\n",*ita, *itb); 
                add(*ita,*itb,X);
            }
            //printf(">>>>>>>>>>>>> FOUEOFWJE\n");
            //printf("ENDING ON %d\n",res);

            i=j-1;
        }
    }

    return res;
}
const int maxv=50000;

void chomp(vector<point> &tb, point a){
    while(tb.size()>=2 && det(a-tb[tb.size()-2],tb.back()-tb[tb.size()-2])<eps) tb.pop_back();
    //if (tb.size()>=2) printf("%lf\n",det(a-tb[tb.size()-2],tb.back()-tb[tb.size()-2]));
    tb.pb(a);
}

vector<point> hull(vector<point> tb){
    vector<point> tl,th;
    sort(ALL(tb));

    REP(i,tb.size()) chomp(tl,tb[i]);
    REPV(i,tb.size()) chomp(th,tb[i]);
    FOR(i,1,th.size()-1) tl.pb(th[i]);
    return tl;
}

point genp(int lim=maxv){return point(rand()%lim,rand()%lim);}

void gen(){
    if (0){
        n=3;
        m=15;
    }else{
        n=50;
        m=500;
    }
    vector<point> tb;

    while(1){
        tb.clear();
        REP(j,n) tb.pb(genp());
        //REP(j,n) tb[j].disp();
        tb=hull(tb);
        if (tb.size()>=3) break;
    }
    n=tb.size();
    REP(i,n) xo[i]=tb[i].x, yo[i]=tb[i].y;


    REP(i,m){
        point aa,bb;
        do{
            aa=genp();
            bb=genp();
        }while(aa==bb);
        xa[i]=aa.x;
        ya[i]=aa.y;
        xb[i]=bb.x;
        yb[i]=bb.y;
    }

}

ll getarea(){
    ll area=0;
    REP(i,n) area+=1ll*xo[i]*yo[i+1]-1ll*xo[i+1]*yo[i];
    return area<0?-area:area;
}
ll getnum(){
    int nedge=0;
    REP(i,n) nedge+=gcd(xo[i+1]-xo[i],yo[i+1]-yo[i]);
    ll nint=(getarea()-nedge)/2+1;
    //printf("have %d edge, %d inside\n",nedge,nint);
    return nint+nedge;
}

void proc(set<pii> &seen, int xa, int ya, int xb, int yb){
    int dx=xb-xa, dy=yb-ya;
    int d=gcd(dx,dy);
    REP(i,d+1){
        int x=xa+dx/d*i, y=ya+dy/d*i;
        assert(min(xa,xb)<=x && x<=max(xb,xa));
        //printf("%d %d\n",x,y);
        seen.insert(MP(x,y));
    }
}

int isin(int x, int y){
    REP(i,n){
        line l=line(point(xo[i],yo[i]),point(xo[i+1],yo[i+1]));
        int s1=sgn(dist(point(xo[(i+2)%n],yo[(i+2)%n]),l));
        int s2=sgn(dist(point(x,y),l));
        if (s1==-s2) return 0;
    }
    return 1;
}


vector<pii> xx;
pair<ll,ll> getsol(){
    set<pii> seen;
    xx.clear();
    ll tot=getnum();
    REP(i,n) proc(seen, xo[i],yo[i],xo[i+1],yo[i+1]);
    REP(i,m) proc(seen, xa[i],ya[i],xb[i],yb[i]);

    int res=0;
    FE(it,seen) if (isin(it->ST,it->ND)) ++res, xx.pb(*it); 
    return MP((ll)res,tot-res);

}

int main(){
    srand(0);
    int test=0;
    int check=0;

    int tn;
    if (test) tn=1000;
    else cin>>tn;


    REP(ti,tn){
        //fprintf(stderr,"test %d\n",ti);

        if (test) gen();
        else{
            cin>>n>>m;

            REP(i,n) scanf(" %d%d",xo+i,yo+i);
            REP(i,m) scanf(" %d%d%d%d",xa+i,ya+i,xb+i,yb+i);
        }
        xo[n]=xo[0];
        yo[n]=yo[0];

        //printf("done gen\n");
        //printf(">>>>>>>>>>>>> TEST CASE DESCRIPTION\n");
        //out(xo,n+1);
        //out(yo,n+1);
        //REP(i,m) printf(" (%d %d) xx (%d %d)\n",xa[i],ya[i],xb[i],yb[i]);
        int om=m;


        pair<ll,ll> sol;
        if (check) sol=getsol();
        //printf("%Ld %Ld\n",sol.ST,sol.ND);
        //continue;

        la.clear(); lb.clear();
        REP(i,m) lb.pb(line(point(xa[i],ya[i]),point(xb[i],yb[i])));
        REP(i,n) la.pb(line(point(xo[i],yo[i]),point(xo[i+1],yo[i+1])));

        ll tot=getnum();



        vector<line> lst=la;
        REP(i,m) lst.pb(lb[i]);
        phi=findrot(lst);
        REP(i,m) lb[i]=lb[i].rotate(phi);
        REP(i,n) la[i]=la[i].rotate(phi);

        //REP(i,m) printf("FUU %lf\n",lb[i].ang);
        //REP(i,m) assert(fabs(lb[i].ang-pi/2)>eps);

        //REP(i,n) la[i].disp();
        //REP(i,m) lb[i].disp();


        REP(i,m){
            int haveint=0, inside=1;
            int rem=0;
            REP(j,n){
                int s1=sgn(dist(la[(j+1)%n].a,la[j]));
                if (s1==0) s1=sgn(dist(la[(j+1)%n].b,la[j]));

                assert(s1!=0);
                int sa=sgn(dist(lb[i].a,la[j]));
                int sb=sgn(dist(lb[i].b,la[j]));

                //printf("LALALLA %d %d %d\n",s1,sa,sb);
                if (s1!=sa && s1!=sb){ rem=1; break; }

                if (s1!=-sa && s1!=-sb) continue;

                inside=0;
                point p;
                if (intersect(lb[i],la[j],p)){
                    haveint=1;
                    //printf("FUUUU\n");
                    //printf("intersect "); lb[i].disp(); la[i].disp();
                    //p.rotate(-phi).disp();
                    if (sb!=s1) lb[i].b=p;
                    if (sa!=s1) lb[i].a=p;
                }
            }
            //printf("FUU %d %d %d\n",rem,haveint,inside);
            if (rem || (!haveint && !inside)){
                //printf(">>>> REMOVING HERE\n");
                //lb[i].rotate(-phi).disp();
                swap(lb[i],lb[--m]);
                --i;
            }

        }

        REP(i,m) if (lb[i].b<lb[i].a){
            //printf("remove here >>\n");
            //lb[i].disp();
            //printf("%d %d\n",lb[i].b<lb[i].a,lb[i].a<lb[i].b);
            swap(lb[i--],lb[--m]);
        }

        //printf("rotate lines\n");
        //REP(i,m) lb[i].rotate(-phi).disp();
        //REP(i,m) lb[i].p0.rotate(-phi).disp();
        //printf("XAXAXA have %d lines\n",m);

        //puts("");
        //REP(i,m) lb[i].disp();

        //puts("");
        //puts("START");
        int res=go();
        pair<ll,ll> ans=MP(res,tot-res);

        if (check){
            //REP(i,xx.size()) printf("%d,",xx[i].ST);puts("");
            //REP(i,xx.size()) printf("%d,",xx[i].ND);puts("");
            //printf("sol: %d %d\n",sol.ST,sol.ND);
            //printf("out: %d %d\n",ans.ST,ans.ND);

            //REP(i,n+1) printf("%d,",xo[i]);puts("");
            //REP(i,n+1) printf("%d,",yo[i]);puts("");
            //REP(i,om) printf("line.append((%d,%d,%d,%d));\n",xa[i],ya[i],xb[i],yb[i]);

            assert(ans==sol);
        }
        printf("%Ld %Ld\n",ans.ST,ans.ND);
    }

    return 0;
}

