#include "cg.hpp"

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline long double sqr(long double x){return x*x;}
inline int dist(int x, int y, int a, int b){return sqr(x-a)+sqr(y-b);}
inline int dist(pii a, pii b){return sqr(a.ST-b.ST)+sqr(a.ND-b.ND);}
inline bool bit_set(int a, int b){return (a&two(b));}

const long double INF=1e20;
const long double EPS=1e-9;
const long double PI=2.*asin(1);
long double Line::x_eval;

Line Point::dual()const{ return Line(x, -y); }
Point Line::dual()const{ return Point(a, -b); }

Point Point::inv(const Point& c)const{
	Point p=*this-c;
	p/=(p.x*p.x+p.y*p.y);
	return c+p;
}

Point Point::vrotate(long double ang)const{ return Point(cos(ang)*x-sin(ang)*y, sin(ang)*x+cos(ang)*y); }
Point& Point::svrotate(long double ang){
	long double nx, ny;
	nx=cos(ang)*x-sin(ang)*y, ny=sin(ang)*x+cos(ang)*y;
	x=nx, y=ny;
	return *this;
}
Point Point::rotate(const Point& p, long double ang)const{
	Point v=*this-p;
	v.svrotate(ang);
	return p+v;
}
Point& Point::srotate(const Point& p, long double ang){
	Point v=*this-p;
	v.svrotate(ang);
	x=p.x+v.x, y=p.y+v.y;
	return *this;
}

Line Line::rotate(const Point& p, long double ang)const{ return Line::FromVect(vect().vrotate(ang), getPoint().rotate(p, ang)); }

Line& Line::srotate(const Point& p, long double ang){
	Line r=rotate(p, ang);
	a=r.a, b=r.b, vert=r.vert;
	return *this;
}

Line Line::FromVect(const Point& v, const Point& p){ return v.getLine(p); }
Point Line::getPoint()const{
	if (vert)
		return Point(a, 0);
	return Point(0, b);
}


Point Line::vect()const{ return (vert)?Point(0, 1):Point(1, a); }

Point operator*(long double s, const Point& p){return p*s;}
bool Point::operator<(const Point& p)const{
	if (inf){
		if (p.inf)
			return x<p.x;
		return x<0;
	}
	return (fabs(x-p.x)<EPS&&y<p.y)||x<p.x;

}
long double Point::angle()const{
	long double r=(fabs(x)<EPS)?PI/2:atan(fabs(y/x));
	if (x>-EPS&&y<-EPS)return 2*PI-r;
	if (y<-EPS)return r+PI;
	if (x<=-EPS)return PI-r;
	return r;
}
bool Point::cmpY(const Point& p)const{return (fabs(y-p.y)<EPS && x<p.x)||y<p.y;}
bool Point::operator==(const Point& p)const{
	if (inf || p.inf)return inf==p.inf && fabs(x-p.x)<EPS;
	return fabs(x-p.x)<EPS&&fabs(y-p.y)<EPS;
}

bool Point::on(const Line& l)const{ 
	if (l.vert){
		return fabs(x-l.a)<EPS;
	}
	return fabs(l.eval(x)-y)<EPS; 
}

Line Point::getLine(const Point& p)const{
	if (fabs(x)<EPS)return Line::Vert(p.x);
	return Line(y/x, p.y-p.x*y/x);
}

long double Line::angle()const{
	if (vert)return PI/2;
	return atan(a);
}

bool Segment::cmpY(const Segment& s)const{ return (eval(x_eval)<s.eval(x_eval)||(eval(x_eval)==s.eval(x_eval) && angle()-s.angle()<-EPS));}
ostream& operator<<(ostream& o, const Point& a){
	o<<"(";
	if (a.inf)
		cout<<((a.x<0)?"-":"+")<<"inf";
	else
		o<<a.x<<", "<<a.y;
	o<<")"; 
	return o;
}


