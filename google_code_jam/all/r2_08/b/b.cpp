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

#define MAX_B 10010




int n, m, a;
int r;

void solve(){
	int t, u, v, w, x, y;
	double temp;


	r = -1;
	if (a > m * n)
		return;

	r = 0;
	temp = a;

	t = u = 0;
	v = n;
	y = ceil(temp / n);
	x = (n - a % n) % n;
	w = 1;
	r = abs((v - t) * (y - u) - (x - t) * (w - u));
	printf("%d %d %d %d %d %d", t, u, v, w, x, y);
	
	



}



int main(){
	int i, x;
	


	scanf("%d", &x);
	REP(i, x){
		scanf("%d %d %d", &n, &m, &a);

		printf("Case #%d: ", i + 1);
		solve();
		if (r == -1)
			printf("IMPOSSIBLE");
		
		printf("\n");


	}

	return EXIT_SUCCESS;
}

