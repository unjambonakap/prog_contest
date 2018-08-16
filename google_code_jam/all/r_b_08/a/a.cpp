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

long long point[3][3];


long long solve(){
	int i, j, k;
	long long s;
	int a, b, c, d, e, f;

	s = 0;
	REP(i, 9){
		a = i % 3, b = i / 3;
		if (point[a][b] == 0)
			continue;

		s += point[a][b] * (point[a][b] - 1) * (point[a][b] - 2) / 3 / 2;

		FOR(j, i + 1, 9){
			
			c = j % 3, d = j / 3;
			if (point[c][d] == 0)
				continue;
			
			if (!(a + c + c) % 3 && !(b + d + d) % 3)
				s += point[c][d] * (point[c][d] - 1) / 2 * point[a][b];

			if (!(a + a + c) % 3 && !(b + b + d) % 3)
				s += point[a][b] * (point[a][b] - 1) / 2 * point[c][d];

			FOR(k, j + 1, 9){
				e = k % 3, f = k / 3;
				if (point[e][f] == 0)
					continue;

				if ((a + c + e) % 3 || (b + d + f) % 3)
					continue;
				s += point[a][b] * point[c][d] * point[e][f];

			}
		}

	}
	return s;





}


int main(){
	int i, j, k;
	int n_c;

	long a, b, c, d, xo, yo, m, x, y, n;

	scanf("%d", &n_c);

	REP(i, n_c){
		scanf("%ld %ld %ld %ld %ld %ld %ld %ld", &n, &a, &b, &c, &d, &xo, &yo, &m);
		x = xo, y = yo;

		REP(j, 3)
			REP(k, 3)
				point[j][k] = 0;
		

		++point[x % 3][y % 3];
		REP(j, n - 1){
			x = (a * x + b) % m, y = (c * y + d) % m;
			++point[x % 3][y % 3];
		}

		printf("Case #%d: %Ld\n", i + 1, solve());
	}


}

