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
#define MOD 1000000007



#define MAX_N 500000
#define MAX_B 20

using std::sort;
using std::lower_bound;




ll tb[MAX_N], a[MAX_N], s_tb[MAX_N];
ll data[1 <<  MAX_B];
char used[MAX_N];

ll m, n, x, y, z;
ll r;

void bit_update(int b, ll value){
	while(b < pow(2, MAX_B))
		data[b - 1] = (data[b - 1] + value) % MOD, b = b + (b & (-b));
	
}

ll bit_get(int b){
	ll ret = 0;

	while(b > 0)
		ret = (ret + data[b - 1]) % MOD, b = b - (b & (-b));
	return ret;


}

void solve(){
	int i;
	ll v;

	r = 0;
	memset(data, 0, sizeof(data));

	REP(i, n){
		v = 1 + bit_get(tb[i] - 1);
		bit_update(tb[i], v);
		r = (r + v) % MOD;
	}
	


}

int main(){
	int t;
	int i, j;


	scanf("%d", &t);
	REP(i, t){
		scanf("%Ld %Ld %Ld %Ld %Ld", &n, &m, &x, &y, &z);
		REP(j, m)
			scanf("%Ld", a + j);

		REP(j, n)
			tb[j] = a[j % m], a[j % m] = (x * a[j % m] + y * (j + 1)) % z;

		memcpy(s_tb, tb, sizeof(ll) * n);

		sort(s_tb, s_tb + n);

		memset(used, 0, sizeof(used));

		REP(j, n)
			tb[j] = lower_bound(s_tb, s_tb + n, tb[j]) - s_tb + 1, used[tb[j]] = 1;
		

		solve();
		printf("Case #%d: %Ld\n", i + 1, r);

	}


	return EXIT_SUCCESS;
}

