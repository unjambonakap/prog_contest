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


#define MAX_R 12
#define MAX_C 9
#define WALL '#'
#define EMPTY '.'
#define MAX_D 1000

int w, h, f;
int map[MAX_R];
int dp[two(MAX_C)][two(MAX_C)][MAX_C][MAX_R];


int play(int x, int y, int sa, int sb, int fa){
	int i, j, m, s, *p, ua, ub;

	if (fa > f)return -2;
	if (y == h-1)return 0;

	p=&dp[sa][sb][x][y];
	if (*p != -1)
		return *p;


	if ((sb&two(x)) == 0)
		return play(x, y+1, sb, map[y+2], fa+1);
	

	

	*p=-2;
	m=MAX_D;

	ua=ub=0;
	if (x < w-1 && (sa&two(x+1)) == 0){
		s=play(x+1, y, sa, sb, 0);

		if (s >= 0)
			m=MIN(m, s), ua=1;;

		if (sb&two(x+1)){

			s=play(x, y, sa, sb-two(x+1), 0);
			if (s >= 0)
				m=MIN(m, s+1);
		}
	}


	if (x > 0 && (sa&two(x-1)) == 0){
		s=play(x-1, y, sa, sb, 0);
		if (s >= 0)
			m=MIN(m, s), ub=1;

		if (sb&two(x-1)){
			s=play(x, y, sa, sb-two(x-1), 0);
			if (s >= 0)
				m=MIN(m, s+1);
		}
	}
	
	if (ua && dp[sa][sb][x+1][y] != -1)
		dp[sa][sb][x+1][y]=MIN(dp[sa][sb][x+1][y], m);
	if (ub && dp[sa][sb][x-1][y] != -1)
		dp[sa][sb][x-1][y]=MIN(dp[sa][sb][x-1][y], m);
	return (*p)=m;

	

}

int solve(){
	int i, j;
	int x, y, v, nv, ny;


	memset(dp, -1, sizeof(dp));


	return play(0, 0, map[0], map[1], 0);
	


}

int main(){
	int i, j, k, T, s;
	char c;
	cin >> T;
	REP(i, T){
		cin >> h >> w >> f;
		scanf("\n");

		REP(j, h){
			
			s=0;
			REP(k, w){
				scanf("%c", &c);
				s|=(c==WALL)?two(k):0;
			}
			map[j]=s;
			scanf("\n");
		}
		printf("Case #%d: ", i+1);
		j=solve();
		if (j == MAX_D)
			printf("No\n");
		else
			printf("Yes %d\n", j);



	}



	return EXIT_SUCCESS;
}

