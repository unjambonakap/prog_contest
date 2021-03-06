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

#include "cg.hpp"

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline double sqr(double x){return x*x;}
inline int dist(int x, int y, int a, int b){return sqr(x-a)+sqr(y-b);}
inline int dist(pii a, pii b){return sqr(a.ST-b.ST)+sqr(a.ND-b.ND);}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;
const double EPS=1e-7;
const double PI=2.*asin(1);


int n, m; 
vector<Point> pl, ql;

double solve(int tt){
	int i, j, k, id;
	double a, area;
	Point p, np;
	Line l;
	double aint[4], cint[4], r;
	vector<Line> sl;
	vector<Point> dpl;
	Point pa, pb, pc;

	if (SZ(pl)<2)return 0.;

	printf("\n");
	cout<<ql[tt]<<endl;
//	printf("\n\n");
	aint[0]=0, aint[1]=PI, aint[2]=PI, aint[3]=2*PI;

	
	REP(id, SZ(pl)){
//		printf("\n\n");
		cout<<pl[id]<<endl;
		np=ql[tt]+2*(pl[id]-ql[tt]);
	//	cout<<np<<endl;
		np=np.inv(ql[tt]);
//		cout<<np<<endl;


		l=(np-ql[tt]).orth().getLine(np);
		cout<<l<<endl;
//		cout<<np<<endl;
		assert(np.on(l));
		sl.pb(l);
//		cout<<pl[id]<<endl;
//		cout<<np<<endl;
//		printf("=>>>\n");
//		cout<<p<<endl;
//		cout<<l<<endl;
		r=(pl[id]-ql[tt]).angle();
		if (r<0)r+=2*PI;
//		cout<<r<<endl;
		r-=PI/2;
//		cout<<r<<endl;
		if (r<0||r>=PI)
			cint[2]=r+((r<0)?2*PI:0), cint[3]=2*PI, cint[0]=0, cint[1]=(r+PI)-((r<0)?0:2*PI);
		else
			cint[0]=r, cint[1]=PI, cint[2]=PI, cint[3]=r+PI;
		//printf(">>>>>><<%lf %lf %lf %lf\n", cint[0], cint[1], cint[2], cint[3]);

		REP(j, 2)
			aint[2*j]=max(aint[2*j], cint[2*j]), aint[2*j+1]=min(aint[2*j+1], cint[2*j+1]);

	}

	if (aint[0]<aint[1]||aint[2]<aint[3]){//not a null intersection
		a=(aint[0]<aint[1])?(aint[0]+aint[1])/2:(aint[2]+aint[3])/2;//the a angle is covered by all lines => if we rotate the plane with a 'a'+PI/2 angle(clockwise) and the bucket as center, then the bucket will be beside every lines => compute lower envelope of those lines
		printf("==================%lf %lf %lf %lf\n", aint[0], aint[1], aint[2], aint[3]);

		//FE(it, pl)
			//cout<<it->rotate(ql[tt], -a-PI/2)<<endl;
		FE(it, sl){
			cout<<*it<<endl;
			cout<<it->rotate(ql[tt], -a-PI/2)<<endl;
			printf("============\n=================\n");
		  pa=it->rotate(ql[tt], -a-PI/2).dual();
			pa.data=it-sl.begin();
			dpl.pb(pa);
			cout<<pa<<endl;
		}
		//printf("use rotation %lf\n", -a-PI/2);
		vector<Point> hull=procHull(dpl).ST;
		reverse(ALL(hull));
		FE(it, hull)
			cout<<"hlul with" <<pl[it->data]<<endl;


		vector<Point> fList;
		fList.pb(ql[tt]);

		REP(i, SZ(hull)-1){
			fList.pb(lineIntersection(sl[hull[i].data], sl[hull[i+1].data]).inv(ql[tt]));
			cout<<"int with" <<pl[hull[i].data]<<pl[hull[i+1].data]<<endl;
			cout<<"Intersection: "<<lineIntersection(sl[hull[i].data], sl[hull[i+1].data])<<lineIntersection(sl[hull[i].data], sl[hull[i+1].data]).inv(ql[tt])<<endl;
			assert(fList.back().inv(ql[tt]).on(sl[hull[i].data]));
			assert(fList.back().inv(ql[tt]).on(sl[hull[i+1].data]));
		}
		//FE(it, hull)
			//cout<<it->dual()<<"<<<<<<<"<<pl[it->data]<<endl;
		printf("<<<<<<<<<<\n");
		fList.pb(ql[tt]);
		FE(it, fList)
			cout<<*it<<endl;
		area=polygonArea(fList);

		//printf("\n\n\n");
		REP(i, SZ(hull)){
			pa=fList[i], pb=fList[i+1], pc=pl[hull[i].data];
			//cout<<(pa-pc).length()<<endl;
		//	cout<<(pb-pc).length()<<endl;
		//	printf("=========Points %lf\n", -a-PI/2);
			cout<<pa<<endl;
			cout<<pb<<endl;
			cout<<pc<<endl;
		//	printf("!!!!!!!!!!!!!!!!!!!!!i\n");
			bool addPi=false;
			Point midP, ta, tb;
			midP=circleMiddlePoint(pa, pb, pc).inv(ql[tt]).rotate(ql[tt], -a-PI/2);
			cout<<circleMiddlePoint(pa, pb, pc)<<">>>>>>>"<<circleMiddlePoint(pa, pb, pc).inv(ql[tt])<<"<<<<<<<<<<<<<"<<midP<<endl;
			l=hull[i].dual();
			
			//cout<<hull[i].dual()<<endl;

			//assert(midP.on(hull[i].dual()));
			//printf("middle point\n");
		//	cout<<midP<<endl;

			if (pa!=ql[tt]){
				ta=pa.inv(ql[tt]).rotate(ql[tt], -a-PI/2);

				if (pb!=ql[tt]){
					tb=pb.inv(ql[tt]).rotate(ql[tt], -a-PI/2);
					addPi=!midP.between(ta, tb);
					printf("<<<<<<<<<<<<< %d\n", addPi);
				}else{
		//			cout<<ta<<endl;
					addPi=midP.x<ta.x;
					printf("2222222222>>>>>><< %d\n", addPi);
				}

				
			}else{

				tb=pb.inv(ql[tt]).rotate(ql[tt], -a-PI/2);
		//		cout<<tb<<endl;
				addPi=midP.x>tb.x;
				printf("11111111 =>>>>>>< %d\n", addPi);
			}
			
			if (addPi)
				cout<<"<<<<<<<"<<pc<<endl;
			//if (i==0)assert(addPi==1);
			//if (i==1)assert(addPi==0);
		//	printf("<<<<<<<<<<<<<<<<<<<<%d\n", addPi);
			area+=sliceArea(pa, pb, pc, addPi)-((addPi)?-1:1)*trArea(pa, pb, pc);
		//	printf("========%lf\n", sliceArea(pa, pb, pc, addPi)-trArea(pa, pb, pc));
		//printf("\n\n\n");


		}

		printf("==%lf\n", area);
		return area;

	}else
		return 0.;
	
}


