#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <assert.h>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ll long long

#define MAX_N 13
#define USED 'x'
#define FREE '.'

class Point{
	public:
		Point(int _x, int _y){x = _x, y = _y;}
		int x, y;
};

int n, m;
char str[MAX_N][MAX_N];
int dp[MAX_N+1][MAX_N][1 << MAX_N][2];
int max[MAX_N][MAX_N];
int r;

void solve(){
	int i, j, k, l;
	int ni, nj, nk, nl;
	int cur;


	memset(dp, -1, sizeof(dp));
	memset(max, -1, sizeof(max));

	dp[0][0][0][0] = 0;
	max[0][0] = 0;

	REP(i, m)
		REP(j, n)
			REP(k, max[i][j] + 1)
				REP(l, 2){
					cur = dp[i][j][k][l];
					if (cur == -1)
						continue;

					if (j == n - 1)
						ni = i + 1, nj = 0, nl = 0;
					else
						ni = i, nj = j + 1, nl = (k >> j) & 1;
					//printf("try %d %d with mask = %d %d (max %d)\n", i, j, k, l, max[i][j]);
					
					nk = k | 1 << j;
					if (str[i][j] == FREE && l == 0 && (j == n - 1 || (k & 1 << (j + 1)) == 0) && (j == 0 || (k & 1 << (j - 1)) == 0)){
					//	printf("can sit\n");

						dp[ni][nj][nk][nl] = cur + 1;
						max[ni][nj] = MAX(nk, max[ni][nj]);
					}
					nk = nk - (1 << j);

					//printf("do not sit => %d %d %d %d = %d\n", ni, nj, nk, nl, cur);
					dp[ni][nj][nk][nl] = MAX(cur, dp[ni][nj][nk][nl]);
					max[ni][nj] = MAX(nk, max[ni][nj]);
					//printf("max => %d \n", max[ni][nj]);
				}


	r = 0;
	REP(k, max[m][0] + 1)
		r = MAX(r, dp[m][0][k][0]);

			

		

	


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

