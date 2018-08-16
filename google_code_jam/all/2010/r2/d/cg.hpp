#ifndef CG_H
#define CG_H


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
#include <climits>
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

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
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

#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

struct Point;
struct Line;
struct Segment;
struct ConvexPolygon;
struct Polygon;

template<class T> class cvector: public vector<T>{
	public:

	struct citerator{
		citerator(cvector<T>* c=NULL):c(c){}
		void setList(cvector<T>* _c){ c=_c; }
		bool operator==(const citerator& ca){return it==ca.it;}
		bool operator!=(const citerator& ca){return it!=ca.it;}

		citerator& operator++(){
			++it;
			if (it==c->end())it=c->begin();
			return *this;
		}

		citerator& operator--(){
			if (it==c->begin())it=c->end();
			--it;
			return *this;
		}
		T& operator*(){return *it;}
		citerator &operator=(const typename cvector<T>::iterator &i){ it=i; return *this;}
		vector<T>* c;
		typename vector<T>::iterator it;
		

	};


};


struct Point{
	static Point Inf(){return Point(1, 0, true);}
	Point(){}
	Point(long double x, long double y, bool inf=false):x(x), y(y), inf(inf){if (inf)x=(x==0)?1:x/abs(x);}
	bool operator<(const Point& p)const;
	bool cmpY(const Point& p)const;

	bool operator<=(const Point& p)const{
		if (inf){
			if (p.inf)
				return !(x>0 && p.x<0);
			return x<0;
		}
		return x<=p.x;
	}
	bool between(const Point& a, const Point& b)const{ return x>=min(a.x, b.x)&&x<=max(a.x, b.x)&&y>=min(a.y, b.y)&&y<=max(a.y, b.y); }
	bool operator==(const Point& p)const;
	bool operator!=(const Point& p)const{return !(*this==p);}
	Point operator-()const{return Point(-x, -y, inf);}

	Point operator+(const Point& a)const{return Point(x+a.x, y+a.y);}
	Point& operator+=(const Point& a){x+=a.x, y+=a.y; return *this;}
	Point operator-(const Point& a)const{return Point(x-a.x, y-a.y);}
	Point& operator-=(const Point& a){x-=a.x, y-=a.y; return *this;}
	Point& operator=(const Point& p){inf=p.inf, x=p.x, y=p.y, data=p.data; return *this;}
	long double operator^(const Point& p)const{return x*p.y-y*p.x;}
	long double operator*(const Point& p)const{return x*p.x+y*p.y;}

	Point operator*(long double s)const{return Point(x*s, y*s);}
	Point operator/(long double s)const{return Point(x/s, y/s);}
	Point operator*=(long double s){x*=s, y*=s; return *this;}
	Point operator/=(long double s){x/=s, y/=s; return *this;}

	long double dist(const Point& p)const{ return sqrt(SQR(p.x-x)+SQR(p.y-y)); }
	long double length()const{return sqrt(x*x+y*y);}
	Point orth()const{return Point(-y, x);}
	Line getLine(const Point&)const;

	Point inv(const Point& c)const;

	Point vrotate(long double)const;
	Point& svrotate(long double);
	Point rotate(const Point& p, long double ang)const;//every rotation are performed counterclockwise
	Point& srotate(const Point& p, long double ang);
	Line dual()const;

	bool on(const Line& l)const;

	long double angle()const;

	bool inf;
	long double x, y;
	int data;
};
char orient(const Point& a, const Point& b, const Point& c);
Point operator*(long double s, const Point& p);


struct Line{
	static const int N=0, D=-1, U=1;
	static Line Vert(long double a){return Line(a, 0, true);}
	static Line FromVect(const Point& v, const Point& p);
	Line(long double a=0, long double b=0, bool vert=false, int side=N):a(a), b(b), vert(vert), side(side){}
	long double eval(long double x)const{ assert(!vert);return a*x+b; }
	Point vect()const;
	Point getPoint()const;

	long double angle()const;
	Point dual()const;

	Line rotate(const Point& p, long double ang)const;
	Line& srotate(const Point& p, long double ang);
	bool operator<(const Line& l)const{return angle()<l.angle();}

	long double a, b;//y=ax+b
	bool vert;//x=a
	int side;
	static long double x_eval;
};



struct Segment:public Line{
	Segment(const Line& d=Line(), const Point& sp=Point::Inf(), const Point& ep=Point::Inf()):Line(d), sp(sp), ep(ep){}
	Segment(const Point& sp, const Point& ep):sp(sp), ep(ep){
		if (sp.x==ep.x)
			vert=1, a=sp.x;
		else
			a=(ep.y-sp.y)/(ep.x-sp.x), b=sp.y-sp.x*a;
	}
	Segment inv()const{
		Segment s=*this;
		s.sp=ep, s.ep=sp;
		return s;
	}

	bool cmpY(const Segment& s)const;
	Point sp, ep;
};


struct ConvexPolygon{
	bool in(const Point& p, int li, int ui)const{
		if (SZ(lower)>0){
			if (li<0 || li>=SZ(lower))return false;
			if (lower[li].eval(p.x)>p.y)return false;
		}
		if (SZ(upper)>0){
			if (upper[ui].eval(p.x)<p.y)return false;
			if (ui<0 || ui>=SZ(upper))return false;
		}
		//cout<<p<<endl;
		//cout<<"<<<<<<<<<<"<<upper[ui].eval(p.x)<<"=>"<<lower[li].eval(p.x)<<endl;
		return true;
	}

	bool done(int li, int ui)const{return li>=SZ(lower)&&ui>=SZ(upper);}

	Point nextPoint(int li, int ui)const{
		if (li==-1 || ui==-1)return sp();
		Point p;
		if (li<SZ(lower))
			p=lower[li].ep;
		if (ui<SZ(lower))
			p=min(p, upper[ui].ep);
		return p;

	}

