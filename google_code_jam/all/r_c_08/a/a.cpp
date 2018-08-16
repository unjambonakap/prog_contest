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

#define MAX_L 2000

using std::sort;

long long r;
int p, k, l;


int store[MAX_L];

void solve(){
	int i, ip, ik;

	r = 0;

	sort(store, store + l);

	ip = 1, ik = 1;
	REPV(i, l){
		if (ik > k)
			ik = 1, ++ip;
		r += store[i] * ip;

		++ik;
	}

}

int main(){
	int i, j, x;

	scanf("%d", &x);


	REP(i, x){


		scanf("%d %d %d", &p, &k, &l);
		REP(j, l)
			scanf("%d", store + j);

		

		solve();
		printf("Case #%d: %Ld\n", i + 1, r);
	}

	return 0;


}