char orient(const Point& a, const Point& b, const Point& c){
	long double d=(b-a)^(c-b);
	return char(d/fabs(d));
}

ostream& operator<<(ostream& o, const Line& a){
	o<<"Line: ";
	if (a.vert)
		o<<"x="<<a.a<<endl;
	else
		o<<"y="<<a.a<<"*x+"<<a.b<<endl;
	if (a.side!=Line::N)
		o<<"Side: "<<a.side<<endl;
	return o;
}

ostream& operator<<(ostream& o, const Segment& a){
	o<<"Segment: ";
	if (a.vert)
		o<<"x="<<a.a<<endl;
	else
		o<<"y="<<a.a<<"*x+"<<a.b<<endl;
	if (a.side!=Line::N)
		o<<"Side: "<<a.side<<endl;

	o<<"Start "<<a.sp;
	o<<"End "<<a.ep;
	return o;
}

ostream& operator<<(ostream& o, const ConvexPolygon& a){
	o<<"Polygon:"<<endl<<"Upper envelope: ";

	FE(it, a.upper)
		o<<it->sp<<" ";
	if (a.upper.size()>0)
		o<<a.upper.back().ep;
	o<<endl;
	o<<"Lower envelope: ";
	FE(it, a.lower)
		o<<it->sp<<" ";
	if (a.lower.size()>0)
		o<<a.lower.back().ep;
	o<<endl;
	return o;


}
ostream& operator<<(ostream& o, const Polygon& a){
	cout<<"Polygon:"<<endl;
	FE(it, a.v)
		cout<<(*it)->p<<endl;
	return o;
}

Point lineIntersection(Line a, Line b){
	if (a.vert && b.vert)return Point::Inf();
	if (b.vert)swap(a, b);

	if (a.vert)
		return Point(a.a, b.eval(a.a));

	if (a.a==b.a)return Point::Inf();

	Point p;
	p.x=(a.b-b.b)/(b.a-a.a);
	p.y=a.eval(p.x);
	return p;
}



Point segmentIntersection(const Segment& a, const Segment& b){
	Point p=lineIntersection(a, b);
	if (p.x>=a.sp.x && p.x>=b.sp.x && p.x<=a.ep.x && p.x<=b.ep.x)return p;
	return Point::Inf();
}


