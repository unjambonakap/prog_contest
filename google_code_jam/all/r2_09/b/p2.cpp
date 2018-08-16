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
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)

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
typedef vector<int> vi;
typedef queue<int> qi;


#define MAX_R 55
#define MAX_C 55
#define WALL '#'
#define EMPTY '.'

int w, h, f;
char map[MAX_R][MAX_C];
int dp[MAX_C][MAX_R][MAX_C][MAX_C];


int play(int x, int y, int sa, int sb, int fa){

	int ea, eb, lhole, rhole;
	int *p=&dp[x][y][sa][sb];
	int s, m;

	if (fa > f)return -2;
	if (y == h-1) return 0;

	if (*p != -1)return *p;

	if (map[x][y+1] == EMPTY)
		return play(x, y+1, x, x, fa+1);

	ea=eb=x;
	lhole=rhole=0;
	while(ea >=  1){
		ea--;
		if (map[ea][y] == WALL && ea < sa){ea++; break;}
		if (map[ea][y+1] == EMPTY){ea++, lhole=1; break;}
	}
	while(eb <  w-1){
		eb++;
		if (map[eb][y] == WALL && eb > sb){eb--; break;}
		if (map[eb][y+1] == EMPTY){eb--, rhole=1; break;}
	}

	m=-2;
	if (lhole == 1){
		s=play(ea-1, y+1, ea-1, ea-1, 1);
		if (s >= 0 && (m == -2 || s < m))
			m=s;
	}

	if (rhole == 1){
		s=play(eb+1, y+1, eb+1, eb+1, 1);
		if (s >= 0 && (m == -2 || s < m))
			m=s;
	}

	int i, j;

	s=-1;
	if (ea != eb){

		FOR(i, ea, eb){
			FOR(j, i, eb){
				if (i == ea && j == eb)continue;
				if (j != eb){
					s=play(j, y+1, i, j, 1);
					//printf("%d %d ==> %d %d\n", i, j, j, s);
					if (s >= 0 && (m == -2 || s+j-i < m))
						m=s+j-i+1;
				}if (i != ea){
					s=play(i, y+1, i, j, 1);
					//printf("%d %d ==> %d %d\n", i, j, i, s);
					if (s >= 0 && (m == -2 || s+j-i < m))
						m=s+j-i+1;
				}
			}


		}
	}

	return ((*p)=m);
}

int solve(){
	int i, j;
	int x, y, v, nv, ny;


	memset(dp, -1, sizeof(dp));


	return play(0, 0, 0, 0, 0);



}

int main(){
	int i, j, k, T;
	cin >> T;
	REP(i, T){
		cin >> h >> w >> f;
		scanf("\n");

		REP(j, h){
			REP(k, w)
				scanf("%c", &map[k][j]);

			scanf("\n");
		}
		printf("Case #%d: ", i+1);
		j=solve();
		if (j < 0)
			printf("No\n");
		else
			printf("Yes %d\n", j);



	}



	return EXIT_SUCCESS;
}

