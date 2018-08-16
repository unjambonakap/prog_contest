
#include <stdio.h>

const int MAX_N = 50000;

typedef unsigned int uint;

struct Missile {
	int x0;
	float y;

	uint _x1;
	uint _x2;
	float m;

	inline float at(uint x) {
		return ((_x1 - x) * (x - _x2)) * m;
	}

	inline float calc(uint x1, uint x2) {
		if (x0 >= x1) {
			if (x0 <= x2)
				return y;
			return x2 > _x1 ? at(x2) : 0;
		} else 
			return x1 < _x2 ? at(x1) : 0;
	}
};

Missile v[MAX_N];

float sqr(float x) {
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
		v[i].y = y;

		v[i]._x1 = p;
		v[i]._x2 = 2 * x - p;

		float d = sqr(p - x);
		v[i].m = y / d;
	}

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int t1, t2, x1, x2;
		scanf("%d %d %d %d", &t1, &t2, &x1, &x2);
		float res = 0;
		for (int j = t1 - 1; j < t2; j++) {
			float h = v[j].calc(x1, x2);
			if (h > res)
				res = h;
		}
		printf("%f\n", res);
	}
	return 0;
}
