#include <iostream>
using namespace std;

const int MAXB = 11;

struct box
{
	int n;
	int w[3], d[3];
} boxes[MAXB];
int maxd;
int bestHeight;

void output(int i)
{
	cout << '[' << boxes[i].w[0];
	cout << ',' << boxes[i].w[1];
	cout << ',' << boxes[i].w[2] << ']';
}

void swapBox(int i, int j)
{
	box tmp = boxes[i];
	boxes[i] = boxes[j];
	boxes[j] = tmp;
}

int bestStack(int i, int n, int w, int d)
{
if (i == 12) cout << i << ',' << n << endl;
	if (i == n)
		return n;
	int ans = i;
	for(int j=0; j<boxes[i].n; j++) {
		if (boxes[i].w[j] <=w && boxes[i].d[j] <= d) {
			int tmp = bestStack(i+1, n, boxes[i].w[j], boxes[i].d[j]);
if (tmp == 12) cout << i << ',' << tmp << endl;
			if (tmp > ans)
				ans = tmp;
		}
	}
	return ans;
}
		
int permute(int i, int n)
{
//cout << i << ',' << n << endl;
	if (i == n) {
		int h = bestStack(0, n, maxd, maxd);
		if (h > bestHeight) {
			bestHeight = h;
		}
	}
	else {
		for(int j=i; j<n; j++) {
			swapBox(i,j);
			permute(i+1,n);
			swapBox(i,j);
		}
	}
}

int main()
{
	int n, i, h, w, d;
	int icase=0;
	cin >> n;
	while (n != 0) {
		icase++;
		maxd = 0;
		bestHeight = 0;
		for(i=0; i<n; i++) {
			cin >> h >> w >> d;
			if (h < w)
				swap(h, w);
			if (w < d)
				swap(w, d);
			if (h < w)
				swap(h, w);
			if (h > maxd)
				maxd = h;
			if (h == d) {
				boxes[i].n=1;
				boxes[i].w[0] = boxes[i].d[0] = h;
			}
			else if (h == w || w == d) {
				boxes[i].n = 2;
				boxes[i].w[0] = h;
				boxes[i].d[0] = w;
				boxes[i].w[1] = w;
				boxes[i].d[1] = d;
			}
			else {
				boxes[i].n = 3;
				boxes[i].w[0] = h;
				boxes[i].d[0] = w;
				boxes[i].w[1] = h;
				boxes[i].d[1] = d;
				boxes[i].w[2] = w;
				boxes[i].d[2] = d;
			}
//cout << bestHeight << endl;
		}
		permute(0, n);
		cout << "Case " << icase << ": " << bestHeight << endl;
		
		cin >> n;
	}
	return 0;
}
