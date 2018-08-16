#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define PI asin(1)*2.
#define EPS 10e-8


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

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;


#define MAX_N 5000
#define TOT 10000

int v[TOT+1][TOT], h[TOT+1][TOT];
int n;
int a[TOT], b[TOT], c[TOT];

int solve(){
	int i, j, k;
	int m;

	memset(v, 0, sizeof(v));
	memset(h, 0, sizeof(h));
	REP(i, TOT+1)
		REP(j, n)
			if (c[j] <= i && a[j]+b[j] <=TOT-i)
				v[i][a[j]]++, h[i][b[j]]++;
			

	int s;

	m=-1;
	REP(i, TOT+1){
		s=v[i][0];
		FOR(j, 1, TOT-i+1){
			s=s+v[i][j]-h[i][TOT-i-j+1];
			m=MAX(m,s);
		}

		


	}



	
	return m;



}


int main(){
	int i, j, k;
	int T;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d", &n);
		REP(j, n)
			scanf("%d %d %d", a+j, b+j, c+j);

		printf("Case #%d: %d\n", i+1, solve());


	}

	return EXIT_SUCCESS;
}

