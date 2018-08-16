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


#define MAX_N 10
#define TOT 10000

int a[MAX_N][3]; 
int n;

int solve(){
	int i, j, k, c, m;

	m=-1;
	REP(i, TOT+1)
		REP(j, TOT-i+1){
			c=0;
			REP(k, n){
				if (a[k][0]<=i && a[k][1]<=j && a[k][2]<=TOT-i-j)
					c++;
			}
			m=MAX(c,m);

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
			scanf("%d %d %d", &a[j][0], &a[j][1], &a[j][2]);
		

		printf("Case #%d: %d\n", i+1, solve());


	}

				


	return EXIT_SUCCESS;
}

