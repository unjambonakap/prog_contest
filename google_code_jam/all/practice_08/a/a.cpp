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



#define MAX_N 2001
#define B 1
#define W 2
#define U 3

int b, w;
char *solve(){


	if (b % 2 == 1)
		printf("BLACK");
	else
		printf("WHITE");
	

	

}


int main(){
	int i, x, r;


	scanf("%d", &x);
	REP(i, x){
		scanf("%d %d", &w, &b);

		printf("Case #%d: ", i + 1);
		solve();
		printf("\n");
	}


	return EXIT_SUCCESS;
}

