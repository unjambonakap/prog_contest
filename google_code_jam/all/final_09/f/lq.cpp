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
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;
const double PI=asin(1.)*2;
const double EPS=10e-9;

struct Pillar{ int x, y, r, id; };
struct Line{double angle, d; int pid, pos;};
struct Point{double x, y;};
struct Area{
	Area(Point a, Point b, Pillar *d):a(a), b(b), d(d){}
	Point a, b; Pillar *d;
};


int nl;
vector<Pillar> lp;
vector<Area> arl[2];
Pillar a[2];
double area[4];
vector<Line> la[2];



const int X=100, Y=100;
int xpos[4]={0, 100, 100, 0};
int ypos[4]={0, 0, 100, 100};

double getAngle(double x, double y){

	double angle;
	angle=(x == 0)?PI/2:atan(abs(y/x));

	if (x > 0 && y < 0)angle=2*PI-angle;
	else if(x < 0 && y < 0)angle=PI+angle;
	else if (x < 0 && y > 0)angle=PI-angle;

	return angle;
}

bool compareAngle(const Line &a, const Line &b){return (a.angle < b.angle);}
bool compareDist(const Line *a, const Line *b){return (a->d > b->d);}


Point getWallInt(Pillar *s, Line *l){
	if (fabs(l->angle-PI) == PI/2)
		return (Point){s->x, ((l->angle)>0?100:0)};
	if (fabs(l->angle-PI/2) == PI/2)
		return (Point){((l->angle>0)?100:0), s->y};



	double u, v, n, w;
	u=cos(l->angle), v=sin(l->angle);

	//x = 100, y=?
	w=(100-s->x)/u;
	if (w > 0){
		n=s->y+w*v;
		if (n >= 0 && n <= 100)
			return (Point){100, n};
	}
	

	//x = 0, y=?
	
	w=(0-s->x)/u;
	if (w > 0){
		n=s->y+w*v;
		if (n >= 0 && n <= 100)
			return (Point){0, n};
	}
	//y = 100, x=?

	w=(100-s->x)/u;
	if (w > 0){
		n=s->x+w*u;
		if (n >= 0 && n <= 100)
			return (Point){n, 0};
	}
	//y = 0, x=?
	w=(0-s->y)/v;
	if (w > 0){
		n=s->y+w*u;
		if (n >= 0 && n <= 100)
			return (Point){n, 100};
	}
	assert(0);
}


Point getCircleInt(Pillar *cen, Line *l, Pillar *p){
	double u=cos(l->angle), v=sin(l->angle);
	double xa=cen->x-p->x, ya=cen->y-p->y;
	double a, b, c, d, us;

	//w2u2+2wu*xa+xa2+w2v2+2wv*ya+ya2=R2
	a=u*u+v*v, b=2*xa*u+2*ya*v, c=xa*xa+ya*ya-p->r*p->r;
	d=b*b-4*a*c;
	assert(d+EPS >= 0);
	d=max(d, d+EPS);
	us=max((-b-sqrt(d))/2./a, (-b+sqrt(d))/2./a);
	return (Point){cen->x+us*u, cen->y+us*v};
}

double trArea(Point& a, Point& b, Point& c){ return fabs((c.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.y-a.y))/2; }
double trArea(Point& a, Point& b, Pillar& c){ return fabs((c.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.y-a.y))/2; }

double pieSlice(Pillar &d, Point &a, Point &b){
	double s=fabs(getAngle(a.x-d.x, a.y-d.y)-getAngle(b.x-d.x, b.y-d.y));
	if (s > PI)s=2*PI-s;
	assert(s < PI);
	return s/2*d.r*d.r;
	

}




