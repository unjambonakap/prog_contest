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
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define ll long long
using namespace std;
typedef pair<int,int> pii;

#define MAX_M 10000
#define MAX_Q 30
#define NA 4



double q[MAX_Q][NA];
int used[MAX_Q];
double store[MAX_M];

int m, nq;
int step;

void set_store(int i){
	int j;
	if (i == nq){
		double prod=1;
		REP(j, nq)
			prod*=q[j][used[j]];
		store[step++]=prod;

		return;
	}

	REP(j, NA){
		used[i] = j;
		set_store(i+1);

	}


}


double solve(){

	memset(used, 0, sizeof(used));
	step=0;
	set_store(0);


	sort(store, store+step);
	reverse(store, store+step);

	double sum=0;
	int i;
	if (m >= pow(NA, nq))return 1;

	REP(i, m)
		sum+=store[i];
	
	return sum;

}

int main(){
	int i, j, k;
	int T;

	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d", &m, &nq);
		REP(j, nq){
			REP(k, NA)
				scanf("%lf", &q[j][k]);
			sort(&q[j][0], &q[j+1][0]);
			reverse(&q[j][0], &q[j+1][0]);
		}

		printf("Case #%d: %.7lf\n", i+1, solve());
	}


	return EXIT_SUCCESS;
}