ConvexPolygon cpIntersection(const ConvexPolygon& a, const ConvexPolygon& b){


	ConvexPolygon c;

	int t;
	Event e, ne;
	if (a.empty()||b.empty())return c;


	ne.setEnvelope(0, 0, 0, 0);
	ne.type=0;
	if (a.sp().inf)ne.p=a.sp(), ne.polygon=0;
	else if (b.sp().inf)ne.p=b.sp(), ne.polygon=1;
	else ne.p=min(a.sp(), b.sp()), ne.polygon=(ne.p==b.sp());

	if (ne.polygon)ne.envelope.pa[0]=ne.envelope.pa[1]=1;
	else ne.envelope.pb[0]=ne.envelope.pb[1]=1;


	if (a.sp()==-Point::Inf() && b.sp()==-Point::Inf()){
		c.setSP(a.sp());
		//printf("<<<<<<<<<<<<<\n");
		Segment sl, su;
		if (a.lower.size()>0 && a.upper.size()>0){
			//cout<<a.upper[0].angle()<<endl;
			//cout<<b.upper[0].angle()<<endl;
			su=(b.upper.size()>0)?max(a.upper[0], b.upper[0]):a.upper[0];
			sl=(b.lower.size()>0)?min(a.lower[0], b.lower[0]):a.lower[0];


			if (su<sl){
				c.la=sl, c.lb=su;
			}

		}else if (b.lower.size()>0 && b.upper.size()>0){
			su=(a.upper.size()>0)?max(a.upper[0], b.upper[0]):b.upper[0];
			sl=(a.lower.size()>0)?min(a.lower[0], b.lower[0]):b.lower[0];
			if (su<sl){
				c.la=sl, c.lb=su;
			}
		}
	}
	int count=0;
	while(!a.done(ne.cur.pa[0], ne.cur.pa[1]) && !b.done(ne.cur.pb[0], ne.cur.pb[1])){
		//	if (++count==9)break;

		e=ne;
		if (e.p==Point::Inf())break;

		//cout<<"On<<<<<<<<<<<<<\n";
		//cout<<e.p;
		//cout<<e.polygon<<endl;
		//cout<<e.type<<endl;
		vector<Event> el;
		//cout<<endl<<endl<<endl;


		if (e.p==-Point::Inf()){
			if (e.polygon)
				e.cur.pb[0]=e.cur.pb[1]=0;
			else
				e.cur.pa[0]=e.cur.pa[1]=0;
		}else if (e.type==0){//vertex of a polygon (not an intersection point)
			if (!e.polygon){
				if (e.cur.pa[0]==-1){//start point of a
					e.cur.pa[0]=e.cur.pa[1]=0;
					if (b.in(e.p, e.cur.pb[0], e.cur.pb[1]))
						c.setSP(e.p);
				}else{
					if (e.envelope.pa[0]){
						if (b.in(e.p, e.cur.pb[0], e.cur.pb[1]))
							c.addLowP(e.p, a.lower[e.cur.pa[0]]);
						++e.cur.pa[0];
					}else{
						if (b.in(e.p, e.cur.pb[0], e.cur.pb[1]))
							c.addSupP(e.p, a.upper[e.cur.pa[1]]);
						++e.cur.pa[1];
					}

				}

			}else{
				if (e.cur.pb[0]==-1){//start point of b polygon
					e.cur.pb[0]=e.cur.pb[1]=0;
					if (a.in(e.p, e.cur.pa[0], e.cur.pa[1]))
						c.setSP(e.p);

				}else{//point on polygon b
					if (e.envelope.pb[0]){
						if (a.in(e.p, e.cur.pa[0], e.cur.pa[1])){
							c.addLowP(e.p, b.lower[e.cur.pb[0]]);
						}
						++e.cur.pb[0];
					}else{
						if (a.in(e.p, e.cur.pa[0], e.cur.pa[1]))
							c.addSupP(e.p, b.upper[e.cur.pb[1]]);
						++e.cur.pb[1];
					}
				}
			}


		}else{//intersection of two lines of the polygons
			if (e.envelope.pa[0]&&e.envelope.pb[0]){
				c.addLowP(e.p, min(a.lower[e.cur.pa[0]], b.lower[e.cur.pb[0]]));

			}else if (e.envelope.pa[0]&&e.envelope.pb[1]){
				if (c.empty())
					c.setSP(e.p);
				else{
					c.addLowP(e.p, a.lower[e.cur.pa[0]]);
					c.addSupP(e.p, a.upper[e.cur.pa[1]]);
				}

			}else if (e.envelope.pa[1]&&e.envelope.pb[0]){
				if (c.empty())
					c.setSP(e.p);
				else{
					c.addLowP(e.p, b.lower[e.cur.pb[0]]);
					c.addSupP(e.p, b.upper[e.cur.pb[1]]);
				}

			}else{
				if (a.upper[e.cur.pa[1]].angle()>b.upper[e.cur.pb[1]].angle())
					c.addSupP(e.p, a.upper[e.cur.pa[1]]);
				else
					c.addSupP(e.p, b.upper[e.cur.pb[1]]);
			}
		}

		ne=e;

		int ok[4];
		memset(ok, 0, sizeof(ok));
		ne.type=0;
		if (ne.cur.pa[0]==-1){
			ne.p=a.sp(), ne.polygon=0;
			el.pb(ne);
		}if (ne.cur.pb[0]==-1){
			ne.p=b.sp(), ne.polygon=1;
			el.pb(ne);
		}
		if (ne.cur.pa[0]>=0 && ne.cur.pa[0]<a.lower.size()){
			ok[0]=1;
			ne.p=a.lower[ne.cur.pa[0]].ep;
			ne.polygon=0, ne.setEnvelope(1, 0, 0, 0);
			el.pb(ne);
		}if (ne.cur.pa[1]>=0 && ne.cur.pa[1]<a.upper.size()){
			ok[1]=1;
			ne.p=a.upper[ne.cur.pa[1]].ep;
			ne.polygon=0, ne.setEnvelope(0, 1, 0, 0);
			el.pb(ne);
		} if (ne.cur.pb[0]>=0 && ne.cur.pb[0]<b.lower.size()){
			ok[2]=1;
			ne.p=b.lower[ne.cur.pb[0]].ep;
			ne.polygon=1, ne.setEnvelope(0, 0, 1, 0);
			el.pb(ne);
		}if (ne.cur.pb[1]>=0 && ne.cur.pb[1]<b.upper.size()){
			ok[3]=1;
			ne.p=b.upper[ne.cur.pb[1]].ep;
			ne.polygon=1, ne.setEnvelope(0, 0, 0, 1);
			el.pb(ne);
		}

		ne.type=1;
		if (ok[0]&&ok[2]){
			ne.p=segmentIntersection(a.lower[ne.cur.pa[0]], b.lower[ne.cur.pb[0]]);
			if (e.p<ne.p){
				ne.setEnvelope(1, 0, 1, 0);
				el.pb(ne);
			}
		}if (ok[0]&&ok[3]){
			ne.p=segmentIntersection(a.lower[ne.cur.pa[0]], b.upper[ne.cur.pb[1]]);
			if (e.p<ne.p){
				ne.setEnvelope(1, 0, 0, 1);
				el.pb(ne);
			}
		}if(ok[1]&&ok[2]){

			//cout<<a.upper[ne.cur.pa[1]]<<endl;
			//cout<<b.lower[ne.cur.pb[0]]<<endl;
			ne.p=segmentIntersection(a.upper[ne.cur.pa[1]], b.lower[ne.cur.pb[0]]);
			//cout<<ne.p<<endl;
			if (e.p<ne.p){
				ne.setEnvelope(0, 1, 1, 0);
				el.pb(ne);
			}
		}if(ok[1]&&ok[3]){
			ne.p=segmentIntersection(a.upper[ne.cur.pa[1]], b.upper[ne.cur.pb[1]]);
			if (e.p<ne.p){
				ne.setEnvelope(0, 1, 0, 1);
				el.pb(ne);
			}
		}

		ne=*min_element(ALL(el));

	}


	if (a.ep()==Point::Inf() && b.ep()==Point::Inf()){
		Segment sl, su;
		if (a.lower.size()>0||b.lower.size()>0){
			if (a.lower.size()>0&&b.lower.size()>0)
				sl=max(a.lower.back(), b.lower.back());
			else
				sl=(a.lower.size()>0)?a.lower.back():b.lower.back();
			if ((a.upper.size()==0||sl<a.upper.back())&&(b.upper.size()==0||sl<b.upper.back()))
				c.addLowP(a.ep(), sl);

		}
		if (a.upper.size()>0||b.upper.size()>0){
			if (a.upper.size()>0&&b.upper.size()>0)
				su=min(a.upper.back(), b.upper.back());
			else
				su=(a.upper.size()>0)?a.upper.back():b.upper.back();
			if ((a.lower.size()==0||a.lower.back()<su)&&(b.lower.size()==0||b.lower.back()<su))
				c.addSupP(a.ep(), su);
		}
	}
	return c;
}