int main(){

	int t, T;
	int i, j, k, md;
	pii a;

	//Line xa(1, 3), xb(5, 4);
	//cout<<lineIntersection(xa, xb)<<endl;
	//ConvexPolygon ca, cb;
	//ca.setSP(-Point::Inf()); cb.setSP(-Point::Inf());
	//ca.addSupP(Point::Inf(), Segment(Line(1/2., 0), -Point::Inf(), Point::Inf()));
	//cb.addSupP(Point::Inf(), Segment(Line(-1, -1), -Point::Inf(), Point::Inf()));

	//cout<<ca;
	//cout<<cb;
	//cout<<cpIntersection(ca, cb)<<endl;
//	vector<Point> pal;
//	pal.pb(Point(0, 0));
//	pal.pb(Point(0, 2));
//	pal.pb(Point(1, 2));
//	pal.pb(Point(3, 3));
//	procHull(pal);
//	return 0;
//
//	Polygon pa;
//
//	pa<<Point(0, 0)<<Point(1, 1)<<Point(0, 2)<<Point(3, 2)<<Point(2, 1)<<Point(3, 0)<<Point(0, 0);
//	pa.setSides();
//	cout<<pa<<endl;
//	cout<<pa.isXMonotone()<<endl;
//	vector<Polygon> trs=pa.triangulate();
//	vector<Polygon> res=pa.splitXMonotone();
//	cout<<res.size()<<endl;
//	FE(it, res)
//		cout<<*it<<endl;
//	return 0;

	cin>>T;
	Point p;
	REP(t, T){
		cin>>n>>m;
		pl.clear(), ql.clear();
		REP(i, n)
			cin>>p.x>>p.y, pl.pb(p);

		REP(i, m)
			cin>>p.x>>p.y, ql.pb(p);




//		lq=vector<vi>(m);
//		REP(i, n){
//			k=-1, md=INT_MAX;
//			REP(j, m)
//				if (k==-1 || md>pl[i].dist(ql[j]))
//					k=j, md=pl[i].dist(ql[j]);
//			lq[k].pb(i);
//		}
		printf("Case #%d:", t+1);

		REP(i, m){


//			if (i!=0)continue;
			printf(" %lf", solve(i));
		}
		printf("\n");
	}


	return EXIT_SUCCESS;
}


