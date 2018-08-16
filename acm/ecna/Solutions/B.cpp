#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 1000;

struct point
{
	int x, y;
} locs[MAX];
int nlocs;

int main()
{
	int x, y, icase=0;
	
	cin >> nlocs;
	while (nlocs > 0) {
		icase++;
		x = y = 0;
		for(int i=0; i<nlocs; i++) {
			cin >> locs[i].x >> locs[i].y;
			x += locs[i].x;
			y += locs[i].y;
		}
		x /= nlocs;
		y /= nlocs;
		int xopt, yopt, dxopt, dyopt;
		int r, d;
		dxopt=0;
		for(int i=0; i<nlocs; i++) {
			dxopt += abs(locs[i].x-x);
		}
		xopt = x;
		r = x;
		while(true) {
			r--;
			d = 0;
			for(int i=0; i<nlocs; i++) {
				d += abs(locs[i].x-r);
			}
			if (d > dxopt)
				break;
			dxopt = d;
			xopt = r;
		}
		r = x;
		while(true) {
			r++;
			d = 0;
			for(int i=0; i<nlocs; i++) {
				d += abs(locs[i].x-r);
			}
			if (d >= dxopt)
				break;
			dxopt = d;
			xopt = r;
		}
		dyopt=0;
		for(int i=0; i<nlocs; i++) {
			dyopt += abs(locs[i].y-y);
		}
		yopt = y;
		r = y;
		while(true) {
			r--;
			d = 0;
			for(int i=0; i<nlocs; i++) {
				d += abs(locs[i].y-r);
			}
			if (d > dyopt)
				break;
			dyopt = d;
			yopt = r;
		}
		r = y;
		while(true) {
			r++;
			d = 0;
			for(int i=0; i<nlocs; i++) {
				d += abs(locs[i].y-r);
			}
			if (d >= dyopt)
				break;
			dyopt = d;
			yopt = r;
		}

		cout << "Case " << icase << ": (" << xopt << ',' << yopt << ") " << dxopt + dyopt << endl;
				
		cin >> nlocs;
	}
}
