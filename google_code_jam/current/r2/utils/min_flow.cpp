#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

#define MAX_LEN 255
#define rep(i,n) for(i=0;i<n;i++)
#define repj(i,j,n) for(i=j;i<n;i++)
#define swap(a,b) {int c = a; a = b; b = c;}


using namespace std;
using std::stack;


typedef struct edge{
	int u, c, x;//u for the capacity, c the cost and x the current flow
	bool used;

}edge;

int n;
int v[MAX_LEN], n_e[MAX_LEN];
edge graph[MAX_LEN][MAX_LEN];
edge graph_rn[MAX_LEN][MAX_LEN];
int previous[MAX_LEN], visited[MAX_LEN]; 
int r_n[MAX_LEN][MAX_LEN];



int find_augmenting_path(int n, int residual_network[][MAX_LEN], int startN, int endN){
	
	queue<int> s;
	int d, i, j, c;


	memset(previous, -1, sizeof(int) * MAX_LEN);
	memset(visited, 0, sizeof(int) * MAX_LEN);


	s.push(startN);
	while(!s.empty()){


		d = s.front();
		visited[d] = 1;
		s.pop();
		if (d == endN)
			break;
		
		rep(i, n){
			if (!visited[i] && residual_network[d][i] != 0){
				previous[i] = d;
				s.push(i);
			}
		}
	}

	d = endN;
	c = 0;

	while(previous[d] != -1){//never enter this loop if no augmenting path found

		if (c == 0)
			c = residual_network[previous[d]][d];
		else
			c = min(c, residual_network[previous[d]][d]);
		d = previous[d];
	}


	d = endN;
	while(previous[d] != -1){

		residual_network[previous[d]][d] -= c;
		residual_network[d][previous[d]] += c;

		d = previous[d];
	}
	return c;
}

//
//bool cancelling_cycle(int start, int end){
//
//	stack<int> s;
//	int d;
//
//	d = start;
//	while(d != -1){
//
//	}
//	s.push(start);
//
//
//
//	return false;
//}
//
//bool find_cycle(){
//
//	int i, j, a, b;
//	stack<int> s;
//
//	rep(i, n){
//		repj(j, i, n){
//
//			if (graph[i][j].used || graph[j][i].used){
//
//				a = i, b = j;
//				if (graph[j][i].used)
//					swap(a,b);
//
//				graph_rn[a][b].used = graph_rn[b][a].used = 1;
//				graph_rn[a][b].c = graph[a][b].c, graph_rn[b][a].c = -graph[a][b].c;
//				graph_rn[a][b].x = graph[a][b].u - graph[a][b].x;
//				graph_rn[b][a].x = graph[a][b].x;
//			   
//			}else
//				graph_rn[i][j].used = graph_rn[j][i].used = 0;
//
//		}
//	}
////	rep(i, n)
////		rep(j, n)
////			if (graph_rn[i][j].used == 1)
////				printf("%d %d => %d\n", i, j , graph_rn[i][j].x);
////
//
//	int e;
//	for (i = 3; i < n; i++){
//
//		memset(previous, -1, sizeof(int) * MAX_LEN);
//		memset(visited, 0, sizeof(int) * MAX_LEN);
//
//		s.push(i);
//		while(!s.empty()){
//
//			e = s.top();
//			s.pop();
//			if (visited[e])
//				continue;
//
//			visited[e] = 1;
//			printf("for node %d>>>>>>>>>>>>>>>>>>>>>>>>>\n", e);
//
//			rep(j,n){
//				if (!graph_rn[e][j].used || graph_rn[e][j].x == 0 || e == j || previous[j] == e)
//					continue;
//				if (j == i){
//					
//
//					printf("found cycle: %d => %d\n", i, e);
//					int d = e;
//					while(d != i && d != -1){
//						printf("%d =>", d);
//						d = previous[d];
//					}
//					printf("\n");
//
//					if (cancelling_cycle(e, i)){
//
//						return 1;
//					}
//
//
//						
//
//				}else if (!visited[j]){
//					s.push(j);
//					previous[j] = e;
//
//				}
//
//
//
//			}
//
//
//		}
//		exit(0);
//
//	}
//	return false;
//}
//


char find_shortest_path(int **r, int s, int t, int *previous){


}
int find_flow(){
	int i, j;
	int startN, endN;

	startN = n;
	endN = n + 1;

	rep(i,n)
		memset(r_n, 0, sizeof(int) * MAX_LEN);


	rep(i,n){
		if (v[i] < 0)
			r_n[i][endN] = -v[i];
		else if (v[i] > 0)
			r_n[startN][i] = v[i];
	}

	rep(i,n)
		rep(j,n)
			r_n[i][j] = (graph[i][j].used) ? graph[i][j].u : 0;



	int previous[MAX_LEN];
	memset(previous, -1, sizeof(previous));
	while(find_shortest_path(startN, endN, r_n, previous)){

	}



}

int solve(){

	int i, j;
	//we make the assumption that the min flow is feasible
	find_flow();


	rep(i,n)
		rep(j,n){
			if (graph[i][j].used == 1)
				printf("%d %d => %d\n", i, j, graph[i][j].u);

		}

	exit(0);


	return 0;
}

int main(){
	int i, j, k;

	scanf("%d", &n);
	memset(v, -1, sizeof(v));
	memset(n_e, 0, sizeof(n_e));

	rep(i,n){
		scanf("%d %d", v + i, n_e + i);
		rep(j,n)
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
	return EXIT_SUCCESS;
}



