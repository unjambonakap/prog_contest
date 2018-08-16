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

#define MAX_N 100
#define USED 'x'
#define FREE '.'

int n, m;
char str[MAX_N][MAX_N];
int used[MAX_N][MAX_N];
int associate[MAX_N][MAX_N];
int r;
int c;


int dfs(int a, int b){
	int i, j;
	
	if (used[a][b] == c)
		return 0;

	used[a][b] = c;

	FOR(i, a - 1, a + 2){
		for(j = b - 1; j <= b + 1; j += 2){
			if (str[i][j] == USED || j < 0 || j >= n || i < 0 || i >= m)
				continue;

			if (associate[i][j] == -1 || dfs(associate[i][j] / MAX_N, associate[i][j] % MAX_N)){
				associate[a][b] = i * MAX_N + j, associate[i][j] = a * MAX_N + b;
				return 1;

			}





		}
	}
	return 0;



}

void solve(){
	int i, j;
	int max;

	REP(i, m){
		REP(j, n)
			associate[i][j] = -1, used[i][j] = -1;
	}

	r = 0, c = 0;

	REP(i, m){
		REP(j, n){
			if (str[i][j] == USED)
				continue;
//			printf("can go on %d %d\n", i, j);
			r++;

			if (j % 2){
				if (dfs(i, j))
					r--;
				
				c++;

			}


		}
	}
	

	


}



int main(){
	int i, j;
	int x;

	scanf("%d", &x);
	REP(i, x){
		scanf("%d %d", &m, &n);
		REP(j, m)
			scanf("%s\n", str[j]);

		solve();
		printf("Case #%d: %d\n", i + 1, r);

	}




	return EXIT_SUCCESS;
}