pair<vector<Point>, vector<Point> > procHull(vector<Point> pl){
	int i, j;
	sort(ALL(pl));
	if (SZ(pl)<=2)
		return MP(pl, pl);
	
	
	vector<Point> hull;


	REP(j, SZ(pl)){
		while(SZ(hull)>=2 && orient(hull[SZ(hull)-2], hull.back(), pl[j])>=0)hull.pop_back();
		hull.pb(pl[j]);
	}
	return extractHulls(hull);
}


pair<vector<Point>, vector<Point> > extractHulls(vector<Point> h){
	vector<Point>::iterator itp=h.begin();

	FE(it, h)
		if (*itp<*it)itp=it;
	vector<Point> lh(h.begin(), itp+1), uh(itp, h.end());
	reverse(ALL(uh));
	return MP(lh, uh);



}


bool Polygon::isXMonotone(){
	cvector<Pol_Vertex*>::citerator ita(&v), itb(&v), itc(&v);
	itb=ita=v.begin();


	FE(it, v){
		if (**it<**ita)ita=it;
		if (**itb<**it)itb=it;
	}
	CLR(xh), CLR(xl);

	xh.pb((*ita)->p), xl.pb((*ita)->p);
	itc=ita;
	while(++itc!=itb)
		xh.pb((*itc)->p);
	itc=ita;
	while(--itc!=itb)
		xl.pb((*itc)->p);
	xh.pb((*itb)->p), xl.pb((*itb)->p);

	int i;
	REP(i, xh.size()-1)
		if (xh[i+1]<xh[i])return false;
	REP(i, xl.size()-1)
		if (xl[i+1]<xl[i])return false;
	return true;
}


