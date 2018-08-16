#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

const double PI = 4*atan(1.0);

double xa, ya, xb, yb, xc, yc, xd, yd;	// global variables -horrible, I know
										//   but hopefully I'll fix it later
double degree(double r)
{
	return r*(180.0/PI);
}

void swap(double &a, double &b)
{
	double tmp = a;
	a = b;
	b = tmp;
}

void swap(double &a, double &b, double &c, double &d)
{
	swap(a, c);
	swap(b, d);
}

double dist(double x1, double y1, double x2, double y2)
{
	double dx = x1-x2;
	double dy = y1-y2;
	return sqrt(dx*dx+dy*dy);
}

void intersect(double a, double b, double c, double d, double e, double f,
			   double &x, double &y)
{
	double den = a*e-b*d;
	x = (c*e-b*f)/den;
	y = (a*f-c*d)/den;
}

double ratio(double alpha, double x1, double y1, double x2, double y2, double x3, double y3, double &len)
{
	double s1 = sin(alpha), c1 = cos(alpha);
	intersect(s1, -c1, 0, c1, s1, x1*c1+y1*s1, xa, ya);
	intersect(s1, -c1, 0, c1, s1, x3*c1+y3*s1, xd, yd);
	intersect(s1, -c1, s1*x2-c1*y2, c1, s1, x1*c1+y1*s1, xb, yb);
	intersect(s1, -c1, s1*x2-c1*y2, c1, s1, x3*c1+y3*s1, xc, yc);
	len =  dist(xa, ya, xb, yb);
	return len/dist(xb, yb, xc, yc) - 1;
}

double iterate(double a1, double a3, double x1, double y1, double x2, double y2, double x3, double y3)
{
	double length;
	double r1 = ratio(a1, x1, y1, x2, y2, x3, y3, length);
	double r3 = ratio(a3, x1, y1, x2, y2, x3, y3, length);
	while (abs(a1-a3) > 0.000000001) {
		double a = (a1+a3)/2.0;
		double r = ratio(a, x1, y1, x2, y2, x3, y3, length);
		if (r*r1 > 0) {
			a1 = a;
			r1 = r;
		}
		else {
			a3 = a;
			r3 = r;
		}
	}
	return length;
}

bool between(double a, double b, double c)
{
	if (abs(a-c) <= 0.0001 || abs(b-c) <= 0.0001)
		return true;
	if (abs(a-c) <= 0.0002 || abs(b-c) <= 0.0002)
		cout << "BOUNDARY PROB: between: abs(a-c) = " << abs(a-c) << ", abs(b-c) = " << abs(b-c) << endl;
	if (a < c && c < b)
		return true;
	return (b < c && c < a);
}

bool onSegment(double x0, double y0, double x1, double y1, double x, double y)
{
	if (abs((x1-x0)*y - (y1-y0)*x - x1*y0 + x0*y1) > 0.0001)
		return 0;								// not ont line
	if (abs((x1-x0)*y - (y1-y0)*x - x1*y0 + x0*y1) > 0.00009)
		cout << "BOUNDARY PROB: onSegment check = " << abs((x1-x0)*y - (y1-y0)*x - x1*y0 + x0*y1) << endl;
	if (between(x0, x1, x) && between(y0, y1, y))
		return 1;
	else
		return 0;								// not ont segment
}
	
bool ok(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3) {
									// check for one point on each segment
	int count, count0, count1, count2, count3, val;
	val = onSegment(xa, ya, xb, yb, x0, y0);
	count = val;
	count0 = val;
	val = onSegment(xa, ya, xb, yb, x1, y1);
	count += val;
	count1 = val;
	val = onSegment(xa, ya, xb, yb, x2, y2);
	count += val;
	count2 = val;
	val = onSegment(xa, ya, xb, yb, x3, y3);
	count += val;
	count3 = val;
	if (count != 1)
		return false;
	val = onSegment(xb, yb, xc, yc, x0, y0);
	count = val;
	count0 += val;
	val = onSegment(xb, yb, xc, yc, x1, y1);
	count += val;
	count1 += val;
	val = onSegment(xb, yb, xc, yc, x2, y2);
	count += val;
	count2 += val;
	val = onSegment(xb, yb, xc, yc, x3, y3);
	count += val;
	count3 += val;
	if (count != 1)
		return false;
	val = onSegment(xc, yc, xd, yd, x0, y0);
	count = val;
	count0 += val;
	val = onSegment(xc, yc, xd, yd, x1, y1);
	count += val;
	count1 += val;
	val = onSegment(xc, yc, xd, yd, x2, y2);
	count += val;
	count2 += val;
	val = onSegment(xc, yc, xd, yd, x3, y3);
	count += val;
	count3 += val;
	if (count != 1)
		return false;
	count = 0;
	count += onSegment(xd, yd, xa, ya, x0, y0);
	count += onSegment(xd, yd, xa, ya, x1, y1);
	count += onSegment(xd, yd, xa, ya, x2, y2);
	count += onSegment(xd, yd, xa, ya, x3, y3);
	val = onSegment(xd, yd, xa, ya, x0, y0);
	count = val;
	count0 += val;
	val = onSegment(xd, yd, xa, ya, x1, y1);
	count += val;
	count1 += val;
	val = onSegment(xd, yd, xa, ya, x2, y2);
	count += val;
	count2 += val;
	val = onSegment(xd, yd, xa, ya, x3, y3);
	count += val;
	count3 += val;
	if (count != 1)
		return false;
									// check one segment for each point
	return (count0==1) && (count1==1) && (count2==1) && (count3==1);
}

