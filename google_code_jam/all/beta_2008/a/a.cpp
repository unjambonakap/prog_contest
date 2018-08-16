#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>

#define REP(i,n) for(i = 0; i < n; i++)
#define REPV(i, n) for (i = n - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = a; i < b; i++)
#define FORV(i, a, b) for(i = b - 1; i >= a; i--)
#define MAX(a,b) ((a < b) ? b : a)
#define MIN(a,b) ((a < b) ? a : b)


#define NOT_TR 0
#define ACUTE 1
#define OBTUSE 2
#define RIGHT 3
#define PI 2 * asin(1)
#define eps 1e-9

int dist(int x, int y){ return x * x + y * y; }



typedef struct point{
	int x, y;
}point;
point l[3];

char iso, type;


void solve(){
	int i, j;
	double xa, xb, ya, yb;
	point *a, *b, *c;
	double oa, ob, diff;

	type = NOT_TR;
	iso = 0;

	REP(i, 3){

		a = l + i, b = l + (i + 1) % 3, c = l + (i + 2) % 3;
		xa = a->x - b->x, xb = c->x - b->x;
		ya = a->y - b->y, yb = c->y - b->y;

		if (dist(xa, ya) == dist(xb, yb))
			iso = 1;
		
		if (type != NOT_TR)
			continue;

		oa = ((xa == 0) ? PI / 2 : fabs(atan(ya / xa)));
		ob = ((xb == 0) ? PI / 2 : fabs(atan(yb / xb)));
		
		if (xa < 0 && ya < 0)
			oa += PI;
		else if (xa < 0)
			oa = PI - oa;
		else if (ya < 0)
			oa = 2 * PI - oa;
				
		
		if (xb < 0 && yb < 0)
			ob += PI;
		else if (xb < 0)
			ob += PI / 2;
		else if (yb < 0)
			ob += 3 * PI / 2;

		diff = fabs(oa - ob);


		if (fabs(diff - PI) < eps)
			diff -= PI;

		if (fabs(diff) < eps)
			return;

		if (diff - PI / 2 > -eps)
			type = OBTUSE;
		if (fabs(diff - PI / 2) < eps)
			type = RIGHT;

	}
	if (type == NOT_TR)
		type = ACUTE;

}

void solve_2(){
	int d[3], i, j, max;
	point *a, *b, *c;


	type = NOT_TR;
	iso = 0;
	max = -1;
	REP(i, 3){

		a = l + i, b = l + (i + 1) % 3, c = l + (i + 2) % 3;
		d[i] = dist(a->x - b->x, a->y - b->y);
		if (max == -1 || d[i] > d[max])
			max = i;
		if ((b->x - a->x)*(b->y - c->y) - (b->y - a->y)*(b->x - c->x)  == 0)
			return;
	}

	j = 0;
	REP(i, 3)
		if (max != i){
			if (d[max] == d[i])
				iso = 1;
			j += d[i];
		}

	
	if (j == d[max])
		type = RIGHT;
	else if (j > d[max])
		type = ACUTE;
	else
		type = OBTUSE;
	if (d[(max+1)%3] == d[(max+2)%3])
		iso = 1;

	

}
int main(){
	int i, j ,x, r;
	char *s[4] = {"not a triangle", "acute", "obtuse", "right"}, *s_l[2] = {"scalene", "isosceles"};


	scanf("%d", &x);

	REP(i, x){
		REP(j, 3)
			scanf("%d %d", &l[j].x, &l[j].y);


		solve_2();

		printf("Case #%d: ", i + 1);
		if (type == NOT_TR)
			printf("%s", s[0]);
		else
			printf("%s %s triangle", s_l[iso], s[type]);
		printf("\n");



	}


}

