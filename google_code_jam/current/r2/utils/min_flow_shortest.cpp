#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

#define MAX_LEN 255
#define REP(i,n) for(i=0;i<n;i++)
#define FOR(i,j,n) for(i=j;i<n;i++)
#define swap(a,b) {int c = a; a = b; b = c;}
#define PROBLEM(s) {printf("Problem: %s\n", s); exit(EXIT_FAILURE);}


using namespace std;
using std::stack;


typedef struct edge{
	int u, c, x;//u for the capacity, c the cost and x the current flow
	bool used;

}edge;

int n;
int v[MAX_LEN], n_e[MAX_LEN];//v => potential

edge **graph, **graph_rn;
void find_shortest_path(edge **r, int s, int t, int *previous, int n){
	//bellmanFord algo
	int i, j, k;
	int *dist;


	dist = (int*)malloc(sizeof(int) * n);

	memset(dist, -1, sizeof(int) * n);
	memset(previous, -1, sizeof(int) * n);

	dist[s] = 0;
	


	REP(i, n - 1){
		REP(j, n)
			REP(k, n)
				if (r[j][k].used == 1 && r[j][k].x < r[j][k].u && dist[j] != -1 && (dist[j] + r[j][k].c < dist[k] || dist[k] == -1))
					dist[k] = dist[j] + r[j][k].c, previous[k] = j;
				
	}




	REP(j, n)
		REP(k, n)
			if (r[j][k].used == 1 && r[j][k].x < r[j][k].u && dist[j] != -1 && dist[k] != -1 && dist[j] + r[j][k].c < dist[k])
				PROBLEM("Negative cycle detected\n");
				
}
int find_flow(){
	int i, j, l;
	edge *e;
	int startN, endN;
	int previous[MAX_LEN + 2];

	l = n + 2;
	startN = n;
	endN = n + 1;

	memset(previous, -1, sizeof(int) * l);
	REP(i, n){
		if (v[i] > 0){
			e = graph_rn[startN] + i;
		   	e->used = 1, e->c = 0, e->u = v[i];
		}
		
		else if (v[i] < 0){
			e = graph_rn[i] + endN;
		   	e->used = 1, e->c = 0, e->u = -v[i];
		}
	}
	REP(i, n)
		REP(j, n)
			graph_rn[i][j].used = 0;

	REP(i, n)
		REP(j, n){
			if (graph[i][j].used){
				memcpy(graph_rn[i] + j, graph[i] + j, sizeof(edge));
				e = graph_rn[j] + i;
				e->used = 1, e->c = -graph[i][j].c, e->u = graph[i][j].u;
				e->x = e->u;
			}
		}

	REP(i, l)
		REP(j, l)
		if (graph_rn[i][j].used)
			printf("%d %d => %d %d\n", i, j, graph_rn[i][j].c, graph_rn[i][j].u);

	int d, c;
	
	while(1){
		find_shortest_path(graph_rn, startN, endN, previous, l);
		

		d = endN, c = -1;
		if (previous[d] == -1)
			break;

		while(previous[d] != -1){
			if (c == -1 || c > graph_rn[previous[d]][d].u - graph_rn[previous[d]][d].x)
				c = graph_rn[previous[d]][d].u - graph_rn[previous[d]][d].x;
			d = previous[d];
		}
		d = endN;
		while(previous[d] != -1){
			graph_rn[previous[d]][d].x += c;
			graph_rn[d][previous[d]].x -= c;
			d = previous[d];
		}

	}
	
	printf("================\n");
	printf("================\n");
	printf("================\n");
	printf("================\n");
	REP(i,l)
		REP(j,l)
			if (graph_rn[i][j].used == 1)
				printf("%d %d => %d / %d\n", i, j, graph_rn[i][j].x, graph_rn[i][j].u);
	printf("================\n");
	printf("================\n");
	printf("================\n");
	printf("================\n");
	c = 0;
	REP(i, n)
		REP(j, n){
			if (graph[i][j].used)
				c += graph_rn[i][j].x * graph_rn[i][j].c;
		}
	printf("cost: %d\n", c);






}

int solve(){

	int i, j;
	//we make the assumption that the min flow is feasible
	find_flow();


//	REP(i,n)
//		REP(j,n){
//			if (graph[i][j].used == 1)
//				printf("%d %d => %d\n", i, j, graph[i][j].u);
//
//		}

	exit(0);


	return 0;
}

int main(){
	int i, j, k;

	scanf("%d", &n);
	memset(v, -1, sizeof(v));
	memset(n_e, 0, sizeof(n_e));
	graph = (edge**)malloc(sizeof(edge*) * MAX_LEN);
	graph_rn = (edge**)malloc(sizeof(edge*) * (MAX_LEN + 2));

	REP(i, MAX_LEN)
		graph[i] = (edge*)malloc(sizeof(edge) * MAX_LEN);

	REP(i, MAX_LEN + 2)
		graph_rn[i] = (edge*)malloc(sizeof(edge) * (MAX_LEN + 2));

	REP(i,n){
		scanf("%d %d", v + i, n_e + i);
		REP(j,n)
			graph[i][j].used = 0;
	}

	i = j = 0;
	while(1){

		while(i < n && j >= n_e[i])
			j = 0, i ++;

		if (i >= n)
			break;

		scanf("%d", &k);
		k --;
		scanf("%d %d", &graph[i][k].u, &graph[i][k].c);
		graph[i][k].used = 1;
		j ++;
	}

	int ret = solve();

	printf("%d\n", solve());
	free(graph);
	free(graph_rn);
	return EXIT_SUCCESS;
}