void solve(){
	int i, j, k, x, y;
	int st[2];
	double closer, d, anga, angb;
	Line l;


	REP(i, 2){
		CLR(arl[i]);
		l.pid=-1, l.d=INF;
		
		REP(j, 4){
			l.pos=j, l.angle=getAngle(xpos[j]-a[i].x, ypos[j]-a[i].y);
			la[i].pb(l);
		}


		FE(it, lp){

			d=dist(it->x, it->y, a[i].x, a[i].y);
			
			anga=asin(it->r/d);
			printf(">>>>>><<%lf\n", anga);
			angb=getAngle(it->x-a[i].x, it->y-a[i].y);
			angb=angb-anga;
			if (angb < 0)
				angb+=2*PI;
			la[i].pb((Line){angb, d, it->id, 0});
			angb+=2*anga;
			if (angb >= 2*PI)
				angb-=2*PI;
			la[i].pb((Line){angb, d, it->id, 1});
		}
		
		sort(ALL(la[i]), compareAngle);


		closer=INF, st[i]=0;
		REP(j, SZ(la[i]))
			if (la[i][j].d < closer)
				closer=la[i][j].d, st[i]=j;




		vector<Line*> lopen;
	   	vector<Line> nla;
		REP(j, SZ(la[i])){
			Line *it=&la[i][(j+st[i])%SZ(la[i])];

			if (it->pid == -1){
			   	if (SZ(lopen) == 0)
					nla.pb(*it);
				continue;
			}

			if (it->pos == 0){
				if (SZ(lopen) == 0 || lopen.back()->d >= it->d)
					nla.pb(*it), lopen.pb(&(*it));

			}else{
				if (SZ(lopen) == 0 || lopen.back()->d >= it->d)
					nla.pb(*it);
				FE(ita, lopen)
					if ((*ita)->pid == it->pid){ lopen.erase(ita);break; }
			}
			sort(ALL(lopen), compareDist);
		}
		la[i]=nla;
		
		FE(it, la[i])
			printf("%lf %lf %d\n", it->angle, it->d, it->pos);
		Line *ta, *tb;
		Point npa, npb;
		Pillar *np;
		double ar;
		
		REP(j, SZ(la[i])){
			ta=&la[i][j], tb=&la[i][(j+1)%SZ(la[i])];

			if (ta->pid == -1 || (ta->pos == 1 && (tb->pos == 0 || tb->pid == -1))){
				if (ta->pid == -1)
					npa.x=xpos[ta->pos], npa.y=ypos[ta->pos];
				else
					npa=getWallInt(a+i, ta);

				if (tb->pid == -1)
					npb.x=xpos[tb->pos], npb.y=ypos[tb->pos];
				else
					npb=getWallInt(a+i, tb);

				ar=trArea(npa, npb, a[i]);
				arl[i].pb(Area(npa, npb, NULL));
				//simple triangle npa > npb > a[i]
			}else{
				np=(ta->pos == 0)?&lp[ta->pid]:&lp[tb->pid];
				npa=getCircleInt(a+i, ta, np);
				npb=getCircleInt(a+i, tb, np);


				ar=trArea(npa, npb, a[i]);
				ar+=trArea(npa, npb, *np)-pieSlice(*np, npa, npb);;

				arl[i].pb(Area(npa, npb, np));
			}
			area[i+1]+=ar;
		}
	}

	FE(it, arl[0])
		FE(ita, arl[1]){




		}

	
	

	area[0]=100*100;
	REP(i, SZ(lp))
		area[0]-=2*PI*lp[i].r*lp[i].r;
	REP(i, 3)
		area[0]-=area[i+1];

	




}

int main(){
	int i, j, k, T, t;
	Pillar p;

	scanf("%d", &T);
	REP(t, T){
		REP(i, 2){
			scanf("%d %d", &a[i].x, &a[i].y);
			CLR(la[i]);
		}

		scanf("%d", &nl);
		CLR(lp);

		REP(i, nl){
			scanf("%d %d %d", &p.x, &p.y, &p.r); p.id=i;
			lp.pb(p);
		}
		REP(i, 4)
			area[i]=0;

		solve();
		printf("Case #%d:\n", t+1);
		REP(i, 4)
			printf("%lf\n", area[i]);




	}


	return EXIT_SUCCESS;
}

