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
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i < (b)) && (c); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define FORVC(i, a, b, c) for(i = (b) - 1; (i >= (a)) && (c); i--)
#define FOREACH(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;

#define C '#'
#define E '.'
#define D '?'

#define MAX_N 16
int w, h;
char map[MAX_N][MAX_N];
int mem[MAX_N][MAX_N][two(MAX_N)];

int doit(int i, int j, int s){
	int m, col;

	if (i >= w)
		i=0, j++;
	if (j >= h)
		return 0;
	if (mem[i][j][s] != -1)
		return mem[i][j][s];
	m=-1;

	col=map[i][j];
	if (col == D || col == E){
		m=MAX(m, doit(i+1, j, s&(two(w)-1-two(i))));
		if (col == D)
			col=C;
	}

	if (col == C){
		int v=4;
		if (j > 0 && s&two(i))
			v-=2;
		if (i > 0 && s&two(i-1))
			v-=2;
		v+=doit(i+1, j, s|two(i));

		m=MAX(v,m);
	}

	return mem[i][j][s]=m;




}

int solve(){

	int i, j, k;
	memset(mem, -1, sizeof(mem));
//	REP(i, h){
//		REP(j, w)
//			printf("%c", map[j][i]);
//		printf("\n");
//
//	}
	return doit(0, 0, 0);


}


int main(){
	int i, j, k, T;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d\n", &h, &w);
		REP(j, h){
			REP(k, w)
				scanf("%c", &map[k][j]);
			scanf("\n");
		}

		printf("Case #%d: %d\n", i+1, solve());


	}



	return EXIT_SUCCESS;
}