int main()
{
	double x0, y0, x1, y1, x2, y2, x3, y3, r;
	int ncases;

	cin >> ncases;
	for(int icase=1; icase<=ncases; icase++) {
		cout << "Case " << icase << ": ";
		cin >> x0 >> y0;
		cin >> x1 >> y1;
		cin >> x2 >> y2;
		cin >> x3 >> y3;
							// set x0, y0 to lowest y0, then others in
							// clockwise order
		if (y1<y0 || (y1==y0 && x1<x0))
			swap(x0, y0, x1, y1);
		if (y2<y0 || (y2==y0 && x2<x0))
			swap(x0, y0, x2, y2);
		if (y3<y0 || (y3==y0 && x3<x0))
			swap(x0, y0, x3, y3);
		x1 -= x0;
		x2 -= x0;
		x3 -= x0;
		x0 = 0;
		y1 -= y0;
		y2 -= y0;
		y3 -= y0;
		y0 = 0;
		double a1 = atan2(y1, x1);
		double a2 = atan2(y2, x2);
		double a3 = atan2(y3, x3);
		if (a1 < a2) {
			swap(x1, y1, x2, y2);
			swap(a1, a2);
		}
		if (a2 < a3) {
			swap(x2, y2, x3, y3);
			swap(a2, a3);
		}
		if (a1 < a2) {
			swap(x1, y1, x2, y2);
			swap(a1, a2);
		}
									// check for impossible cases
									// 1) three points colinear
		if (x1*y2 == x2*y1 || x3*y2 == x2*y3) {
			cout << "no solution" << endl;
			continue;
		}
		if ((x2-x1)*(y3-y2) == (x3-x2)*(y2-y1)) {
			cout << "no solution" << endl;
			continue;
		}
									// 2) one point inside others
		double a = (y3-y1), b = (x3-x1), c = x1*y3-y1*x3;
		if (c*(c-x2*a+y2*b) > 0) {
			cout << "no solution" << endl;
			continue;
		}
									// check for multiple solutions, when
									//   diagonals are perpendicular and have
									//   same length
		if ((x2-x0)*(x3-x1) == -(y2-y0)*(y3-y1) &&
			abs(dist(x0, y0, x2, y2)-dist(x1, y1, x3, y3)) <= 0.0001) {
//			cout << dist(x0, y0, x2, y2)+10 << endl;
			printf("%.2f\n", dist(x0, y0, x2, y2)+10);
			continue;
		}
		if ((x2-x0)*(x3-x1) == -(y2-y0)*(y3-y1) &&
			abs(dist(x0, y0, x2, y2)-dist(x1, y1, x3, y3)) <= 0.0002) {
			cout << "BOUNDARY PROB: mult sol check value = " << abs(dist(x0, y0, x2, y2)-dist(x1, y1, x3, y3)) << endl;
		}

		double length, maxlength = 0;
		double prevr = ratio(0.0, x1, y1, x2, y2, x3, y3, length);
		for(int angle = 1; angle <= 180; angle += 1) {
			r = ratio(angle*PI/180.0, x1, y1, x2, y2, x3, y3, length);
			if (r*prevr <= 0) {
				length = iterate((angle-1)*PI/180.0, angle*PI/180.0, x1, y1, x2, y2, x3, y3);
				if (ok(0, 0, x1, y1, x2, y2, x3, y3) && length > maxlength) {
					maxlength = length;
				}
			}
			prevr = r;
		}

		if (maxlength == 0) {
			cout << "no solution" << endl;
		}
		else
//			cout << maxlength+10 << endl;
			printf("%.2f\n", maxlength+10);
	}
}

