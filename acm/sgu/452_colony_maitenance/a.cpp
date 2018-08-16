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

const int l=100;
const int maxn=17;
const double oo=1e100;
const int maxp=maxn*8;
const int maxf=maxn*6;
const double pi=acos(-1.);

double res;
int n;

struct edge;
struct face;
struct point;
struct cube;

struct coord{
    int x,y,z;

    coord(){x=y=z=0;}
    coord(int x,int y, int z):x(x),y(y),z(z){}

    coord operator+(const coord &a)const{return coord(x+a.x,y+a.y,z+a.z);}
    coord operator-(const coord &a)const{return coord(x-a.x,y-a.y,z-a.z);}
    coord operator/(int v)const{return coord(x/v,y/v,z/v);}
    coord operator*(int v)const{return coord(x*v,y*v,z*v);}
    void disp(){printf("(%d,%d,%d)\n",x,y,z);}

    int operator*(const coord &a)const{return x*a.x+y*a.y+z*a.z;}

    int adj(const coord &a)const{return (a-*this)*(a-*this)==l*l;}
    int dist()const{return *this**this;}

    void read(){scanf(" %d%d%d",&x,&y,&z);}
    bool operator<(const coord &a)const{
        if (x!=a.x) return x<a.x;
        if (y!=a.y) return y<a.y;
        return z<a.z;
    }
    bool operator==(const coord &a)const{return x==a.x&&y==a.y&&z==a.z;}
};

set<coord> cubepos;
struct cube{
    coord p;
}cubes[maxn];

struct point{
    coord p;
    vector<face*> fl;
    vector<edge*> el;
    vector<cube*> cl;

    point(){}
    point(const coord &p):p(p){}

}points[maxp];

struct edge{
    point *p1,*p2;
    vector<face*> fl;
    vector<cube*> cl;

    edge(point *p1=0, point *p2=0):p1(p1),p2(p2){}


}edges[maxp];

struct face{
    vector<point*> pl;
    vector<edge*> el;
    vector<cube*> cl;

    int can;
    coord mid;
    coord dir;

    void disp(){
        puts("");
        printf("CAN > %d\n", can);
        printf("MID > "); mid.disp();
        printf("DIR > "); dir.disp();
        printf("cubes > "); 
        FE(it,cl) (*it)->p.disp();
        printf("adj >> \n");
        if (1)FE(it,adj){
            it->ST->mid.disp();
            it->ND->p1->p.disp();
            it->ND->p2->p.disp();

            printf("xx\n");
        }

    }
    vector<pair<face*,edge*> > adj;

}faces[maxf];



int np,ne,nf,nc;
coord ps,pe;
face *endf;

const double eps=1e-7;
double dx[maxf][maxp];
priority_queue<pair<double,pii> > q;

vector<cube*> intersect(vector<cube*> &la, vector<cube*> &lb){
    vector<cube*> res;
    int j=0;
    REP(i,la.size()){
        for (; j<lb.size() && lb[j]<la[i]; ++j);
        if (j<lb.size() && lb[j]==la[i]) res.pb(la[i]);
    }
    return res;
}

face *getf(coord p){
    face *best=faces;
    REP(i,nf){
        face *fx=faces+i;
        if ((fx->mid-p).dist()<(best->mid-p).dist()) best=fx;
    }
    return best;
}

int add(face *f, point *p, double d){
    int f0=f-faces, p0=p-points;
    int fd=0;
    if (d+eps<dx[f0][p0]) q.push(MP(-(dx[f0][p0]=d),MP(f0,p0))), fd=1;
    return fd;
}

pii operator+(const pii &a, const pii &b){return MP(a.ST+b.ST,a.ND+b.ND);}
pii operator-(const pii &a, const pii &b){return MP(a.ST-b.ST,a.ND-b.ND);}
pii operator*(const pii &a, int v){return MP(a.ST*v,a.ND*v);}
double dist(const pii &a){return sqrt(a.ST*a.ST+a.ND*a.ND);}
double getang(const pii &a){return atan2(a.ND,a.ST);}

pii unit(pii a){
    if (a.ST) a.ST/=fabs(a.ST);
    if (a.ND) a.ND/=fabs(a.ND);
    return a;
}

void disp(pii a){printf(" xx (%d %d\n",a.ST,a.ND);}

