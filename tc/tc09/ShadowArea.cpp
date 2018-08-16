// BEGIN CUT HERE

// END CUT HERE
#line 5 "ShadowArea.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline long double sqr(long double a){return a*a;}
const long double EPS=10e-9;

const long double PI=acos(-1);
long double procAng(long double x, long double y){
	long double a=(fabs(x)<=EPS)?PI/2:atan(fabs(y/x));
	if (x>=0 && y>=0)return a;
	if (x<0 && y>=0)return PI-a;
	if (x<0 && y<0)return PI+a;
	return 2*PI-a;
}


struct Point{ long double x, y, ang; 
	void procAng(); 
	long double procDist()const;
	string str()const{
		stringstream is;
		is<<"("<<x<<" "<<y<<")";
		return is.str();
	}
};
Point light;

void Point::procAng(){ ang=::procAng(x-light.x, y-light.y); }
long double Point::procDist()const{return sqr(x-light.x)+sqr(y-light.y);}

struct wall{
	Point s, e, m;
	long double md;
	int id, st;
	long double getAng()const{ return st?s.ang:e.ang; }

	bool operator<(const wall &a)const{
		long double wa, wb;
		wa=getAng(), wb=a.getAng();
		return fabs(wa-wb)>EPS?wa<wb:(fabs(md-a.md)>EPS?md<a.md:st>a.st);
	}

};

Point getIntersect(long double w, const wall &wa){
	if (fabs(w-wa.s.ang)<=EPS)return wa.s;
	if (fabs(w-wa.e.ang)<=EPS)return wa.e;
	//printf("======\n");
	//cout<<wa.s.str()<<"  "<<wa.e.str()<<endl;
	//cout<<w<<endl;
	Point a, b, da, db;
	a=light, b=wa.s;
	da.x=cos(w), da.y=sin(w);
	db.x=wa.e.x-wa.s.x, db.y=wa.e.y-wa.s.y;
	long double c, d, v;
	if (fabs(da.x)<=EPS){
		assert(db.x!=0);
		v=(a.x-b.x)/db.x;



	}else{
		c=(b.x-a.x)/da.x, d=db.x/da.x;
		assert(fabs(db.y-da.y*d)>EPS);
		v=(a.y+c*da.y-b.y)/(db.y-da.y*d);
	}
	a.x=b.x+v*db.x, a.y=b.y+v*db.y;
	return a;
	/*
	   ax+u*dax=bx+v*dbx
	   ay+u*day=by+v*dby
	   =>
	   u=(bx+v*dbx-ax)/dax=c+d*v
	   =>v(dby-day*d)=(ay+c*day-by)

	   if (vertical (da.x==0

	   ax=bx+v*dbx =< v=(ax-bx)/dbx
	   */

}

long double currAng;
struct cmpA{ bool operator()(const wall &a, const wall &b)const{ 
	if ((a.id<0) != (b.id<0))return b.id<0;
	long double da, db;
	Point pa, pb;

	pa=getIntersect(currAng, a);
	pb=getIntersect(currAng, b);
	da=pa.procDist();
	db=pb.procDist();
	return fabs(da-db)>EPS?da<db:(fabs(a.md-b.md)>EPS?a.md<b.md:a.id<b.id); } 
};
int vx[]={0, 1, 1, 0};
int vy[]={0, 0, 1, 1};

long double trArea(const Point &a, const Point &b, const Point &c){ return fabs((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))/2.; }


