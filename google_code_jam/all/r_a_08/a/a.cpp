#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>

#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PB push_back


#define MAX_N 1000
long long tb[2][MAX_N];
int n;
long long r;

int main(){
	int i, j, x;


	scanf("%d", &x);
	REP(i, x){
		scanf("%d", &n);

		REP(j, n)
			scanf("%Ld", tb[0] + j);
		REP(j, n)
			scanf("%Ld", tb[1] + j);

		std::sort(tb[0], tb[0] + n);
		std::sort(tb[1], tb[1] + n);

		r = 0;

		REP(j, n)
			r += tb[0][j] * tb[1][n - j - 1];
		
		printf("Case #%d: %Ld\n", i + 1, r);
		



	}


	return EXIT_SUCCESS;

}