vector<Polygon> Polygon::triangulate()const{
	vector<Polygon> res;
	int ih, il;

	il=ih=1;
	printf("\n\n\n\n\n\n");
	while(ih<xh.size()&&il<xl.size()){
		if (xh[ih]<xl[il]){
			//		cout<<xh[ih]<<xh[ih+1]<<xl[il+1]<<endl;
			res.pb(Polygon()<<xh[ih]<<xl[il]<<xl[il-1]<<xh[ih]);
			++ih;
		}else{
			//		cout<<xl[il+1]<<endl;
			res.pb(Polygon()<<xl[il]<<xh[ih]<<xh[ih-1]<<xl[il]);
			++il;
		}
	}
	res.pop_back();
	//FE(it, res) 
	//	cout<<*it<<endl;



	return res;


}
struct cmpA{bool operator()(const Pol_Vertex* a, const Pol_Vertex *b){return *a<*b;}};
struct cmpB{bool operator()(const Pol_Vertex *a, const Pol_Vertex *b){return a->cmpY(*b);}};
struct cmpC{bool operator()(const Pol_Edge *a, const Pol_Edge *b){return a->cmpY(*b);}};

void Polygon::setSides(){ }
Pol_Edge* otherEdge(const Pol_Edge *e, const Pol_Vertex *v){ return (v->src==e)?v->sink:v->src; }



