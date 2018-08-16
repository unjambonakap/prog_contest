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
#define MAX_N 200

#define MOD 210

using std::vector;


char s[MAX_N];
ll r;
ll tb[MAX_N][MOD];
char set[MAX_N];
int n;



void setPos(int a);

void solve(){

	int i, j, k;
	n = strlen(s);

	memset(set, 0, sizeof(set));
	setPos(0);
	
	r = 0;
	REP(i, MOD)
		if (i % 2 == 0 || i % 3 == 0 || i % 5  == 0|| i % 7 == 0)
			r += tb[0][i];
		


}

void setPos(int a){

	int i, j;
    ll t, b;
	if (set[a])
		return;

	setPos(a + 1);

	REP(i, MOD)
		tb[a][i] = 0;
	
	set[a] = 1;

	if (a == n - 1){
		tb[a][s[a] - '0'] = 1;
		return;
	}

	t = 0;
	//printf("set %d\n", a);
	FOR(i, a, n - 1){
		t = (t * 10 + s[i] - '0') % MOD;
		//printf("\n\nnew step %d / %d with %d\n", i, n, t);

		REP(j, MOD){


			if (tb[i + 1][j] == 0)
				continue;



			b = (t + j + MOD) % MOD;
			//printf("can have %d (from %d  + %d)\n", b, t, j);

			tb[a][b] += tb[i + 1][j];


			b = (t - j + MOD) % MOD;
			tb[a][b] += tb[i + 1][j];
		}

	}
	t = (t * 10 + s[n - 1] - '0') % MOD;
	tb[a][t]++;





}

int main(){
	int i, x;


	scanf("%d", &x);
	REP(i, x){
		scanf("%s\n", s);
		solve();
		printf("Case #%d: %Ld\n", i + 1, r);


	}


}


