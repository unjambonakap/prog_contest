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
#define MAX(a,b) ((a < b) ? b : a)
#define MIN(a,b) ((a < b) ? a : b)


#define MAX_B 32
#define MAX_D 10000

typedef long long ll;

int x;
ll r[MAX_D][MAX_B];

ll g(ll d, ll b){
	b = MIN(d, b);

	if (b >= MAX_B)
		return -1;
	else if (b == 0)
		return -2;

	if (d >= MAX_D){
		ll fa;
		if (b == 1)
			fa = d;
		else if (b == 2)
			fa = d * (d + 1) / 2;
		else
			fa = -1;
		return fa;
	}
	if (r[d][b] != -2)
		return r[d][b];

	if (g(d-1,b-1) == -1 || g(d-1, b) == -1)
		return -1;

	ll a = g(d-1, b-1) + g(d-1, b) + 1;
	if (a >= 4294967296)
		a = -1;

	return r[d][b] = a;

}



ll min_d(ll f, ll d, ll b){
	ll h, l, m;

	h = MIN(d, MAX_D), l = 0;
	while(h > l){
		m = (h + l) / 2;
		if (g(m, b) == -1 || g(m, b) >= f)
			h = m;
		else
			l = m + 1;
	}
	return h;

}

ll min_b(ll f, ll d, ll b){
	ll h, l, m;

	h = MIN(b, MAX_B), l = 0;
	while(h > l){
		m = (h + l) / 2;
		if (g(d, m) == -1 || g(d, m) >= f)
			h = m;
		else
			l = m + 1;
	}
	return h;

}


int main(){

	int i, j;
	ll f, d, b, fa;


	REP(i, MAX_D)
		REP(j, MAX_B)
		r[i][j] = -2;


	REP(i, MAX_B)
		r[0][i] = 0, r[1][i] = 1;;

	REP(i, MAX_D)
		r[i][0] = 0, r[i][1] = i;

	scanf("%d", &x);

	REP(i, x){
		scanf("%lld %lld %lld", &f, &d, &b);

		printf("Case #%d: %lld %lld %lld\n", i + 1, g(d, b), min_d(f, d, b), min_b(f, d, b));

	}

	return EXIT_SUCCESS;

}




