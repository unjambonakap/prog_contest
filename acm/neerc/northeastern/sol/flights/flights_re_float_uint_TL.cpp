
#include <stdio.h>

typedef unsigned int uint;
typedef unsigned __int64 res_t;

const int MAX_N = 50000;
const res_t MULT = (res_t)10000 * 50000 * 50000;

struct Missile {
	int x0;
	res_t y;

	uint _x1;
	uint _x2;
	res_t m;

	inline res_t at(uint x) {
		return ((_x1 - x) * (x - _x2)) * m;
	}

	inline res_t calc(uint x1, uint x2) {
		if (x0 >= x1) {
			if (x0 <= x2)
				return y;
			return x2 > _x1 ? at(x2) : 0;
		} else 
			return x1 < _x2 ? at(x1) : 0;
	}
};

Missile v[MAX_N];

res_t sqr(res_t x) {
	return x * x;
}

int main(int argc, char* argv[]) {
	freopen("flights.in", "r", stdin);
	freopen("flights.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int p, x, y;
		scanf("%d %d %d", &p, &x, &y);
		
		v[i].x0 = x;
		v[i].y = y * MULT;

		v[i]._x1 = p;
		v[i]._x2 = 2 * x - p;

		res_t d = sqr(p - x);
		v[i].m = y * MULT / d;
	}

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int t1, t2, x1, x2;
		scanf("%d %d %d %d", &t1, &t2, &x1, &x2);
		res_t res = 0;
		for (int j = t1 - 1; j < t2; j++) {
			res_t h = v[j].calc(x1, x2);
			if (h > res)
				res = h;
		}
		printf("%f\n", (double)res / MULT);
	}
	return 0;
}