vector<Polygon> Polygon::splitXMonotone(){
	vector<Polygon> res;

	vector<Pol_Vertex*> nv=v;
	map<Pol_Edge*, pair<Pol_Vertex*, Pol_Edge*> > helpers;
	map<Pol_Edge*, pair<Pol_Vertex*, Pol_Edge*> >::iterator ith;
	set<Pol_Edge*, cmpC> lineStatus;
	set<Pol_Edge*>::iterator its;
	map<Pol_Edge*, vector<Point>* > ml, mu;
	map<Pol_Edge*, vector<Point>* >::iterator itc, itcb;
	vector<Point> *vpp, *vppb;

	sort(ALL(nv), cmpA());
	//FE(it, nv)
	//	cout<<(*it)->p<<endl;


	Pol_Vertex *va, *vb, *vc, *vd;
	Pol_Edge *ea, *eb;
	bool la, lb;

	printf("===================START===========\n");
	printf("===================START===========\n");
	printf("===================START===========\n");
	printf("===================START===========\n");
	printf("===================START===========\n");
	printf("===================START===========\n");
	FE(it, nv){
		printf("\n\n\n\n\n\n");
		cout<<(*it)->p<<endl;
		va=(*it)->src->dest, vb=(*it)->sink->org;

		la=*va<**it, lb=*vb<**it;
		ea=(va->src->dest==*it)?va->src:va->sink;
		eb=(vb->src->dest==*it)?vb->src:vb->sink;
		Line::x_eval=(*it)->p.x;
		printf("%d %d\n", la, lb);

		cout<<"line status"<<endl;
		FE(itz, lineStatus)
			cout<<(*itz)->s<<endl;
		printf("\n\n===========================----------------------\n\n");

		if (la^lb){
			cout<<ea->s<<endl;
			cout<<eb->s<<endl;
			cout<<va->p<<endl;
			cout<<vb->p<<endl;
			FE(itha, helpers)
				cout<<itha->ST->s<<endl;
			if (cmpA()(vb, va))
				swap(va, vb), swap(ea, eb);
			assert(lineStatus.find(ea)!=lineStatus.end());
			lineStatus.erase(ea);
			lineStatus.insert(eb);



			ith=helpers.find(ea);
			assert(ith!=helpers.end());

			if ((itc=ml.find(ea))!=ml.end()){
				vpp=itc->ND;
				ml.erase(itc);
				ml.insert(MP(eb, vpp));
			} else{
				itc=mu.find(ea);
				assert(itc!=mu.end());


				vpp=itc->ND;
				if (ith->ND.ND!=NULL){//helper is a merge vertex
					itcb=ml.find(ith->ND.ND);
					assert(itcb!=ml.end());
					vppb=itcb->ND;

					//delete lower chain
					ml.erase(itcb);

					//here add polygon with 2 monotone strings vpp and vppb

					res.pb(Polygon());
					FE(itz, *vpp)
						res.back()<<*itz;
					res.back()<<(*it)->p;
					FEV(itz, *vppb)
						res.back()<<*itz;
					FE(itz, *vpp)
						cout<<*itz<<endl;
					printf("================}\n");
					FE(itz, *vppb)
						cout<<*itz<<endl;
					printf("================}\n");
					printf("================}\n");
					printf("================}\n");
					printf("================}\n");


					//======= now update upper chain coming from helper
					itcb=mu.find(otherEdge(ith->ND.ND, ith->ND.ST));
					assert(itcb!=mu.end());
					vppb=itcb->ND;
					mu.erase(itcb);
					vpp=vppb;
				}

				mu.erase(itc);
				mu.insert(MP(eb, vpp));
			}
			vpp->pb((*it)->p);
			cout<<"Normal point"<<endl;
			helpers.erase(ith);
			helpers.insert(MP(eb, MP(*it, (Pol_Edge*)NULL)));

		}else{
			if (la&lb){
				if (cmpC()(ea, eb))swap(va, vb), swap(ea, eb);
				//ea below eb
				cout<<eb->s<<endl;
				cout<<ea->s<<endl;
				printf("\nooooooooooooooooooooooooooooooooo\n");
				FE(itcz, mu)
					cout<<itcz->ST->s<<endl;
				printf("\nooooooooooooooooooooooooooooooooo\n");

				Line::x_eval-=EPS;
				if ((itc=mu.find(eb))!=mu.end()){//eb upper edge=>end vertex
					cout<<"End Point"<<endl;
					assert(itcb!=ml.end());
					//add polygon itc--itcb
					cout<<"line status"<<endl;
					FE(itz, lineStatus)
						cout<<(*itz)->s<<endl;

					ith=helpers.find(eb);
					res.pb(Polygon());

					if (ith->ND.ND!=NULL){//previous helper=> merge vertex => add diagonal
						itcb=ml.find(ith->ND.ND);
						FE(itz, *itc->ND)
							res.back()<<*itz;
						res.back()<<(*it)->p;
						FEV(itz, *itcb->ND)
							res.back()<<*itz;

						ml.erase(itcb), mu.erase(itc);

						res.pb(Polygon());
						itc=mu.find(otherEdge(ith->ND.ND, ith->ND.ST)), itcb=ml.find(ea);
						assert(itc!=mu.end());



					}else
						itcb=ml.find(ea);

					assert(itcb!=ml.end());

					FE(itz, *itc->ND)
						res.back()<<*itz;
					res.back()<<(*it)->p;
					FEV(itz, *itcb->ND)
						res.back()<<*itz;


					ml.erase(itcb), mu.erase(itc);

					//removing helpers
					assert(ith!=helpers.end());
					helpers.erase(ea);
					helpers.erase(ith);


				}else{//eb lower=>merge vertex
					helpers.erase(ea), helpers.erase(eb);
					cout<<"Merge Point"<<endl;

					cout<<ea->s.eval(Line::x_eval)<<endl;
					FE(itz, lineStatus)
						cout<<(*itz)->s<<"=>>>>\n"<<cmpC()(ea, *itz)<<endl;

					its=lineStatus.find(eb);
					assert(its!=lineStatus.end());
					++its;
					assert(its!=lineStatus.end());
					printf("\nUpper\n");
					cout<<(*its)->s<<endl;

					ith=helpers.find(*its);
					assert(ith!=helpers.end());
					ith->ND=MP(*it, eb);

					itc=ml.find(eb);
					assert(itc!=ml.end());
					itcb=mu.find(ea);
					assert(itcb!=mu.end());
					itc->ND->pb((*it)->p), itcb->ND->pb((*it)->p);



				}
				cout<<cmpC()(ea, eb)<<endl;
				cout<<cmpC()(eb, ea)<<endl;
				assert(lineStatus.find(ea)!=lineStatus.end());
				assert(lineStatus.find(eb)!=lineStatus.end());
				lineStatus.erase(ea), lineStatus.erase(eb);

			}else{
				if (cmpC()(eb, ea))swap(va, vb), swap(ea, eb);

				its=lineStatus.insert(ea).ST;
				++its;

				la=false;
				helpers.insert(MP(ea, MP(*it, (Pol_Edge*)NULL)));
				helpers.insert(MP(eb, MP(*it, (Pol_Edge*)NULL)));
				if (its==lineStatus.end() || ml.find(*its)!=ml.end()){//start point
					cout<<"Start point"<<endl;
					ml.insert(MP(ea, new vector<Point>(1, (*it)->p)));
					mu.insert(MP(eb, new vector<Point>(1, (*it)->p)));

				}else{//split point
					ith=helpers.find(*its);//find current helper of the immediately upper edge
					assert(ith!=helpers.end());

					if (ith->ND.ND){//current helper issued from a merge vertex (ith->ND.ST)
						//now find chains (upper and lower), so that we update them with a new diagonal going from the helper to *it
						itc=ml.find(ith->ND.ND), itcb=mu.find(otherEdge(ith->ND.ND, ith->ND.ST));

						assert(itc!=ml.end());
						assert(itcb!=mu.end());
						vpp=itc->ND, vppb=itcb->ND;
						ml.erase(itc), mu.erase(itcb);

						vpp->pb((*it)->p); vppb->pb((*it)->p);
						ml.insert(MP(eb, vpp)), mu.insert(MP(ea, vppb));

					}else{//upper case
						itc=mu.find(*its);
						assert(itc!=mu.end());
						vpp=itc->ND;
						mu.erase(itc);

						vpp->pb((*it)->p);
						mu.insert(MP(ea, vpp));

						mu.insert(MP(*its, new vector<Point>(1, ith->ND.ST->p)));
						ml.insert(MP(eb, new vector<Point>(1, ith->ND.ST->p))).ST->ND->pb((*it)->p);



					}
					cout<<"Split point"<<endl;

					ith->ND=MP(*it, (Pol_Edge*)NULL);//make *it the new helper

				}

				cout<<ea->s<<endl;
				cout<<eb->s<<endl;
				lineStatus.insert(eb);



			}

		}




	}
	printf("ret\n");

	return res;
}


