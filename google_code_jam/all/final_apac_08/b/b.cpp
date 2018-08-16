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
#define pb push_back
#define ll long long

using namespace std;
typedef pair<int,int> pii;



#define INF 200
#define MAX_C 55
#define inside(x,y) ((x) >= 0 && (x) < c && (y) >= 0 && (y) < r)


int vx[] = {0, -1, 1, 0};
int vy[] = {-1, 0, 0, 1};

int r, c, xo, yo;


int get_s(int m[][MAX_C]){
	int i, j, k, nx, ny;
	int xm, ym;
	int nm[MAX_C][MAX_C];



	memcpy(nm, m, sizeof(nm));

	REP(i, r){
		REP(j, c){
			if (j == xo && i == yo)
				continue;
			if (m[j][i] == 0)
				continue;

			xm = ym = -1;
			REP(k, 4){
				nx = j + vx[k], ny = i + vy[k];
				if (inside(nx, ny)){
					if (xm == -1 || m[nx][ny] > m[xm][ym])
						xm = nx, ym = ny;
				}

			}
			nm[xm][ym] = MAX(0, nm[xm][ym] - m[j][i]);
		}
	}

	if (nm[xo][yo] == 0)
		return 0;
	
	//REP(i, r){
	//	REP(j, c)
	//		printf("%d ", m[j][i]);
	//	printf("\n");
	//}
	//REP(i, r){
	//	REP(j, c)
	//		printf("%d ", nm[j][i]);
	//	printf("\n");
	//}

	int s = -1;
	REP(k, 4){
		nx = xo + vx[k], ny = yo + vy[k];
		if (inside(nx, ny) && nm[nx][ny] > 0){
			int att = MIN(m[xo][yo], nm[nx][ny]);
			nm[nx][ny] -= att;
			s = MAX(s, get_s(nm));

			nm[nx][ny] += att;
			if (s == INF)
				return INF;
		}

	}
	if (s == -1)
		return INF;
	s = MAX(s, get_s(nm));
	if (s == INF)
		return INF;

	return s + 1;












}
void solve(int map[][MAX_C]){

	int surv;

	surv = get_s(map);
	if (surv == INF)
		printf("forever\n");
	else
		printf("%d day(s)\n", surv);

}

int main(){
	int i, j, k;
	int x, a;
	int map[MAX_C][MAX_C];

	scanf("%d", &x);
	REP(i, x){
		scanf("%d %d %d %d", &c, &r, &xo, &yo);
		xo--, yo--;
		REP(j, r)
			REP(k, c){
				scanf("%d", &a);
				map[k][j] = a;
			}



		//if (i!=1)continue;
		//printf("START MAP==========\n");
		//REP(j, r){
		//	REP(k, c)
		//		printf("%d ", map[k][j]);
		//	printf("\n");
		//}
		//printf("================================///////////:\n");

		//printf("play at %d %d\n", xo, yo);
		printf("Case #%d: ", i + 1);
		solve(map);





	}


	return EXIT_SUCCESS;
}