pii remap(coord v1, coord v2, pii p1, pii p2, pii dx){

    pii p0,r1,r2;


    if (v1.x==0 && v2.x==0){
        r1.ST=v1.y; r1.ND=v1.z;
        r2.ST=v2.y; r2.ND=v2.z;
    }else if (v1.y==0 && v2.y==0){
        r1.ST=v1.x; r1.ND=v1.z;
        r2.ST=v2.x; r2.ND=v2.z;
    }else{
        r1.ST=v1.y; r1.ND=v1.x;
        r2.ST=v2.y; r2.ND=v2.x;
        assert(v1.z==0 && v2.z==0);
    }

    if (r1.ST!=r2.ST) swap(r1.ST,r1.ND), swap(r2.ST,r2.ND);

    assert(r1.ST==r2.ST);
    assert(fabs(r1.ND-r2.ND)==l);


    dx=unit(dx);
    pii dx2=unit(p2-p1);
    
    p0=p1+dx*fabs(r1.ST)+dx2*fabs(r1.ND);

    return p0;
}

int rec;

void go(double d0, face *pf, edge *ex, pii c0, pii pfc, pii ec1, pii ec2, double a1, double a2){
    if (min(dist(ec1-c0),dist(ec2-c0))+d0>res) return;
    if (a1+eps>a2) return;

    //printf("\n\nNEW GO\n");
    //disp(c0);
    //disp(pfc);
    //disp(ec1);
    //disp(ec2);
    //ex->p1->p.disp();
    //ex->p2->p.disp();
    ////pf->disp();
    //printf("ang >> %lf %lf\n",a1,a2);


    pii ec3,ec4;
    edge *iex;
    REP(i,pf->el.size()){
        edge *e=pf->el[i];
        if (e->p1==ex->p1 || e->p1==ex->p2
                || e->p2==ex->p1 || e->p2==ex->p2) continue;
        iex=e;
        break;
    }
    map<point*,pii> rmp;
    rmp[ex->p1]=ec1;
    rmp[ex->p2]=ec2;

    pii dp;
    if (ec1.ST==ec2.ST) dp=MP(2*(ec1.ST-pfc.ST),0);
    else dp=MP(0,2*(ec1.ND-pfc.ND));

    if (iex->p1->p.adj(ex->p1->p)) rmp[iex->p1]=ec1+dp, rmp[iex->p2]=ec2+dp;
    else rmp[iex->p1]=ec2+dp, rmp[iex->p2]=ec1+dp;

    //here proc end
    if (pf==endf){
        pii pp=remap(pe-ex->p1->p,pe-ex->p2->p,ec1,ec2,dp);
        double ang=getang(pp-c0);
        if (a1-eps<ang&&ang<a2+eps) res=min(res,d0+dist(pp-c0));
    }

    assert(rmp.size()==4);



    FE(it,pf->pl){
        assert(rmp.count(*it));
        pii p=rmp[*it]-c0;

        double ang=getang(p);
        if (ang+eps<a1 || a2+eps<ang) continue;

        add(pf,*it,d0+dist(p));
    }


    REP(i,pf->adj.size()){
        face *nfx=pf->adj[i].ST;
        edge *nex=pf->adj[i].ND;
        if (nex==ex) continue;
        pii p1=rmp[nex->p1], p2=rmp[nex->p2];

        double na1=getang(p1-c0), na2=getang(p2-c0);
        if (na1>na2) swap(na1,na2);
        na1=max(na1,a1);
        na2=min(na2,a2);

        go(d0,nfx,nex,c0,pfc+dp,p1,p2,na1,na2);
    }




    return;
}


void go0(face *f, point *p, double d){
    rec=0;

    if (endf==f) res=min(res,d+sqrt((p->p-pe).dist()));


    REP(i,f->adj.size()){
        face *fx=f->adj[i].ST;
        edge *ex=f->adj[i].ND;

        coord p0=p->p;
        coord p1=ex->p1->p;
        coord p2=ex->p2->p;

        if (p0==p1) go(d,fx,ex,MP(0,0),MP(-l/2,l/2),MP(0,0),MP(0,l),0,pi/2);
        else if (p0==p2) go(d,fx,ex,MP(0,0),MP(0,0),MP(-l/2,l/2),MP(0,l),0,pi/2);
        else{
            pii pp0,pp1,pp2;
            pp1=MP(0,0); pp2=MP(l,0);

            pp0=remap(p1-p0,p2-p0,pp1,pp2,MP(0,-1));


            double a1=getang(pp1-pp0), a2=getang(pp2-pp0);
            if (a1>a2) swap(a1,a2);
            go(d,fx,ex,pp0,MP(l/2,-l/2),pp1,pp2,a1,a2);
        }



    }
}

void expand(face *f, point *p, double d){
    REP(i,f->adj.size()){
        edge *e=f->adj[i].ND;
        if (e->p1==p || e->p2==p) add(f->adj[i].ST,p,d);
    }
}