long double polygonArea(const vector<Point>& pl){
	
	if (SZ(pl)==3)
		return trArea(pl[0], pl[1], pl[2]);
	long double s=0;
	int i;
	REP(i, SZ(pl)-1)
		s+=pl[i].x*pl[i+1].y-pl[i+1].x*pl[i].y;

	return fabs(s)/2;

}
long double trArea(Point pa, Point pb, const Point& pc){
	pa-=pc, pb-=pc;
	return 1/2.*fabs(pa^pb);
}

long double sliceArea(Point pa, Point pb, const Point& c, bool addPi){
	long double s=0., ang;
	//cout<<pa<<pb<<endl;
	pa-=c, pb-=c;
	//printf("%lf %lf\n", pa.angle(), pb.angle());
	ang=fabs(pa.angle()-pb.angle());
	if (ang>=2*PI)ang-=2*PI;
	if (ang>=PI)ang=2*PI-ang;

	//printf("<<<<<<<angle: %lf\n", ang);
	if (addPi)ang=2*PI-ang;
	if (ang==0)return 0.;


	//printf("<<<<<<<angle: %lf >>>>>>><< %lf\n", ang, (pa.x*pa.x+pa.y*pa.y)*ang/2.);
	return (pa.x*pa.x+pa.y*pa.y)*ang/2.;
}

