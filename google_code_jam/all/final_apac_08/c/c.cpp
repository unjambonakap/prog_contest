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
#define SZ(a) (a).size()
#define two(a) (1 << (a))
#define pb push_back
#define ll long long

using namespace std;
typedef pair<int,int> pii;


#define MAX_N 15
#define WIN 1000000
double tb[MAX_N+1][two(MAX_N) + 1];
int m, x;
double p, q;

double solve(){
	int i, j, k;
	int na, nb;


	tb[m][1] = 1, tb[m][0] = 0;
	REPV(i, m){
		REP(j, two(m-i)+1){
			tb[i][j] = 0;
			REP(k, two(m-i)+1){
				na = (j+k) >> 1;
				nb = (j-k) >> 1;

				if (na > two(m-i-1)+1 || nb < 0)
					break;

				tb[i][j] = MAX(tb[i][j], p*tb[i+1][na] + q*tb[i+1][nb]);
			}

		}

	}
	double a, b;
	a = WIN, b = two(m);
	a = a / b;
	b = x;
	a = b / a;
	return tb[0][(int)a];


}

int main(){

	int i, T;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d %lf %d", &m, &p, &x);
		q=1-p;
		printf("Case #%d: %lf\n", i + 1, solve());


	}


	return EXIT_SUCCESS;
}

