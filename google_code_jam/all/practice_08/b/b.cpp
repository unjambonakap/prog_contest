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
#define pb push_back
#define ll long long

#define MAX_N 15
#define MAX_COORD 64000

int n, k;
int px[MAX_N], py[MAX_N];
int f[MAX_N][1 << MAX_N];



int solve(){
	int i, j, l;
	int minx, miny, maxx, maxy;

	FOR(i, 1, 1 << n){

		maxx = maxy = -MAX_COORD;
		minx = miny = MAX_COORD;

		REP(j, n){
			if (i & 1 << j)
				maxx = MAX(maxx, px[j]), maxy = MAX(maxy, py[j]), minx = MIN(minx, px[j]), miny = MIN(miny, py[j]);
			f[0][i] = MAX(maxx - minx, maxy - miny);
		}
	}
	FOR(i, 1, k){
		FOR(j, 1, 1 << n){
			f[i][j] = MAX_COORD;
			for(l = j; l != 0; l = j & (l - 1))
				f[i][j] = MIN(MAX(f[i-1][j - l], f[0][l]), f[i][j]);

		}

	}
	return f[k - 1][(1 << n) - 1];


}

int main(){
	int i, j, T;

	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d", &n, &k);
		REP(j, n)
			scanf("%d %d", px + j, py + j);
		printf("Case #%d: %d\n", i + 1, solve());

	}


	return EXIT_SUCCESS;
}

