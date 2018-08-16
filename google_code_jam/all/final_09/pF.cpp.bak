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

const long double INF=1e20;
const long double PI=asin(1.)*2;
const long double EPS=1e-11;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline long double dist(ll x, ll y, ll a, ll b){return sqrt((long double)(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int sgn(double a){return (a <= EPS)?-1:(a==0)?0:1;}


struct Pillar{ int x, y, r, id; };
struct Line{long double angle, d; int pid, pos;};
struct Point{long double x, y;};
struct Area{
	Area(Point a, Point b, Pillar *d):a(a), b(b), d(d){}
	Point a, b; Pillar *d;
};


int nl;
vector<Pillar> lp;
vector<Area> arl[2];
Pillar a[2];
long double area[4];
vector<Line> la[2];



const int X=100, Y=100;
int xpos[4]={0, 100, 100, 0};
int ypos[4]={0, 0, 100, 100};

long double getAngle(long double x, long double y){

	long double angle;
	angle=(x == 0)?PI/2:atan(abs(y/x));

	if (x >= 0 && y < 0)angle=2*PI-angle;
	else if(x < 0 && y <= 0)angle=PI+angle;
	else if (x < 0 && y > 0)angle=PI-angle;

	return angle;
}

bool compareAngle(const Line &a, const Line &b){return (a.angle < b.angle || (a.angle == b.angle && a.d < b.d));}
bool compareDist(const Line a, const Line b){return (a.d <= b.d);}
bool comparePoint(const Point &a, const Point &b){return (a.y < b.y || (a.y == b.y && a.x <= b.x));}
bool eqPoint(const Point &a, const Point &b){return (fabs(a.x-b.x)<=EPS && fabs(a.y-b.y)<=EPS);}
bool compL(const pair<Point*,Point*>& a, const pair<Point*,Point*>& b){return getAngle(a.ND->x-a.ST->x, a.ND->y-a.ST->y) < getAngle(b.ND->x-b.ST->x, b.ND->y-b.ST->y);}


Point getWallInt(Pillar *s, Line *l){
	if (fabs(l->angle-PI) == PI/2)
		return (Point){s->x, ((l->angle)>0?100:0)};
	if (fabs(l->angle-PI/2) == PI/2)
		return (Point){((l->angle<PI/2)?100:0), s->y};



	long double u, v, n, w;
	u=cos(l->angle), v=sin(l->angle);

	//ux+x0=100

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

	w=(100-s->y)/v;
	if (w > 0){
		n=s->x+w*u;
		if (n >= 0 && n <= 100)
			return (Point){n, 100};
	}
	//y = 0, x=?
	w=(0-s->y)/v;
	if (w > 0){
		n=s->x+w*u;
		if (n >= 0 && n <= 100)
			return (Point){n, 0};
	}
	assert(0);
}


Point getCircleInt(Pillar *cen, Line *l, Pillar *p){
	long double u=cos(l->angle), v=sin(l->angle);
	long double xa=cen->x-p->x, ya=cen->y-p->y;
	long double a, b, c, d, us;

	//w2u2+2wu*xa+xa2+w2v2+2wv*ya+ya2=R2
	a=u*u+v*v, b=2*xa*u+2*ya*v, c=xa*xa+ya*ya-p->r*p->r;
	d=b*b-4*a*c;
	//printf("%Lf %d %d => %d %d %d\n", l->angle, cen->x, cen->y, p->x, p->y, p->r);
	assert(d+EPS >= 0);
	d=max(d, (long double)0.);
	us=min((-b-sqrt(d))/2./a, (-b+sqrt(d))/2./a);

	assert(sqr(cen->x+us*u-p->x)+sqr(cen->y+us*v-p->y)-sqr(p->r)<=EPS);
	return (Point){cen->x+us*u, cen->y+us*v};
}

long double trArea(Point& a, Point& b, Point& c){return fabs((c.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.y-a.y))/2; }
	
long double trArea(Point& a, Point& b, Pillar& c){ return fabs((c.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.y-a.y))/2; }

long double pieSlice(Pillar &d, Point &a, Point &b){
	//printf("%d %d %lf %lf %lf %lf\n", d.x, d.y, a.x, a.y, b.x, b.y);
	long double s=fabs(getAngle(a.x-d.x, a.y-d.y)-getAngle(b.x-d.x, b.y-d.y));
	if (s >= PI)s=2*PI-s;
	assert(s < PI);
	return s/2*d.r*d.r;
	

}

bool aboveLine(Point a, Point b, Point c){ return ((c.x-b.x)*(a.y-b.y)-(c.y-b.y)*(a.x-b.x)+EPS >= 0); }

bool insideTr(Point a, Point *l){
	int i;
	REP(i, 3)
		if (aboveLine(a, l[i], l[(i+1)%3]) != aboveLine(l[(i+2)%3], l[i], l[(i+1)%3]))
			return false;
	return true;
}

long double polygonArea(vector<Point> &pl){
	long double a;
	int i;

	if (SZ(pl) <= 2)return 0.;
	vector<pair<Point*,Point*> > l;

	sort(ALL(pl), comparePoint);
	REP(i, SZ(pl)-1)
		l.pb(make_pair(&pl[0], &pl[i+1]));
	sort(ALL(l), compL);

	a=0;
	REP(i, SZ(l)-1)
		a+=trArea(pl[0], *l[i].ND, *l[i+1].ND);
	
	return a;
}


bool crossPoint(Point a, Point b, Point c, Point d, Point *p){
	long double lx, ly, ux, uy, vx, vy, v, l;
	lx=c.x-a.x, ly=c.y-a.y;
	ux=b.x-a.x, uy=b.y-a.y, vx=c.x-d.x, vy=c.y-d.y;

	v=ux*vy-vx*uy;
	if (fabs(v)<=EPS)return false;//parallel lines

	l=(lx*vy-ly*vx)/v;

	p->x=a.x+ux*l, p->y=a.y+uy*l;
//	printf(">>>>>>%lf %lf <<<<<<<<<<<< %lf %lf %lf %lf %lf %lf %lf %lf\n", p->x, p->y, a.x ,a.y,b.x,b.y,c.x,c.y, d.x,d.y);
	if (p->x < min(a.x, b.x) || p->x > max(a.x, b.x) ||
			p->y < min(a.y, b.y) || p->y > max(a.y, b.y))return false;
	if (p->x < min(c.x, d.x) || p->x > max(c.x, d.x) ||
			p->y < min(c.y, d.y) || p->y > max(c.y, d.y))return false;

	return true;
}



void solve(){
	int i, j, k, x, y, f;
	int st[2];
	long double closer, d, anga, angb;
	Line l;

	REP(i, 2){
		//printf(">>>>>>>>>>>>>>>>>>>>>>><< %d %d\n", a[i].x, a[i].y);
		CLR(arl[i]);
		l.pid=-1, l.d=INF;
		
		REP(j, 4){
			l.pos=-1, l.angle=getAngle(xpos[j]-a[i].x, ypos[j]-a[i].y);
			la[i].pb(l);
		}


		closer=INF, st[i]=0;
		FE(it, lp){

			d=dist(it->x, it->y, a[i].x, a[i].y);
			assert(d != 0);
			

			anga=asin(it->r/d);
			angb=getAngle(it->x-a[i].x, it->y-a[i].y);
			assert(sgn(it->x-a[i].x) == sgn(cos(angb)));
			assert(sgn(it->y-a[i].y)==sgn(sin(angb)));
			

			angb=angb-anga;

			if (angb < 0)
				angb+=2*PI;
		//	printf("(%d)%d %d =>%Lf %Lf // %d\n", it->id, it->x, it->y, d, angb, it->r);
			la[i].pb((Line){angb, d, it->id, 0});

			if (d < closer)st[i]=SZ(la[i])-1, closer=d;

			angb+=2*anga;
			if (angb >= 2*PI)
				angb-=2*PI;
		//	printf("(%d)%d %d  =>%Lf %Lf\n", it->id, it->x, it->y, d, angb);
			la[i].pb((Line){angb, d, it->id, 1});
		}
		

		vector<Line> lopen;
	   	vector<Line> nla;

		d=la[i][st[i]].angle;

		for(j=4;j<SZ(la[i]);j+=2){
			if (st[i] == j)continue;
			anga=la[i][j].angle, angb=la[i][j+1].angle;
			assert(la[i][j].pos == 0 && la[i][j+1].pos==1);
			if (angb < anga)
				angb+=2*PI;
			if (anga < d && angb > d)lopen.pb(la[i][j]);
			else if (anga < d+2*PI && angb > d+2*PI)lopen.pb(la[i][j]);
		}
		//FE(itz, lopen)
		//	printf("<<%Lf %d %d\n", itz->angle, itz->pos, itz->pid);

		int ol=SZ(lopen);
		sort(ALL(la[i]), compareAngle);
		//FE(itz, la[i])
		//	printf("=============%Lf %d %d => %Lf\n", itz->angle, itz->pos, itz->pid, itz->d);

		closer=INF, st[i]=0;
		REP(j, SZ(la[i]))
			if (la[i][j].d < closer && la[i][j].pos==0)
				closer=la[i][j].d, st[i]=j;

		//printf("closer: %Lf %d\n", la[i][st[i]].angle, la[i][st[i]].pid);


		REP(j, SZ(la[i])){
			Line it=la[i][(j+st[i])%SZ(la[i])];

			if (it.pid == -1){
//				printf("laa\n");
			   	if (SZ(lopen) == 0)
					nla.pb(it);
				continue;
			}

			Pillar np=lp[it.pid];
			if (it.pos == 0){
				if (SZ(lopen) == 0 || lopen.front().d >= it.d-np.r)
					nla.pb(it);
				
//				printf("===%Lf %d %d\n", it->angle, it->pid, it->pos);
				it.d-=np.r;
			   	lopen.pb(it);
				sort(ALL(lopen), compareDist);

			}else{
				f=it.pid;
				if (lopen.front().pid == it.pid){

		//			printf("close %d => %d\n", it->pid, SZ(lopen));
					if (SZ(lopen) > 1)
						it.pid=lopen[1].pid;
					else
						it.pid=-1;
					nla.pb(it);
				}

				
				assert(f!=-1);
				FE(ita, lopen)
					if (f == ita->pid){ lopen.erase(ita);f=-1;break; }
				assert(f==-1);

			}
			sort(ALL(lopen), compareDist);
		}
		//FE(itz, lopen)
		//	printf("<<<<<<%Lf %d %d\n", itz->angle, itz->pos, itz->pid);
		//printf("%d == %d\n", SZ(lopen), ol);

		assert(SZ(lopen)==ol);
		la[i]=nla;
		
		Line *ta, *tb;
		Point npa, npb;
		Pillar *np;
		long double ar;
		
		FE(itz, la[i])
			printf("<<%Lf %d %d\n", itz->angle, itz->pos, itz->pid);
		printf("\n\n\n%d %d\n", a[i].x, a[i].y);

		REP(j, SZ(la[i])){
			ta=&la[i][j], tb=&la[i][(j+1)%SZ(la[i])];
			//printf("%Lf %d %d %Lf %d\n", ta->angle, ta->pid, ta->pos, tb->angle, tb->pid);

			if (ta->pid == -1){
				//if (ta->pos == 1)
				//	npa.x=xpos[ta->pos], npa.y=ypos[ta->pos];
				//else
				npa=getWallInt(a+i, ta);

				//if (tb->pos == 1)
				//	npb.x=xpos[tb->pos], npb.y=ypos[tb->pos];
				//else
				npb=getWallInt(a+i, tb);

				ar=trArea(npa, npb, a[i]);
				arl[i].pb(Area(npa, npb, NULL));
				//simple triangle npa > npb > a[i]
			}else{
				assert(ta->pos == 0 || ta->pid != -1);

				np=&lp[ta->pid];
				//printf("%Lf %d %d %Lf %d /// %d %d\n", ta->angle, ta->pid, ta->pos, tb->angle, tb->pid, a[i].x, a[i].y);
				//printf("%d %d %d\n", np->x, np->y, np->r);
				//printf("intersection with %d %d %d\n", np->x, np->y, np->id);
				npa=getCircleInt(a+i, ta, np);
				npb=getCircleInt(a+i, tb, np);


				assert(trArea(npa, npb, *np) <= pieSlice(*np, npa, npb)+EPS);
				ar=trArea(npa, npb, a[i]);
				ar+=trArea(npa, npb, *np)-pieSlice(*np, npa, npb);
				printf(">>>>>>>>>%Lf %Lf %Lf %Lf => %Lf\n", npa.x, npa.y, npb.x, npb.y, ar);

				arl[i].pb(Area(npa, npb, np));
			}
			
			area[i+1]+=ar;
		}
		//printf("%Lf %Lf\n", area[1], area[2]);
		//exit(0);
	}

	Point np; long double ar;
	vector<Point> tp;

	assert(area[1]<=10000.);
	assert(area[2]<=10000.);
	//printf("\n\n\n");
	FE(it, arl[0])
		FE(ita, arl[1]){
			CLR(tp);
			ar=0;
			Point tla[2][3];
			tla[0][0]=it->a, tla[0][1]=it->b, tla[0][2]=(Point){a[0].x, a[0].y};
			tla[1][0]=ita->a, tla[1][1]=ita->b, tla[1][2]=(Point){a[1].x, a[1].y};

			printf("\n\n\n\n");
			REP(i, 2)
				printf(" %Lf %Lf %Lf %Lf %Lf %Lf\n",tla[i][0].x, tla[i][0].y,tla[i][1].x, tla[i][1].y,tla[i][2].x, tla[i][2].y);


			if (it->d == NULL || it->d != ita->d){
				//intersection is a triangle


				REP(i, 2)
					REP(j, 3)
						if (insideTr(tla[i][j], tla[1-i]))
							tp.pb(tla[i][j]);

				REP(i, 3)
					REP(j, 3)
						if (crossPoint(tla[0][i], tla[0][(i+1)%3], tla[1][j], tla[1][(j+1)%3], &np))
							tp.pb(np);
						
				sort(ALL(tp), comparePoint);

				vector<Point>::iterator ity=unique(ALL(tp), eqPoint);
				tp.resize(SZ(tp)-(tp.end()-ity));
//				printf("%d\n", SZ(tp));

				FE(itz, tp)
					printf("%Lf %Lf\n", itz->x, itz->y);
				FE(itz, tp)
					printf("%Lf %Lf\n", itz->x, itz->y);
				printf("=>>>>>\n");

				ar=polygonArea(tp);
				FE(itz, tp)
					printf("%Lf %Lf\n", itz->x, itz->y);
				printf("%Lf\n", ar);

				printf("!%Lf %Lf\n", ar, trArea(tla[0][0], tla[0][1], tla[0][2]));
				printf(">%Lf %Lf\n", ar, trArea(tla[1][0], tla[1][1], tla[1][2]));

				assert(ar <= trArea(tla[0][0], tla[0][1], tla[0][2])+100*EPS);
				assert(ar <= trArea(tla[1][0], tla[1][1], tla[1][2])+100*EPS);


			}else{

				REP(j, 2)
					REP(i, 2)
						if (insideTr(tla[i][j], tla[i^1]))
							tp.pb(tla[i][j]);
						
				sort(ALL(tp), comparePoint);
				vector<Point>::iterator ity=unique(ALL(tp), eqPoint);
				tp.resize(SZ(tp)-(tp.end()-ity));
				assert(SZ(tp) <= 2);
					
				//if (SZ(tp) < 2)continue;

				bool pie=false;
				Point ppa, ppb;
			   	if (SZ(tp) == 2)ppa=tp[0], ppb=tp[1], pie=true;

				REP(i, 2)
					if (insideTr(tla[i][2], tla[i^1]))
						tp.pb(tla[i][2]);

				FOR(i, 1, 2)
					FOR(j, 1, 2)
						if (crossPoint(tla[0][i], tla[0][(i+1)%3], tla[1][j], tla[1][(j+1)%3], &np))
							tp.pb(np);
						
				sort(ALL(tp), comparePoint);
				ity=unique(ALL(tp), eqPoint);
				tp.resize(SZ(tp)-(tp.end()-ity));
				//printf("%d\n", SZ(tp));

				//printf("=>>>>> %d %d %d\n", it->d->x, it->d->y, it->d->r);
				//REP(i, 2)
				//	REP(j, 3)
				//		printf("%Lf %Lf \n", tla[i][j].x, tla[i][j].y);
				//printf("=======\n");
				//FE(itz, tp)
				//	printf("%Lf %Lf\n", itz->x, itz->y);
				//printf("%Lf %Lf %Lf %Lf\n", ppa.x, ppa.y, ppb.x, ppb.y);
				//printf("\n\n");
				ar=polygonArea(tp);
				if (pie)
					ar+=trArea(ppa, ppb, *it->d)-pieSlice(*it->d, ppa, ppb);

				assert(pieSlice(*it->d, ppa, ppb) >= trArea(ppa, ppb, *it->d));



//				printf("!%Lf %Lf\n", ar, trArea(tla[0][0], tla[0][1], tla[0][2]));
//				printf(">%Lf %Lf\n", ar, trArea(tla[1][0], tla[1][1], tla[1][2]));
				assert(ar <= trArea(tla[0][0], tla[0][1], tla[0][2])+100*EPS);
				assert(ar <= trArea(tla[1][0], tla[1][1], tla[1][2])+100*EPS);

				///printf("laa\n");
				//complicated issue

			}
			area[3]+=ar;
			area[2]-=ar, area[1]-=ar;

		}



	//FE(ita, lp)
	//	printf("%d %d %d\n", ita->x, ita->y, ita->r);

	//printf("%d %d %d %d\n", a[0].x, a[0].y, a[1].x, a[1].y);
	//printf("%Lf\n", area[3]);
	assert(area[3]<=10000);

	area[0]=100*100;
	REP(i, SZ(lp))
		area[0]-=PI*lp[i].r*lp[i].r;
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
		//if (t!=12)continue;

//		REP(i, 2)printf("%d %d\n", a[i].x, a[i].y);
//		FE(it, lp)
//			printf("%d %d %d\n", it->x, it->y, it->r);

		solve();
		printf("Case #%d:\n", t+1);
		REP(i, 4)
			printf("%.10Lf\n", fabs(area[i]));




	}


	return EXIT_SUCCESS;
}

