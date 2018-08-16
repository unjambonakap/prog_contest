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


#define MAX_C 50
long double e[MAX_C];
int n, c;
long double fact_tb[MAX_C];
long double cb_tb[MAX_C][MAX_C];

double prob(int x, int k){
	if (x < n - k)
		return 0;
	return cb_tb[c - k][x] * cb_tb[k][n - x] / cb_tb[c][n];

}

double get_e(int k){
	int i, m;
	double t;

	if (e[k] != -1)
		return e[k];
	if (k == c)
		return e[k] = 0;
	m = MIN(n, c - k);


	t = 0;
	FOR(i, 1, m + 1)
		t += prob(i, k) * get_e(k + i);

	
	
	//t += (m + 1 - n) * prob(m, k) * get_e(k + m);
	//FOR(i, m, 

	++t;
	t /=  (1 - prob(0, k));

	e[k] = t;
	return e[k];

}

void solve(){
	int i;
	REP(i, MAX_C)
		e[i] = -1;

	
	get_e(0);

}


int main(){
	int i, j, x;


	scanf("%d", &x);

	fact_tb[0] = 1;
	FOR(i, 1, MAX_C)
		fact_tb[i] = fact_tb[i - 1] * i;

	REP(i, MAX_C)
		REP(j, i + 1)
			cb_tb[i][j] = ceil(fact_tb[i] / (fact_tb[j] * fact_tb[i - j]));
		
		


	
	REP(i, x){
		scanf("%d %d", &c, &n);
		solve();
		printf("Case #%d: %.9Lf\n", i + 1, e[0]);



	}


}

