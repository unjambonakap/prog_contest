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
#define SQR(a) (pow((a), 2))
#define PB push_back


#define MAX_LEN 256
#define PI acos(0) * 2

double f, R, t, r, g;

double arc_area(double x, double y, double a, double b){
	double alpha, area;

	//2 points are on the circle of radius R - t
	alpha = atan(y / x) - atan(b / a);

	area = alpha * SQR(R - t) / 2;

	area -= (x * (y - b) + b * (a - x)) / 2;
	assert(a - x > 0);
	assert(y - b > 0);

	//printf("area (%lf), %lf %lf %lf %lf: %lf\n", alpha, x, y, a, b, area);
	return area;


}

double solve(){

	double p, x, y, s_y, m_x, m_y, e_x;
	double a_t, a_i;

	a_t = PI / 4. * SQR(R), a_i = 0;

	if (g <= 0)
		return 1;
	//printf("g => %lf / %lf\n", g, a_t);
	
	y = r;
	while(y < R - t){

		x = r;
		while (SQR(x) + SQR(y) < SQR(R - t)){


			s_y = y + g;
			e_x = x + g;

			if (SQR(x) + SQR(s_y) < SQR(R - t) && SQR(e_x) + SQR(y) < SQR(R - t) || 1){
				
				if (SQR(e_x) + SQR(s_y) < SQR(R - t)){
					a_i += g * g;
				}
				
				else{
					e_x = MIN(x + g, sqrt(SQR(R - t) - SQR(y)));
					s_y = MIN(y + g, sqrt(SQR(R - t) - SQR(x)));
					m_x = MIN(sqrt(SQR(R - t) - SQR(s_y)), e_x), m_y = MIN(sqrt(SQR(R - t) - SQR(e_x)), s_y);
				   	a_i += g * (m_x - x) + arc_area(m_x, s_y, e_x, m_y) + (e_x - m_x) * (m_y - y);
//					printf(">>>>>>>>>%lf %lf %lf %lf\n", s_y, m_y, e_x, m_x);
				}

			}
			//}else{
			//	if (SQR(x) + SQR(s_y) < SQR(R - t)){
			//		a_i += arc_area(sqrt(SQR(R - t) - SQR(s_y)), s_y, sqrt(SQR(R - t) - SQR(y)), y) + g * (sqrt(SQR(R - t) - SQR(s_y)) - x);
			//		printf("laa\n");
			//	}
			//	else if (SQR(e_x) + SQR(y) < SQR(R - t)){
			//		a_i += arc_area(x, sqrt(SQR(R - t) - SQR(x)), e_x, y) + g * (sqrt(SQR(R - t) - SQR(e_x)) - y);
			//		printf("ici\n");
			//	}
			//	else{
			//		a_i += arc_area(x, sqrt(SQR(R - t) - SQR(x)), sqrt(SQR(R - t) - SQR(y)), y);
			//		printf("there\n");
			//	}
			//}

			//printf("ai: %lf // %lf\n", a_i, a_t);
			assert(a_i == a_i);

			x += g + 2 * r;
		}
		y += g + 2 * r;
	}
	
	return 1 - a_i / a_t;
}

int main(){
	int i, x;
	

	scanf("%d", &x);
	REP(i, x){
		scanf("%lf %lf %lf %lf %lf", &f, &R, &t, &r, &g);
		t += f, r += f, g -= 2 * f;
		printf("Case #%d: %lf\n", i + 1, solve());


	}
	return EXIT_SUCCESS;



}


