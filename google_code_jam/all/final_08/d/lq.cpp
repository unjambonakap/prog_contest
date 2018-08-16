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

#define MAX_N 30
#define FOREST 'T'
#define WATER '.'
#define ISL '#'


char map[MAX_N][MAX_N];


int w, h;
int edge[MAX_N*MAX_N][MAX_N*MAX_N];
int parent[MAX_N*MAX_N];
int visited[MAX_N*MAX_N], revisited[MAX_N*MAX_N], nvisited[MAX_N*MAX_N];
int root[MAX_N*MAX_N];
std::vector<pii> v;


int vx[]={-1, 0, 1, 0};
int vy[]={0, 1, 0, -1};

int inside(int x, int y){return (x>=0 && y>=0 && x<w && y<h);}
class data{
	public:
		data(){}
		data(int _x, int _y, int _c, int _cumul=0){x=_x, y=_y, c=_c, cumul=_cumul;}
		bool operator<(const data &d)const {return (cumul > d.cumul);}
		int x, y, c, cumul;

};


int bfs(){
	int i, j, k, c, id, sid, nx, ny;
	data d;

	std::queue<data> q;
	memset(revisited, 0, sizeof(revisited));

	FOREACH(it, v){
		q.push(data(it->first, it->second, 1));
		revisited[it->first+it->second*w]=1;
	}



	c=0;
	//REP(i, h){
	//	REP(j, w)
	//		printf("%d", revisited[j+i*w]);
	//	printf("\n");

	//}
	while(!q.empty()){
		d=q.front();
		q.pop();

		sid=d.x+d.y*w;
		REP(i, 4){
			nx=d.x+vx[i], ny=d.y+vy[i];
			id=nx+ny*w;

			if (!inside(nx, ny) || map[nx][ny] == WATER || revisited[id])continue;

			revisited[id]=1;
			q.push(data(nx, ny, d.c+1));
			if (!visited[id])
				c+=d.c;
			
		}


	}
	return c;


}

int bfs2(){
	int i, j, k, l;
	int nx, ny;
	int id, sid;
	int c, xa, ya;
	data d;
	std::queue<data> q;

	memset(edge, 0, sizeof(edge));
	memset(visited, 0, sizeof(nvisited));
	memset(root, 0, sizeof(root));

	visited[0]=1;
	c=0;
	FOR(l, 1, SZ(v)){

		memset(nvisited, 0, sizeof(nvisited));
		memset(parent, -1, sizeof(parent));
		REP(j, SZ(v)){

			sid=v[j].first+v[j].second*w;
			if (visited[sid]){
				q.push(data(v[j].first, v[j].second, 1, 0));
				root[sid]=nvisited[sid]=1;
			}
		}
		while(!q.empty()){
			d=q.front();
			q.pop();



			REP(j, SZ(v)){
				xa=v[j].first, ya=v[j].second;
				sid=xa+ya*w;


				if (d.x == xa && d.y == ya){
					if (visited[sid])continue;
					k=sid;

					while(parent[k] != -1){

						visited[k]=1;
						edge[parent[k]][k]=edge[k][parent[k]]=1;
						k=parent[k];
					}
					visited[k]=1;

					c+=d.cumul;
					q=std::queue<data>();
					break;
				}
			}
			if (j != SZ(v))
				continue;


			sid=d.x+d.y*w;

			REP(i, 4){
				nx=d.x+vx[i], ny=d.y+vy[i], id=nx+ny*w;


				if (!inside(nx, ny) || nvisited[id] || map[nx][ny] == WATER)continue;
				if (root[id])continue;
				parent[id]=sid, nvisited[id]=1;

				if (visited[id])
					q.push(data(nx, ny, d.c+1, d.cumul));
				else
					q.push(data(nx, ny, d.c+1, d.cumul+d.c));
			}

		}
	}
	return c+bfs();
}


int solve(){
	int i, j, k;

	v.clear();
	REP(i, h)
		REP(j, w)
			if (map[j][i] == FOREST)
				v.pb(pii(j, i));

	return bfs2();


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
				//printf("%d %d\n", w, h);
				//REP(j, h){
				//	REP(k, w)
				//	printf("%c", map[k][j]);
				//	printf("\n");
				//}

		printf("Case #%d: %d\n", i+1, solve());
	}



	return EXIT_SUCCESS;
}

