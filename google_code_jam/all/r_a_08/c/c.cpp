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

int store[1000];



int main(){

	int i, j, x, r;
	double s;
	unsigned long n;

	scanf("%d", &x);
	store[0] = 2, store[1] = 6;

	FOR(i, 2, 1000){
		store[i] = (6 * store[i - 1] - 4 * store[i - 2]) % 1000;
		if (store[i] < 0)
			store[i] += 1000;
		if (store[i] < 0)
			return 0;
	}
		
	
	
	REP(i, x){


		scanf("%ld", &n);
		if (n >= 104)
			n = (n - 4) % 100 + 4;
		r = 1000 + store[n] - 1;
		r %= 1000;
		printf("Case #%d: ", i + 1);
		if (r < 10)
			printf("00");
		else if (r < 100)
			printf("0");
		printf("%d\n", r);




	}


}

