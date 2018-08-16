//PROG: eyeball
//LANG: C++
//ID: raveman.n2

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<memory.h>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>

using namespace std;

typedef pair<int,int>		pii;
typedef vector<int>		vi;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define CL(a,b)			memset(a,b,sizeof a)
#define SORT(v)			sort((v).begin(),(v).end())
#define UN(v)			SORT(v),(v).erase(unique((v).begin(),(v).end()),(v).end())
#define pb			push_back

const double pi = acos(-1.);
const double eps = 1e-6;

double dist(double x,double y,double X,double Y){return sqrt((x-X)*(x-X)+(y-Y)*(y-Y));}

struct Segment{
	double x,y,X,Y;
	Segment(){
	}
	Segment(double _x,double _y,double _X,double _Y){
		x=_x;
		X=_X;
		y=_y;
		Y=_Y;
	}
	void read(){
		scanf("%lf %lf %lf %lf",&x,&y,&X,&Y);
		if(x>X) swap(x,X);
		if(y>Y) swap(y,Y);
	}
	bool isH(){return fabs(y-Y)<eps;}
	bool isEndp(double xx,double yy){
		return dist(xx,yy,x,y)<eps || dist(xx,yy,X,Y)<eps;
	}
	bool operator<(const Segment &s)const{
		if(fabs(x-s.x)>eps) return x<s.x;
		if(fabs(X-s.X)>eps) return X<s.X;
		if(fabs(y-s.y)>eps) return y<s.y;
		if(fabs(Y-s.Y)>eps) return Y<s.Y;
		return 0;		
	}
};

vector<Segment> read(int n){
	vector<Segment> res;
	REP(i,n){
		Segment t;
		t.read();
		res.pb(t);
	}	
	return res;
}

double det(double a11,double a12,double a21,double a22){return a11*a22-a12*a21;}

typedef pair<double,double> 		pdd;

pdd inter_res;
double a[2][3];
bool intersect(Segment s, double x,double y, double angle){
	a[0][0] = cos(angle); a[0][1] = -(s.X - s.x); a[0][2] = s.x - x;
	a[1][0] = sin(angle); a[1][1] = -(s.Y - s.y); a[1][2] = s.y - y;
	
	double d = det(a[0][0],a[0][1],a[1][0],a[1][1]);
	double d1 = det(a[0][2],a[0][1],a[1][2],a[1][1]);
	double d2 = det(a[0][0],a[0][2],a[1][0],a[1][2]);
	if(fabs(d)<eps){
		if(fabs(d1)<eps && fabs(d2)<eps){
			double t1 = dist(x,y,s.x,s.y);
			double t2 = dist(x,y,s.X,s.Y);
			double xx = s.x, yy = s.y;
			if(t2<t1) xx = s.X, yy = s.Y;
			
			double aa = atan2(yy-y, xx -x);
			if(fabs(aa-angle)<eps || fabs(2*pi-fabs(aa-angle))<eps){
				inter_res=pdd(xx,yy);
				return 1;
			}
		}
		return 0;
	}else{
		double t1 = d1/d;
		double t2 = d2/d;
		if(t2>-eps && t2<1+eps && t1>0){
			inter_res = pdd(x+cos(angle)*t1,y+sin(angle)*t1);
			return 1;
		}
		return 0;
	}
}

pdd findClosest(vector<Segment> &v, double x,double y, double angle, int DONT){
	pdd res(1e100,1e100);
	REP(i,v.size()) if(i!=DONT)
		if(intersect(v[i], x,y, angle))
			if(dist(x,y,res.first,res.second)>dist(x,y,inter_res.first,inter_res.second))
				res = inter_res;
	return res;	
}

vector<Segment>  cut(vector<Segment> &big, double mx, double my, double MX, double MY){
	vector<Segment> v;
	REP(i,big.size()){
		if(big[i].isH()){
			if(big[i].y > MY + eps) continue;
			if(big[i].y < my - eps) continue;
			if(big[i].X < mx - eps) continue;
			if(big[i].x > MX + eps) continue;
			
			v.pb(Segment(max(big[i].x, mx),big[i].y,min(big[i].X, MX),big[i].y));
		}else{
			if(big[i].x > MX + eps) continue;
			if(big[i].x < mx - eps) continue;
			if(big[i].Y < my - eps) continue;
			if(big[i].y > MY + eps) continue;
			
			v.pb(Segment(big[i].x, max(big[i].y, my), big[i].x, min(big[i].Y, MY)));
		}
	}
	return v;
}

