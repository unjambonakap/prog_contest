#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <string.h>

#define ABS(x) ((x)<0?-(x):(x))
#define SQR(x) ((x)*(x))
#define PB push_back
#define MP make_pair
#define SS stringstream
#define LL long long
#define LD long double
#define SZ(x) int(x.size())
#define ALL(x) x.begin(),x.end()
#define FOR(a,b) for(int a=0;a<b;a++)
#define DFOR(a,b) for(int a=b-1;a>=0;a--)
#define CLR(a,b) memset(a,b,sizeof(a))

using namespace std;

int n, m;
char a[88][88];
int dp[11][10][1<<10][2];

void solvecase() {
	scanf("%d%d\n", &n, &m);
	FOR(i, n) scanf("%s\n", a[i]);
	CLR(dp, -1);
	dp[0][0][0][0] = 0;
	int M = 1<<m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int mask = 0; mask < M; mask++)
				for (int f = 0; f < 2; f++) if (dp[i][j][mask][f] != -1) {
					int cur = dp[i][j][mask][f];
					int nj, ni, nf, nmask;
					if (j == m-1) {
						nj = 0;
						ni = i+1;
						nf = 0;
					} else {
						nj = j + 1;
						ni = i;
						nf = (mask >> j) & 1;
					}
					// sit here
					if (a[i][j] != 'x' && f == 0 && (mask & (1<<(j+1))) == 0 && (j==0 || (mask & (1<<(j-1))) == 0)) {
						printf("can sit %d %d with mask %x (%d)\n", i, j, mask, f);
						nmask = mask | (1<<j);
						dp[ni][nj][nmask][nf] = max(dp[ni][nj][nmask][nf], cur+1);
						printf("%d %d %d %d => %d\n", ni, nj, nmask, nf, dp[ni][nj][nmask][nf]);
					}
					// don't sit
					nmask = mask - (mask & (1<<j));
					dp[ni][nj][nmask][nf] = max(dp[ni][nj][nmask][nf], cur);
				}
	int res = 0;
	FOR(i, M) res = max(res, dp[n][0][i][0]);
	printf("%d", res);
}

void solve() {
	int n;
	scanf("%d\n", &n);
	FOR(i, n) {
		printf("Case #%d: ", i+1);
		solvecase();
		printf("\n");
		return;

	}
}

int main() {
	//freopen("input.txt", "rt", stdin);
	solve();
	return 0;
}
