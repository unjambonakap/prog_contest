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
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define ll long long
using namespace std;
typedef pair<int,int> pii;

#define MAX_M 10000
#define MAX_Q 30
#define NA 4




double q[MAX_Q][NA];

int m, nq;



double solve(){
	ll i, j, k;
	double d, e;
	double sum = 0;
	if (m >= pow(NA, nq))return 1.;

	priority_queue<double,vector<double>, greater<double> > qa, pa;
	priority_queue<double,vector<double>, greater<double> > *a, *b, *c;

	a = &qa, b = &pa;
	a->push(1);


	REP(i, nq){
		while(!a->empty()){
			d=a->top();a->pop();
			REP(j, NA){
				e=d*q[i][j];

				if (b->size() < m)
					b->push(e);
				else if (e > b->top()){

					b->pop();
					b->push(e);
				}

			}

		}
		SWAP(a,b,c);
	}
	

	while(!a->empty()){
		sum+=a->top();
		a->pop();
	}




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