Point circleMiddlePoint(Point a, Point b, const Point& c){
	long double ang, ra, rb;
	a-=c, b-=c;
	ra=a.angle(), rb=b.angle();
	
	//printf("%lf %lf =>", ra, rb);
	if (ra<0)ra+=2*PI;
	if (rb<0)rb+=2*PI;
	//printf("%lf %lf =>", ra, rb);

	if (ra<rb)swap(ra, rb);
	if (ra-rb>PI)
		rb+=2*PI, swap(ra, rb);

	//ra>rb
	ang=rb+(ra-rb)/2;
	if (ang>2*PI)ang-=2*PI;
	//cout<<ang<<endl;

	Point d=a.length()*Point(cos(ang), sin(ang))+c;
	assert(fabs(a.length()-d.dist(c))<EPS);
	return d;
}

vector<Point> circleIntersection(const Point& pa, const Point& pb, long double ra, long double rb){
	long double A, B, a, b, c, d;
	long double xa, xb, ya, yb, x, r;
	vector<Point> inter;

	xa=pa.x, ya=pa.y, xb=pb.x, yb=pb.y;
	//printf("%Lf %Lf %Lf %Lf\n", xa, ya, xb, yb);
	//printf("%Lf %Lf\n", ra, rb);

	if (ya-yb==0){
		x=(xa*xa+ya*ya-xb*xb-yb*yb-sqr(ra)+sqr(rb))/2/(xa-xb);
		d=sqr(r-ra)-sqr(x-xa);
		if (d > 0)
			inter.pb(Point(x, sqrt(d)+ya)), inter.pb(Point(x, -sqrt(d)+ya));
		else if (d == 0)
			inter.pb(Point(x, 0));
	}else{
		A=(xa*xa+ya*ya-xb*xb-yb*yb-sqr(ra)+sqr(rb))/2/(ya-yb)-ya;
		B=-(xa-xb)/(ya-yb);
		a=1+B*B, b=-2*xa+2*A*B, c=xa*xa+A*A-sqr(ra);
		d=b*b-4*a*c;
		assert(a!=0);
		//printf("===== %Lf %Lf >>>%Lf %Lf %Lf %Lf\n", A, B, a, b, c, d);
		if (d<0);
		else if (d == 0){
			x=-b/2/a;
			inter.pb(Point(x, A+B*x+ya));
		}
		else{
			x=(-b-sqrt(d))/2/a;
			inter.pb(Point(x,  A+B*x+ya));

			//cout<<inter.back()<<endl;
			x=(-b+sqrt(d))/2/a;
			inter.pb(Point(x,  A+B*x+ya));
			//cout<<inter.back()<<endl;
		}
	}
	return inter;
}



