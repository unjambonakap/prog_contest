#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>

#define REP(i,n) for(i = 0; i < n; i++)
#define REPV(i, n) for (i = n - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = a; i < b; i++)
#define FORV(i, a, b) for(i = b - 1; i >= a; i--)
#define MAX(a,b) ((a < b)? b : a)
#define MIN(a,b) ((a < b)? a : b)

#define MAX_LEN 10000
#define EAST 8
#define WEST 4
#define SOUTH 2
#define NORTH 1
#define WALK 'W'
#define LEFT 'L'
#define RIGHT 'R'

void update(int *d, int *x, int *y, char c){

	if (c == WALK){
		if (*d == NORTH)
			(*y)--;
		else if (*d == SOUTH)
			(*y)++;
		else if (*d == EAST)
			(*x)++;
		else
			(*x)--;

	}else if (c == LEFT){
		if (*d == EAST)
			*d = NORTH;
		else if (*d == WEST)
			*d = SOUTH;
		else if (*d == NORTH)
			*d = WEST;
		else if (*d == SOUTH)
			*d = EAST;
	}else if (c == RIGHT){
		if (*d == EAST)
			*d = SOUTH;
		else if (*d == WEST)
			*d = NORTH;
		else if (*d == NORTH)
			*d = EAST;
		else if (*d == SOUTH)
			*d = WEST;
	}
	

}	

int opposite_dir(int d){

	if (d == EAST)
		return WEST;
	if (d == WEST)
		return EAST;
	if (d == NORTH)
		return SOUTH;
	return NORTH;
}


int cases[2 * MAX_LEN][MAX_LEN];

void resolve(char *a, char *b){


	int i, j, minX, minY, maxX, maxY;
	int x, y, d, out_x, out_y, out_d, previous_x, previous_y;


	REP(i, 2 * MAX_LEN)
		memset(cases[i], 0,MAX_LEN * sizeof(char));

	x = MAX_LEN, y = -1, d = SOUTH;
	previous_x = MAX_LEN, previous_y = -1;

	minX = x, minY = 0, maxX = x, maxY = 0;


	REP(i, strlen(a)){
		update(&d, &x, &y, a[i]);

		if (a[i] == WALK){

			if (previous_x >= 0 && previous_y >= 0 && previous_x < 2 * MAX_LEN && previous_y < MAX_LEN)
				cases[previous_x][previous_y] |= d;

			if (x >= 0 && y >= 0 && x < 2 * MAX_LEN && y < MAX_LEN)
				cases[x][y] |= opposite_dir(d);
			
			

			if (i != strlen(a) - 1){
				maxX = MAX(x, maxX);
				maxY = MAX(y, maxY);
				minX = MIN(x, minX);
				minY = MIN(y, minY);
			}
		}

	
		previous_x = x, previous_y = y;
	}

	out_x = previous_x, out_y = previous_y;
	previous_x = x, previous_y = y;
	x = out_x, y = out_y;

	d = opposite_dir(d);


	REP(i, strlen(b)){
		update(&d, &x, &y, b[i]);

		if (b[i] == WALK){
			if (previous_x >= 0 && previous_y >= 0 && previous_x < 2 * MAX_LEN && previous_y < MAX_LEN)
				cases[previous_x][previous_y] |= d;

			if (x >= 0 && y >= 0 && x < 2 * MAX_LEN && y < MAX_LEN)
				cases[x][y] |= opposite_dir(d);

			if (i != strlen(b) - 1){
				maxX = MAX(x, maxX);
				maxY = MAX(y, maxY);
				minX = MIN(x, minX);
				minY = MIN(y, minY);
			}
		}
		previous_x = x, previous_y = y;
	}

	FOR(i, minY, maxY + 1){
		FOR(j, minX, maxX + 1)
			printf("%x", cases[j][i]);
		printf("\n");


	}



}

int main(){
	int x, i;
	char a[MAX_LEN], b[MAX_LEN];



	scanf("%d", &x);
	REP(i, x){
		scanf("%s %s\n", a, b);
		printf("Case #%d:\n", i + 1);
		resolve(a, b);
	}


}