class ShadowArea {
	public:
	double area(vector <string> room) {
		vector<wall> pl;
		vector<pii> wl;
		int i, j, k;
		int r, c;

		r=room.size();
		c=room[0].length();
		wl.pb(MP(0, 0));
		for (i=0; i<r; ++i)
			for (j=0; j<c; ++j)
				if (room[i][j]=='*')
					light.x=j+0.5, light.y=r-i-0.5;
				else if (room[i][j]=='#')
				   	wl.pb(MP(j, r-i-1));

		//printf("LIGHT ON %lf %lf\n", light.x, light.y);
		FE(it, wl){
			int _w, _h;
			wall w;
			w.id=4*(it-wl.begin()-1);
			if (it==wl.begin())
				_w=c, _h=r;
			else
				_w=_h=1;
		//	printf("on %d %d\n", it->ST, it->ND);
			
			for (i=0; i<4; ++i){
				w.s.x=it->ST+_w*vx[i], w.s.y=it->ND+_h*vy[i];
				w.e.x=it->ST+_w*vx[(i+1)%4], w.e.y=it->ND+_h*vy[(i+1)%4];
				w.m.x=(w.s.x+w.e.x)/2., w.m.y=(w.s.y+w.e.y)/2.;
				w.md=sqr(light.x-w.m.x)+sqr(light.y-w.m.y);
				w.s.procAng(); w.e.procAng(); w.m.procAng();

				long double temp;
				temp=w.e.ang-w.s.ang;
				if (temp<-EPS)temp+=2*PI;
				if (temp>PI)
					swap(w.s, w.e);
		//		cout<<"add "<<w.s.str()<< " "<<w.e.str()<<" "<<w.md<<endl;
				w.st=1;
				pl.pb(w);
				w.st=0;
				pl.pb(w);
				++w.id;
			}
		//	printf("\n\n");
		}
		int n=pl.size();

				
		if (wl.size()==1)
			return 0.;

		//for (i=0; i<8; ++i)
		//		cout<<pl[i].s.str()<<" "<<pl[i].e.str()<<endl;
		int id=-1;
		sort(ALL(pl));
		for (i=0; i<n; ++i)
			if (pl[i].id>=0 && pl[i].st==1 && (id==-1 || pl[id].md>pl[i].md))
				id=i;

//		cout<<"choose "<<pl[id].s.str()<<" "<<pl[id].e.str()<<endl;

		set<wall, cmpA> opened;
		for (i=0; i<n; ++i){
			if (pl[i].id>=0)continue;
			long double wa, wb;
			wa=pl[i].s.ang, wb=pl[i].e.ang;
			if (wb+EPS<wa)
				if (pl[id].s.ang<=wb+EPS || pl[id].s.ang+EPS>=wa)break;
			if (pl[id].s.ang+EPS>=wa && pl[id].s.ang<=wb+EPS)break;
		}
		assert(i!=n);
		opened.insert(pl[i]);
		//printf("%Lf\n", pl[id].s.ang);
		//cout<<"wall on: "<<opened.begin()->s.str()<<" "<<opened.begin()->e.str()<<endl;
		//exit(0);
		long double s=0.;

		for (i=0; i<n; ++i){
			int p, np;
			p=(i+id)%n, np=(p+1)%n;
			long double wa, wb;
			wa=pl[p].getAng();
			wb=pl[np].getAng();
			currAng=wa;
			if (wa>wb+EPS)
				wb+=2*PI;
			//if (pl[p].s.x==7 && pl[p].s.y==0 && pl[p].e.x==7 && pl[p].e.y==3)exit(0);

		//	printf("event: %d\n", pl[p].st);
		//	cout<<pl[p].s.str()<<"      xxx    "<<pl[p].e.str()<<endl;
			if (pl[p].st==0){
				int on=opened.size();
				opened.erase(pl[p]);
//				if (fabs(pl[p].e.ang-pl[id].s.ang)>EPS && opened.size()==on){
//					printf("have: \n");
//					FE(it, opened)
//						cout<<it->s.str()<<"      xxx    "<<it->e.str()<<endl;
//					exit(0);
//
//				}
			}
			else{
				opened.insert(pl[p]).ND;
			}
			if (fabs(wa-wb)<=EPS)continue;

			assert(opened.size()>0);
			Point pa, pb;
			pa=getIntersect(wa, *opened.begin());
			pb=getIntersect(wb, *opened.begin());
		//	cout<<"on "<<opened.begin()->s.str()<<"       "<<opened.begin()->e.str()<<endl;
		//	cout<<"triangle : "<<light.str()<<"   ===                "<<pa.str()<<"      === "<<pb.str()<<"res: "<<trArea(light, pa, pb)<<endl;
		//	printf("\n\n\n");

			s+=trArea(light, pa, pb);
		}
		return r*c-s-wl.size()+1;


	}













	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { ".*#...",
		"......",
		".#...#",
		".....#",
		".....#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 13.5; verify_case(0, Arg1, area(Arg0)); }
	void test_case_1() { string Arr0[] = { "..............................",
		"..............................",
		"..........#...................",
		".........#*#..................",
		"..........#...................",
		"..............................",
		"..............................",
		"..............................",
		"..............................",
		".............................." }
		; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 295.0; verify_case(1, Arg1, area(Arg0)); }
		void test_case_2() { string Arr0[] = { ".#....*",
			"##.....",
			"#......" }
			; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.166666666666666; verify_case(2, Arg1, area(Arg0)); }
			void test_case_3() { string Arr0[] = { "..........",
				"..........",
				"..........",
				"###..#####",
				"..........",
				"*........." }
				; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 29.27777777777778; verify_case(3, Arg1, area(Arg0)); }
				void test_case_4() { string Arr0[] = { "...........",
					"...........",
					"......#....",
					"........#..",
					"..........#",
					"..........*" }
					; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 25.43333333333333; verify_case(4, Arg1, area(Arg0)); }
					void test_case_5() { string Arr0[] = { "*" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(5, Arg1, area(Arg0)); }

					// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	ShadowArea ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
