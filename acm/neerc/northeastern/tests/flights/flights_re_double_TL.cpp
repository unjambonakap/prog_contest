
#include <stdio.h>

const int MAX_N = 50000;

struct Missile {
	int x0;
	double y;

	double a;
	double b;
	double c;

	inline double at(int x) {
		return (a * x + b) * x + c;
	}

	inline double calc(int x1, int x2) {
		if (x0 >= x1) {
			if (x0 <= x2)
				return y;
			return at(x2);
		} else 
			return at(x1);
	}
};

Missile v[MAX_N];

double sqr(double x) {
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

		double d = sqr(p - x);

		v[i].a = -y / d;
		v[i].b = 2 * y * x / d;
		v[i].c = (y * sqr(p - x) - y * sqr(x)) / d;
	}

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int t1, t2, x1, x2;
		scanf("%d %d %d %d", &t1, &t2, &x1, &x2);
		double res = 0;
		for (int j = t1 - 1; j < t2; j++) {
			double h = v[j].calc(x1, x2);
			if (h > res)
				res = h;
		}
		printf("%f\n", res);
	}
	return 0;
}