void solve(){
    res=nc*sqrt(2)*l*2;
    while(q.size()) q.pop();
    REP(i,nf) REP(j,np) dx[i][j]=oo;

    endf=getf(pe);
    face *fx=getf(ps);

    point pp(ps);
    go0(fx,&pp,0);



    while(q.size()){
        pii a=q.top().ND;
        double d=-q.top().ST;
        q.pop();
        if (dx[a.ST][a.ND]+eps<d) continue;
        expand(faces+a.ST,points+a.ND,d);

        if (res-eps<d) break;
        go0(faces+a.ST,points+a.ND,d);
    }

    if (0) REP(j,np){
        REP(i,nf) if (dx[i][j]<oo){
            if (points[j].p.z!=50) continue;
            printf("%lf xx %d>> ",dx[i][j],j);
            points[j].p.disp();
        }
        puts("");
    }
}


int main(){
    int ti=0;
    while(cin>>nc,!cin.eof()){

        ++ti;

        REP(i,nc) cubes[i].p.read();

        cubepos.clear();
        REP(i,nc) cubepos.insert(cubes[i].p);

        ps.read(); pe.read();


        np=0;
        map<coord,point*> rmp;
        REP(i,nc) REP(x,2) REP(y,2) REP(z,2){
            coord cx=cubes[i].p+coord(x*l,y*l,z*l)-coord(l/2,l/2,l/2);
            if (!rmp.count(cx)) *(rmp[cx]=points+np++)=point(cx);
            rmp[cx]->cl.pb(cubes+i);

        }

        ne=0;
        REP(i,np) REP(j,i) if (points[i].p.adj(points[j].p)){
            points[i].el.pb(edges+ne);
            points[j].el.pb(edges+ne);

            (edges[ne++]=edge(points+i,points+j)).cl=intersect(points[i].cl,points[j].cl);;
        }

        nf=0;
        map<vector<point*>,face*> rmp2;

        REP(i,np){
            point *p1=points+i;
            FE(it,p1->el){
                edge *e1=*it;
                point *p2=e1->p1==p1?e1->p2:e1->p1;

                FE(it2,p2->el){
                    edge *e2=*it2;
                    point *p3=e2->p1==p2?e2->p2:e2->p1;

                    if (p3==p1) continue;
                    FE(it3,p3->el){
                        edge *e3=*it3;
                        point *p4=e3->p1==p3?e3->p2:e3->p1;

                        if (p4!=p2 && p4->p.adj(p1->p)){
                            vector<point*> tb;
                            tb.pb(p1); tb.pb(p2); tb.pb(p3); tb.pb(p4);
                            faces[nf]=face();
                            faces[nf].pl=tb;

                            sort(ALL(tb));
                            if (rmp2.count(tb)) continue;
                            rmp2[tb]=faces+nf++;


                            face *f=rmp2[tb];
                            f->pl=tb;
                            f->el.pb(*it);
                            f->el.pb(*it2);
                            f->el.pb(*it3);

                            FE(it4,p4->el){
                                edge *e4=*it4;
                                if (e4->p1==p1 || e4->p2==p1){ f->el.pb(e4); break; }
                            }

                            REP(i,f->el.size()) f->el[i]->fl.pb(f);


                            f->cl=f->el[0]->cl;
                            REP(i,3) f->cl=intersect(f->cl,f->el[i+1]->cl);
                        }
                    }
                }
            }
        }


        REP(i,nf){
            face *fx=faces+i;
            fx->can=fx->cl.size()==1;
            assert(fx->el.size()==4);
            assert(fx->pl.size()==4);
            if (!fx->can) continue;

            coord cc;
            REP(j,4) cc=cc+fx->pl[j]->p;
            fx->mid=cc/4;
            fx->dir=fx->cl[0]->p-fx->mid;
        }

        REP(i,nf){
            face *fx=faces+i;
            if (!fx->can) continue;
            REP(j,fx->el.size()){
                edge *ex=fx->el[j];

                REP(k,ex->fl.size()){
                    face *fy=ex->fl[k];
                    if (!fy->can || fy<=fx) continue;

                    if (fx->cl==fy->cl
                            || fx->dir==fy->dir
                            || cubepos.count(fx->cl[0]->p+fy->dir*2)) {
                        fx->adj.pb(MP(fy,ex));
                        fy->adj.pb(MP(fx,ex));
                    }
                }
            }
        }

        //printf("HAVE %d faces\n",nf);
        //REP(i,nf) faces[i].disp();
        solve();




        printf("%.15lf\n",res);
    }

    return 0;
}


