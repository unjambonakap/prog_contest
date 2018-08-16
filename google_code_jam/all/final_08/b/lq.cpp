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


#define MAX_W 101
int w, h;
int map[MAX_W][MAX_W];
pii st, v[2];


int solve(){
	std::queue<pii> q;
	pii t;
	int nx, ny, j;
	int c;

	if (st.first >= w || st.second >= h || st.first < 0 || st.second < 0)
		return 0;
	memset(map, 0, sizeof(map));
	q.push(st);
	map[st.first][st.second]=1;
	c=1;
	while(!q.empty()){
		t=q.front();
		q.pop();
		REP(j, 2){
			nx=t.first+v[j].first, ny=t.second+v[j].second;
			if (nx < 0 || ny < 0 || nx >= w || ny >= h)continue;
			if (map[nx][ny])continue;

			c++, map[nx][ny]=1;
			q.push(pii(nx,ny));
		}
	}
	return c;


}


int main(){
	int i, j, T;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d", &w, &h);
		REP(j, 2)
			scanf("%d %d", &v[j].first, &v[j].second);
		scanf("%d %d", &st.first, &st.second);
		printf("Case #%d: %d\n", i+1, solve());



	}


	return EXIT_SUCCESS;
}

