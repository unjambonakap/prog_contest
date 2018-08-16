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

#define MAX_N 55

int w, h;
int map[MAX_N][MAX_N];

int vx[]={0,1,1,1,0,-1,-1,-1,0};
int vy[]={0,1,0,-1,-1,-1,0,1,1};


int getl(int y){
	int nx, ny;
	int c, i;

	if (w%3 != 0)
		i=0;
	else 
		i=1;

	c=0;
	
	for(i; i < w; i+=3)
		c+=map[i][y];
	

	return c;
}

int solve(){
	int i, c;

	if (h%3 == 0){
		c=0;
		for(i=0; i < (h-1)/2;i+=3)
			c+=getl(i);
		for(i=h-1; i > (h-1)/2; i-=3)
			c+=getl(i);
		for(i=1; i < h; i+=3)
			c-=getl(i);

		assert(c <= w);


		return c;
	}
	
	c=0;
	if (h%3 == 2)
		for(i=1; i <= (h-1)/2; i+=3)
			c+=getl(i)-getl(i-1);
	else{
		for(i=1; i < (h-1)/2;i+=3)
			c-=getl(i);
		for(i=h-2; i > (h-1)/2; i-=3)
			c-=getl(i);
		for(i=0; i < h; i+=3)
			c+=getl(i);
		assert(c >= 0 && c <= w);

	}

	return c;




}

int main(){
	int i, j, k, T;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d", &h, &w);
		REP(j, h)
			REP(k, w)
				scanf("%d", &map[k][j]);

		printf("Case #%d: %d\n", i+1, solve());



	}


	return EXIT_SUCCESS;
}

