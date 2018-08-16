#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>

#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PROBLEM(s) {fprintf(stderr, "Error: %s\n", s); exit(EXIT_FAILURE); }
#define pb push_back


#define BUF_LEN 1024


char isAlpha(char c){
	c |= 0x20;//convertit c de uppercase a lowercase (c codé sur 1 octet, le 5ème bit diffère pour uppercase/lowercase, cf table ASCII)
	return c >= 'a' && c <= 'z';
}

char isNum(char c){
	return c >= '0' && c <= '9';
}
char isAlNum(char c){
	return isNum(c) || isAlpha(c) || c == '_';
}




void purge(FILE *f){
	int c;
	while( (c = getc(f) != '\n') && c != EOF && c != 1);//on lit jusqu'à la fin de ligne (flush input buffer)
}

int readString(char *s, int l, FILE *f){
	//fonction pour lire proprement une chaine au clavier
	char *a;

	if ((a = fgets(s, l, f)) == NULL)//copie l'input dans la chaine de caractère s
		return -1;


	while(*a != '\0' && *a != '\n')//on recherche le dernier caractère rentrée: '\0' ou '\n'
		a ++;


	if (*a == '\0')//on a rentré plus de caractère que la chaine peut en contenir => il faut lire les caractères restants pour que les saisies suivantes soient correctes
		purge(f);
	else
		*a = '\0';// équivalent à chomp

	return 0;
}
char *nextWord(char *s){
	int blank = 0;

	//recupere l'addresse du prochaine mot ou NUL/ si c'est le dernier mot


	while(*s != '\0'){//tant qu'on a pas parcouru toute la chaine de caractère

		if (blank == 0 && isAlNum(*s) == 0) blank = 1;//s est à la fin du mot actuel (premier caractère non alphanumérique)
		else if (blank == 1 && isAlNum(*s) == 1) return s;//on attend le prochain caractère alnum qui représente le début du prochain mot
		s++;

	}
	return NULL;

}

#define MAX_N 100
#define MAX_M (MAX_N * (MAX_N + 1))
#define MAX_EDGES 202

int n, n_t;
int m[MAX_M][MAX_M];
int checker_id[MAX_N];
int checker[MAX_N];
int y_d[MAX_M];
int x_d[MAX_M];


typedef struct edge{
	int u, c, x;//u for the capacity, c the cost and x the current flow
	bool used;

}edge;

int v[MAX_EDGES];//v => potential

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
				if (r[j][k].used == 1 && r[j][k].x < r[j][k].u && dist[j] != -1 && (dist[j] + r[j][k].c < dist[k] || dist[k] == -1)){
					dist[k] = dist[j] + r[j][k].c, previous[k] = j;
				}
				
	}




	REP(j, n)
		REP(k, n)
			if (r[j][k].used == 1 && r[j][k].x < r[j][k].u && dist[j] != -1 && dist[k] != -1 && dist[j] + r[j][k].c < dist[k])
				PROBLEM("Negative cycle detected\n");
				
}
int find_flow(int n){
	int i, j, l;
	edge *e;
	int startN, endN;
	int previous[MAX_EDGES + 2];

	l = n + 2;
	startN = n;
	endN = n + 1;

	REP(i, l)
		REP(j, l)
			graph_rn[i][j].used = 0;

	REP(i, n){
		if (v[i] > 0){
			e = graph_rn[startN] + i;
		   	e->used = 1, e->c = 0, e->u = v[i], e->x = 0;
		}
		
		else if (v[i] < 0){
			e = graph_rn[i] + endN;
		   	e->used = 1, e->c = 0, e->u = -v[i], e->x = 0;
		}
	}

	REP(i, n)
		REP(j, n){
			if (graph[i][j].used){
//				printf("%d %d defined\n", i, j);
				memcpy(graph_rn[i] + j, graph[i] + j, sizeof(edge));
				e = graph_rn[j] + i;
				e->used = 1, e->c = -graph[i][j].c, e->u = graph[i][j].u;
				e->x = e->u;
			}
		}

	//REP(i, l)
	//	REP(j, l)
	//	if (graph_rn[i][j].used)
	//		printf("%d %d => %d %d / %d\n", i, j, graph_rn[i][j].c, graph_rn[i][j].x, graph_rn[i][j].u);

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
	
//	printf("================\n");
//	printf("================\n");
//	printf("================\n");
//	printf("================\n");
//	REP(i,l)
//		REP(j,l)
//			if (graph_rn[i][j].used == 1)
//				printf("%d %d => %d / %d\n", i, j, graph_rn[i][j].x, graph_rn[i][j].u);
//	printf("================\n");
//	printf("================\n");
//	printf("================\n");
//	printf("================\n");
	c = 0;
	REP(i, n)
		REP(j, n){
			if (graph[i][j].used)
				c += graph_rn[i][j].x * graph_rn[i][j].c;
		}
//	printf("cost: %d\n", c);
//
	return c;





}

