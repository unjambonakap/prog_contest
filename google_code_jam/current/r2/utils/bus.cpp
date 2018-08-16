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


#define MOD 30031
#define MAX_N 1000
#define MAX_P 10

int n, k, p;

int matrix[two(MAX_P)][two(MAX_P)];
int a[two(MAX_P)][two(MAX_P)], b[two(MAX_P)][two(MAX_P)], c[two(MAX_P)][two(MAX_P)];
int cor[two(MAX_P)], corv[two(MAX_P)];
int nm;


void mul(int x[][two(MAX_P)], int y[][two(MAX_P)], int z[][two(MAX_P)]){
	int i, j, l;
	memset(b, 0, sizeof(b));
	REP(i, nm)
		REP(j, nm)
			REP(l, nm)
				b[i][j]=(b[i][j]+x[i][l]*y[l][j])%MOD;
	memcpy(z, b, sizeof(b));
			

}
void fast_exp(int x[][two(MAX_P)], int o){
	int i, j;
	memset(a, 0, sizeof(a));
	REP(i, nm)
		a[i][i]=1;

	while(o != 0){
		if (o&1)
			mul(a,x,a);
		mul(x,x,x);
		o>>=1;
	}
}


int solve(){
	int i, j, c;
	
	if (k == p)return 1;

	nm=0;
	REP(i, two(p)){
		c=0;
		if (!(i&1))
			continue;

		REP(j, p)
			if (i&two(j))
				c++;
		if (c == k)
			cor[i]=nm, corv[nm++]=i;
	}

	memset(matrix, 0, sizeof(matrix));
	REP(i, nm){
		FOR(j, 1, p+1){
			if (corv[i]&two(j))continue;
			c=((corv[i]-1)|two(j))>>1;
			if (!(c&1))break;
			matrix[i][cor[c]]=1;
		}
	}


	//memcpy(a, matrix, sizeof(matrix));
	//REP(i, n-k-1)
	//	mul(a, matrix);
	fast_exp(matrix, n-k);
	return a[cor[two(k)-1]][cor[two(k)-1]];

}


int main(){
	int i, j, T;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d %d", &n, &k, &p);
		printf("Case #%d: %d\n", i+1, solve());



	}


	return EXIT_SUCCESS;
}

