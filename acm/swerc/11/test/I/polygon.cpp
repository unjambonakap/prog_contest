// Author: Adrian Kuegel
// Date: October 19th, 2011
// Algorithm: circumcircle, brute force

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <complex>
#include <algorithm>
using namespace std;

#define DET(a,b,c,d)         ((a)*(d)-(b)*(c))
#define CRAMER1(a,b,x,c,d,y) (DET(x,b,y,d)/DET(a,b,c,d))

typedef complex<double> tComp;

// intersection of lines (a,b) and (c,d)
// returns NAN when (parallel(a,b,c,d) == 1)
tComp intersection(tComp a, tComp b, tComp c, tComp d) {
  return a + CRAMER1(real(b-a), real(c-d), real(c-a),
                     imag(b-a), imag(c-d), imag(c-a)) * (b-a);
}

// circuncircle center of triangle (A, B, C)
// A, B, C pairwise different
tComp circumcircle(tComp A, tComp B, tComp C) {
  tComp d = A + (B - A) / 2.0;
  tComp e = B + (C - B) / 2.0;
  return intersection(d, d + (B - A) * tComp(0, 1),
                      e, e + (C - B) * tComp(0, 1));
}

int main()
{
	int n;
	double x, y, mPI = acos(0.0) * 2;
	char line[1000];
	tComp p[3];
	srand(time(0));
	while(gets(line) && strcmp(line, "END")) {
		sscanf(line, "%lf %lf", &x, &y);
		p[0] = tComp(x, y);
		for (int i=1; i<3; ++i) {
			gets(line);
			sscanf(line, "%lf %lf", &x, &y);
			p[i] = tComp(x, y);
		}
		for (int i=0; i<3; ++i)
			for (int j=i+1; j<3; ++j)
				assert(abs(p[i]-p[j]) >= 1);
		tComp c = circumcircle(p[0], p[1], p[2]);
		double phi[3];
		for (int i=0; i<3; ++i) {
			phi[i] = atan2(p[i].imag()-c.imag(), p[i].real()-c.real());
			if (phi[i] < 0)
				phi[i] += 2 * mPI;
		}
		sort(phi, phi+3);
		for (int i=0; i<3; ++i)
			phi[i] += 2 * mPI - phi[2];
		for (int i=0; i<3; ++i)
			phi[i] /= 2 * mPI;
		double mindiff = 1e9;
		int best;
		for (int t=3; t<=1000; ++t) {
			double maxdiff = 0;
			for (int i=0; i<2; ++i) {
				double temp = phi[i] * t;
				double rem = fmod(temp, 1);
				if (rem < 0.5)
					maxdiff = max(maxdiff, rem);
				else
					maxdiff = max(maxdiff, 1-rem);
			}
			if (maxdiff < mindiff) {
				mindiff = maxdiff;
				best = t;
				if (mindiff < 1e-7)
					break;
			}
		}
		printf("%d\n", best);
	}
    return 0;
}