int solve(std::vector<int> diag[]){

	int i, j, k, c, ret;
	edge *e;


	//normal ret: 5 (for sample)
	
	ret = -1;
	REP(i, n)
		v[i] = 1, v[i + n] = -1;
	REP(i, 3){
		REP(j, MAX_EDGES)
			REP(k, MAX_EDGES)
			graph[j][k].used = 0;

		REP(j, n)
			REP(k, diag[i].size()){
				e = graph[j] + n + k;
				e->x = 0, e->used = 1, e->u = 1, e->c = checker[j] * m[checker_id[j]][diag[i][k]];
			}

		c = find_flow(2 * n);
		if (ret == -1 || ret > c)
			ret = c;

	}
	return ret;

}


int main(){
	char buf[BUF_LEN], *a;
	int i, j, k, l, x, t;

	scanf("%d\n", &x);



	memset(v, -1, sizeof(v));
	graph = (edge**)malloc(sizeof(edge*) * MAX_EDGES);
	graph_rn = (edge**)malloc(sizeof(edge*) * (MAX_EDGES + 2));

	REP(i, MAX_EDGES)
		graph[i] = (edge*)malloc(sizeof(edge) * MAX_EDGES);

	REP(i, MAX_EDGES + 2)
		graph_rn[i] = (edge*)malloc(sizeof(edge) * (MAX_EDGES + 2));


	REP(i, x){

		std::vector<int> diag[3];
		if (readString(buf, BUF_LEN, stdin))
			return EXIT_FAILURE;

		a = buf;

		j = 0;
		do{
			checker_id[j++] = strtol(a, NULL, 10) - 1;
			
		}while(a = nextWord(a));

		n = j;



		if (readString(buf, BUF_LEN, stdin))
			return EXIT_FAILURE;

		a = buf;

		j = 0;
		do{
			checker[j++] = strtol(a, NULL, 10);
		}while(a = nextWord(a));


		//if (i != 12  && i != 10)
		//	continue;
		n_t = 0;
		FOR(j, (n + 1) / 2, n + 1){


			if (!(j % 2)){
				REP(k, j)
					x_d[n_t + k] = 2 * (k - j / 2) + 1;
			}else{
				REP(k, j)
					x_d[n_t + k] = 2 * (k - (j - 1) / 2);
			}
			REP(k, j){
				y_d[n_t + k] = j - n;

				if (y_d[n_t + k] == x_d[n_t + k])
					diag[0].pb(n_t + k);
				if (y_d[n_t + k] == -x_d[n_t + k])
					diag[1].pb(n_t + k);
				if (j == n)
					diag[2].pb(n_t + k);
			}


			n_t += j;
		}

		FORV(j ,(n + 1) / 2, n){


			if (!(j % 2)){
				REP(k, j)
					x_d[n_t + k] = 2 * (k - j / 2) + 1;
			}else{
				REP(k, j)
					x_d[n_t + k] = 2 * (k - (j - 1) / 2);
			}
			REP(k, j){
				y_d[n_t + k] = n - j;

				if (y_d[n_t + k] == x_d[n_t + k])
					diag[0].pb(n_t + k);
				if (y_d[n_t + k] == -x_d[n_t + k])
					diag[1].pb(n_t + k);
			}
			n_t += j;
		}
		//REP(j, n_t)
		//	printf("(%d %d)\n", x_d[j], y_d[j]);


		REP(j, n_t){
			m[j][j] = 0;
			FOR(k, j + 1, n_t){
				t = abs(x_d[j] - x_d[k]) - abs(y_d[j] - y_d[k]);
				if (t <= 0)
					m[j][k] = m[k][j] = abs(y_d[j] - y_d[k]);



				if (t > 0)
					m[j][k] = m[k][j] = abs(y_d[j] - y_d[k]) + t / 2;

			}
		}


		//REP(j, 3)
		//	REP(k, diag[j].size())
		//	printf("(%d %d) => %d\n", x_d[diag[j][k]], y_d[diag[j][k]], diag[j][k]);
		//printf("checkers:\n");
		//REP(j, n_t)
		//	printf("%d %d => %d\n", 1, j, m[1][j]);



		printf("Case #%d: %d\n", i + 1, solve(diag));







	}



	return EXIT_SUCCESS;
}

