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


#define MAX_N 25
#define NE 0
#define NW 1
#define SE 2
#define SW 3
//[
#define TB(p) p.x][p.y][p.d
#define E 0
#define W 1
#define N 2
#define S 3
//]


int map[2*MAX_N][2*MAX_N];
int queued[2*MAX_N][2*MAX_N];
int ts[MAX_N][MAX_N];
int tw[MAX_N][MAX_N];
int tt[MAX_N][MAX_N];
int w, h;

int vx[]={-1, 0, 1, 0};
int vy[]={0, 1, 0, -1};

int get_nt(int x, int y, int nx, int ny, int t){
	int a, b, temp, l;
	a=x/2, b=y/2;
	l=ts[a][b]+tw[a][b];
	if (x != nx){

		if ((x%2 == 0 && nx == x+1) || (x%2 == 1 && nx == x-1)){

			if(tw[a][b] == 0)return -1;
			temp=((t-tt[a][b])%l+l)%l;
			if (temp < ts[a][b])
				t+=ts[a][b]-temp;
			return t+1;
		}




		return t+2;


	}else{
		if ((y%2 == 1 && ny == y-1) || (y%2 == 0 && ny == y+1)){
			if(ts[a][b] == 0)return -1;
			temp=((t-tt[a][b])%l+l)%l;
			if (temp >= ts[a][b])
				t+=tw[a][b]-(temp-ts[a][b]);
			return t+1;
		}
		return t+2;

	}


}
int solve(){
	int t, i, nt, p;
	int x, y, nx, ny;




	qi q;
	memset(map, -1, sizeof(map));
	memset(queued, 0, sizeof(queued));

	x=0, y=h-1;
	q.push(x+y*w);
	map[x][y]=0;


	while(!q.empty()){

		p=q.front(); q.pop();
		x=p%w, y=p/w;

		t=map[x][y], queued[x][y]=0;

		REP(i, 4){
			nx=x+vx[i], ny=y+vy[i];
			if (nx < 0 || ny < 0 || nx >= w || ny >= h)continue;
			nt=get_nt(x, y, nx, ny, t);
			if (nt == -1)continue;

			if (map[nx][ny] == -1 || map[nx][ny] > nt){
				map[nx][ny]=nt;
				if (!queued[nx][ny])
					queued[nx][ny]=1, q.push(nx+ny*w);

			}
	
		}


	}
	return map[w-1][0];


}


int main(){
	int i, j, k, T;
	scanf("%d", &T);

	REP(i, T){
		scanf("%d %d", &h, &w);
			
		REP(j, h)
			REP(k, w)
				scanf("%d %d %d", &ts[k][j], &tw[k][j], &tt[k][j]);
		
		w*=2, h*=2;

		
		printf("Case #%d: %d\n", i+1, solve());



	}


	return EXIT_SUCCESS;
}

