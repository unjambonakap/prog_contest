#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <assert.h>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define SWAPG(a,b,c) c = a, a = b, b = c;
#define pb push_back
#define ll long long


#define MAX_H 200
#define MAX_W  200
#define MOD 10007

int grid[MAX_W][MAX_H];
int w, h;
int ret;
class Point{
	public:

		Point(int _x, int _y){x = _x, y = _y;}
		int x, y;

};


void solve(){
	std::vector<Point*> *la, *lb, *lc;
	Point *p;
	int c, a, b, i, j;


	if (w == 1 && h == 1){ret = 1; return;}

	la = new std::vector<Point*>();
	lb = new std::vector<Point*>();

	la->pb(new Point(0, 0));
	grid[0][0] = 1;

	ret = 0;

	while(!la->empty()){
		REP(i, la->size()){
			p = (*la)[i];
			c = grid[p->x][p->y];
			grid[p->x][p->y] = 0;
			printf("on point %d %d with %d\n", p->x, p->y, c);

			a = p->x + 0, b = p->y + 3;

			REP(j, 2){
				a++, b--;
				if (a < w && b < h && grid[a][b] != -1){
					if (grid[a][b] == 0)
						lb->pb(new Point(a, b));
					grid[a][b] = (grid[a][b] + c) % MOD;

				}
			}
			delete p;
		}
		la->clear();
		SWAPG(la, lb, lc);
		if (grid[w-1][h-1] != 0){
			ret = grid[w-1][h-1];
			REP(i, la->size())
				delete (*la)[i];
			la->clear();

		}



	}
	la->clear();

	delete la;
	delete lb;



}

int main(){
	int i, j, x, r;
	int a, b;

	scanf("%d", &x);
	REP(i, x){
		scanf("%d %d %d", &h, &w, &r);

		REP(j, w)
			memset(grid[j], 0, sizeof(int) * h);
		REP(j, r){
			scanf("%d %d", &a, &b);
			grid[b-1][a-1] = -1;
		}
		solve();
		printf("Case #%d: %d\n", i + 1, ret);






	}


	return EXIT_SUCCESS;
}

