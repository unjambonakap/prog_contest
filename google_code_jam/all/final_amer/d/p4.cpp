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

#define MAX_C 15
#define E '.'
#define N '#'
#include "../../algo/matching.hpp"
int r, c;
int vx[] = {1, 1, 1, 0, -1, -1, -1, 0};
int vy[] = {1, 0, -1, -1, -1, 0, 1, 1};
int startx, starty;
char map[MAX_C][MAX_C];

int solve(){
	int i, j, k, len, len2;
	int nx, ny;

	vector<pii> edges;
	REP(i, c)
		REP(j, r){
			if (map[i][j] == N)continue;

			if (i == startx && j == starty)continue;
			REP(k, 4){
				nx=i+vx[k], ny=j+vy[k];
				if (nx < 0 || ny < 0 || nx >= c || ny >= r)continue;
				if (nx == startx && ny == starty) continue;
				if (map[nx][ny] == E)
					edges.pb(pii(i*MAX_C+j,nx*MAX_C+ny));

				
			}
		}


	len = SZ(get_matching(edges, MAX_C*MAX_C));

	REP(k, 8){
		nx=startx+vx[k], ny=starty+vy[k];
		if (nx < 0 || ny < 0 || nx >= c || ny >= r)continue;
		if (map[nx][ny] == E)
			edges.pb(pii(startx*MAX_C+starty,nx*MAX_C+ny));
	}
	len2 = SZ(get_matching(edges, MAX_C*MAX_C));
	if (len == len2)
		return 1;
	return 0;




}


int main(){
	int i, j, k, T;


	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d\n", &r, &c);
		REP(j, r){
			REP(k, c){
				scanf("%c", &map[k][j]);
				if (map[k][j] == 'K')
					startx=k, starty=j, map[k][j]=E;
			}
			getchar();
		}
		
		
		//if (i!=97)continue;
		//REP(j, r){
		//	REP(k, c)
		//	printf("%c", map[k][j]);
		//	printf("\n");
		//}
		//printf("%d %d\n", startx, starty);

		printf("Case #%d: ", i+1);
		if (solve() == 0)
			printf("A\n");
		else
			printf("B\n");


	}


	return EXIT_SUCCESS;
}

