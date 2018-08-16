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
#define PB push_back
#define ll long long



#define MAX_L 2000
#define MAX_S 40
#define L 'L'
#define F 'F'
#define R 'R'
#define MAX_GRID 10000
#define MID 5000
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

char str[MAX_L][MAX_S];
int repeat[MAX_L];
int dir_tb[4];
int count_tb[4];
int l, r;
int xl[MAX_GRID], xh[MAX_GRID], yl[MAX_GRID], yh[MAX_GRID];
int count;
int minx, miny;

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

void set_grid(){
	int i, j, k;
	int x, y, nx, ny, ax, ay;
	int dir, in_dir;


	REP(i, MAX_GRID){
		memset(area[i], 0, sizeof(int) * MAX_GRID);
		xl[i] = yl[i] = MAX_GRID;
		xh[i] = yh[i] = 0;
	}

	minx = MAX_GRID;
	miny = MAX_GRID;



	x = y = MID;
	dir = NORTH;
	if (count > 0)
		in_dir = WEST;
	else
		in_dir = EAST;

	REP(i, l){
		REP(j, repeat[i]){
			REP(k, strlen(str[i])){
				if (str[i][k] == F){
					move(x, y, &nx, &ny, dir);

					ax = MIN(x, nx), ay = MIN(y, ny);
					if (in_dir == WEST)
						ax--;
					else if (in_dir == SOUTH)
						ay--;
					xl[ay] = MIN(xl[ay], ax);
					xh[ay] = MAX(xh[ay], ax);
					yl[ax] = MIN(yl[ax], ay);
					yh[ax] = MAX(yh[ax], ay);
					//printf("%d %d => (%d %d) %d =============== coloring %d %d with in dir: %d\n", x, y, nx, ny, dir, ax, ay, in_dir);

					if (in_dir == WEST)
						area[ax][ay] |= RS;
					else if (in_dir == EAST)
						area[ax][ay] |= LS;
					else if (in_dir == NORTH)
						area[ax][ay] |= BS;
					else
						area[ax][ay] |= US;

					minx = MIN(minx, ax);
					miny = MIN(miny, ay);

					x = nx, y = ny;

				}else{
					dir = turn(dir, str[i][k]), in_dir = turn(in_dir, str[i][k]);
					//printf("turn %c\n", str[i][k]);
				}
				
			}
		}
	}

}

void get_area(){
	int i, j;
	int in;
	r = 0;


	i = miny;
	while(xl[i] <= xh[i]){
		in = 0;
		FOR(j, xl[i], xh[i]){
			//printf("%d %d=> %d ( %d), in = %d\n", j, i, area[j][i], area[j][i] | LS, in);
			if (area[j][i] > 0){
				if (area[j][i] & LS)
					in = 1;
				if (area[j][i] & RS)
					in = 0;
			}
			else if (in == 0)
				area[j][i] = -1, r++;
			
		}
		i++;
	}

	i = minx;
	while(yl[i] <= yh[i]){
		in = 0;
		FOR(j, yl[i], yh[i]){
			if (area[i][j] > 0){
				if (area[i][j] & BS)
					in = 1;
				if (area[i][j] & US)
					in = 0;
			}
			else if (in == 0 && area[i][j] == 0)
				area[i][j] = -1, r++;
			
		}
		i++;
	}

}

void solve(){

	set_grid();
	get_area();

}

int main(){
	int i, j, k;
	int x;
	int temp;

	scanf("%d", &x);

	REP(i, x){
		scanf("%d", &l);

		count = 0;
		REP(j, l){
			scanf("%s %d", str[j], repeat + j);
			temp = 0;

			REP(k, strlen(str[j])){
				if (str[j][k] == L)
					temp++;
				else if (str[j][k] == R)
					temp--;
			}

			count += temp * repeat[j];
		}
		assert(count != 0);

		solve();
		printf("Case #%d: %d\n", i + 1, r);
	}


	return EXIT_SUCCESS;
}

