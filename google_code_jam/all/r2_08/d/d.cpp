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

#define MAX_S 50001
#define MAX_T 20
#define MAX_P 1 << MAX_T

int s, t;
char str[MAX_S];

int cost[MAX_T][MAX_T][MAX_T];
int dp[MAX_P][MAX_T];
int r;
int count;

int get_shortest(int end, int set, int n){

	int temp, c, i, ns;

	if (dp[set][n] != -1)
		return dp[set][n];

	//printf("new on %d (%d\n", n, set);
	c = MAX_S;
	if (set == 1 << n)
		c = cost[end][end][n];
	//	printf("end cost: %d on %d\n", c, n);
	
	else{
		ns = set - (1 << n);
		REP(i, t){

			if (i == n || i == end || !(set & (1 << i))) continue;
	//		printf("check %d => %d (set : %d)\n", i, n, set);
			temp = get_shortest(end, ns, i) + cost[end][i][n];
			c = MIN(c, temp);
	//		printf("%d => %d: %d with cost %d\n", i, n , temp, cost[end][i][n]);
			
		}
	}


	return dp[set][n] = c;


}

void solve(){
	int i, j, k, l;
	int m;

	m = s / t;

	REP(i, t)
		REP(j, t)
			REP(k, t){
				if (j == k) continue;

				cost[i][j][k] = 0;
				if (j == i){
					REP(l, m - 1)
						if (str[l * t + j] != str[(l + 1) * t + k])
							cost[i][j][k]++;
				}else{
					REP(l, m)
						if (str[l * t + j] != str[l * t + k])
							cost[i][j][k]++;
				}
				//printf("%d %d %d => %d\n", i, j, k, cost[i][j][k]);
			}

	r = MAX_S;
		
	REP(i, t){
		REP(j, 1 << t)
			REP(k, t)
				dp[j][k] = -1;

		count = 0;
		r = MIN(r, get_shortest(i, (1 << t) - 1, i)  + 1);
	}
	if (t == 1)
		r = 1;


	

}




int main(){
	int i, x;
	scanf("%d", &x);
	REP(i, x){
		scanf("%d", &t);
		scanf("%s\n", str);
		s = strlen(str);
		solve();

		printf("Case #%d: %d\n", i + 1, r);

	}



	return EXIT_SUCCESS;
}

