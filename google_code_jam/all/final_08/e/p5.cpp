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
typedef vector<vector<int> > vvi;
typedef queue<int> qi;

#define C '#'
#define E '.'
#define D '?'
#define MAX_N 52
#define MAX_E MAX_N*MAX_N

int w, h, n;
char map[MAX_N][MAX_N];


int visited[MAX_E+2], parent[MAX_E+2];
int cf[MAX_E+2][MAX_E+2], c[MAX_E+2][MAX_E+2], f[MAX_E+2][MAX_E+2];
vvi edge;

int vx[]={-1, 0, 1, 0};
int vy[]={0, 1, 0, -1};

int inside(int x, int y){return (x>=0 && x<w && y>=0 && y<h);}
int rinside(int x, int y){return (x>=1 && x<w-1 && y>=1 && y<h-1);}

int bfs(int s, int t){
	int i, a;
	qi q;

	memset(parent, -1, sizeof(parent));
   	memset(visited, 0, sizeof(visited));

	q.push(s);
	visited[s]=1;

	while(!q.empty()){
		a=q.front();
		q.pop();
		if (a == t)
			return 1;

		FE(it, edge[a]){
			if (visited[*it] || cf[a][*it] <= 0)continue;
			visited[*it]=1, parent[*it]=a;
			q.push(*it);



		}


	}
	return 0;


}
int solve(){
	int i, j, k;
	int s, t;

	n=w*h;
	s=n, t=n+1;


	memset(cf, 0, sizeof(cf));
	memset(c, 0, sizeof(c));
	memset(f, 0, sizeof(f));

	int nx, ny, id, sid;
	int TE=0;

	REP(i, MAX_E)
		edge[i].clear();

	REP(i, w)
		REP(j, h){
			sid=i+j*w;
			REP(k, 4){
				nx=i+vx[k], ny=j+vy[k], id=nx+ny*w;
				if (rinside(nx, ny) && c[sid][id] == 0)
					cf[id][sid]=cf[sid][id]=c[id][sid]=c[sid][id]=1, TE++, edge[sid].pb(id), edge[id].pb(sid);
				

			}
			if (map[i][j] == E)
				cf[s][sid]=c[s][sid]=MAX_E, edge[s].pb(sid);
			if (map[i][j] == C)
				cf[sid][t]=c[sid][t]=MAX_E, edge[sid].pb(t);
			
		}


	int a, flow, nf;
	flow=0;

	while(bfs(s, t) == 1){
		a=t, flow++;

	//	printf("=============np================\n");
		while(parent[a]!=-1){
	//		printf("find (%d %d) to (%d %d)\n", parent[a]%w, parent[a]/w, a%w, a/w);
			f[parent[a]][a]++, cf[parent[a]][a]--;
			f[a][parent[a]]--, cf[a][parent[a]]++;
		//	printf("%d %d ,,,,,,,,,,,, %d %d\n", f[parent[a]][a], cf[parent[a]][a], f[a][parent[a]], cf[a][parent[a]]);

			a=parent[a];
		}
		//REP(i, w*h)
		//	REP(j, w*h)
		//		printf("cap %d %d => %d %d: %d\n", i%w, i/w, j%w, j/w, cf[i][j]);
		//REP(i, w*h)
		//	printf("s => %d %d: %d\nt=>%d  %d: %d\n", i%w, i/w, cf[s][i], i%w, i/w, cf[i][t]);
		
		assert(a == s);


	}
			
//	printf("flow: %d\n", flow);

	return TE-flow;






}


int main(){
	int i, j, k, T;
	scanf("%d", &T);
	REP(i, MAX_E)
		edge.pb(vi());

	REP(i, T){
		scanf("%d %d\n", &h, &w);
		REP(j, h){
			REP(k, w){
				scanf("%c", &map[k+1][j+1]);
			}
			scanf("\n");
		}

		//REP(j, h){
		//	REP(k, w){
		//		printf("%c", map[k+1][j+1]);
		//	}printf("\n");
		//}

		REP(j, h+2)
			map[0][j]=map[w+1][j]=E;
		REP(j, w+2)
			map[j][0]=map[j][h+1]=E;

		w+=2, h+=2;
		REP(j, h){
			REP(k, w){
				if ((j+k)%2==0 && map[k][j] != D)
					map[k][j] ^= C^E;
//				printf("%c", map[k][j]);
			}
				
			
//			printf("\n");
		}
		
		printf("Case #%d: %d\n", i+1, solve());


	}



	return EXIT_SUCCESS;
}

