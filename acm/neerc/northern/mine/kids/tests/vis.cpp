#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int tWidth = 800;
const int tHeight = 600;

const int maxN = 5000;

double x[maxN + 1], y[maxN + 1];
double minX = 0, maxX = 0, minY = 0, maxY = 0, k;
int i1 = 0, j1 = 0, k1 = 0, i2 = 0, j2 = 0, k2 = 0;
int n;

double transX( double x ) {
  return (x - minY) * k;
}

double transY( double y ) {
  return (maxY - y) * k;
}

int main( int argc, char *argv[] ) {
  assert(argc >= 2);
  assert(freopen(argv[1], "r", stdin));
  assert(scanf("%d", &n) == 1);
  for (int i = 0; i < n; i++) {
    assert(scanf("%lf%lf", &x[i], &y[i]) == 2);
    if (i == 0 || minX > x[i]) {
      minX = x[i];
    }
    if (i == 0 || maxX < x[i]) {
      maxX = x[i];
    }
    if (i == 0 || minY > y[i]) {
      minY = y[i];
    }
    if (i == 0 || maxY < y[i]) {
      maxY = y[i];
    }
  }
  x[n] = x[0];
  y[n] = y[0];
  if (maxX > maxY) {
    maxY = maxX;
  }
  if (minX < minY) {
    minY = minX;
  }
  fclose(stdin);
  if (argc >= 3) {
    assert(freopen(argv[2], "r", stdin));
    if (scanf("%*s%d%d%d%d%d%d", &i1, &j1, &k1, &i2, &j2, &k2) == 6) {
      i1--, j1--, k1--;
      i2--, j2--, k2--;
    } else {
      i1 = j1 = k1 = i2 = j2 = k2 = -1;
    }
    fclose(stdin);
  } else {
    i1 = j1 = k1 = i2 = j2 = k2 = -1;
  }
  k = min(tWidth / (maxX - minX), tHeight / (maxY - minY));
  printf("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  printf("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  printf("<svg\n"
    "\tversion=\"1.1\"\n"
    "\tbaseProfile=\"full\"\n"
    "\txmlns=\"http://www.w3.org/2000/svg\"\n"
    "\txmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
    "\txmlns:ev=\"http://www.w3.org/2001/xml-events\"\n"
    "\twidth=\"%d\" height=\"%d\">\n", tWidth, tHeight);
  printf("\t<path fill=\"none\" stroke=\"red\" d=\"");
  for (int i = 0; i <= n; i++) {
    printf("%c %.0lf %.0lf", i ? 'L' : 'M', transX(x[i]), transY(y[i]));
    if (i < n) {
      printf(" ");
    }
  }
  printf("\" />\n");
  if (i1 != -1) {
    printf("\t<path opacity=\"0.5\" fill=\"#800080\" stroke=\"#ffff00\" d=\"M %.0lf %.0lf L %.0lf %.0lf L %.0lf %.0lf\" />\n",
      transX(x[i1]), transY(y[i1]), transX(x[j1]), transY(y[j1]), transX(x[k1]), transY(y[k1]));
    printf("\t<path opacity=\"0.5\" fill=\"#008000\" stroke=\"#ffff00\" d=\"M %.0lf %.0lf L %.0lf %.0lf L %.0lf %.0lf\" />\n",
      transX(x[i2]), transY(y[i2]), transX(x[j2]), transY(y[j2]), transX(x[k2]), transY(y[k2]));
  }
  printf("</svg>\n");
  return 0;
}
