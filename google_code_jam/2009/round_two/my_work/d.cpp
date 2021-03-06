#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>

#include <cmath>

using namespace std;
#define MAX_S 50

#define REP(i,n) for(i=0;i<n;i++)
typedef struct Point{
	double x, y;
}Point;
typedef struct Circle{
	Point p;
	double r;
}Circle;

Circle pl[MAX_S];

Point applicants[MAX_S * MAX_S];

int n, s, n_app;
double eps = 1e-8;
double radius;

char compare(double a, double b){ return (fabs(a - b) < eps) ? 0 : (a < b) ? -1 : 1; }
double sqr(double x){ return x*x; }
double dist(Point *p, Point *q){ return sqrt(sqr(p->x - q->x) + sqr(p->y - q->y)); }

void disp_c(Circle *u){ printf("Circle (%lf %lf) r = %lf\n", u->p.x, u->p.y, u->r); }
void disp_p(Point *p){ printf("Point (%lf %lf)\n", p->x, p->y); }

int getIntersect(Circle *u, Circle *v, Point *p, Point *q){
	char cmp;
	double e, f, g, delta, a, b, c;

	if (compare(dist(&u->p, &v->p), u->r + v->r) == 1 )
		return 0;


	if (compare(v->p.x, u->p.x) == 0){

		//x1 == X2 (we assume that y1 != y2)

		p->y = q->y = (sqr(u->r) - sqr(v->r) + sqr(v->p.y) - sqr(u->p.y)) / (2. * (v->p.y - u->p.y));
		//(x - xA)^2 = R1^2 -(y - yA)^2 = e^2
		e  = sqrt(sqr(u->r) - sqr(p->y - u->p.y));
		p->x = u->p.x - e;
		q->x = u->p.x + e;

		return 2;
	}

	//(x - xA)^2 + (y - yA)^2 = R1^2
	//(x - xB)^2 + (y - yB)^2 = R2^2
	//x = e + xA - f * y

	//e^2 - 2*e*f*y + f^2*y^2 + y^2 - y * yA * 2 + yA^2 = R1^2)            => dvpt from first equation
	//y^2 * (1 + f^2) - 2 * y (e*f + yA) + (e^2 + yA^2 - r1^2)
	



	e = (sqr(u->r) - sqr(v->r) + sqr(v->p.x) + sqr(v->p.y) - sqr(u->p.x) - sqr(u->p.y)) / (2. * (v->p.x - u->p.x)) - u->p.x;
	f = (v->p.y - u->p.y) / (v->p.x - u->p.x);
	
	a = 1 + sqr(f);
	b = - 2. * (e * f + u->p.y);
	c = sqr(e) + sqr(u->p.y) - sqr(u->r);
	delta = sqr(b) - 4. * a * c;

	cmp = compare(delta, 0);
	
	if (cmp == -1)
		return 0;
	else if (cmp == 0)
		delta = 0;
	p->y = (-b - sqrt(delta)) / (2 * a);
	q->y = (-b + sqrt(delta)) / (2 * a);
	p->x = e + u->p.x - f * p->y;
	q->x = e + u->p.x - f * q->y;

	return 2;


}

bool check(Point *p, Point *q, double radius){

	for (int i = 0; i < s; i++){
		if (compare(dist(p, &pl[i].p) + pl[i].r, radius) == 1 && compare(dist(q, &pl[i].p) + pl[i].r, radius) == 1){
		//	printf("%lf %lf %lf %lf\n", dist(p, &pl[i].p) + pl[i].r, radius, dist(q, &pl[i].p) + pl[i].r, radius);
			return false;
		}
	}
	return true;

}

double solve_binary_search(){
	int i, j, c, temp, k;
	double low_b, up_b;
	Circle a, b;

	low_b = 0;
	up_b = 5000;
	if (s == 1)
		return pl[0].r;

	while(fabs(up_b - low_b) > 1e-7){
		radius = (up_b + low_b) / 2.;

		n_app = 0;

		for (i = 0; i < s; i++){
			memcpy(applicants + (n_app++), &pl[i].p, sizeof(Point));
			memcpy(&a, pl + i, sizeof(Circle));
			a.r = radius - pl[i].r;
			for (j = i + 1; j < s; j++){
				memcpy(&b, pl + j, sizeof(Circle));
				b.r = radius - pl[j].r;

				n_app += getIntersect(&a, &b, applicants + n_app, applicants + n_app + 1);
			}
		}

		bool found = false;


		for (i = 0; !found && i < n_app; i++){
			for (j = i + 1; !found && j < n_app; j++){
				if (check(applicants + i, applicants + j, radius) == true){
					found = true;
					break;
				}
			}
		}
			

		
		if (found)//radius too big
			up_b = radius;

		else//radius too small
			low_b = radius;
	}

	return radius;


}

int main(){
	int i, j;
	double ret;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &s);
		REP(j,s)
			scanf("%lf %lf %lf", &pl[j].p.x, &pl[j].p.y, &pl[j].r);

		ret = solve_binary_search();
		printf("Case #%d: %.6lf\n", i + 1, ret);

	}

}
