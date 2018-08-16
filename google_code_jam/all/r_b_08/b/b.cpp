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


#define MAX_D 1000001

int previous[MAX_D];
int prime[MAX_D];

long long a, b, p;

int parent(int c){if (previous[c] == -1) return c; return previous[c] = parent(previous[c]);} 

int solve(){
	int i, j, k, o, c;
	memset(previous, -1, sizeof(previous));


	FOR(i, p, b - a + 1){

		if (!prime[i]) continue;

		j = i - (a % i);
		if (j == i)
			j = 0;
		assert((a + j) % i == 0);
		o = parent(j);

		j += i;
		while(j <= b - a){
			c = parent(j);
			if (c != o)
				previous[c] = o;
		   	j += i;
		}
	}
	o = 0;
	REP(i, b - a + 1)
		if (previous[i] == -1)
			++o;

	return o;
}


int main(){
	int i, j, k;
	int x;

	scanf("%d", &x);
	memset(prime, 0, sizeof(prime));

	k = 1;
	prime[2] = 1;

	for (i = 3; i <= MAX_D; i += 2){
		if (k * k <= i)
			++k;

		for (j = 3; j <= k; j += 2)
			if (i % j == 0) break;

		if (j > k)
			prime[i] = 1;
	}

	REP(i, x){
		scanf("%Ld %Ld %Ld", &a, &b, &p);
		printf("Case #%d: %d\n", i + 1, solve());
	}



}

