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

#define PI asin(1)*2.
#define EPS 10e-8


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



struct Point{
	double x, y;
	Point(){}
	Point(double x, double y):x(x), y(y){}
	bool operator<(const Point &a)const{return x<a.x || (x==a.x && y<a.y);}
	bool operator==(const Point &a)const{return x==a.x && y==a.y;}
};

struct Rect{
	Rect(){}
	Point a, b;
	int id;
};

struct Line{
	Line(){}
	Line(Point a, int id, int event):a(a), id(id), event(event){}
	bool operator<(const Line &l)const{return a<l.a || (a==l.a && id<l.id);}

	int event;
	Point a;
	int id;

};

bool cmpH(const Line &u, const Line &v){ return u.a<v.a || (u.a==v.a && u.id<v.id); }
bool eqH(const Line &u, const Line &v){return u.a.x==v.a.x;}


vector<bool> open;
vector<Line> vl, hl, nhl;
vector<Rect> rl;
int n, no;


struct Node{
	double s, e;
	Node *p, *r, *l;
	double m;
	set<int> sl;
};

Node *createN(int s, int e, Node *p){
	Node *n=new Node;
	int mid=(s+e)/2;
	n->p=p;

	
	n->s=nhl[s].a.x, n->e=nhl[e].a.x;
	n->m=0;

	if (s == e)
		n->r=n->l=NULL;
	else if (s+1 == e){
		n->l=createN(s, s, n);
		n->r=createN(e, e, n);

	}else{
		n->l=createN(s, mid, n);
		n->r=createN(mid, e, n);
	}
	return n;

}


void delN(Node *r){

	if (r == NULL)return;
	delN(r->r), delN(r->l);
	delete r;
}

void updateMeasure(Node *r){
	if (r == NULL)return;

	if (SZ(r->sl) == 0)
		r->m=r->r->m+r->l->m, updateMeasure(r->p);
}

void addInt(Node *r, double s, double e, int rid){

	//printf("add %lf %lf to %lf %lf => %d %d\n", s, e, r->s, r->e, r->r==NULL, r->l==NULL);
	if (s <= r->s && e >= r->e){
		r->sl.insert(rid);
		r->m=r->e-r->s;
	}else{
		if (e >= r->l->s && r->l->e >= s)
			addInt(r->l, max(r->l->s, s), min(r->l->e, e), rid);
		if (e > r->r->s && r->r->e >= s)
			addInt(r->r, max(r->r->s, s), min(r->r->e, e), rid);
		if (SZ(r->sl) == 0)r->m=r->l->m+r->r->m;
	}
}

void delInt(Node *r, double s, double e, int rid){

	if (s <= r->s && e >= r->e){
		r->sl.erase(rid);
		if (SZ(r->sl) == 0)r->m=r->l->m+r->r->m;
	}else{
		if (e >= r->l->s && r->l->e >= s)
			delInt(r->l, max(r->l->s, s), min(r->l->e, e), rid);
		if (e > r->r->s && r->r->e >= s)
			delInt(r->r, max(r->r->s, s), min(r->r->e, e), rid);
		if (SZ(r->sl) == 0)r->m=r->l->m+r->r->m;

	}
}

double solve(){

	nhl=hl;
	vector<Line>::iterator it=unique(ALL(nhl), eqH);
	nhl.resize(it-nhl.begin());

	Node *r=createN(0, SZ(nhl)-1, NULL);

	addInt(r, rl[1].a.x, rl[1].b.x, 1);
	printf("%lf\n", r->m);
	addInt(r, rl[0].a.x, rl[0].b.x, 0);
	printf("%lf\n", r->m);


	delInt(r, rl[0].a.x, rl[0].b.x, 0);
	printf("%lf\n", r->m);
	exit(0);
	delN(r);
	return r->m;
}

int main(){
	int i, j, k;
	Rect r;

	scanf("%d", &n);
	REP(i, n){
		scanf("%lf %lf %lf %lf", &r.a.x, &r.a.y, &r.b.x, &r.b.y);
		assert(r.a.x <= r.b.x && r.a.y <= r.b.y);
		open.pb(false);

		r.id=i;
		rl.pb(r);
		vl.pb(Line(r.a, i, 0));
		vl.pb(Line(r.b, i, 1));
		hl.pb(Line(r.a, i, 0));
		hl.pb(Line(r.b, i, 1));

	}

	sort(ALL(vl));
	sort(ALL(hl), cmpH);
	printf("%lf\n", solve());


	return EXIT_SUCCESS;
}