void parse(vector<Segment> &t, double x, double y, double X, double Y, double scale){
	REP(i,t.size()){
		t[i].x = X + (t[i].x - X) * scale;
		t[i].X = X + (t[i].X - X) * scale;
		t[i].y = Y + (t[i].y - Y) * scale;
		t[i].Y = Y + (t[i].Y - Y) * scale;
	}
	REP(i,t.size()){
		t[i].x += (x-X);
		t[i].X += (x-X);
		t[i].y += (y-Y);
		t[i].Y += (y-Y);
	}
}

void out(vector<Segment> v){
	puts("begin");
	REP(i,v.size())
		cout<<v[i].x<<' '<<v[i].y<<" >> "<<v[i].X<<' '<<v[i].Y<<endl;
	puts("end");
}

bool equal(vector<Segment> &v1, vector<Segment> &v2){
	//puts("EQUAL");
	//out(v1);
	SORT(v2);
	//out(v2);
	if(v1<v2 || v2<v1) return 0;
	return 1;
}



int main(){	
	freopen("eyeball.in","r",stdin);
	freopen("eyeball.out","w",stdout);
	int tc=0;
	int n,m;
	while(cin>>n>>m,n||m){
		vector<Segment> small = read(n);
		vector<Segment> big = read(m);
		SORT(small);
		//out(small);
		//out(big);
		bool good = 0;
		if(n==1){
			REP(side,2)REP(se,m)if(small[0].isH()==big[se].isH()){
				double x = (side?big[se].x:big[se].X);
				double y = (side?big[se].y:big[se].Y);

				bool works = 1;
				REP(i,m)if(i!=se) if(big[i].isEndp(x,y))works=0;
				if(works){
					good = 1;
					goto out;
				}				
			}
		}else{
			double mx=1e100,MX=-1e100,my=1e100,MY=-1e100;
			REP(fe,n){
				mx = min(mx, small[fe].x);
				my = min(my, small[fe].y);
				MX = max(MX, small[fe].X);
				MY = max(MY, small[fe].Y);
			}
			
			
			REP(fe,n)REP(side,2)REP(se,m)
//			FOR(fe,1,2)FOR(side,0,1)FOR(se,11,m)
								if(small[fe].isH()==big[se].isH()){
				double x = (side?small[fe].x:small[fe].X);
				double y = (side?small[fe].y:small[fe].Y);
				double X = (side?big[se].x:big[se].X);
				double Y = (side?big[se].y:big[se].Y);
				int another = (fe?0:1);
				
				//cout<<x<<' '<<y<<endl;
				double angle = atan2(small[another].y -y , small[another].x-x);
				
				pdd r1 = findClosest(small, x,y, angle, fe);
				pdd r2 = findClosest(big, X,Y, angle, se);
				
				//cout<<angle<<' '<<cos(angle)<<' '<<sin(angle)<<endl;
				//cout<<r1.first<<' '<<r1.second<<endl;
				//cout<<r2.first<<' '<<r2.second<<endl;
				
				double scale = dist(x,y,r1.first,r1.second)/dist(X,Y,r2.first,r2.second);
				//cout<<scale<<endl;
				double _mx = X - (x-mx)/scale;
				double _MX = X + (MX-x)/scale;
				double _my = Y - (y-my)/scale;
				double _MY = Y + (MY-y)/scale;
				//cout<<_mx<<' '<<_MX<<endl;
				//cout<<_my<<' '<<_MY<<endl;
				vector<Segment> t = cut(big, _mx, _my, _MX, _MY);
				//out(t);
				parse(t, x, y, X, Y, scale);
				
				//out(t);
				
				if(equal(small, t)){
					good = 1;
					goto out;
				}
			}
		}
	out:
	if(tc)	puts("");
		printf("Case %d: ",++tc);
		if(good) puts("valid puzzle");
		else puts("impossible");
	}
	return 0;
}
