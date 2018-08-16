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
#define SWAP(a,b,c) (c=a, a=b, b=c)
#define SZ(a) (a).size()
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int, int> pii;


#define MAX_K 17
#define MAX_N 305
#define MOD 9901

int n, m;
int fact[MAX_N];

vector<pii> fb, cons;
vector<int> edge[MAX_N];
int seen[MAX_N];


int dfs(int id, int depth, int prev){
	if (seen[id] == 1)
		return depth;
	

	seen[id] = 1;

	int ret, i;
	REP(i, SZ(edge[id])){
		if (edge[id][i] == prev)
			continue;
		return dfs(edge[id][i], depth + 1, id);
	}
	return -1;

}

int getp(){
	int i, j, k, spec, spec_id;

	spec = 0;

	REP(i, n)
		edge[i].clear();

	REP(i, SZ(cons)){
		edge[cons[i].first].pb(cons[i].second), edge[cons[i].second].pb(cons[i].first);
		if (SZ(edge[cons[i].first]) > 2 || SZ(edge[cons[i].second]) > 2)
			return 0;
	}
	
		
	int count = SZ(cons);
	REP(i, n){

		if (SZ(edge[i]) == 1){
			continue;
		}else if (SZ(edge[i]) == 0)
			continue;
		
		if (SZ(edge[i]) > 2)
			return 0;
		count--;
		

		int depth, ok, id;

		memset(seen, 0, sizeof(seen));

		depth = dfs(i, 0, -1);
		if (depth == n)
			return 2;
		else if (depth != -1)
			return 0;
		
	}

	return (fact[n - SZ(cons) - 1] * (1 << count)) % MOD;


	


	


}

int solve(){
	int i, j, k;
	int sgn, ret;

	ret = 0;

	REP(i, 1 << m){
		sgn = 1;
		cons.clear();
		REP(j, m)
			if (i & 1 << j){
				sgn *= -1;
				cons.pb(fb[j]);
			}
		ret = (MOD + ret + sgn * getp()) % MOD;
		

	}
	return ((ret + MOD) * 4951) % MOD;

}



int main(){
	int i, j, x;
	int a, b;

	fact[0] = 1;
	FOR(i, 1, MAX_N)
		fact[i] = (fact[i-1]*i)%MOD;

	scanf("%d", &x);
	
	REP(i, x){
		scanf("%d %d", &n, &m);
		fb.clear();

		REP(j, m){
			scanf("%d %d", &a, &b);
			fb.pb(pii(a-1, b-1));
		}
	
		printf("Case #%d: %d\n", i + 1, solve());

	}


	return EXIT_SUCCESS;
}

