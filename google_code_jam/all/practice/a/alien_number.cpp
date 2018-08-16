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

#define MAX_LEN 256


int x;

int main(){
	char a[MAX_LEN], b[MAX_LEN], n[MAX_LEN], reverse_a[MAX_LEN], result[MAX_LEN];

	int i, j, na, nb, nn, r, k;


	scanf("%d", &x);
	REP(k, x){
		scanf("%s %s %s\n", n, a, b);

		na = strlen(a), nb = strlen(b), nn = strlen(n);

		REP(i, na)
			reverse_a[a[i]] = i;

		r = 0;
		REP(i, nn)
			r += pow(na, nn - i - 1) * reverse_a[n[i]];
		


		i = 0;
		while(r > 0){
			result[i++] = b[r % nb];
			r /= nb;
		}
		printf("Case #%d: ", k + 1);
		REPV(j, i)
			printf("%c", result[j]);
		printf("\n");


		


			






	}

	





}
