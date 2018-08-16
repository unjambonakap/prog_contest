
#include <stdio.h>

const int MAX_N = 50000;

typedef __int64 i64;

const int MULT = 10000;

struct Missile {
	int x0;
	i64 y;

	i64 a;
	i64 b;
	i64 c;
	i64 d;

	inline i64 at(int x) {
		return ((a * x + b) * x + c) / d;
	}

	inline i64 calc(int x1, int x2) {
		if (x0 >= x1) {
			if (x0 <= x2)
				return y;
			return at(x2);
		} else 
			return at(x1);
	}
};

Missile v[MAX_N];

i64 sqr(i64 x) {
	return x * x;
}

void main(i64 argc, char* argv[]) {
	freopen("flights.in", "r", stdin);
	freopen("flights.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int p, x, y;
		scanf("%d %d %d", &p, &x, &y);
		
		v[i].x0 = x;
		v[i].y = y * MULT;

		v[i].a = -y * MULT;
		v[i].b = 2 * y * x * MULT;
		v[i].c = (y * sqr(p - x) - y * sqr(x)) * MULT;
		v[i].d = sqr(p - x);

	}

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int t1, t2, x1, x2;
		scanf("%d %d %d %d", &t1, &t2, &x1, &x2);
		i64 res = 0;
		for (int j = t1 - 1; j < t2; j++) {
			i64 h = v[j].calc(x1, x2);
			if (h > res)
				res = h;
		}
		printf("%f\n", res / (double)MULT);
	}
}