	void addLowP(const Point& p, const Segment& s){
		Point a=(lower.size()==0)?actl:lower.back().ep;
		lower.pb(Segment(s, a, p));
		actl=p;
	}
	void addLowP(const Point& p){addLowP(p, Segment(lastLowP(), p));}

	void addSupP(const Point& p, const Segment& s){
		if (upper.size()==0)
			upper.pb(Segment(s, actu, p));
		else
			upper.pb(Segment(s, upper.back().ep, p));
		actu=p;
	}
	void addSupP(const Point& p){ addSupP(p, Segment(lastSupP(), p)); }
	void setSP(const Point& p){actl=actu=p;}

	bool empty()const{return lower.size()==0 && upper.size()==0;}
	Point lastLowP()const{return actl;}
	Point lastSupP()const{return actu;}

	Point sp()const{ return (lower.size()>0)?lower[0].sp:upper[0].sp; }//assert not empty
	Point ep()const{ return (lower.size()>0)?lower.back().ep:upper.back().ep; }//assert not empty

	vector<Segment> lower, upper;
	Point actl, actu;
	Line la, lb;
};

struct Circle{
	long double r;
	Point c;
};




struct State{ 
	State(int la=-1, int ua=-1, int lb=-1, int ub=-1){ pa[0]=la, pa[1]=ua, pb[0]=lb, pb[1]=ub;}
	State& operator=(const State& s){
		memcpy(pa, s.pa, 2*sizeof(int));
		memcpy(pb, s.pb, 2*sizeof(int));
		return *this;
	}
	State getNs(int a, int b){
		State s;
		s=*this;
		if (a==0)
			++s.pa[b];
		else
			++s.pb[b];
		return s;
	}
	int pa[2], pb[2];
};

struct Event{
	int type;//0=> polygon point, 1=>intersection point
	State cur;
	Point p;
	State envelope;
	bool polygon;

	void setEnvelope(int a, int b, int c, int d){envelope.pa[0]=a, envelope.pa[1]=b, envelope.pb[0]=c, envelope.pb[1]=d;}
	bool operator<(const Event& e){return p<e.p;}
};
ostream& operator<<(ostream& o, const Point& a);
ostream& operator<<(ostream& o, const Line& a);
ostream& operator<<(ostream& o, const Segment& a);
ostream& operator<<(ostream& o, const ConvexPolygon& a);
Point lineIntersection(Line a, Line b);
Point segmentIntersection(const Segment& a, const Segment& b);
ConvexPolygon cpIntersection(const ConvexPolygon& a, const ConvexPolygon& b);

pair<vector<Point>, vector<Point> > procHull(vector<Point>);
pair<vector<Point>, vector<Point> > extractHulls(vector<Point>);


struct Pol_Vertex;
struct Pol_Edge;

struct Pol_Vertex{
	Point p;
	Pol_Edge *src, *sink;

	Pol_Vertex(const Point& p=Point()):p(p), src(NULL), sink(NULL), c(-1){}

	int c;
	
	bool operator<(const Pol_Vertex& v)const{return p<v.p;}
	bool cmpY(const Pol_Vertex& v)const{return p.cmpY(v.p);}
};

struct Pol_Edge{
	Pol_Vertex *org, *dest;
	Segment s;
	bool cmpY(const Pol_Edge& e)const{return s.cmpY(e.s);}
	Pol_Edge *next, *prev;
	bool side;
};


struct Polygon{
	cvector<Pol_Vertex*> v;
	cvector<Pol_Edge*> e; 
	vector<Point> xh, xl;

	Polygon& operator=(const Polygon& a){
		v.clear(), e.clear();
		FE(it, a.v)
			v.pb(new Pol_Vertex(**it));
		FE(it, a.e)
			e.pb(new Pol_Edge(**it));
		xh=a.xh, xl=a.xl;
	}
	Polygon(){}
	Polygon(const Polygon& a){
		FE(it, a.v)
			v.pb(new Pol_Vertex(**it));
		FE(it, a.e)
			e.pb(new Pol_Edge(**it));
		xh=a.xh, xl=a.xl;
	}

	~Polygon(){
		FE(it, v)
			delete *it;
		FE(it, e)
			delete *it;
	}


	Polygon& operator<<(const Point& a){
		Pol_Edge *ea;
		Pol_Vertex *va, *vb;

		if (v.size()==0){
			v.pb(new Pol_Vertex(a));
			return *this;
		}


		va=v.back();
		if (v[0]->p==a)
			vb=v[0];
		else
			v.pb(vb=new Pol_Vertex(a));

		e.pb(ea=new Pol_Edge);
		ea->org=va, ea->dest=vb;
		ea->s=Segment(va->p, vb->p);
		
		cout<<va->p<<endl;
		va->src=vb->sink=ea;
		ea->prev=va->sink; 
		if (ea->prev!=NULL)ea->prev->next=ea;

		assert(ea!=NULL);
		return *this;
	}

	vector<Polygon> splitXMonotone();
	bool isXMonotone();
	void buildTriangulation();
	vector<Polygon> triangulate()const;

	void setSides();


};
ostream& operator<<(ostream& o, const Polygon& a);
Pol_Edge* otherEdge(const Pol_Edge *e, const Pol_Vertex *v);

long double polygonArea(const vector<Point>& pl);
long double trArea(Point pa, Point pb, const Point& pc);
long double sliceArea(Point pa, Point pb, const Point& c, bool addPi=false);
Point circleMiddlePoint(Point, Point, const Point&);
vector<Point> circleIntersection(const Point& pa, const Point& pb, long double ra, long double rb);
#endif


