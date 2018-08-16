#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define PI asin(1)*2.
#define EPS 10e-7
#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)
#define SQR(x) (pow((x),2))
#define DIST(x,y) (sqrt(SQR(x)+SQR(y)))
#define CMP(x,y) ((abs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long
using namespace std;
typedef pair<int,int> pii;


typedef struct Point{int x, y;}Point;
typedef struct Pointf{double x, y;}Pointf;

double scale;
Point p[3], q[3];
Point va[2], vb[2];
int perm[3], used[3];
Pointf sol;

double get_alpha(int x, int y){
	double a;
	if (x == 0)
		a=PI/2;
	else
		a=atan(fabs((double)y/(double)x));
	if (x < 0 && y < 0)
		a+=PI;
	else if (x < 0)
		a=PI-a;
	else if (y < 0)
		a=2.*PI-a;
	return a;

}

int check_it1(){
	int i, j, k;
	double nc;

	scale=-1;
	FOR(i, 1, 3){
		va[i-1].x=p[i].x-p[0].x, va[i-1].y=p[i].y-p[0].y;
		vb[i-1].x=q[perm[i]].x-q[perm[0]].x, vb[i-1].y=q[perm[i]].y-q[perm[0]].y;
		
		nc=(double)DIST(vb[i-1].x, vb[i-1].y)/(double)DIST(va[i-1].x, va[i-1].y);

		
		if (scale == -1)
			scale=nc;
		else if (CMP(scale,nc) != 0)
			return 0;
	}

	double fa, fb;

	fa=get_alpha(va[0].x, va[0].y)-get_alpha(va[1].x, va[1].y)+PI;
	fb=get_alpha(vb[0].x, vb[0].y)-get_alpha(vb[1].x, vb[1].y)+PI;
	while(fa > PI)
		fa-=PI;
	while(fb > PI)
		fb-=PI;
	if (CMP(fa,fb) != 0)
		return 0;
	
	return 1;
}


/*
   (xo,yo) + u*(a,b) + v*(c,d)=(e,f)
   (xa,ya) + u*(a',b') + v*(c',d')=(e,f)

   xo +ua+vc=xsol
   yo+ub+vd=ysol
   xa+ua'+vc'=xsol
   yx+ub'+vd'=ysol

   xo-xa +u(a-a') +v(c-c')=0
   yo-ya +u(b-b') + v(d-d')=0
   au+cv=e
   bu+dv=f


 */
int find_point(){

	double a, b, c, d, e, f;
	double u, v;
	e=-(p[0].x-q[perm[0]].x), f=-(p[0].y-q[perm[0]].y);
	a=va[0].x-vb[0].x, b=va[0].y-vb[0].y;
	c=va[1].x-vb[1].x, d=va[1].y-vb[1].y;


	if ((a==0 && c==0) || (b==0 && d==0)){
		if (e != 0 || f != 0)
			return 0;
		
		
		
		sol.x=p[0].x, sol.y=p[0].y;
		return 1;
	}

	if (a==0){
		v=e/c;
		if (b==0){
			u=0;
			assert(e/c==f/d);
		}
		else
			u=(f-d*v)/b;
	}else{
		if (d-c*b/a == 0)
			v=0;
		else
			v=(f-e*b/a)/(d-c*b/a);
		u=(e-c*v)/a;
	}

	if (u < 0 || v < 0 || u+v > 1)
		return 0;
	
	sol.x=p[0].x+u*va[0].x+v*va[1].x;
	sol.y=p[0].y+u*va[0].y+v*va[1].y;
	return 1;
}

int solve(int a){
	int i, ret;
	if (a == 3){
		if (!check_it1())
			return 0;
		return find_point();

	}else{
		REP(i, 3){
			if (used[i])continue;
			used[i]=1, perm[a]=i;

			ret=solve(a+1);
			if (ret)
				return ret;
			used[i]=0;
		}
	}
	return ret;



}

int main(){
	int i, j, T;

	scanf("%d", &T);
	REP(i, T){
		REP(j, 3)
			scanf("%d %d", &p[j].x, &p[j].y);
		REP(j, 3)
			scanf("%d %d", &q[j].x, &q[j].y);


		memset(used, 0, sizeof(used));
		printf("Case #%d: ", i+1);
		if (solve(0))
			printf("%lf %lf\n", sol.x, sol.y);
		else
			printf("No Solution\n");





	}



	return EXIT_SUCCESS;
}

