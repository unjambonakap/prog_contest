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


#define MAX_M 10010

int m, v;
int g[MAX_M], c[MAX_M], iv[MAX_M];
int ret;
int ask[2][MAX_M];

int lc(int a){return 2 * (a + 1) - 1;}
int rc(int a){return 2 * (a + 1);}
int leaf(int a){return (a >= (m - 1) / 2);}

int compute(int a){

	if (iv[a] != -1)
		return iv[a];
	return iv[a] = ((g[a]) ? compute(lc(a)) & compute(rc(a)) : compute(lc(a)) | compute(rc(a)));

}

int ask_compute(int a, int v){
	int t, u, w;



	if (ask[v][a] != -2){
		assert(ask[v][a] >= -1);
		return ask[v][a]; 
	}

	if (iv[a] == v)
		return 0;
	if (leaf(a))
		return -1;

	w = -1;
	if (v == 1){
		
		

		if (c[a] || !g[a]){
			t = ask_compute(lc(a), 1);
			u = ask_compute(rc(a), 1);
			if (t == -1 && u == -1)
				t = -1;
			else if (t == -1 || u == -1)
				t = MAX(t, u);
			else
				t = MIN(t, u);

			if (g[a] && t != -1)
				t++;

			w = t;
		}
		if (g[a]){
			t = ask_compute(lc(a), 1);
			u = ask_compute(rc(a), 1);

			if (t == -1 || u == -1)
				t = -1;
			else
				t += u;
			if (w == -1 || t == -1)
				w = MAX(t, w);
			else
				w = MIN(t, w);
		}

	}else{

		if (g[a] || c[a]){
			t = ask_compute(lc(a), 0);
			u = ask_compute(rc(a), 0);
			if (t == -1 && u == -1)
				t = -1;
			else if (t == -1 || u == -1)
				t = MAX(t, u);
			else
				t = MIN(t, u);

			if (!g[a] && t != -1)
				t++;

			w = t;
		}


		if (!g[a]){

			u = ask_compute(lc(a), 0);
			t = ask_compute(rc(a), 0);
			if (t == -1 || u == -1)
				t = -1;
			else
				t += u;

			if (w == -1 || t == -1)
				w = MAX(t, w);
			else
				w = MIN(t, w);

		}




	}


	return (ask[v][a] = w);


}


void solve(){
	int i, j;
	ret = 0;
	REP(i, 2)
		REP(j, MAX_M)
			ask[i][j] = -2;

	compute(0);
	ret = ask_compute(0, v);

}

int main(){
	int i, x;
	int j;

	scanf("%d", &x);

	REP(i, x){

		scanf("%d %d", &m, &v);

		REP(j, (m - 1) / 2){
			scanf("%d %d", g + j, c + j);
			iv[j] = -1;
		}

		REP(j, (m + 1) / 2)
			scanf("%d", iv + (m - 1) / 2 + j);

		solve();
		printf("Case #%d: ", i + 1);

		if (ret == -1)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", ret);



	}


	return EXIT_SUCCESS;
}

