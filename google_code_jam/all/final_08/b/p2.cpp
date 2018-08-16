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


#define MAX_N 1000000

pii vec[2];
pii st;
int w, h;

int get_nv(pii &p, pii v, int step){
	int c;
	int a, b;
	int x, y;
	x=p.first, y=p.second;
	if (x < 0 || y < 0 || x >= w || y >= h){

		a=b=-1;
		REP(a, step){
			x+=v.first, y+=v.second;
			if (!(x < 0 || y < 0 || x >= w || y >= h))
				break;
		}
		if (a == step)
			return 0;
		p.first=x, p.second=y;
	}


	c=0;
	a=b=-1;
	if (v.first < 0)
		a=-x/v.first+1;
	else if (v.first > 0)
		a=(w-1-x)/v.first+1;

	if (v.second < 0)
		b=-y/v.second+1;
	else if (v.second > 0)
		b=(h-1-y)/v.second+1;


	if (a == -1 && b == -1)
		return 0;
	else if (a == -1 || b == -1)
		return MAX(a, b);
	return MIN(a, b);


}


ll solve(){
	int i, j;
	int nx, ny;
	ll c;
	pii sw;

	if (vec[0].first*vec[1].second-vec[0].second*vec[1].first == 0){//colinear vectors
		int map[2*MAX_N];
		memset(map, 0, sizeof(map));

		std::queue<pii> q;
		q.push(st);
		map[st.first+st.second]=1;
		c=0;
		while(!q.empty()){
			sw=q.front();
			q.pop();
			c++;
			REP(j, 2){
				nx=sw.first+vec[j].first, ny=sw.second+vec[j].second;
				if (nx < 0 || ny < 0 || nx >= w || ny >= h)continue;
				if (map[nx+ny])continue;
				map[nx+ny]=1;
				q.push(pii(nx,ny));

			}
		}
		return c;



	}
	c=0;
	sw=st;
	int prev=0;
	while(1){
		prev=get_nv(sw, vec[1], prev-1);
		c+=prev;
		if (prev == 0)
			break;
		sw.first+=vec[0].first, sw.second+=vec[0].second;

	}

	return c;
	






}


int main(){
	int i, j, T;
	scanf("%d", &T);

	REP(i, T){
		scanf("%d %d", &w, &h);
		REP(j, 2)
			scanf("%d %d", &vec[j].first, &vec[j].second);
		scanf("%d %d", &st.first, &st.second);
//		if (i != 58)continue;
//		printf("%d %d\n", w, h);
//		printf("%d %d\n", vec[0].first, vec[1].second);
//		printf("%d %d\n", vec[1].first, vec[1].second);
//		printf("%d %d\n", st.first, st.second);

		printf("Case #%d: %Ld\n", i+1, solve());
	}


	return EXIT_SUCCESS;
}

