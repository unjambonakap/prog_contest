#include <algorithm>
#include <iostream>
using namespace std;

int gx, gy;
char g[15][15];

char memo[15][15][1<<16];
char doit(int x, int y, int b) {
	if (x == gx) {
		x = 0;
		if (++y == gy) return 0;
	}
	char& ret = memo[x][y][b];
	if (ret != -1) return ret;
	int b2 = (b<<1) & ((1<<(gx+1))-1);
	if (g[y][x] != '.') {
		ret = doit(x+1, y, b2);
	} else {
		ret = doit(x+1, y, b2+1);
		if (x && (b&1)) ret >?= 1 + doit(x+1, y, b2-2);
		if (x && (b&(1<<gx)))
			ret >?= 1 + doit(x+1, y, b2);
		if (b&(1<<(gx-1)))
			ret >?= 1 + doit(x+1, y, b2-(1<<gx));
		if (x < gx-1 && (b&(1<<(gx-2))))
			ret >?= 1 + doit(x+1, y, b2-(1<<(gx-1)));
	}
	return ret;
}

main() {
	int N, prob=1;
	for (cin >> N; N--;) {
		cin >> gy >> gx;
		int kx, ky;
		for (int y = 0; y < gy; y++)
			for (int x = 0; x < gx; x++) {
				cin >> g[y][x];
				if (g[y][x] == 'K') {kx = x; ky = y;}
			}
		memset(memo, -1, sizeof(memo));
		int m1 = doit(0, 0, 0);
		g[ky][kx] = '.';
		memset(memo, -1, sizeof(memo));
		int m2 = doit(0, 0, 0);
		cout << "Case #" << prob++
			<< ": " << ((m2 > m1) ? 'A' : 'B')
			<< endl;
	}
}
