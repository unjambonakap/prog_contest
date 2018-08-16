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
#define FORV(i, b, a) for(i = (b); i > (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PB push_back
#define ll long long



#define MAX_L 2000
#define MAX_S 40
#define L 'L'
#define F 'F'
#define R 'R'
#define MAX_GRID 8000
#define MID 4000
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LS 1
#define RS 2
#define US 4
#define BS 8

typedef struct Point{
	int x, y;
}Point;

int area[MAX_GRID][MAX_GRID];
int cross[MAX_GRID][MAX_GRID];
int count_cross[MAX_GRID];
int max_col[MAX_GRID];
int min_col[MAX_GRID];
int l;
int r;

char str[MAX_L][MAX_S];
int repeat[MAX_L];

int turn(int dir, char mov){
	if (mov == L)
		return (4 + dir - 1) % 4;
	return (dir + 1) % 4;
}
void move(int x, int y, int *nx, int *ny, int dir){
	*nx = x, *ny = y;
	if (dir == NORTH)
		(*ny)++;
	else if (dir == SOUTH)
		(*ny)--;
	else if (dir == WEST)
		(*nx)--;
	else 
		(*nx)++;


}

void solve(){

	int i, j, k;
	int dir;
	int x, y;
	int nx, ny;
	int minx, miny;
	int maxx, maxy;
	int px[4], py[4];

	REP(i, MAX_GRID){
		count_cross[i] = 0;
		REP(j, MAX_GRID)
			cross[i][j] = 0;
	}

	dir = NORTH;
	x = y = MID;
	maxx = minx = x, maxy = miny = y;


	py[NORTH] = -MAX_GRID, py[SOUTH] = MAX_GRID, px[WEST] = MAX_GRID, px[EAST] = -MAX_GRID;

	REP(i, l){
		REP(j, repeat[i]){
			REP(k, strlen(str[i])){
				if (F == str[i][k]){
					move(x, y, &nx, &ny, dir);
					if (nx != x)
						count_cross[MIN(x, nx)]++, cross[MIN(x, nx)][y] = 1;
					minx = MIN(x, minx), miny = MIN(y, miny);
					maxx = MAX(x, maxx), maxy = MAX(y, maxy);
					x = nx, y = ny;

				}else
					dir = turn(dir, str[i][k]);
			}
		}
	}

	r = 0;
	REP(i, MAX_GRID)
		max_col[i] = -MAX_GRID, min_col[i] = MAX_GRID;
	FOR(x, minx, maxx + 1){
		int in = 0;

		FOR(y, miny, maxy + 1){
			if (cross[x][y])
				in = !in;
			if (in){
				r++;
			   	max_col[x] = MAX(max_col[x], y), min_col[x] = MIN(min_col[x], y);
				
				if (y > py[NORTH] || (y == py[NORTH] && x > px[NORTH]))
					px[NORTH] = x, py[NORTH] = y;
				if (y < py[SOUTH] || (y == py[SOUTH] && x > px[SOUTH]))
					px[SOUTH] = x, py[SOUTH] = y;
				if (x < px[WEST] || (x == px[WEST] && y < py[WEST]))
					px[WEST] = x, py[WEST] = y;
				if (x > px[EAST] || (x == px[EAST] && y > py[EAST]))
					px[EAST] = x, py[EAST] = y;
			}

		}

	}


	int ta = 0, starty;

	FOR(i, px[WEST] + 1, px[NORTH] + 1)
		max_col[i] = MAX(max_col[i], max_col[i - 1]);
	FOR(i, px[WEST] + 1, px[SOUTH] + 1)
		min_col[i] = MIN(min_col[i], min_col[i - 1]);



	FORV(i, px[EAST] - 1, px[NORTH])
		max_col[i] = MAX(max_col[i], max_col[i + 1]);


	FORV(i, px[EAST] - 1, px[SOUTH])
		min_col[i] = MIN(min_col[i], min_col[i + 1]);

	FOR(i, px[WEST], px[EAST] + 1)
		ta += max_col[i] - min_col[i] + 1;
	
	//starty = py[WEST];
	//y = max_col[px[WEST]];
	//FOR(i, px[WEST], px[NORTH]){
	//	y = MAX(y, max_col[i]);
	//	ta += y - starty + 1;
	//}

	//y = py[NORTH];
	//FOR(i, px[NORTH], px[EAST] + 1){
	//	y = MIN(y, max_col[i]);
	//	if (y < starty)
	//		break;
	//	ta += y - starty + 1;
	//}
	//starty = py[WEST];
	//y = min_col[px[WEST]];
	//FOR(i, px[WEST], px[SOUTH]){
	//	y = MIN(y, min_col[i]);
	//	ta += starty - y;
	//}

	//y = py[SOUTH];
	//FOR(i, px[SOUTH], px[EAST] + 1){
	//	y = MAX(y, min_col[i]);
	//	if (y > starty)
	//		break;
	//	ta += starty - y;
	//}
	
	r = ta - r;


	assert(r >= 0);
}

int main(){
	int i, j, k;
	int x;

	scanf("%d", &x);

	REP(i, x){
		scanf("%d", &l);

		REP(j, l)
			scanf("%s %d", str[j], repeat + j);



		solve();
		printf("Case #%d: %d\n", i + 1, r);
	}


	return EXIT_SUCCESS;
}

