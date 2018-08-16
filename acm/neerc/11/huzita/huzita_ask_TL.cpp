#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define PROBLEM "huzita"

struct Point { double x, y; };

static Point operator+(const Point &a, const Point &b) { return {a.x + b.x, a.y + b.y}; }
static Point operator-(const Point &a, const Point &b) { return {a.x - b.x, a.y - b.y}; }
static double operator*(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
static Point operator*(const double &a, const Point &b) { return {a * b.x, a * b.y}; }
static Point operator*(const Point &a, const double &b) { return {a.x * b, a.y * b}; }
static double Norm(const Point &a) { return sqrt(a.x * a.x + a.y * a.y); }
static double DistN(const Point &a, const Point &v1, const Point &v2) {
    return fabs((v2.x - v1.x) * (v1.y - a.y) - (v1.x - a.x) * (v2.y - v1.y));
}
static Point Reflect(const Point &p, const Point &v1, const Point &v2) {
    Point n = v2 - v1;
    //n = n * (1 / Norm(n));
    return 2 * v1 + 2 * n * (p - v1) * n - p;
}

static Point l1a, l1b, p1, l2a, l2b, p2, sa, sb;
static double n1, n2;

static double d(const double &a) { return double(rand()) / RAND_MAX * a; }
static std::ostream& operator <<(std::ostream& os, const Point &p) { return os << "(" << p.x << " " << p.y << ")"; }

bool solve () {
    sa = { d(20) - 10, d(20) - 10 };
    double phi = d(7);
    const double k = 0.999;
    double v = 1e100, a = 5;

    Point na, nb;
    double nphi, nv, d1, d2;

    auto ch = [&] (int dx, int dy, int da) {
        na = { sa.x + d(dx * a), sa.y + d(dy * a) };
        nphi = phi + d(da * a / 5);
        nb = { na.x + cos(nphi), na.y + sin(nphi) };
        Point r1 = Reflect(p1, na, nb);
        Point r2 = Reflect(p2, na, nb);
        d1 = DistN(r1, l1a, l1b) * n1;
        d2 = DistN(r2, l2a, l2b) * n2;
        nv = d1 + d2;
        return nv < v;
    };

    while (a > 1e-15) {
        if (
            ch( 1, 1, 1) || ch( 1, 1, -1) || ch( 1, -1, 1) || ch( 1, -1, -1) ||
            ch(-1, 1, 1) || ch(-1, 1, -1) || ch(-1, -1, 1) || ch(-1, -1, -1)
        ) {
            v = nv;
            sa = na;
            sb = nb;
            phi = nphi;
            //Point r1 = Reflect(p1, sa, sb);
            //Point r2 = Reflect(p2, sa, sb);
            //std::cout << r1 << r2 << DistN(r1, l1a, l1b) * n1 << " " << DistN(r2, l2a, l2b) * n2 << std::endl;
            if (d1 < 1e-4 && d2 < 1e-4) return true;
        }
        //else
            a *= k;
    }
    return false;
}

bool solveN () {
    for (int i = 0; i < 10; ++i) { if (solve()) return true; }
    return false;
}

int main() {
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);

    srand(time(0));

    size_t t;
    std::cin >> t;
    std::cout.precision(10);
    while (t--) {
        std::cin >>
            l1a.x >> l1a.y >> l1b.x >> l1b.y >>
            p1.x >> p1.y >>
            l2a.x >> l2a.y >> l2b.x >> l2b.y >>
            p2.x >> p2.y;
        n1 = 1 / Norm(l1b - l1a);
        n2 = 1 / Norm(l2b - l2a);
        if (solveN())
            std::cout << sa.x << " " << sa.y << " " << sb.x << " " << sb.y << std::endl;
        else
            std::cout << "0 0 0 0" << std::endl;
    }
    return 0;
}
