#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <assert.h>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PB push_back
#define EPS 10e-10
#define ll long long

#define MAX_N 10010
#define MAX_P 4*10e12
#define MAX_X 10e6
#define cmp(a, b) ((fabs(a - b) < EPS) ? 0 : (a < b) ? -1 : 1)

typedef struct Point{
	double x, y, z;
	int p;
}Point;

Point pt[MAX_N];
int l;
double r;
Point po;
double xl, xh, yl, yh, zl, zh;
double a, b, c, d, e, f, g, h;

/*

   ==============
   xi + yi + zi  - p * pi <= x + y + z <= p * pi + xi + yi + zi
1  A 						<= x + y + z <= B
   ==============
   yi + zi - xi - p * pi <= y + z - x <= p * pi + yi + zi - xi
2  C 						<= y + z - x <= D
   =============
   xi + yi - zi - p * pi <= x + y - z <= p * pi + xi + yi - zi
3  E 						<= x + y - z <= F
   =============
   xi + zi - yi - p * pi <= x + z - y <= p * pi + xi + zi - yi
4  G 						<= x + z - y <= H


1" => A - x <= y + z <= B - x
2" => C + x <= y + z <= D + x
3" => E - x <= y - z <= F - x
4" => x - H <= y - z <= x - G


1" + 4" => (A - H) / 2 <= y <= (B - G) / 2
2" - 4" => (C + G) / 2 <= z <= (D + H) / 2

=> conditions of existence of y and z

For x: 
1 - 2 => (A - D) / 2 <= x <= (B - C) / 2




   */

int intersect(Point *x, double p){
	double R = p * x->p;
	int temp;

	a = MAX(a, x->x + x->y + x->z - R), b = MIN(b, x->x + x->y + x->z + R);
	c = MAX(c, x->y + x->z - x->x - R), d = MIN(d, -x->x + x->y + x->z + R);
	e = MAX(e, x->x + x->y - x->z - R), f = MIN(f, x->x + x->y - x->z + R);
	g = MAX(g, x->x + x->z - x->y - R), h = MIN(h, x->x - x->y + x->z + R);

	xl = (a - d) / 2, xh = (b - c) / 2;
	yl = (a - h) / 2, yh = (b - g) / 2;
	zl = (c + g) / 2, zh = (d + h) / 2;

	//exit(0);
	
	if (cmp(a, b) == 1 || cmp(c, d) == 1 || cmp(e, f) == 1 || cmp(g, h) == 1)
		return 0;
	


	
	return (!(cmp(xh, xl) == -1 || cmp(yh, yl) == -1 || cmp(zh, zl) == -1));
	//temp = cmp(xh, xl);
	//if (temp == -1)
	//	return 0;
	////if (temp == 0)
	////	po.x = xl;

	//temp = cmp(yh, yl);
	//if (temp == -1)
	//	return 0;
	////if (temp == 0)
	////	po.y = yl;

	//temp = cmp(zh, zl);
	//if (temp == -1)
	//	return 0;
	////if (temp == 0)
	////	po.z = zl;

	//
	//return 1;

}

void solve(){
	int i, j;
	double ha, ta, m;
	ha = MAX_P, ta = 0;

	while(ha - ta > EPS){
		m = (ha + ta) / 2;
		a = c = e = g = -MAX_P, b = d = f = h = MAX_P;


		REP(i, l)
			if (intersect(pt + i, m) == 0)
				break;

		if (i != l)
			ta = m;
		else
			ha = m;
		
			
	}
	r = ha;



}

int main(){
	int i, j;
	int t;
	int a, b, p;

	scanf("%d", &t);

	REP(i, t){
		scanf("%d", &l);

		REP(j, l)
			scanf("%lf %lf %lf %d", &pt[j].x, &pt[j].y, &pt[j].z, &pt[j].p);

		
		solve();
		printf("Case #%d: %.7lf\n", i + 1, r);



	}



	return EXIT_SUCCESS;
}

