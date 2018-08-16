#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i=0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;


#define MAX_W 5
int w, h;
int map[MAX_W][MAX_W];
int remap[MAX_W][MAX_W];

int nm[MAX_W][MAX_W];

int vx[]={-1, -1, -1, 0, 1, 1, 1, 0, 0};
int vy[]={-1, 0, 1, 1, 1, 0, -1, -1, 0};

int inside(int x, int y){return (x>=0 && y>=0 && x<w && y<h);}
int checkit(int x, int y, int ask, int m[][MAX_W]){
	int l, c;

	c=0;
	REP(l, 9)
		if (inside(x+vx[l], y+vy[l]) && m[x+vx[l]][y+vy[l]])
			c++;
	return (c == ask);
}


int checkit2(int y, int m[][MAX_W], int bm[][MAX_W]){
	int i;
	REP(i, w)
		if (!checkit(i, y, m[i][y], bm))
			return false;
	return true;

				

}

bool find(int y, int v, int m[][MAX_W], int bm[][MAX_W]){
	int i, j;

	if (y < 0 || y >= h)
		return checkit2(y-v, m, bm);

	REP(i, two(w)){
		REP(j, w)
			bm[j][y]=i&two(j);

		if (!checkit2(y-v, m, bm))
			continue;
		if (find(y+v, v, m, bm))
			return true;
	}
	return false;



}


int solve(){

	int i, j, k, l, u, v;
	int nx, ny;
	int c, m, mid;
	bool f;
	
	mid=(h-1)/2;

	m=-1;
	REP(i, two(w)){
		c=0;

		memset(nm, 0, sizeof(nm));
		REP(j, w)
			if (i&two(j))
				c++, nm[j][mid]=1;


		if (c <= m)continue;

		if (h == 1){
			f=true;
			REPC(j, w, f){
				c=0;
				FOR(l, -1, 1)
					if (inside(j+l, 0) && nm[j+l][0])
						c++;
				if (c != map[j][0])
					f=false;
			}
			if (f)
				m=MAX(m, c);
		}else{

			
			bool ok=false;
			REPC(j, two(w), !ok){
				REPC(k, two(w), !ok){
					REP(l, w)
						nm[l][mid+1]=j&two(l), nm[l][mid-1]=k&two(l);

					//printf("tryy %d %d\n", j, k);
					if (!checkit2(mid, map, nm))
						continue;
					

					//REP(u, h){
					//	REP(v, w)
					//		printf("%d ", map[v][u]);
					//	printf("\n");
					//}
					//	printf("\n");
					//	printf("\n");
					//REP(u, h){
					//	REP(v, w)
					//		printf("%d ", nm[v][u]);
					//	printf("\n");
					//}
					//printf("\n");

					if (find(mid-1, -1, map, nm) && find(mid+1, 1, map, nm))
						ok=true;


				}

			}
			if (ok == true)
				m=MAX(m, c);
		
		}

	}
	return m;

}

int main(){
	int i, j, k, T;
	scanf("%d", &T);

	REP(i, T){
		scanf("%d %d", &h, &w);
		REP(j, h)
			REP(k, w)
			scanf("%d", &map[k][j]);

		printf("Case #%d: %d\n", i+1, solve());






	}


	return EXIT_SUCCESS;
}

